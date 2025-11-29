/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-03-11     Wangyuqiang   first version
 */

#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>
#include <board.h>
#include "mb.h"
#include "mb_m.h"
#include "ecat_def.h"
#include "objdef.h"

#define DBG_TAG "ECAT2MB"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define PORT_NUM        5
#define PORT_BAUDRATE   115200
#define PORT_PARITY     MB_PAR_NONE

#define MB_POLL_THREAD_PRIORITY  10
#define MB_SEND_THREAD_PRIORITY  RT_THREAD_PRIORITY_MAX - 1

#define MB_POLL_CYCLE_MS   10

#define MAX_E2M_OBJECTS  64
#define MB_QUEUE_SIZE    32

typedef struct
{
    UINT16 coe_index;
    UINT8  dev_addr;      // Modbus 从站地址 (1~247)
    UINT16 reg_addr;      // Holding Register 地址
    const char* name;
} e2m_mdata_t;

typedef struct {
    UINT8  slave_addr;
    UINT16 reg_addr;
    UINT16 value;
} mb_write_req_t;

typedef enum {
    MB_OP_WRITE = 0,
    MB_OP_READ  = 1
} mb_op_t;

typedef struct {
    mb_op_t op;
    UINT8   slave_addr;
    UINT16  reg_addr;
    UINT16  value;        // 写时使用
    UINT16  index_in_list; // 对应 mdata_list 的下标，用于读结果回填
} mb_task_t;

#include "ecat_slave_data.h"

extern uint16_t usMRegHoldBuf[16][RT_M_REG_HOLDING_NREGS];

// 动态对象字典
TOBJECT* e2m_objdic = NULL;
TSDOINFOENTRYDESC e2m_entry_desc = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

static rt_mq_t mb_task_mq = RT_NULL;

void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");

    while (1)
    {
        rt_thread_mdelay(1000);
    }
}

UINT8 e2m_sdo_read(UINT16 Index, UINT8 Subindex, UINT32 Size, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    // rt_kprintf("read %04X-%04X size %d\n", Index, Subindex, Size);
    for (int i = 0; i < mdata_count; i++) {
        if (mdata_list[i].coe_index == Index) {
            UINT8  slave = mdata_list[i].dev_addr;
            UINT16 reg   = mdata_list[i].reg_addr;

            // 立即返回当前缓存值（保证 CoE 响应快）
            *pData = usMRegHoldBuf[slave - 1][reg];

            // 投递异步读请求（后台刷新缓存）
            if (mb_task_mq) {
                mb_task_t task = {
                    .op            = MB_OP_READ,
                    .slave_addr    = slave,
                    .reg_addr      = reg,
                    .index_in_list = i
                };
                rt_mq_send(mb_task_mq, &task, sizeof(task));
            }
            return 0;
        }
    }
    return 1;
}

UINT8 e2m_sdo_write(UINT16 Index, UINT8 Subindex, UINT32 Size, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    // rt_kprintf("write %04X-%04X size %d\n", Index, Subindex, Size);
    for (int i = 0; i < mdata_count; i++) {
        if (mdata_list[i].coe_index == Index) {
            UINT8  slave = mdata_list[i].dev_addr;
            UINT16 reg   = mdata_list[i].reg_addr;
            UINT16 value = (UINT16)*pData;

            // usMRegHoldBuf[slave - 1][reg] = value;

            // 投递写任务
            if (mb_task_mq) {
                mb_task_t task = {
                    .op         = MB_OP_WRITE,
                    .slave_addr = slave,
                    .reg_addr   = reg,
                    .value      = value
                };
                rt_mq_send(mb_task_mq, &task, sizeof(task));
            }
            return 0;
        }
    }
    return 1;
}

static void send_thread_entry(void *parameter)
{
    mb_task_t task;
    eMBMasterReqErrCode err;
    eMBMasterReqErrCode error_code = MB_MRE_NO_ERR;

    rt_thread_delay(2000);

    if (mdata_count == 0 || mdata_count > MAX_E2M_OBJECTS) {
        return 1;
    }

    e2m_objdic = (TOBJECT*)rt_malloc((mdata_count + 1) * sizeof(TOBJECT));
    if (!e2m_objdic) {
        return 1;
    }

    for (int i = 0; i < mdata_count; i++) {
        e2m_objdic[i].pPrev   = NULL;
        e2m_objdic[i].pNext   = NULL;
        e2m_objdic[i].Index   = mdata_list[i].coe_index;
        e2m_objdic[i].ObjDesc = (TSDOINFOOBJDESC){DEFTYPE_UNSIGNED8, 0 | (OBJCODE_VAR << 8)};
        e2m_objdic[i].pEntryDesc   = &e2m_entry_desc;
        e2m_objdic[i].pName    = (UCHAR*)mdata_list[i].name;
        // e2m_objdic[i].pVarPtr  = &usMRegHoldBuf[mdata_list[i].dev_addr][mdata_list[i].reg_addr];
        e2m_objdic[i].Read    = e2m_sdo_read;
        e2m_objdic[i].Write   = e2m_sdo_write;
        e2m_objdic[i].NonVolatileOffset   = 0x000;

        rt_kprintf("name: %s index: %04X \n", e2m_objdic[i].pName, e2m_objdic[i].Index);
    }

    // 结束项
    e2m_objdic[mdata_count] = (TOBJECT){
        .Index = 0xFFFF, .pVarPtr = NULL
    };
    extern UINT16 AddObjectsToObjDictionary(TOBJECT OBJMEM * pObjEntry);
    AddObjectsToObjDictionary(e2m_objdic);

    while (1)
    {
#if defined(RT_VERSION_CHECK) && (RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 0, 1))
        if (rt_mq_recv(mb_task_mq, &task, sizeof(task), RT_WAITING_FOREVER) > 0)
#else
        if (rt_mq_recv(mb_task_mq, &task, sizeof(task), RT_WAITING_FOREVER) == RT_EOK)
#endif
        {
            if (task.op == MB_OP_WRITE)
            {
                err = eMBMasterReqWriteHoldingRegister(
                        task.slave_addr,
                        task.reg_addr,
                        task.value,
                        RT_WAITING_FOREVER
                      );
                if (err != MB_MRE_NO_ERR) {
                    // rt_kprintf("MB Write Fail: %d-%d=%d, err=%d\n",
                    //            task.slave_addr, task.reg_addr, task.value, err);
                }
            }
            else if (task.op == MB_OP_READ)
            {
                err = eMBMasterReqReadHoldingRegister(
                        task.slave_addr,
                        task.reg_addr,
                        1,
                        RT_WAITING_FOREVER
                      );
                if (err != MB_MRE_NO_ERR) {
                    // rt_kprintf("MB Read Fail: %d-%d, err=%d\n",
                    //            task.slave_addr, task.reg_addr, err);
                }
            }
        }
    }
}

static void mb_master_poll(void *parameter)
{
    eMBMasterInit(MB_RTU, PORT_NUM, PORT_BAUDRATE, PORT_PARITY);
    eMBMasterEnable();

    while (1)
    {
        eMBMasterPoll();
        rt_thread_mdelay(MB_POLL_CYCLE_MS);
    }
}

static int mb_master_app(void)
{
    // 创建统一任务队列
    mb_task_mq = rt_mq_create("mb_task", sizeof(mb_task_t), MB_QUEUE_SIZE, RT_IPC_FLAG_FIFO);

    // 启动 Modbus Master 轮询线程
    rt_thread_t poll_tid = rt_thread_create("mb_poll", mb_master_poll, RT_NULL, 1024, MB_POLL_THREAD_PRIORITY, 10);
    if (poll_tid) rt_thread_startup(poll_tid);

    // 启动 Modbus Master 读写请求处理线程
    rt_thread_t send_tid = rt_thread_create("mb_send", send_thread_entry, RT_NULL, 1024, MB_SEND_THREAD_PRIORITY - 2, 10);
    if (send_tid) rt_thread_startup(send_tid);

    return RT_EOK;
}

INIT_APP_EXPORT(mb_master_app);

