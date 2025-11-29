/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
        #include "bsp_api.h"

        /** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
        FSP_HEADER

                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (21)
        #endif
        /* ISR prototypes */
        void cmt_cm_int_isr(void);
        void gpt_counter_overflow_isr(void);
        void ethercat_ssc_port_isr_esc_sync0(void);
        void ethercat_ssc_port_isr_esc_sync1(void);
        void ethercat_ssc_port_isr_esc_cat(void);
        void sci_uart_eri_isr(void);
        void sci_uart_rxi_isr(void);
        void sci_uart_txi_isr(void);
        void sci_uart_tei_isr(void);
        void canfd_rx_fifo_isr(void);
        void canfd_error_isr(void);
        void canfd_channel_tx_isr(void);
        void canfd_common_fifo_rx_isr(void);

        /* Vector table allocations */
        #define VECTOR_NUMBER_CMT0_CMI ((IRQn_Type) 53) /* CMT0_CMI (CMT0 Compare match) */
        #define VECTOR_NUMBER_GPT8_OVF ((IRQn_Type) 194) /* GPT_OVF (GPT8 GTCNT overflow (GTPR compare match)) */
        #define VECTOR_NUMBER_ESC_SYNC0 ((IRQn_Type) 277) /* ESC_SYNC0 (EtherCAT Sync0 interrupt) */
        #define VECTOR_NUMBER_ESC_SYNC1 ((IRQn_Type) 278) /* ESC_SYNC1 (EtherCAT Sync1 interrupt) */
        #define VECTOR_NUMBER_ESC_CAT ((IRQn_Type) 279) /* ESC_CAT (EtherCAT interrupt) */
        #define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 288) /* SCI0_ERI (SCI0 Receive error) */
        #define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 289) /* SCI0_RXI (SCI0 Receive data full) */
        #define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 290) /* SCI0_TXI (SCI0 Transmit data empty) */
        #define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 291) /* SCI0_TEI (SCI0 Transmit end) */
        #define VECTOR_NUMBER_CAN_RXF ((IRQn_Type) 316) /* CAN_RXF (CANFD RX FIFO interrupt) */
        #define VECTOR_NUMBER_CAN_GLERR ((IRQn_Type) 317) /* CAN_GLERR (CANFD Global error interrupt) */
        #define VECTOR_NUMBER_CAN0_TX ((IRQn_Type) 318) /* CAN0_TX (CANFD0 Channel TX interrupt) */
        #define VECTOR_NUMBER_CAN0_CHERR ((IRQn_Type) 319) /* CAN0_CHERR (CANFD0 Channel CAN error interrupt) */
        #define VECTOR_NUMBER_CAN0_COMFRX ((IRQn_Type) 320) /* CAN0_COMFRX (CANFD0 Common RX FIFO or TXQ interrupt) */
        #define VECTOR_NUMBER_CAN1_TX ((IRQn_Type) 321) /* CAN1_TX (CANFD1 Channel TX interrupt) */
        #define VECTOR_NUMBER_CAN1_CHERR ((IRQn_Type) 322) /* CAN1_CHERR (CANFD1 Channel CAN error interrupt) */
        #define VECTOR_NUMBER_CAN1_COMFRX ((IRQn_Type) 323) /* CAN1_COMFRX (CANFD1 Common RX FIFO or TXQ interrupt) */
        #define VECTOR_NUMBER_SCI5_ERI ((IRQn_Type) 435) /* SCI5_ERI (SCI5 Receive error) */
        #define VECTOR_NUMBER_SCI5_RXI ((IRQn_Type) 436) /* SCI5_RXI (SCI5 Receive data full) */
        #define VECTOR_NUMBER_SCI5_TXI ((IRQn_Type) 437) /* SCI5_TXI (SCI5 Transmit data empty) */
        #define VECTOR_NUMBER_SCI5_TEI ((IRQn_Type) 438) /* SCI5_TEI (SCI5 Transmit end) */
        typedef enum IRQn {
            SoftwareGeneratedInt0 = -32,
            SoftwareGeneratedInt1 = -31,
            SoftwareGeneratedInt2 = -30,
            SoftwareGeneratedInt3 = -29,
            SoftwareGeneratedInt4 = -28,
            SoftwareGeneratedInt5 = -27,
            SoftwareGeneratedInt6 = -26,
            SoftwareGeneratedInt7 = -25,
            SoftwareGeneratedInt8 = -24,
            SoftwareGeneratedInt9 = -23,
            SoftwareGeneratedInt10 = -22,
            SoftwareGeneratedInt11 = -21,
            SoftwareGeneratedInt12 = -20,
            SoftwareGeneratedInt13 = -19,
            SoftwareGeneratedInt14 = -18,
            SoftwareGeneratedInt15 = -17,
            DebugCommunicationsChannelInt = -10,
            PerformanceMonitorCounterOverflowInt = -9,
            CrossTriggerInterfaceInt = -8,
            VritualCPUInterfaceMaintenanceInt = -7,
            HypervisorTimerInt = -6,
            VirtualTimerInt = -5,
            NonSecurePhysicalTimerInt = -2,
            CMT0_CMI_IRQn = 53, /* CMT0_CMI (CMT0 Compare match) */
            GPT8_OVF_IRQn = 194, /* GPT_OVF (GPT8 GTCNT overflow (GTPR compare match)) */
            ESC_SYNC0_IRQn = 277, /* ESC_SYNC0 (EtherCAT Sync0 interrupt) */
            ESC_SYNC1_IRQn = 278, /* ESC_SYNC1 (EtherCAT Sync1 interrupt) */
            ESC_CAT_IRQn = 279, /* ESC_CAT (EtherCAT interrupt) */
            SCI0_ERI_IRQn = 288, /* SCI0_ERI (SCI0 Receive error) */
            SCI0_RXI_IRQn = 289, /* SCI0_RXI (SCI0 Receive data full) */
            SCI0_TXI_IRQn = 290, /* SCI0_TXI (SCI0 Transmit data empty) */
            SCI0_TEI_IRQn = 291, /* SCI0_TEI (SCI0 Transmit end) */
            CAN_RXF_IRQn = 316, /* CAN_RXF (CANFD RX FIFO interrupt) */
            CAN_GLERR_IRQn = 317, /* CAN_GLERR (CANFD Global error interrupt) */
            CAN0_TX_IRQn = 318, /* CAN0_TX (CANFD0 Channel TX interrupt) */
            CAN0_CHERR_IRQn = 319, /* CAN0_CHERR (CANFD0 Channel CAN error interrupt) */
            CAN0_COMFRX_IRQn = 320, /* CAN0_COMFRX (CANFD0 Common RX FIFO or TXQ interrupt) */
            CAN1_TX_IRQn = 321, /* CAN1_TX (CANFD1 Channel TX interrupt) */
            CAN1_CHERR_IRQn = 322, /* CAN1_CHERR (CANFD1 Channel CAN error interrupt) */
            CAN1_COMFRX_IRQn = 323, /* CAN1_COMFRX (CANFD1 Common RX FIFO or TXQ interrupt) */
            SCI5_ERI_IRQn = 435, /* SCI5_ERI (SCI5 Receive error) */
            SCI5_RXI_IRQn = 436, /* SCI5_RXI (SCI5 Receive data full) */
            SCI5_TXI_IRQn = 437, /* SCI5_TXI (SCI5 Transmit data empty) */
            SCI5_TEI_IRQn = 438, /* SCI5_TEI (SCI5 Transmit end) */
            SHARED_PERIPHERAL_INTERRUPTS_MAX_ENTRIES = BSP_VECTOR_TABLE_MAX_ENTRIES
        } IRQn_Type;

        /** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
        FSP_FOOTER

        #endif /* VECTOR_DATA_H */