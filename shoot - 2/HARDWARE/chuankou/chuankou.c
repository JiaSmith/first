#include "chuankou.h"
#include "sys.h"
#include "led.h"

//PB2,PB3,PB4,PB5  4个筐开关引脚
//PB6              红蓝队开关引脚

//串口UART4	发送  帧头0x55	(左激光)高八位	低八位	(右激光)	高八位	低八位	一筐序号	二筐序号	帧尾0xaa
//串口UART4 接收	左右筐   
//四个筐坐标  红队 700高(-2000,4200)	800高(2000,0)   	900高(2000,4200) 1000高(-2000,0)
//						蓝队 700高(2000,0)     	800高(-2000,4200)	900高(-2000,0)   1000高(2000,4200)
//红a34 b32 c21 d14 蓝a12 b23 c34 d14

//PA 11第一次准备是否就绪   PA12每次是否就绪
//PB12 红蓝队


u8 laojia;

void UART4_Init(void)
{
	
	GPIO_InitTypeDef    GPIO_InitStruct5;
	USART_InitTypeDef   USART_InitStruct5;
	NVIC_InitTypeDef    NVIC_InitStruct5;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	GPIO_InitStruct5.GPIO_Pin = GPIO_Pin_10;  //TX
	GPIO_InitStruct5.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽
	GPIO_InitStruct5.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC,&GPIO_InitStruct5);
	
	GPIO_InitStruct5.GPIO_Pin = GPIO_Pin_11;    //RX
	GPIO_InitStruct5.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
	GPIO_Init(GPIOC,&GPIO_InitStruct5);
	
	USART_InitStruct5.USART_BaudRate = 115200;   //波特率
	USART_InitStruct5.USART_WordLength = USART_WordLength_8b; //数据位8位
	USART_InitStruct5.USART_StopBits = USART_StopBits_1;  //停止位1位
	USART_InitStruct5.USART_Parity = USART_Parity_No;   //无奇偶校验位
	USART_InitStruct5.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流控
	USART_InitStruct5.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;    //收发模式
	USART_Init(UART4,&USART_InitStruct5);    //配置串口参数

	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(UART4, ENABLE);                    //使能串口1 
		USART_ClearFlag(UART4,USART_IT_RXNE); //清楚标志位
	
	NVIC_InitStruct5.NVIC_IRQChannel=UART4_IRQn;
	NVIC_InitStruct5.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct5.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct5.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(& NVIC_InitStruct5);
	
}

void UART4_IRQHandler(void)
{
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断
	{
		laojia = USART_ReceiveData(UART4);//(UART4->DR);	//读取接收到的数据
	}
}

u8 FQXH(void)
{
	return laojia;
}

void SWITCH_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void UART4_Send(u16 laserleft,u8 fqrr,u8 zero,u8 first,u8 second)
{
	u8 lefth;
	u8 leftl;
	lefth = laserleft >> 8;
	leftl = laserleft;
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4,0x55);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4,lefth);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4,leftl);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4,fqrr);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4,0);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4,first);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4,second);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4,0xaa);
}

void SQ_State(u8 state)
{
	if (state == 0)
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
	else 
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
}
