#include "chuankou.h"
#include "sys.h"
#include "led.h"

//PB2,PB3,PB4,PB5  4���𿪹�����
//PB6              �����ӿ�������

//����UART4	����  ֡ͷ0x55	(�󼤹�)�߰�λ	�Ͱ�λ	(�Ҽ���)	�߰�λ	�Ͱ�λ	һ�����	�������	֡β0xaa
//����UART4 ����	���ҿ�   
//�ĸ�������  ��� 700��(-2000,4200)	800��(2000,0)   	900��(2000,4200) 1000��(-2000,0)
//						���� 700��(2000,0)     	800��(-2000,4200)	900��(-2000,0)   1000��(2000,4200)
//��a34 b32 c21 d14 ��a12 b23 c34 d14

//PA 11��һ��׼���Ƿ����   PA12ÿ���Ƿ����
//PB12 ������


u8 laojia;

void UART4_Init(void)
{
	
	GPIO_InitTypeDef    GPIO_InitStruct5;
	USART_InitTypeDef   USART_InitStruct5;
	NVIC_InitTypeDef    NVIC_InitStruct5;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	GPIO_InitStruct5.GPIO_Pin = GPIO_Pin_10;  //TX
	GPIO_InitStruct5.GPIO_Mode = GPIO_Mode_AF_PP;   //��������
	GPIO_InitStruct5.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC,&GPIO_InitStruct5);
	
	GPIO_InitStruct5.GPIO_Pin = GPIO_Pin_11;    //RX
	GPIO_InitStruct5.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
	GPIO_Init(GPIOC,&GPIO_InitStruct5);
	
	USART_InitStruct5.USART_BaudRate = 115200;   //������
	USART_InitStruct5.USART_WordLength = USART_WordLength_8b; //����λ8λ
	USART_InitStruct5.USART_StopBits = USART_StopBits_1;  //ֹͣλ1λ
	USART_InitStruct5.USART_Parity = USART_Parity_No;   //����żУ��λ
	USART_InitStruct5.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������
	USART_InitStruct5.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;    //�շ�ģʽ
	USART_Init(UART4,&USART_InitStruct5);    //���ô��ڲ���

	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���1 
		USART_ClearFlag(UART4,USART_IT_RXNE); //�����־λ
	
	NVIC_InitStruct5.NVIC_IRQChannel=UART4_IRQn;
	NVIC_InitStruct5.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct5.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct5.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(& NVIC_InitStruct5);
	
}

void UART4_IRQHandler(void)
{
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�
	{
		laojia = USART_ReceiveData(UART4);//(UART4->DR);	//��ȡ���յ�������
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
