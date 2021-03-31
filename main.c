

#include <reg51.h>

#include "app.h"	
#include "lcd.h"	
#include "uart.h"	
#include "HX711.h"	
#include "timer0.h"	
#include "key.h"

sbit led = P1^3;		
/* 主函数入口 */
void main(void) {
	unsigned char i = 0;
	unsigned int weight;
	unsigned long refAD;

	P0 = P1 = P2 = P3 = 0xFF;

	Lcd1602Init();	/* LCD初始化 */
	uartInit();		/* UART初始化*/
	timer0Init();	/* Timer0初始化 */	
	EA = 1;			/* 总中断允许 */
				

	refAD = AD_average(10);


	/* 程序不断运行中 */
	while(1) {

		refAD = AD_average(5);	
		weight = (unsigned int)(refAD/100+0.5);	
		led=0;


		
		/* 按键处理 */
		keyPros();

		/* LCD显示进程 */
		if(flag_time&0x02) {
			flag_time &= ~0x02;	 // 清除标志位
			LcdDisp(weight);
			delay_ms(5);
		}

		/* uart发送串行口数据进程 */		
		if(flag_time&0x04) {		// 1秒钟闪一次，发送一次数据
			flag_time &= ~0x04;
			BTSend(DisBuf);	
			led=1;
		}

		/* uart接收串行口数据进程 */	
		BTRecv(buffer);

	}
}

