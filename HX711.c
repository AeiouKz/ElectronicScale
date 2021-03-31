
#include <intrins.h>   // _nop()_
#include "HX711.h"


unsigned char	_gain	=	128;     // default channel A
long			_offset	=	0;		 // 零点偏移
float			_scale	=	1;		 // 比例系数


// 延时
void Delay_hx711_us(void){
	_nop_();
	_nop_();
}

// 读取HX711 DOUT数据
unsigned long HX711_Read(void)
{
	unsigned long dat;
	unsigned char i;
	unsigned char m = 1;   // default gain == 128

	HX711_DOUT = 1;	   // DOUT置1
	Delay_hx711_us();
	Delay_hx711_us();	
	HX711_SCK = 0;	   // SCK置0
	dat = 0;

	// 等待HX711_DOUT下降沿到来
	while(HX711_DOUT && i<50);	 // AD转换未结束则等待 否则开始读取数据
	{
		Delay_hx711_us();
		i++;
	}
	// 发送24个脉冲，读取24位数据
	for(i = 0;i < 24;i++)	
	{
		HX711_SCK = 1;	   // SCK置1 发送一个脉冲 读取一位数据
		_nop_();
		_nop_();
		dat = dat << 1;	 // 下降沿来时dat变量左移一位 右侧补零
		HX711_SCK = 0;
		if(HX711_DOUT)	// DOUT为高电平 count+1
			dat++;
	}
	
  	if(_gain == 64) m = 3;
  	if(_gain == 32) m = 2;

	while(m > 0) {
		// 第25个脉冲 增益为128
		HX711_SCK = 1;
		/* 把采集到的值与0x800000进行“异或”运算 
		   HX711直接取出来的数值，是
		   以补码的形式出现的，并且是有符号的值 */
		dat = dat ^ 0x800000;  /* 下降沿来时 转换数据	*/
		Delay_hx711_us();
		HX711_SCK = 0;
		m--;
	}
	return(dat);
}
/* 取平均值 multiple raw reads */
unsigned long AD_average(unsigned char times) {
	
	unsigned long sum = 0;
	unsigned char i = 0;
	for(i = times; i > 0; i--) 
	{
		sum += HX711_Read();
	}
	return (unsigned long)(sum / times);
}

/* 校准 得到比例系数*/
void callibrate_scale(unsigned int weight, unsigned char times) {

	_scale = (1.0 * weight) / (AD_average(times) - _offset);
}
/* 得到实际值 */
float get_units(unsigned char times) {

	float units;
	units =  (AD_average(times) - _offset) * _scale;
	return units;
}
// TARE 设置零点偏移AD
/* call tare to calibrate zero */
void tare(unsigned char times) { 

	_offset = AD_average(times); 
}
/* 获取实际零点偏移*/
float get_tare(void) { 

	return -_offset * _scale; 
}
/* 设置HX711增益 */
void set_gain(unsigned char gain) { 

	_gain = gain; 
}

