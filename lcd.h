
/*
 *	FileName	: lcd.h
 *	Author		: Tkz
 *	Date		: 2021.02.5
 */

#ifndef __LCD_H_
#define __LCD_H_

#include <reg51.h>

/* PIN口定义 */
#define LCD1602_DATAPINS P0
sbit LCD1602_EN = P2^7;
sbit LCD1602_RW = P2^5;
sbit LCD1602_RS = P2^6;



/* 忙检测函数，判断bit7是0，允许执行；1 禁止  */
static void ReadBusy(void);
/* ms时延 */          
static void Lcd1602_Delay1ms(unsigned int c);
/* LCD1602写入8位命令子函数 */
void LcdWriteCom(unsigned char com);
/* LCD1602写入8位数据子函数 */	
void LcdWriteData(unsigned char dat);
/* LCD1602初始化子程序 */		
void Lcd1602Init(void);	
	
/* 设置坐标	 */
void LcdSetCursor(unsigned char X,unsigned char Y);  		  
/* LCD1602显示字符串 */
void LcdWriteStr(unsigned char * str);

		
#endif
