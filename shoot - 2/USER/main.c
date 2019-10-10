#include "stm32f10x.h"
#include "dm4015.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "pwm.h"
#include "laser.h"
#include "usart.h"
#include "led.h"
#include "chuankou.h"
#include "math.h"
//ALIENTEK Mini STM32开发板范例代码2
//按键输入实验		   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

//串口分配  底盘 4；左激光 3；右激光 5；云台电机 2.

//变量名
//左激光 Laser_left; 右激光 Laser_right; 分球标志 fq_flag; 筐一横坐标 xx1,纵坐标 yy1; 筐一横坐标 xx2,纵坐标 yy2; 筐高度 height;

s16 xx1 = 0;
s16 yy1 = 0;
s16 xx2 = 0;
s16 yy2 = 0;
u8 fq_flag = 0;
u8 k1 = 0;
u8 k2 = 0;
u8 height = 0;
u16 x,y;
u16 zxx;
u8 sfyq;
double zxjd;
double pi = 3.1415926;
s32 zzjd;
void FQPD(void)          //TEAM1为蓝队   TEAM0为红队
{
	if (TEAM == 1)
	{
		
		if (BUCKET1 == 0 && BUCKET2 == 0)
		 {
			 xx1 = -2000;
			 yy1 = 0;
			 xx2 = 2000;
			 yy2 = 0;
			 k1 = 1;
			 k2 = 2;
		 }
		 else if (BUCKET1 == 0 && BUCKET3 == 0)
		 {
			 xx1 = -2000;
			 yy1 = 0;
			 xx2 = 2000;
			 yy2 = 4200;
			 k1 = 1;
			 k2 = 3;
		 }
		 else if (BUCKET1 == 0 && BUCKET4 == 0)
		 {
			 xx1 = -2000;
			 yy1 = 0;
			 xx2 = -2000;
			 yy2 = 4200;
			 k1 = 1;
			 k2 = 4;
		 }
		 else if (BUCKET2 == 0 && BUCKET3 == 0)
		 {
			 xx1 = 2000;
			 yy1 = 0;
			 xx2 = 2000;
			 yy2 = 4200;
			 k1 = 2;
			 k2 = 3;
		 }
		 else if (BUCKET2 == 0 && BUCKET4 == 0)
		 {
			 xx1 = 2000;
			 yy1 = 0;
			 xx2 = -2000;
			 yy2 = 4200;
			 k1 = 2;
			 k2 = 4;
		 }
		 else if (BUCKET3 == 0 && BUCKET4 == 0)
		 {
			 xx1 = 2000;
			 yy1 = 4200;
			 xx2 = -2000;
			 yy2 = 4200;
			 k1 = 3;
			 k2 = 4;
		 }
	 }
	else if (TEAM == 0) 
		{
		
		if (BUCKET1 == 0 && BUCKET2 == 0)
		 {
			 xx1 = -2000;
			 yy1 = 0;
			 xx2 = 2000;
			 yy2 = 0;
			 k1 = 1;
			 k2 = 2;
		 }
		 else if (BUCKET1 == 0 && BUCKET3 == 0)
		 {
			 xx1 = -2000;
			 yy1 = 0;
			 xx2 = 2000;
			 yy2 = 4200;
			 k1 = 1;
			 k2 = 3;
		 }
		 else if (BUCKET1 == 0 && BUCKET4 == 0)
		 {
			 xx1 = -2000;
			 yy1 = 0;
			 xx2 = -2000;
			 yy2 = 4200;
			 k1 = 1;
			 k2 = 4;
		 }
		 else if (BUCKET2 == 0 && BUCKET3 == 0)
		 {
			 xx1 = 2000;
			 yy1 = 0;
			 xx2 = 2000;
			 yy2 = 4200;
			 k1 = 2;
			 k2 = 3;
		 }
		 else if (BUCKET2 == 0 && BUCKET4 == 0)
		 {
			 xx1 = 2000;
			 yy1 = 0;
			 xx2 = -2000;
			 yy2 = 4200;
			 k1 = 2;
			 k2 = 4;
		 }
		 else if (BUCKET3 == 0 && BUCKET4 == 0)
		 {
			 xx1 = 2000;
			 yy1 = 4200;
			 xx2 = -2000;
			 yy2 = 4200;
			 k1 = 3;
			 k2 = 4;
		 }
	 }
}
		 
u8 FQ_Receiver(void)
{
	fq_flag = FQXH();
	if (TEAM == 0)
	{
		if (k1 == 1&&k2 == 2)
		{
			if (fq_flag == 'a')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 10;
			}
			else if (fq_flag == 'b')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 8;
			}
		}
		else if (k1 == 1&&k2 == 3)
		{
			if (fq_flag == 'a')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 10;
			}
			else if (fq_flag == 'c')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 9;
			}
		}
		else if (k1 == 1&&k2 == 4)
		{
			if (fq_flag == 'a')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 10;
			}
			else if (fq_flag == 'd')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 7;
			}
		}
		else if (k1 == 2&&k2 == 3)
		{
			if (fq_flag == 'b')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 8;
			}
			else if (fq_flag == 'c')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 9;
			}
		}
		else if (k1 == 2&&k2 == 4)
		{
			if (fq_flag == 'b')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 8;
			}
			else if (fq_flag == 'd')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 7;
			}
		}
		else if (k1 == 3&&k2 == 4)
		{
			if (fq_flag == 'c')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 9;
			}
			else if (fq_flag == 'd')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 7;
			}
		}
	}
	else if (TEAM == 1)
	{
		if (k1 == 1&&k2 == 2)
		{
			if (fq_flag == 'a')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 9;
			}
			else if (fq_flag == 'b')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 7;
			}
		}
		else if (k1 == 1&&k2 == 3)
		{
			if (fq_flag == 'a')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 9;
			}
			else if (fq_flag == 'c')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 10;
			}
		}
		else if (k1 == 1&&k2 == 4)
		{
			if (fq_flag == 'a')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 9;
			}
			else if (fq_flag == 'd')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 8;
			}
		}
		else if (k1 == 2&&k2 == 3)
		{
			if (fq_flag == 'b')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				LED1 = 0;
				return 7;
			}
			else if (fq_flag == 'c')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 10;
			}
		}
		else if (k1 == 2&&k2 == 4)
		{
			if (fq_flag == 'b')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 7;
			}
			else if (fq_flag == 'd')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 8;
			}
		}
		else if (k1 == 3&&k2 == 4)
		{
			if (fq_flag == 'c')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 10;
			}
			else if (fq_flag == 'd')
			{
				OUTPUT_DEGREES(-355);
				x = 4407.4 - Laser1(0x44);
				return 8;
			}
		}
	}
	return 0;
}

void SPEED_NB(void)
{
	
	if (fq_flag !=0)
		 {
			 if (height == 7)
			 {
				 x = 4407.4 - Laser1(0x44);
				 y = 1.2827*0.000000001*x*x*x - 6.4017*0.000001*x*x + 0.0156*x + 4.8273; //40
				 HY_SPEED(y);
				 //SQ_State(1);
			 }
			 else if (height == 8)
			 {
				 x = 4407.4 - Laser1(0x44);
				 y = (4.2753*0.000000001*x*x*x) - (2.3887*0.00001*x*x) + 0.0487*x -14.9271; //50
				 HY_SPEED(y);
				 //SQ_State(1);
			 }
			 else if (height == 9)
			 {	
			   x = 4407.4 - Laser1(0x44);
				 y = (3.268*0.000000001*x*x*x) - (1.746*0.00001*x*x) + 0.0356*x -6.162; //60
			   HY_SPEED(y);
				 //SQ_State(1);
		   }
			 else if (height == 10)
			 {	
			   x = 4507.4 - Laser1(0x44);
				 y = -8.8584*0.00000000001*x*x*x + 2.7319*0.000001*x*x - 0.0044*x + 20.1762;  //70
			   HY_SPEED(y);
				 //SQ_State(1);
		   }
		 }
}

void SPEED_WD(void)
{
	u8 h;
	h = FQ_Receiver();
	}
 int main(void)
 {	
   u8 t=0;
		u16 zxdx;
	 u16 zxdy;
	 u16 zxdjl;
	 float sd=22.5;
	 u16 laserleft,laserright;
	 delay_init();	    	 //延时函数初始化	  
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	 Myusart_Init();
	 //KEY_Init();          	//初始化与按键连接的硬件接口
   MyusartInit3();
	 UART4_Init();
	 OUTPUT_ZERO();  //归零度
	 PWM_Init();
	 Easy_Init();
	 delay_ms(1000);
	 delay_ms(1000);
	 HY_SPEED(15);
	 LED_Init();
	 SWITCH_Init();
	 FQPD();
	 UART4_Send(laserleft,0,0,k1,k2);	
	 while(1)
	 {
		 fq_flag = FQXH();
		 if (TEAM == 1)
			 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 else if (TEAM == 0)
			 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 laserleft = Laser1(0x44);
	 	 
		 if (fq_flag == 'a'||fq_flag == 'b'||fq_flag == 'c'||fq_flag == 'd')		
			 
		 
		 {
			 GPIO_SetBits(GPIOA,GPIO_Pin_11);
		 LED1=0;
		 LED0=0;
		 }
		 else 
			 GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		 
		 
		 
		 if (PINK_BASKET == 1)
		 {
			 GPIO_ResetBits(GPIOA,GPIO_Pin_12);
			 height = FQ_Receiver();
			 SPEED_NB();
			 GPIO_SetBits(GPIOA,GPIO_Pin_12);
		 }
		 
		 else if (WB_BASKET == 1)
		 {
//			 zxx = Laser1(0x44);
//			 zxjd = atan(1.0*(zxx - 2200)/2300);
//			 zzjd = zxjd *180 /pi *4;
//			 OUTPUT_DEGREES(zzjd);
			 OUTPUT_ZERO();
			 GPIO_ResetBits(GPIOA,GPIO_Pin_12);
			 zxdx = abs(2200 - zxx);
			 zxdjl = sqrt(zxdx * zxdx + 2300 * 2300);
			 zxdy = -1.9648*0.00001*zxdjl*zxdjl + 0.0995*zxdjl - 102.497;
			 HY_SPEED(zxdy);
			 GPIO_SetBits(GPIOA,GPIO_Pin_12);
			 }
		 else 
		 {
			 GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		 }
		 
	}
		 
//			 y = (4.2753*0.000000001*x*x*x) - (2.3887*0.00001*x*x) + 0.0487*x -14.9271; //50
//			 y = (3.268*0.000000001*x*x*x) - (1.746*0.00001*x*x) + 0.0356*x -6.162; //60
//			 y = 1.2827*0.000000001*x*x*x - 6.4017*0.000001*x*x + 0.0156*x + 4.8273; //40
//			 y = -8.8584*0.00000000001*x*x*x + 2.7319*0.000001*x*x - 0.0044*x + 20.1762;  //70		 
}
