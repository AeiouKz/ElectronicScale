
/*
 *	FileName	: lcd.h
 *	Author		: Tkz
 *	Date		: 2021.02.5
 */

#ifndef __LCD_H_
#define __LCD_H_

#include <reg51.h>

/* PIN�ڶ��� */
#define LCD1602_DATAPINS P0
sbit LCD1602_EN = P2^7;
sbit LCD1602_RW = P2^5;
sbit LCD1602_RS = P2^6;



/* æ��⺯�����ж�bit7��0������ִ�У�1 ��ֹ  */
static void ReadBusy(void);
/* msʱ�� */          
static void Lcd1602_Delay1ms(unsigned int c);
/* LCD1602д��8λ�����Ӻ��� */
void LcdWriteCom(unsigned char com);
/* LCD1602д��8λ�����Ӻ��� */	
void LcdWriteData(unsigned char dat);
/* LCD1602��ʼ���ӳ��� */		
void Lcd1602Init(void);	
	
/* ��������	 */
void LcdSetCursor(unsigned char X,unsigned char Y);  		  
/* LCD1602��ʾ�ַ��� */
void LcdWriteStr(unsigned char * str);

		
#endif
