#ifndef __LASER_H
#define __LASER_H	 
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define USART_REC_LEN_3  			200  	//�����������ֽ��� 200	

extern u8  USART_RX_BUF3[USART_REC_LEN_3]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA3;         		//����״̬���	
extern u16 Distance;

u16 Laser1(u16 date);

void MyusartInit3(void);
		 				    
#endif
