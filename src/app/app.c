#include "LPC17xx.h"
#include "vector.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_systick.h"

volatile uint32_t tick;
uint32_t get_tick(void);
void delay(uint32_t ms_time);

// Set p[0]:2 as uart tx
PINSEL_CFG_Type pinsel_config_tx = {
    .Portnum = PINSEL_PORT_0,
    .Pinnum = PINSEL_PIN_2,
    .Funcnum = PINSEL_FUNC_1,
};

// Set p[0]:3 as uart rx
PINSEL_CFG_Type pinsel_config_rx = {
    .Portnum = PINSEL_PORT_0,
    .Pinnum = PINSEL_PIN_3,
    .Funcnum = PINSEL_FUNC_1,
};

// Config uart as 8N1, 115200
UART_CFG_Type uart_config = {
    .Baud_rate = 115200,
    .Parity = UART_PARITY_NONE,
    .Databits = UART_DATABIT_8,
    .Stopbits = UART_STOPBIT_1,
};

char *buffer = "hello, from lpc\r\n";

int main(void)
{
    // Clock source initialization
    SystemInit();

    // Configuring system tick
    SYSTICK_InternalInit(10); // 10ms interrupts
    SYSTICK_Cmd(ENABLE);
    SYSTICK_IntCmd(ENABLE);
    
    // Enable uart0 clock
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCUART0, ENABLE);

    UART_Init(LPC_UART0, &uart_config);
    
    // Set alternate functions for tx and rx pins
    PINSEL_ConfigPin(&pinsel_config_tx);
    PINSEL_ConfigPin(&pinsel_config_rx);

    // Enable uart tx pin
    UART_TxCmd(LPC_UART0, ENABLE);

    uint32_t now = get_tick();
    uint32_t delay_10ms = 200; // 2 sec delay

    while (1) {
        if ((get_tick() - now) > delay_10ms) {
            UART_Send(LPC_UART0, (uint8_t *)buffer, 17, BLOCKING);
            now = get_tick();
        }
    }
    return 0;
}

uint32_t get_tick(void)
{
    return tick;
}

void delay(uint32_t ms_time)
{
    // FIXME: This is not relaiable. Defuse the overflow
    uint32_t now = get_tick();
    if (ms_time < 10) ms_time = 10; // Minimum delay time is 10 ms
    ms_time /= 10;
    while((get_tick() - now) < ms_time) {
        __asm__("nop");
    }
}

void systick_handler(void)
{
    tick++;
}
