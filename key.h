

#ifndef __KEY_H_
#define __KEY_H_

#include <reg51.h>


//#define	MATRIX_KEY // 矩阵键盘

// 独立按键 已接地
sbit K1 = P3^2;
sbit K2 = P3^3;
// 灯
sbit LED1 = P1^1;
sbit LED2 = P1^2;

#ifdef	MATRIX_KEY	// 矩阵键盘
#define GPIO_KEY P2
#endif


// 延时函数
static void delayMs(unsigned char t);
// 按键处理
void keyPros(void);

#ifdef	MATRIX_KEY

// 判断是否有键按下 无键按下返回0
unsigned char isKeyDown(void);
// 读取键值
unsigned char readKey(void);
// 矩阵键盘扫描
void keyScan(void);
// 返回键值（设计该函数为了解耦）
unsigned char getKeyValue(void);

#endif



#endif


