#include "ch32v003.h"

void delay(void);

void peripheralsinit(void);

uint8_t NumberToAscii (uint8_t number);

void NumberToString(char* string, uint32_t number);

int main(void)
{
    //char string[32];

    peripheralsinit();

    //uint32_t seq = 0;  
    
    uint16_t Byte = ADCRead(ADC);
    uint8_t lowbyte = (uint8_t)Byte;
    uint8_t highbyte = (uint8_t) (Byte >> 8);
    uint8_t rxbyte;
    
    while(1)
    {
        delay();
 //       UsartRxByte(&rxbyte, USART);

   //     {
            Byte = ADCRead(ADC);
            lowbyte = (uint8_t)Byte;
            highbyte = (uint8_t) (Byte >> 8);
            UsartSendByte(&lowbyte,USART);
            UsartSendByte(&highbyte,USART);
     //   }
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

void NumberToString(char* string, uint32_t number)
{
    uint32_t temp;
    uint8_t n;
    uint8_t index;
    uint8_t base;

    if(number < 10)
    {
        
    }

    else if(number < 100)
    {

    }

    else if(number < 1000)
    {
        n=3;
        index = 0;
        base = 100;
        for(uint8_t i = n; i >= 2; i--)
        {
            temp = number / base;
            temp = NumberToAscii(temp);
            *string = (char)temp;
            string++;
            temp = number % base;
            base = base / 10;
        }

        string++;
        temp = number % 10;
    
    }

    else if(number < 10000)
    {

    }

    else if(number < 100000)
    {

    }

    else if(number < 1000000)
    {

    }

    else if(number < 10000000)
    {

    }

    else if(number < 100000000)
    {

    }

    else if(number < 1000000000)
    {

    }

    else if(number < 10000000000)
    {

    }

}


uint8_t NumberToAscii (uint8_t number)
{
    switch(number)
    {
        case 0:
            return 48;
            break;

        case 1:
            return 49;
            break;

        case 2:
            return 50;
            break;

        case 3:
            return 51;
            break;

        case 4:
            return 52;
            break;

        case 5:
            return 53;
            break;

        case 6:
            return 54;
            break;

        case 7:
            return 55;
            break;

        case 8:
            return 56;
            break;

        case 9:
            return 57;
            break;
    }
}
