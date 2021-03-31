
#include <intrins.h>   // _nop()_
#include "HX711.h"


unsigned char	_gain	=	128;     // default channel A
long			_offset	=	0;		 // ���ƫ��
float			_scale	=	1;		 // ����ϵ��


// ��ʱ
void Delay_hx711_us(void){
	_nop_();
	_nop_();
}

// ��ȡHX711 DOUT����
unsigned long HX711_Read(void)
{
	unsigned long dat;
	unsigned char i;
	unsigned char m = 1;   // default gain == 128

	HX711_DOUT = 1;	   // DOUT��1
	Delay_hx711_us();
	Delay_hx711_us();	
	HX711_SCK = 0;	   // SCK��0
	dat = 0;

	// �ȴ�HX711_DOUT�½��ص���
	while(HX711_DOUT && i<50);	 // ADת��δ������ȴ� ����ʼ��ȡ����
	{
		Delay_hx711_us();
		i++;
	}
	// ����24�����壬��ȡ24λ����
	for(i = 0;i < 24;i++)	
	{
		HX711_SCK = 1;	   // SCK��1 ����һ������ ��ȡһλ����
		_nop_();
		_nop_();
		dat = dat << 1;	 // �½�����ʱdat��������һλ �Ҳಹ��
		HX711_SCK = 0;
		if(HX711_DOUT)	// DOUTΪ�ߵ�ƽ count+1
			dat++;
	}
	
  	if(_gain == 64) m = 3;
  	if(_gain == 32) m = 2;

	while(m > 0) {
		// ��25������ ����Ϊ128
		HX711_SCK = 1;
		/* �Ѳɼ�����ֵ��0x800000���С�������� 
		   HX711ֱ��ȡ��������ֵ����
		   �Բ������ʽ���ֵģ��������з��ŵ�ֵ */
		dat = dat ^ 0x800000;  /* �½�����ʱ ת������	*/
		Delay_hx711_us();
		HX711_SCK = 0;
		m--;
	}
	return(dat);
}
/* ȡƽ��ֵ multiple raw reads */
unsigned long AD_average(unsigned char times) {
	
	unsigned long sum = 0;
	unsigned char i = 0;
	for(i = times; i > 0; i--) 
	{
		sum += HX711_Read();
	}
	return (unsigned long)(sum / times);
}

/* У׼ �õ�����ϵ��*/
void callibrate_scale(unsigned int weight, unsigned char times) {

	_scale = (1.0 * weight) / (AD_average(times) - _offset);
}
/* �õ�ʵ��ֵ */
float get_units(unsigned char times) {

	float units;
	units =  (AD_average(times) - _offset) * _scale;
	return units;
}
// TARE �������ƫ��AD
/* call tare to calibrate zero */
void tare(unsigned char times) { 

	_offset = AD_average(times); 
}
/* ��ȡʵ�����ƫ��*/
float get_tare(void) { 

	return -_offset * _scale; 
}
/* ����HX711���� */
void set_gain(unsigned char gain) { 

	_gain = gain; 
}

