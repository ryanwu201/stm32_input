/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_exti.h"

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置中断源：按键1 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* 配置中断源：按键2，其他使用上面相关配置 */  
  NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  配置 IO为EXTI中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*开启按键GPIO口的时钟*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
												
	/* 配置 NVIC 中断*/
	NVIC_Configuration();
	
/*--------------------------KEY1配置-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 上升沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------KEY2配置-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
		
		/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 下降沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	

	
	
  //GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12); 
  //EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  //EXTI_Init(&EXTI_InitStructure);
	
  //GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13); 
  //EXTI_InitStructure.EXTI_Line = EXTI_Line13;
  //EXTI_Init(&EXTI_InitStructure);
	
  //GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14); 
  //EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  //EXTI_Init(&EXTI_InitStructure);
	
  //GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15); 
  //EXTI_InitStructure.EXTI_Line = EXTI_Line15;
  //EXTI_Init(&EXTI_InitStructure);

}


void EXTIX_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//外部中断，需要使能AFIO时钟
		
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		//初始化PB12~15中断
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级 2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断通道使能
	NVIC_Init(&NVIC_InitStructure);//初始化中断结构体
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);//中断线5与GPIOB映射起来
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);//中断线6与GPIOB映射起来
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//中断线7与GPIOB映射起来
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);//中断线4与GPIOB映射起来
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}

/*********************************************END OF FILE**********************/