#include "stm32f10x.h"
#include "stm32_eval.h"

void My_GPIO_SET(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //E포트 인에이블   LED   
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;//n번 핀을 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //xx기능으로
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //xx모드로 사용
    GPIO_Init(GPIOE, &GPIO_InitStructure); //configure 환경설정
}

void EXTI_SET(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
   /* Enable GPIOA clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  
  /* Configure PA.00 pin as input floating */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

 
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource11);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource12);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource13);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource14);

  EXTI_InitStructure.EXTI_Line =  EXTI_Line11 | EXTI_Line12 | EXTI_Line13 | EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 13;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  

}