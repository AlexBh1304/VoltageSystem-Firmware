#include "ch32v003.h"
//#include "string.h"
#define N 64

void delay(void);

void peripheralsinit(void);
void tim2init(void);
int main(void)
{
    char string[25];
    char* pString = string;

    peripheralsinit();
    tim2init();
    //uint32_t seq = 0;  
    
    uint32_t sum = 0;
    uint16_t Byte = ADCRead(ADC);
    uint8_t lowbyte = (uint8_t)Byte;
    uint8_t highbyte = (uint8_t) (Byte >> 8);
    
    while(1)
    {
       // for(uint32_t j = 0; j<N; j++)
     //   {
            delay();
            //sum += ADCRead(ADC);
            Byte = ADCRead(ADC);
            lowbyte = (uint8_t)Byte;
            highbyte = (uint8_t) (Byte >> 8);
            UsartSendByte(&lowbyte,USART);
            UsartSendByte(&highbyte,USART);
   //     }

 //       while(1);
    }

    return 0;
}

// void delay(void)
// {
//     for(volatile uint32_t i = 0; i < 619202 ; i++);
// }


void delay(void)
{
    while(!(TIM2->INTFR & 0x1));
    TIM2->INTFR &= ~(1 << 0);
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

//void CreateFrame(char* pString, uint16_t seq)
//{
//    uint8_t temp[10];
//    uint8_t i;
//    *pString = 'V';
//    pString++;
//
//    *pString = ',';
//    pString++;
//
//    //SEQ
//    i = NumberToString(pString, seq
//    pString++;
//    //
//    *pString = ',';
//    pString++;
//
//    //SUM
//
//    pString++;
//    //
//    *pString = ',';
//    pString++;
//    
//    //N
//
//    pString++;
//    //
//    *pString = '*';
//    pString++;
//
//    //CHECKSUM
//
//    pString++;
//    //
//
//    *pString = '\n';
//    pString++;
//
//})

void tim2init(void)
{
    RCC->APB1PCENR |= (1 << 0);
    uint16_t temp;
    TIM2->PSC = 7999; 
    TIM2->ATRLR = 999; 
    TIM2->CTLR1 |= (1 << 0);
}
