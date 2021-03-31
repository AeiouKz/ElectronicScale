

#include "key.h"


// ��ʱ����
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

#ifdef	MATRIX_KEY	   // �������

static unsigned char KeyValue = 0xFF;	//	������Ŷ�ȡ���ļ�ֵ ��ʼֵΪ0xFF

// �ж��Ƿ��м����� �޼����·���0
unsigned char isKeyDown(void) {
	unsigned char statu;
	GPIO_KEY = 0x0F;
	statu = GPIO_KEY & 0xF0;
	return statu;
}
// ��ȡ��ֵ
unsigned char readKey(void) {

	unsigned char key = 0xFF;	  // ���ü�ֵ��ʼֵΪ 0xFF
	//	������ ȷ������һ�б�����
	GPIO_KEY = 0X0F;
	switch(GPIO_KEY)
	{
		case 0X07:	key = 0; break;
		case 0X0B:	key = 1; break;
		case 0X0D:  key = 2; break;
		case 0X0E:	key = 3; break;
		default: break;
	}
	//	������ ȷ������һ�б�����
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
// ����ɨ��
void keyScan(void)
{
	unsigned char i = 0;
	GPIO_KEY = 0x0F;   			// ȫɨ���� 0x0F 
	if((GPIO_KEY&0x0F) != 0x0F)	// ��ȡ�����Ƿ���
	{
		delayMs(10);			// ��ʱ10ms��������
		if((GPIO_KEY&0x0F) != 0x0F)	// �ٴμ������Ƿ���
		{	
			KeyValue = readKey();	 // ��ȡ��ֵ
			// �ȴ����µļ����ͷ�
			while((i < 50) && (isKeyDown() != 0x00)) {			
				delayMs(10);
				i++;
			}
		}
	}
}
// ���ؼ�ֵ����Ƹú���Ϊ�˽��
unsigned char getKeyValue(void) {
	return KeyValue;	   
}
// ������̴���
void keyPros(void) {

	keyScan();
	if(KeyValue == 0)
	{
		LED1 = 0;
	}
}

#else // ��������

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





