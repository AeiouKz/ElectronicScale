


#ifndef __HX711_H_
#define __HX711_H_

#include <reg51.h>

/* PIN口定义 */
sbit HX711_SCK = P2^0;
sbit HX711_DOUT = P2^1;


/* 延时	*/
static void Delay_hx711_us(void);
/* 读取HX711 DOUT的数据	 增益128 */
unsigned long HX711_Read(void);  
/* 取AD平均值 */
unsigned long AD_average(unsigned char times); 
/* 校准 得到比例系数*/
void callibrate_scale(unsigned int weight, unsigned char times);
/* 得到实际值 */
float get_units(unsigned char times);
/* 获取实际零点偏移*/
float get_tare(void);
/* 设置HX711增益 */
void set_gain(unsigned char gain);
void tare(unsigned char times);
float get_tare(void);
void set_gain(unsigned char gain);



#endif
