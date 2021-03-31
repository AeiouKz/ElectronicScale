
#include <reg51.h>
#include "timer0.h"

unsigned char flag_time = 0x00;

unsigned char ref_us = 125;
unsigned char ref_ms = 20;
unsigned char ref_s  = 1000;

void timer0Init(void) {
	TMOD |= 0x01;	 /* 工作方式1 */
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
	ET0 = 1;	  // 允许定时中断
	TR0 = 1;	  // 启动定时器
}

/* timer0 定时器中断服务函数 */
void timer0_isr(void) interrupt 1
{
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
	ref_s--;
	ref_ms--;

	if(0 == ref_us) {
		ref_us = 125;
		flag_time |= 0x01;	
	}

	if(0 == ref_ms) {
		ref_ms = 20;
		flag_time |= 0x02;	
	}

	if(0 == ref_s) {
		ref_s = 1000;
		flag_time |= 0x04;
	}

}

/* ms时延 */
void delay_ms(unsigned char ms) {
	unsigned char i=100,j;
	for(;ms;ms--){
		while(--i){
			j=10;
			while(--j);
		}
	}
}