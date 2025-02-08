/* 
 * Source: libopencm3 library: https://github.com/libopencm3/libopencm3
 */

#define NVIC_WDT_IRQ 0
#define NVIC_TIMER0_IRQ 1
#define NVIC_TIMER1_IRQ 2
#define NVIC_TIMER2_IRQ 3
#define NVIC_TIMER3_IRQ 4
#define NVIC_UART0_IRQ 5
#define NVIC_UART1_IRQ 6
#define NVIC_UART2_IRQ 7
#define NVIC_UART3_IRQ 8
#define NVIC_PWM_IRQ 9
#define NVIC_I2C0_IRQ 10
#define NVIC_I2C1_IRQ 11
#define NVIC_I2C2_IRQ 12
#define NVIC_SPI_IRQ 13
#define NVIC_SSP0_IRQ 14
#define NVIC_SSP1_IRQ 15
#define NVIC_PLL0_IRQ 16
#define NVIC_RTC_IRQ 17
#define NVIC_EINT0_IRQ 18
#define NVIC_EINT1_IRQ 19
#define NVIC_EINT2_IRQ 20
#define NVIC_EINT3_IRQ 21
#define NVIC_ADC_IRQ 22
#define NVIC_BOD_IRQ 23
#define NVIC_USB_IRQ 24
#define NVIC_CAN_IRQ 25
#define NVIC_GPDMA_IRQ 26
#define NVIC_I2S_IRQ 27
#define NVIC_ETHERNET_IRQ 28
#define NVIC_RIT_IRQ 29
#define NVIC_MOTOR_PWM_IRQ 30
#define NVIC_QEI_IRQ 31
#define NVIC_PLL1_IRQ 32
#define NVIC_USB_ACT_IRQ 33
#define NVIC_CAN_ACT_IRQ 34

#define NVIC_IRQ_COUNT 35

typedef void (*vector_table_entry_t)(void);

typedef struct {
	unsigned int *initial_sp_value; /**< Initial stack pointer value. */
	vector_table_entry_t reset;
	vector_table_entry_t nmi;
	vector_table_entry_t hard_fault;
	vector_table_entry_t memory_manage_fault; /* not in CM0 */
	vector_table_entry_t bus_fault;           /* not in CM0 */
	vector_table_entry_t usage_fault;         /* not in CM0 */
	vector_table_entry_t reserved_x001c[4];
	vector_table_entry_t sv_call;
	vector_table_entry_t debug_monitor;       /* not in CM0 */
	vector_table_entry_t reserved_x0034;
	vector_table_entry_t pend_sv;
	vector_table_entry_t systick;
	vector_table_entry_t irq[NVIC_IRQ_COUNT];
} vector_table_t;

extern unsigned _data_lma, _data, _edata, _ebss, _stack;
extern vector_table_t vector_table;
