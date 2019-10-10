#ifndef __CHUANKOU_H
#define __CHUANKOU_H
#include "sys.h"

#define BUCKET1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //读取按钮1为桶1
#define BUCKET2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) //读取按钮2为桶2
#define BUCKET3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) //读取按钮3为桶3
#define BUCKET4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) //读取按钮4为桶4
#define TEAM GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)    //读取开关红蓝队

#define WB_BASKET GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) //白黑球7引脚高电平
#define PINK_BASKET GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) //粉球8引脚高电平

extern u8 laojia;

void UART4_Init(void);
void SWITCH_Init(void);
void UART4_Send(u16 laserleft,u8 fqrr,u8 zero,u8 first,u8 second);
u8 FQXH(void);
void SQ_State(u8 state);

#endif
