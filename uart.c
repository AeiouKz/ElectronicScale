
#include <reg51.h>
#include "uart.h"

unsigned char flag_recv = 0;
unsigned char flag_send = 0;

/* �������ú��� */
void uartInit(void) {
	TMOD |= 0x20;	// timer1������ʽ2 ������
	SCON |= 0x50;	// 10λ�첽�շ� �����ж� �������
	PCON |= 0x80;	// �����ʼӱ�SMOD=0
	TH1 = 0xF3;		// 4800
	TL1 = 0xF3;
	ES = 1;		// �����ж�����
	TR1 = 1;
}
/* �����жϷ����� */
/* ��������ԭ�� https://www.cnblogs.com/freesblog/p/5040474.html*/	   
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


