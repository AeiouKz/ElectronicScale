
#include <reg51.h>
#include "uart.h"

unsigned char flag_recv = 0;
unsigned char flag_send = 0;

/* 串口配置函数 */
void uartInit(void) {
	TMOD |= 0x20;	// timer1工作方式2 波特率
	SCON |= 0x50;	// 10位异步收发 允许中断 允许接收
	PCON |= 0x80;	// 波特率加倍SMOD=0
	TH1 = 0xF3;		// 4800
	TL1 = 0xF3;
	ES = 1;		// 串口中断允许
	TR1 = 1;
}
/* 串口中断服务函数 */
/* 程序死机原因 https://www.cnblogs.com/freesblog/p/5040474.html*/	   
void uart_isr(void) interrupt 4
{
	if(RI) {
		RI = 0;	
		flag_recv = 1;

	}else {
		TI = 0;
		flag_send = 1;
	}
}

void uartSendChr(unsigned char chr) {
	SBUF = chr;
	while(!flag_send);
	flag_send = 0;	
}

void uartSendStr(unsigned char *str) {
	while(*str != '\0') {
		uartSendChr(*str++);
	}
}


