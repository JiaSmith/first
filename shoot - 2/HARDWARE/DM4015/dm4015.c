#include "dm4015.h"
#include "sys.h"
 u8 res =0x44;
 


void Myusart_Init(void)
{
	 USART_InitTypeDef USART_InitStruct1;                        //创建串口1结构体对象
	 GPIO_InitTypeDef  GPIO_InitStruct1;                         //创建GPIO1结构体对象
	 NVIC_InitTypeDef  NVIC_InitStruct1;                         //创建中断1结构体对象
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      //GPIOA时钟使能
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);     //串口1时钟使能
	
	 GPIO_InitStruct1.GPIO_Mode=  GPIO_Mode_AF_PP;             //1.不同的模式分开初始化
	 GPIO_InitStruct1.GPIO_Pin= GPIO_Pin_2;   //TX
	 GPIO_InitStruct1.GPIO_Speed=GPIO_Speed_50MHz ;
	 GPIO_Init(GPIOA,&GPIO_InitStruct1);
	 GPIO_InitStruct1.GPIO_Mode=  GPIO_Mode_IN_FLOATING;
	 GPIO_InitStruct1.GPIO_Pin= GPIO_Pin_3;   //RX
	 GPIO_Init(GPIOA,&GPIO_InitStruct1);                        //2.上拉浮空输入不需要输出频率
	
	 
	 USART_InitStruct1.USART_BaudRate=115200;
	 USART_InitStruct1.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	 USART_InitStruct1.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	 USART_InitStruct1.USART_Parity=USART_Parity_No;
	 USART_InitStruct1.USART_StopBits=USART_StopBits_1;
     USART_InitStruct1.USART_WordLength=USART_WordLength_8b;	
	 USART_Init(USART2,&USART_InitStruct1);
	 USART_Cmd(USART2,ENABLE);
	 USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);	
	 
	 NVIC_InitStruct1.NVIC_IRQChannel=USART2_IRQn;
	 NVIC_InitStruct1.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_InitStruct1.NVIC_IRQChannelPreemptionPriority=1;   //抢占优先级
	 NVIC_InitStruct1.NVIC_IRQChannelSubPriority=1;					 //从优先级
	 NVIC_Init(& NVIC_InitStruct1);
	
     USART_ClearFlag(USART2,USART_FLAG_TC);
}

 void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{
		res = USART_ReceiveData(USART2);
		USART_SendData(USART1,res);
	}
	
}

void OUTPUT_DEGREES(s32 angle1)
{
	s32 a32;
	u8 a[4],jg;
	a32 = angle1 * 100;
	
	a[0]=a32>>24;
	a[1]=a32>>16;
	a[2]=a32>>8;
	a[3]=a32;
	
	if(a32 >= 0){
		jg = a[0] + a[1] + a[2] + a[3];
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	USART_SendData(USART2,0x3E);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xA3);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x01);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x08);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xEA);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,a[3]);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,a[2]);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,a[1]);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,a[0]);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,jg);
	}
	else{
		jg = a[0] + a[1] + a[2] + a[3] + 0xFF + 0xFF + 0xFF + 0xFF;
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x3E);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xA3);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x01);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x08);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xEA);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,a[3]);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,a[2]);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,a[1]);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,a[0]);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xFF);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xFF);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xFF);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xFF);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,jg);
	}
		
}

void OUTPUT_ZERO(void)
{
	
	USART_SendData(USART2,0x3E);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xA3);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x01);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x08);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0xEA);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2,0x00);
}
