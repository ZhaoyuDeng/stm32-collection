#include "stm32f10x.h"
#include "pwmic.h"

//网上参考程序 使用PWM波输入
//使用TIM4	PB.7 检测

void Tim2_PWMIC_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 
  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   
  /* TIM4 chennel2 configuration : PB.07 */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   
  /* Connect TIM pin to AF2 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
         
  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
         
        TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
 
  TIM_PWMIConfig(TIM4, &TIM_ICInitStructure);
 
  /* Select the TIM4 Input Trigger: TI2FP2 */
  TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2);
 
  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(TIM4,TIM_MasterSlaveMode_Enable);
 
  /* TIM enable counter */
  TIM_Cmd(TIM4, ENABLE);
 
  /* Enable the CC2 Interrupt Request */
   TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
 
}
//中断程序：
void TIM4_IRQHandler(void)
{
  /* Clear TIM4 Capture compare interrupt pending bit */
  TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_CC2);
 
  /* Get the Input Capture value */
  IC2Value = TIM_GetCapture2(TIM4);//周期
 
  if (IC2Value != 0)
  {
                highval[filter_cnt]=TIM_GetCapture1(TIM4);//高电平周期
                waveval[filter_cnt]=IC2Value;
                filter_cnt++;
                if(filter_cnt>=FILTER_NUM)
                        filter_cnt=0;
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}
