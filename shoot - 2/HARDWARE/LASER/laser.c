#include "laser.h"
#include "delay.h"

u16 Distance1;

u16 USART_RX_STA3=0;       //接收状态标记	 
u8 USART_RX_BUF3[USART_REC_LEN_3];     //接收缓冲,最大USART_REC_LEN个字节.

 void MyusartInit3(void)
{
	 USART_InitTypeDef USART_InitStruct3;                        //创建串口1结构体对象
	 GPIO_InitTypeDef  GPIO_InitStruct3;                         //创建GPIO1结构体对象
	 NVIC_InitTypeDef  NVIC_InitStruct3;                         //创建中断1结构体对象

//	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      //GPIOA时钟使能
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);     //串口1时钟使能
	
	
	 GPIO_InitStruct3.GPIO_Mode=  GPIO_Mode_AF_PP;             //1.不同的模式分开初始化
	 GPIO_InitStruct3.GPIO_Pin= GPIO_Pin_10;   //TX
	 GPIO_InitStruct3.GPIO_Speed=GPIO_Speed_50MHz ;
	 GPIO_Init(GPIOB,&GPIO_InitStruct3);
	
	 GPIO_InitStruct3.GPIO_Mode=  GPIO_Mode_IN_FLOATING;
	 GPIO_InitStruct3.GPIO_Pin= GPIO_Pin_11;   //RX
	 GPIO_Init(GPIOB,&GPIO_InitStruct3);                        //2.上拉浮空输入不需要输出频率
	
	 USART_InitStruct3.USART_BaudRate=19200;
	 USART_InitStruct3.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	 USART_InitStruct3.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	 USART_InitStruct3.USART_Parity=USART_Parity_No;
	 USART_InitStruct3.USART_StopBits=USART_StopBits_1;
   USART_InitStruct3.USART_WordLength=USART_WordLength_8b;	
		 
	 USART_Init(USART3,&USART_InitStruct3);
	 USART_Cmd(USART3,ENABLE);
	 USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	 USART_ClearFlag(USART3, USART_FLAG_TC);		//清楚发送标志
	 
	 
	 NVIC_InitStruct3.NVIC_IRQChannel=USART3_IRQn;
	 NVIC_InitStruct3.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_InitStruct3.NVIC_IRQChannelPreemptionPriority=1;
	 NVIC_InitStruct3.NVIC_IRQChannelSubPriority=2;
	 NVIC_Init(& NVIC_InitStruct3);
//	 	 DMA_Configuration();

}

void USART3_IRQHandler(void)
{ 
	static uint8_t k=0,rebuf[9]={0};
	u16 r=0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{
		rebuf[k++] =USART_ReceiveData(USART3);//(USART1->DR);	//读取接收到的数据
		if(!(rebuf[0]=='D'))//如果帧头错误，清缓存
		 {
		 	k=0;
			rebuf[0]=0;
		 }
		  if(k==9)//数据接收完毕
		 {
			if(rebuf[8]=='m')//判断帧尾，正确则解析姿态角
			{
			r=(rebuf[3]-30)*1000+(rebuf[5]-30)*100+(rebuf[6]-30)*10+(rebuf[7]-30) - 20000;
					//LCD_ShowString(120,90,200,16,16,"d=");	
					//LCD_ShowxNum(120,110,r,6,16,0X80);
			Distance1 = r;
			}
			k=0;//清缓存
//		USART_SendData(USART2,r);
//		while(USART_GetFlagStatus(USART2,USART_FLAG_TC) != SET);
	   } 
//	USART_ClearFlag(USART2,USART_FLAG_TC);

	}
}

u16 Laser1(u16 date)
{
	u8 len;
	u16 Distance;
	u8 t=0;
  USART_SendData(USART3,date);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
		len=USART_RX_STA3&0x3fff;//得到此次接收到的数据长度
		Distance=(USART_RX_BUF3[t+2]-0x30)*1000+(USART_RX_BUF3[t+4]-0x30)*100+(USART_RX_BUF3[t+5]-0x30)*10+(USART_RX_BUF3[t+6]-0x30)*1.0;
					//LCD_ShowString(60,90,200,16,16,"d=");	
					//LCD_ShowxNum(60,110,Distance,6,16,0X80);
					delay_ms(500);	
					USART_RX_STA3=0;
					return Distance1;
}
