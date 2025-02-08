
/* 
 * Source: libopencm3 library: https://github.com/libopencm3/libopencm3
 */

#include "vector.h"

void blocking_handler(void);
void null_handler(void);
void reset_handler(void);
int main(void);

void  nmi_handler(void) __attribute__((weak, alias("null_handler")));
void  hard_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void  sv_call_handler(void) __attribute__((weak, alias("null_handler")));
void  pend_sv_handler(void) __attribute__((weak, alias("null_handler")));
void  systick_handler(void) __attribute__((weak, alias("null_handler")));
void  mem_manage_handler(void) __attribute__((weak, alias("blocking_handler")));
void  bus_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void  usage_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void  debug_monitor_handler(void) __attribute__((weak, alias("null_handler")));

void wdt_isr(void) __attribute__((weak, alias("blocking_handler")));
void timer0_isr(void) __attribute__((weak, alias("blocking_handler")));
void timer1_isr(void) __attribute__((weak, alias("blocking_handler")));
void timer2_isr(void) __attribute__((weak, alias("blocking_handler")));
void timer3_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart0_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart1_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart2_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart3_isr(void) __attribute__((weak, alias("blocking_handler")));
void pwm_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c0_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c1_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c2_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi_isr(void) __attribute__((weak, alias("blocking_handler")));
void ssp0_isr(void) __attribute__((weak, alias("blocking_handler")));
void ssp1_isr(void) __attribute__((weak, alias("blocking_handler")));
void pll0_isr(void) __attribute__((weak, alias("blocking_handler")));
void rtc_isr(void) __attribute__((weak, alias("blocking_handler")));
void eint0_isr(void) __attribute__((weak, alias("blocking_handler")));
void eint1_isr(void) __attribute__((weak, alias("blocking_handler")));
void eint2_isr(void) __attribute__((weak, alias("blocking_handler")));
void eint3_isr(void) __attribute__((weak, alias("blocking_handler")));
void adc_isr(void) __attribute__((weak, alias("blocking_handler")));
void bod_isr(void) __attribute__((weak, alias("blocking_handler")));
void usb_isr(void) __attribute__((weak, alias("blocking_handler")));
void can_isr(void) __attribute__((weak, alias("blocking_handler")));
void gpdma_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2s_isr(void) __attribute__((weak, alias("blocking_handler")));
void ethernet_isr(void) __attribute__((weak, alias("blocking_handler")));
void rit_isr(void) __attribute__((weak, alias("blocking_handler")));
void motor_pwm_isr(void) __attribute__((weak, alias("blocking_handler")));
void qei_isr(void) __attribute__((weak, alias("blocking_handler")));
void pll1_isr(void) __attribute__((weak, alias("blocking_handler")));
void usb_act_isr(void) __attribute__((weak, alias("blocking_handler")));
void can_act_isr(void) __attribute__((weak, alias("blocking_handler")));

#define IRQ_HANDLERS \
    [NVIC_WDT_IRQ] = wdt_isr, \
    [NVIC_TIMER0_IRQ] = timer0_isr, \
    [NVIC_TIMER1_IRQ] = timer1_isr, \
    [NVIC_TIMER2_IRQ] = timer2_isr, \
    [NVIC_TIMER3_IRQ] = timer3_isr, \
    [NVIC_UART0_IRQ] = uart0_isr, \
    [NVIC_UART1_IRQ] = uart1_isr, \
    [NVIC_UART2_IRQ] = uart2_isr, \
    [NVIC_UART3_IRQ] = uart3_isr, \
    [NVIC_PWM_IRQ] = pwm_isr, \
    [NVIC_I2C0_IRQ] = i2c0_isr, \
    [NVIC_I2C1_IRQ] = i2c1_isr, \
    [NVIC_I2C2_IRQ] = i2c2_isr, \
    [NVIC_SPI_IRQ] = spi_isr, \
    [NVIC_SSP0_IRQ] = ssp0_isr, \
    [NVIC_SSP1_IRQ] = ssp1_isr, \
    [NVIC_PLL0_IRQ] = pll0_isr, \
    [NVIC_RTC_IRQ] = rtc_isr, \
    [NVIC_EINT0_IRQ] = eint0_isr, \
    [NVIC_EINT1_IRQ] = eint1_isr, \
    [NVIC_EINT2_IRQ] = eint2_isr, \
    [NVIC_EINT3_IRQ] = eint3_isr, \
    [NVIC_ADC_IRQ] = adc_isr, \
    [NVIC_BOD_IRQ] = bod_isr, \
    [NVIC_USB_IRQ] = usb_isr, \
    [NVIC_CAN_IRQ] = can_isr, \
    [NVIC_GPDMA_IRQ] = gpdma_isr, \
    [NVIC_I2S_IRQ] = i2s_isr, \
    [NVIC_ETHERNET_IRQ] = ethernet_isr, \
    [NVIC_RIT_IRQ] = rit_isr, \
    [NVIC_MOTOR_PWM_IRQ] = motor_pwm_isr, \
    [NVIC_QEI_IRQ] = qei_isr, \
    [NVIC_PLL1_IRQ] = pll1_isr, \
    [NVIC_USB_ACT_IRQ] = usb_act_isr, \
    [NVIC_CAN_ACT_IRQ] = can_act_isr

__attribute__ ((section(".vectors")))
vector_table_t vector_table = {
    .initial_sp_value = &_stack,
    .reset = reset_handler,
    .nmi = nmi_handler,
    .hard_fault = hard_fault_handler,
    .memory_manage_fault = mem_manage_handler,
    .bus_fault = bus_fault_handler,
    .usage_fault = usage_fault_handler,
    .sv_call = sv_call_handler,
    .debug_monitor = debug_monitor_handler,
    .pend_sv = pend_sv_handler,
    .systick = systick_handler,
    .irq = { IRQ_HANDLERS },
};

void reset_handler(void) {
    unsigned int *src, *dest;

    for (src = &_data_lma, dest = &_data;
            dest < &_edata;
            src++, dest++) {
        *dest = *src;
    }

    while (dest < &_ebss) {
        *dest++ = 0;
    }

    (void)main();

    blocking_handler();
}

void blocking_handler(void) {
    while(1) {}
}

void null_handler(void) { }

