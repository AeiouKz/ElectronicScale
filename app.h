
#ifndef __APP_H_
#define __APP_H_

#include <reg51.h>


extern unsigned char DisBuf[6];
extern unsigned char buffer[6];
	


/* AD�ɼ����ƫ��ƽ��ֵ */
unsigned long AD_offset(void);
/* AD weight */
unsigned int AD_Weight(unsigned long offset);


/* ������ʾ */
void LcdDisp(unsigned int weight);

/* BT������������ */
void BTSend(unsigned char *ptr);
/* BT������������ */ 
void BTRecv(unsigned char *ptr);


#endif
