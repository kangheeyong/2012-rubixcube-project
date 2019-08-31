#include "stm32f10x.h"
#include "stm32_eval.h"
#include "stdio.h"

#define TIM6_INTERRUPT

//---------------------------- printf 쓸려면 필요함 ---------------------------
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
    /* Write a character to the USART */  
    if( ch == '\n') {
        USART_SendData(USART1, '\r');
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, '\n');
    }else {
        USART_SendData(USART1, (uint8_t) ch);
    }

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return ch;
}

//------------------------------------------------------------------------------

void My_USART1_Setting_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //USART1 인에이블
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
     - BaudRate = 115200 baud  
     - Word Length = 8 Bits
     - One Stop Bit
     - No parity
     - Hardware flow control disabled (RTS and CTS signals)
     - Receive and transmit enabled
     */
    USART_InitStructure.USART_BaudRate   = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;
    USART_InitStructure.USART_Parity     = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl
                                         = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure the USARTx */ 
    USART_Init(USART1, &USART_InitStructure);
    
    /* 수신부 인터럽트 */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel =  USART1_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USART1 */
    USART_Cmd(USART1, ENABLE); 
}

void My_USART3_Setting_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //USART1 인에이블
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
     - BaudRate = 115200 baud  
     - Word Length = 8 Bits
     - One Stop Bit
     - No parity
     - Hardware flow control disabled (RTS and CTS signals)
     - Receive and transmit enabled
     */
    USART_InitStructure.USART_BaudRate   = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;
    USART_InitStructure.USART_Parity     = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl
                                         = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure the USARTx */ 
    USART_Init(USART3, &USART_InitStructure);
    
    /* 수신부 인터럽트 */
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel =  USART3_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USART1 */
    USART_Cmd(USART3, ENABLE); 
}

/*
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    = USART_ReceiveData(USART1);

     USART_SendData(USART1,'3');
  }

}
*/

void My_SetSysClock_Setting(void) //40MHz 설정 
{
  int  HSEStartUpStatus;
  
  RCC_DeInit(); //RCC 초기화
  RCC_HSEConfig(RCC_HSE_ON); //외부 크리스탈 8MHz
  
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
      FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); // Enable Prefetch Buffer
      FLASH_SetLatency(FLASH_Latency_2); // 플레쉬 메모리 설정 if 48MHz < SYSCLK <= 72MHz
      RCC_HCLKConfig(RCC_SYSCLK_Div1); // HCLK = SYSCLK   
      RCC_PCLK2Config(RCC_HCLK_Div1); // /PCLK2 = HCLK to APB2
      RCC_PCLK1Config(RCC_HCLK_Div2); // /PCLK1 = HCLK/2 to APB1 -> 최대가 36MHz
  }
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_5); //PLLCLK = 8MHz * 5 = 40 MHz
  
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; // Wait till PLL is ready
      
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while(RCC_GetSYSCLKSource() != 0x08); //Wait till PLL is used as system clock source
}

void My_Count_TIM6_Configuration(void) //TIM6
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  
  /* Enable the TIM6 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel =  TIM6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
   
    //시스템클럭 주기 * Prescaler * Period = 인터럽트 걸리는 t
    TIM_TimeBaseStructure.TIM_Period = 99;
    TIM_TimeBaseStructure.TIM_Prescaler = 3;  // 시스템 클럭 40Mhz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    
    TIM_Cmd(TIM6, ENABLE);
      //TIM_ClearFlag(TIM6, TIM_FLAG_Update); //clear TIMx update pending flag
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
}

#ifdef TIM6_INTERRUPT

typedef struct
{
  __IO int us;
  __IO int ms;
  __IO int s;
} CNT;

CNT Cnt;

void TIM6_IRQHandler(void)
{
  //Bit 0 UIF: Update interrupt flag
  //인터럽트가 발생하면 하드웨어가 1로 바꾸어 주기 때문에 인터럽트 핸들러에서 0으로 바꾸어줌
     TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
     
     Cnt.us++;
     Cnt.ms = Cnt.ms + (Cnt.us / 100); 
     Cnt.us = Cnt.us % 100;
     Cnt.s = Cnt.s + (Cnt.ms / 1000); 
     Cnt.ms = Cnt.ms % 1000;
     Cnt.s = Cnt.s % 36000;   
}
int TIM6_100ms(void)
{
  return Cnt.ms % 100 == 0;
}
int TIM6_30ms(void)
{
  return Cnt.ms % 30 == 0;
}
int TIM6_10ms(void)
{
  return Cnt.ms % 10 == 0;
}
int TIM6_1ms(void)
{
  return Cnt.us == 0;
}
int TIM6_100us(void)
{
  return Cnt.us % 10 == 0;
}

#endif