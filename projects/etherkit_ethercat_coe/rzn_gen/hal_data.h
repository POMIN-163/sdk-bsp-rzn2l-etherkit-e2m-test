/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_sci_uart.h"
            #include "r_uart_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_canfd.h"
#include "r_can_api.h"
FSP_HEADER
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart5;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart5_ctrl;
            extern const uart_cfg_t g_uart5_cfg;
            extern const sci_uart_extended_cfg_t g_uart5_cfg_extend;

            #ifndef user_uart5_callback
            void user_uart5_callback(uart_callback_args_t * p_args);
            #endif

            #define FSP_NOT_DEFINED (1)
            #if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
                #define g_uart5_P_TRANSFER_TX (NULL)
            #else
                #define g_uart5_P_TRANSFER_TX (&FSP_NOT_DEFINED)
            #endif
            #if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
                #define g_uart5_P_TRANSFER_RX (NULL)
            #else
                #define g_uart5_P_TRANSFER_RX (&FSP_NOT_DEFINED)
            #endif
            #undef FSP_NOT_DEFINED
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer1_ctrl;
extern const timer_cfg_t g_timer1_cfg;

#ifndef timer1_callback
void timer1_callback(timer_callback_args_t * p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT01_1_INT0_DISABLE
  #define TIMER_GPT01_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT01_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_1_INT1_DISABLE
  #define TIMER_GPT01_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT01_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_1_INT2_DISABLE
  #define TIMER_GPT01_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT01_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_1_INT3_DISABLE
  #define TIMER_GPT01_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT01_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** CANFD on CANFD Instance. */
extern const can_instance_t g_canfd1;
/** Access the CANFD instance using these structures when calling API functions directly (::p_api is not used). */
extern canfd_instance_ctrl_t g_canfd1_ctrl;
extern const can_cfg_t g_canfd1_cfg;
extern const canfd_extended_cfg_t g_canfd1_cfg_extend;

#ifndef canfd1_callback
void canfd1_callback(can_callback_args_t * p_args);
#endif

/* Global configuration (referenced by all instances) */
extern canfd_global_cfg_t g_canfd_global_cfg;
/** CANFD on CANFD Instance. */
extern const can_instance_t g_canfd0;
/** Access the CANFD instance using these structures when calling API functions directly (::p_api is not used). */
extern canfd_instance_ctrl_t g_canfd0_ctrl;
extern const can_cfg_t g_canfd0_cfg;
extern const canfd_extended_cfg_t g_canfd0_cfg_extend;

#ifndef canfd0_callback
void canfd0_callback(can_callback_args_t * p_args);
#endif

/* Global configuration (referenced by all instances) */
extern canfd_global_cfg_t g_canfd_global_cfg;
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart0;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart0_ctrl;
            extern const uart_cfg_t g_uart0_cfg;
            extern const sci_uart_extended_cfg_t g_uart0_cfg_extend;

            #ifndef user_uart0_callback
            void user_uart0_callback(uart_callback_args_t * p_args);
            #endif

            #define FSP_NOT_DEFINED (1)
            #if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
                #define g_uart0_P_TRANSFER_TX (NULL)
            #else
                #define g_uart0_P_TRANSFER_TX (&FSP_NOT_DEFINED)
            #endif
            #if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
                #define g_uart0_P_TRANSFER_RX (NULL)
            #else
                #define g_uart0_P_TRANSFER_RX (&FSP_NOT_DEFINED)
            #endif
            #undef FSP_NOT_DEFINED
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
