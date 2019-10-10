#ifndef __CHUANKOU_H
#define __CHUANKOU_H
#include "sys.h"

#define BUCKET1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //��ȡ��ť1ΪͰ1
#define BUCKET2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) //��ȡ��ť2ΪͰ2
#define BUCKET3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) //��ȡ��ť3ΪͰ3
#define BUCKET4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) //��ȡ��ť4ΪͰ4
#define TEAM GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)    //��ȡ���غ�����

#define WB_BASKET GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) //�׺���7���Ÿߵ�ƽ
#define PINK_BASKET GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) //����8���Ÿߵ�ƽ

extern u8 laojia;

void UART4_Init(void);
void SWITCH_Init(void);
void UART4_Send(u16 laserleft,u8 fqrr,u8 zero,u8 first,u8 second);
u8 FQXH(void);
void SQ_State(u8 state);

#endif
