#include "ch32v003.h"
void delay(void);
void peripheralsinit(void);

int main(void)
{
    peripheralsinit();
    
    uint16_t Byte = ADCRead(ADC);
    uint8_t lowbyte = (uint8_t)Byte;
    uint8_t highbyte = (uint8_t) (Byte >> 8);
    uint8_t rxbyte;

    UsartRxByte(&rxbyte, USART);

    if(rxbyte == 0b00000001)
    {
        UsartSendByte(&lowbyte,USART);
        UsartSendByte(&highbyte,USART);
        while(1);
    }

    while(1)
    {
//         UsartRxByte(&Byte, USART);

        
    }

    return 0;
}

void delay(void)
{
    for(volatile uint32_t i = 0; i < 619202 ; i++);
}

void peripheralsinit(void)
{
    USART_Config usartconfig;
    usartconfig.DataSize = DATA_BITS_8; 
    usartconfig.Parity = NO_PARITY; 
    usartconfig.NoStopBits = STOP_BITS_1; 
    usartconfig.Baudrate = BD9600; 
    
    USARTInit(USART, &usartconfig);
    
    ADC_Config adcconfig;
    adcconfig.SampleTime = SAMPLE_TIME_241_CYCLES;
    
    ADCInit(ADC, &adcconfig);
}

