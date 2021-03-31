

#include <reg51.h>

#include "app.h"	
#include "lcd.h"	
#include "uart.h"	
#include "HX711.h"	
#include "timer0.h"	
#include "key.h"

sbit led = P1^3;		
/* ��������� */
void main(void) {
	unsigned char i = 0;
	unsigned int weight;
	unsigned long refAD;

	P0 = P1 = P2 = P3 = 0xFF;

	Lcd1602Init();	/* LCD��ʼ�� */
	uartInit();		/* UART��ʼ��*/
	timer0Init();	/* Timer0��ʼ�� */	
	EA = 1;			/* ���ж����� */
				

	refAD = AD_average(10);


	/* ���򲻶������� */
	while(1) {

		refAD = AD_average(5);	
		weight = (unsigned int)(refAD/100+0.5);	
		led=0;


		
		/* �������� */
		keyPros();

		/* LCD��ʾ���� */
		if(flag_time&0x02) {
			flag_time &= ~0x02;	 // �����־λ
			LcdDisp(weight);
			delay_ms(5);
		}

		/* uart���ʹ��п����ݽ��� */		
		if(flag_time&0x04) {		// 1������һ�Σ�����һ������
			flag_time &= ~0x04;
			BTSend(DisBuf);	
			led=1;
		}

		/* uart���մ��п����ݽ��� */	
		BTRecv(buffer);

	}
}

