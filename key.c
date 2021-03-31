

#include "key.h"


// 延时函数
void delayMs(unsigned char t) {
    unsigned char a,b;
	for(; t>0; t--)
	{
		 for(b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	} 
}

#ifdef	MATRIX_KEY	   // 矩阵键盘

static unsigned char KeyValue = 0xFF;	//	用来存放读取到的键值 初始值为0xFF

// 判断是否有键按下 无键按下返回0
unsigned char isKeyDown(void) {
	unsigned char statu;
	GPIO_KEY = 0x0F;
	statu = GPIO_KEY & 0xF0;
	return statu;
}
// 读取键值
unsigned char readKey(void) {

	unsigned char key = 0xFF;	  // 设置键值初始值为 0xFF
	//	测试列 确定是哪一列被按下
	GPIO_KEY = 0X0F;
	switch(GPIO_KEY)
	{
		case 0X07:	key = 0; break;
		case 0X0B:	key = 1; break;
		case 0X0D:  key = 2; break;
		case 0X0E:	key = 3; break;
		default: break;
	}
	//	测试行 确定是哪一行被按下
	GPIO_KEY = 0XF0;
	switch(GPIO_KEY)
	{
		case 0X70:	key = key; break;
		case 0XB0:	key = key + 4; break;
		case 0XD0:  key = key + 8; break;
		case 0XE0:	key = key + 12; break;
		default: break;
	}
	return key;
}
// 键盘扫描
void keyScan(void)
{
	unsigned char i = 0;
	GPIO_KEY = 0x0F;   			// 全扫描码 0x0F 
	if((GPIO_KEY&0x0F) != 0x0F)	// 读取按键是否按下
	{
		delayMs(10);			// 延时10ms进行消抖
		if((GPIO_KEY&0x0F) != 0x0F)	// 再次检测键盘是否按下
		{	
			KeyValue = readKey();	 // 读取键值
			// 等待按下的键被释放
			while((i < 50) && (isKeyDown() != 0x00)) {			
				delayMs(10);
				i++;
			}
		}
	}
}
// 返回键值（设计该函数为了解耦）
unsigned char getKeyValue(void) {
	return KeyValue;	   
}
// 矩阵键盘处理
void keyPros(void) {

	keyScan();
	if(KeyValue == 0)
	{
		LED1 = 0;
	}
}

#else // 独立按键

void keyPros(void) {

	if((K1 == 0)||(K2 == 0)) {
		delayMs(10);
		if((K1 == 0)||(K2 == 0)) {
			if(K1 == 0)
			{
				LED1 =! LED1;
			}
			else if(K2 == 0)
			{
				LED2 =! LED2;
			}
			while(K1 == 0);
			while(K2 == 0);
		}
	}
}

#endif





