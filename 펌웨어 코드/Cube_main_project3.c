#include "stm32f10x.h"
#include "stm32_eval.h"
#include "stm32f10x_conf.h"
#include "stdio.h"

#define  AAAA      TIM4->CCR1

  #define F0          TIM4->CCR1= 65     // 1
  #define F90         TIM4->CCR1= 157    // 216
  #define F180        TIM4->CCR1= 253   //3

  #define R0          TIM4->CCR2= 58        //4
  #define R90         TIM4->CCR2= 155        //5
  #define R180        TIM4->CCR2= 246        //6
  
  #define B0          TIM2->CCR4= 53         //7
  #define B90         TIM2->CCR4= 150        //8
  #define B180        TIM2->CCR4= 238        //9
  
  #define L0          TIM2->CCR3= 53         //10
  #define L90         TIM2->CCR3= 143        //11
  #define L180        TIM2->CCR3= 237        //12
  
  #define BF_OUT       TIM4->CCR4= 143,TIM2->CCR2= 142           //14
  #define BF_IN      TIM4->CCR4= 198,TIM2->CCR2= 193             //13
  
  #define RL_OUT       TIM2->CCR1= 115,TIM4->CCR3= 120           //16
  #define RL_IN      TIM2->CCR1= 190,TIM4->CCR3= 170            //15

int RX,TX;
int LR_01 = 0;
int BF_10 = 0;
int For_Back_ward_11 = 0;
int m = 0;



void LR_rotation(void)
{
  if((LR_01 & 56) == 32)  L0;
  else if((LR_01 & 56) == 16) L90;
  else if((LR_01 & 56) == 8) L180;
   
  if((LR_01 & 7) == 4) R0;
  else if((LR_01 & 7) == 2) R90;
  else if((LR_01 & 7) == 1) R180;  
}
void BF_rotation(void)
{
  if((BF_10 & 56) == 32) B0;
  else if((BF_10 & 56) == 16) B90;
  else if((BF_10 & 56) == 8) B180;
  
  if((BF_10 & 7) == 4) F0;
  else if((BF_10 & 7) == 2) F90;
  else if((BF_10 & 7) == 1) F180;
}
void For_Back_ward_rotation(void)
{
  if((For_Back_ward_11 & 3) == 1) RL_IN ;
  if((For_Back_ward_11 & 3) ==2) RL_OUT ;
  if((For_Back_ward_11 & 12) == 4) BF_IN ;
  if((For_Back_ward_11 & 12) == 8) BF_OUT ;
}


int i = 0;

int main(void)
{
  My_SetSysClock_Setting();
  My_USART3_Setting_Configuration();
  //My_USART1_Setting_Configuration();
  My_Count_TIM6_Configuration();
  
  My_Moter_TIM2_Configuration();
  My_Moter_TIM4_Configuration();
 
  My_GPIO_SET(); 
         
  //EXTI_SET();
   
  GPIOE->ODR = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  
  //TIM2->CCR1 = TIM2->CCR2 = TIM2->CCR3 = TIM2->CCR4 = 0;  //A
  //TIM4->CCR1 = TIM4->CCR2 = TIM4->CCR3 = TIM4->CCR4 = 0;  //B
  
   
  B90;
  R90;
  F90;  
  L90;
  
  RL_IN;
  BF_IN;
  
  //TIM4->CCR2= 249;
  
  //TIM4->CCR2= 157;
  
  //TIM4->CCR2= 60;
  
  //TIM2->CCR2 = 180;
  
  /*
  
  150
  
  큰 모터 65~235
  작은모터 70 160 248
            0  90   180
  */
  while (1)
  {
  // i = i + TIM6_1ms();
    if(m)
    {
       
     
     
      
      m = 0;
    }
  }
}




void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
  {
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    RX = USART_ReceiveData(USART3);
    TX = RX;
    USART_SendData(USART3, TX);

   // AAAA = RX;
   // TIM4->CCR3 = RX
    
  if(((RX >> 6)== 3) == 1)
  {
    For_Back_ward_11 = RX;
    For_Back_ward_rotation();

  }
       else if(((RX >> 6)== 1) == 1)
       {
         LR_01 = RX; 
          LR_rotation();
       }
     else if(((RX >> 6)== 2) == 1)
     {
       BF_10 = RX;
        BF_rotation();
     }
    else
    {
      m = 0;
      if(RX == 1) TIM2->CCR4 = 57; //B0;
    if(RX == 3) TIM2->CCR4 = 232;//B180;
    if(RX == 4) TIM4->CCR2 = 63;//R0;
    if(RX == 6) TIM4->CCR2 = 243;//R180;
    
    if(RX == 7) TIM4->CCR1 = 67;//F0;
    if(RX == 9) TIM4->CCR1 = 245;//F180;
    
    if(RX == 10) TIM2->CCR3 = 55;//L0;
    if(RX == 12) TIM2->CCR4 = 232;//L180;
       if(RX == 17) TIM2->CCR3 = 55, TIM4->CCR2 = 243;//L0,R180;
    if(RX == 18) TIM2->CCR3 = 232, TIM4->CCR2 = 63;//L180,R0;
    
    if(RX == 19) TIM2->CCR4 = 57, TIM4->CCR1 = 245;//F0,B180;
    if(RX == 20) TIM2->CCR4 = 232, TIM4->CCR1 = 67;//F180,B0;
    }
    
    /*
 if(RX > 30)
  {
    
  }
    else
    {
    if(RX == 1) B0;
    if(RX == 2) B90;
    if(RX == 3) B180;
    if(RX == 4) R0;
    if(RX == 5) R90;
    if(RX == 6) R180;
    
    if(RX == 7) F0;
    if(RX == 8) F90;
    if(RX == 9) F180;
    
    if(RX == 10) L0;
    if(RX == 11) L90;
    if(RX == 12) L180;
    
    if(RX == 13) BF_IN;
    if(RX == 14) BF_OUT;
    
    if(RX == 15) RL_IN;
    if(RX == 16) RL_OUT;
    
    if(RX == 17) TIM2->CCR3 = 55, TIM4->CCR2 = 243;//L0,R180;
    if(RX == 18) TIM2->CCR3 = 232, TIM4->CCR2 = 63;//L180,R0;
    
    if(RX == 19) TIM2->CCR4 = 57, TIM4->CCR1 = 245;//F0,B180;
    if(RX == 20) TIM2->CCR4 = 232, TIM4->CCR1 = 67;//F180,B0;
    }
  */
  }
}
/*
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    RX = USART_ReceiveData(USART1);
  
   if(((RX >> 6)== 3) == 1) For_Back_ward_11 = RX;
    else if(((RX >> 6)== 1) == 1) LR_01 = RX;  
    else if(((RX >> 6)== 2) == 1) BF_10 = RX;
    
    
 // ----------------------------------------
  if(RX > 40)
  {
    TIM4->CCR2 = RX;
  }
    else
    {
    if(RX == 1) B0;
    if(RX == 2) B90;
    if(RX == 3) B180;
    if(RX == 4) R0;
    if(RX == 5) R90;
    if(RX == 6) R180;
    
    if(RX == 7) F0;
    if(RX == 8) F90;
    if(RX == 9) F180;
    
    if(RX == 10) L0;
    if(RX == 11) L90;
    if(RX == 12) L180;
    
    if(RX == 13) BF_IN;
    if(RX == 14) BF_OUT;
    
    if(RX == 15) RL_IN;
    if(RX == 16) RL_OUT;
    }
    
   // }

  }

}*/
  