
#ifndef __APP_H_
#define __APP_H_

#include <reg51.h>


extern unsigned char DisBuf[6];
extern unsigned char buffer[6];
	


/* AD采集零点偏移平均值 */
unsigned long AD_offset(void);
/* AD weight */
unsigned int AD_Weight(unsigned long offset);


/* 数据显示 */
void LcdDisp(unsigned int weight);

/* BT蓝牙发送数据 */
void BTSend(unsigned char *ptr);
/* BT蓝牙接收数据 */ 
void BTRecv(unsigned char *ptr);


#endif
