

#ifndef __KEY_H_
#define __KEY_H_

#include <reg51.h>


//#define	MATRIX_KEY // �������

// �������� �ѽӵ�
sbit K1 = P3^2;
sbit K2 = P3^3;
// ��
sbit LED1 = P1^1;
sbit LED2 = P1^2;

#ifdef	MATRIX_KEY	// �������
#define GPIO_KEY P2
#endif


// ��ʱ����
static void delayMs(unsigned char t);
// ��������
void keyPros(void);

#ifdef	MATRIX_KEY

// �ж��Ƿ��м����� �޼����·���0
unsigned char isKeyDown(void);
// ��ȡ��ֵ
unsigned char readKey(void);
// �������ɨ��
void keyScan(void);
// ���ؼ�ֵ����Ƹú���Ϊ�˽��
unsigned char getKeyValue(void);

#endif



#endif


