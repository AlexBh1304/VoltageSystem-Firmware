#include "ch32v003.h"
#include "string.h"
#define N 64

void delay(void);

void peripheralsinit(void);
void tim2init(void);

void CreateFrame(char* pString, uint16_t seq, uint16_t sum);
uint8_t CheckSum(char* pStart, char* pEnd);
char NibbleToHex(uint8_t Nibble);
void SendFrame(char* pFrame);

int main(void)
{

    peripheralsinit();
    tim2init();

    uint16_t seq = 0;  
    uint16_t sum = 0;

    while(1)
    {
        char text[50];

        for(uint8_t i = 0; i < N; i++)
        {
            sum += ADCRead(ADC);
        }
        
        CreateFrame(text, seq, sum);

        sum = 0;
        seq++;
        delay();
        SendFrame(text);

            //delay();
            //sum += ADCRead(ADC);
            //Byte = ADCRead(ADC);
            //lowbyte = (uint8_t)Byte;
            //highbyte = (uint8_t) (Byte >> 8);
            //UsartSendByte(&lowbyte,USART);
            //UsartSendByte(&highbyte,USART);
    }

    return 0;
}

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

void tim2init(void)
{
    RCC->APB1PCENR |= (1 << 0);
    TIM2->PSC = 7999; 
    TIM2->ATRLR = 999; 
    TIM2->CTLR1 |= (1 << 0);
}

void CreateFrame(char* pString, uint16_t seq, uint16_t sum)
{
    char temp[10];
    uint8_t i;
    char* pEndCheckSum;
    char* pStartCheckSum = pString;
    uint8_t CheckSumResult;
    
    *pString = 'V';
    pString++;

    *pString = ',';
    pString++;

    //SEQ
    i = NumberToString(temp, seq, sizeof(temp));
 
    for(uint8_t j = 0; j < i; j++)
    {
        *pString = temp[j];
        pString++;
    }

    *pString = ',';
    pString++;

    //SUM
    i = NumberToString(temp, sum, sizeof(temp));
 
    for(uint8_t j = 0; j < i; j++)
    {
        *pString = temp[j];
        pString++;
    }
    //

    *pString = ',';
    pString++;
    
    //N
    *pString = '6';
    pString++;

    *pString = '4';
    pEndCheckSum = pString;
    pString++;

   //
    *pString = '*';
    pString++;

    //CHECKSUM
    CheckSumResult = CheckSum(pStartCheckSum,pEndCheckSum);
    *pString = NibbleToHex(CheckSumResult >> 4);

    pString++;
    
    *pString = NibbleToHex(CheckSumResult & 0x0F);

    pString++;
    
    *pString = '\0';
}

uint8_t CheckSum(char* pStart, char* pEnd)
{
    uint8_t sum = 0;
    while(pStart <= pEnd)
    {
        sum+= *pStart;
        pStart++;
    }

    return sum;
}

char NibbleToHex(uint8_t Nibble)
{
    switch(Nibble)
    {

        case 0:
            return '0';

        case 1:
            return '1';

        case 2:
            return '2';

        case 3:
            return '3';

        case 4:
            return '4';

        case 5:
            return '5';

        case 6:
            return '6';

        case 7:
            return '7';

        case 8:
            return '8';

        case 9:
            return '9';

        case 10:
            return 'A';

        case 11:
            return 'B';

        case 12:
            return 'C';

        case 13:
            return 'D';

        case 14:
            return 'E';

        case 15:
            return 'F';

        default:
            return '?';
    }
}

void SendFrame(char* pFrame)
{
    while(*pFrame != '\0')
    {
        UsartSendByte((uint8_t*)pFrame,USART);
        pFrame++;
    }
    UsartSendByte((uint8_t*)pFrame,USART);
}




