

#include "app.h"

#include "HX711.h"
#include "lcd.h"
#include "uart.h"
#include "timer0.h"
#include "key.h"

#define  StandardValue   1600000			//质量基准值
		
/* AD采集零点偏移平均值 */
unsigned long AD_offset(void)
{	
	  unsigned char i = 5;
	  unsigned long offset = 0;
      for (i = 5; i > 0; i--) 
      {
        	offset = offset + HX711_Read();
      }
      offset = (unsigned long)(offset / 5);
	  return offset;
}
/*  */
unsigned int AD_Weight(unsigned long offset) {
	
	unsigned long ADvalue = 0;	

	ADvalue = AD_average(5) - offset;	 
	
	  
	if (ADvalue < 0)
	{
		ADvalue = 0;
	}		   
	//Weight_Shiwu = (unsigned int)((float)(Weight_Shiwu*10)/GapValue)-qupi;
	return (unsigned int)(ADvalue/100+0.5);
}







void changeDat(unsigned int value) {

	DisBuf[0] = value / 100000 % 10;  //高
	DisBuf[1] = value / 10000 % 10;
	DisBuf[2] = value / 1000 % 10;
	DisBuf[3] = value / 100 % 10;
	DisBuf[4] = value / 10 % 10;
	DisBuf[5] = value % 10;			  //低
}

unsigned char DisBuf[6] = {0};
/* 数据显示 */
void LcdDisp(unsigned int value) { 
	unsigned char i = 0;

	changeDat(value);

	LcdWriteCom(0x80+0x40);
	do{
		LcdWriteData('0'+DisBuf[i]);
		i++;
		if(i == 3) {
			//LcdWriteData('.');
		}
		 
	}while(i < 6);	
}

/* BT蓝牙发送数据 */
void BTSend(unsigned char *ptr) {

	unsigned char i = 0;

	uartSendStr(" >> The Value is: ");
	do{
		uartSendChr('0'+ptr[i++]);
	}while(i < 6);
	//uartSendStr("kg!");
}

unsigned char buffer[6]= {' '};
unsigned char cnt = 0; 
/* BT蓝牙接收数据 */ 
void BTRecv(unsigned char *ptr) {

	if(flag_recv && (!flag_send)) {			
		flag_recv = 0;	  		// 清除接收标志位

		ptr[cnt] = SBUF;	 	// 接收一个字节数据，保存到ptr
		LcdSetCursor(10,1);	   	// 设置显示坐标
		LcdWriteData(ptr[cnt]); // 显示在LCD1602
		cnt++;							 
		if(6 == cnt) {
			cnt = 0;
		}
	}
}





