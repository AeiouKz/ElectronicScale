


#ifndef __HX711_H_
#define __HX711_H_

#include <reg51.h>

/* PIN�ڶ��� */
sbit HX711_SCK = P2^0;
sbit HX711_DOUT = P2^1;


/* ��ʱ	*/
static void Delay_hx711_us(void);
/* ��ȡHX711 DOUT������	 ����128 */
unsigned long HX711_Read(void);  
/* ȡADƽ��ֵ */
unsigned long AD_average(unsigned char times); 
/* У׼ �õ�����ϵ��*/
void callibrate_scale(unsigned int weight, unsigned char times);
/* �õ�ʵ��ֵ */
float get_units(unsigned char times);
/* ��ȡʵ�����ƫ��*/
float get_tare(void);
/* ����HX711���� */
void set_gain(unsigned char gain);
void tare(unsigned char times);
float get_tare(void);
void set_gain(unsigned char gain);



#endif
