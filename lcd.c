 
/*
	FileName	: lcd.c
	Author		: Tkz
	Date		: 2021.02.5
*/

#include "lcd.h"


unsigned char code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ ����������


void ReadBusy(void)           //æ��⺯�����ж�bit7��0������ִ�У�1��ֹ
{
    unsigned char statu;      //
    LCD1602_DATAPINS = 0xff;
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do
    {
        LCD1602_EN = 1;
        statu = LCD1602_DATAPINS;
        LCD1602_EN = 0;    //ʹ�ܣ���������ͣ��ͷ�����
    }while(statu & 0x80);
}

void Lcd1602_Delay1ms(unsigned int c)   //��� 0us
{
    unsigned char a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	} 	
}

/* LCD1602д������ */
void LcdWriteCom(unsigned char com)	  //д������
{
	ReadBusy();
	LCD1602_EN = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��д������ ����/����ѡ���(H/L) 1/0
	LCD1602_RW = 0;	   //ѡ��д�� ��/дѡ���(H\L)     1/0
	
	LCD1602_DATAPINS = com;     //��������
	Lcd1602_Delay1ms(1);		//�ȴ������ȶ�

	LCD1602_EN = 1;	          //д��ʱ��
	Lcd1602_Delay1ms(5);	  //����ʱ��
	LCD1602_EN = 0;
}

/* LCD1602д������ */		   		   
void LcdWriteData(unsigned char dat)			//д������
{
	ReadBusy();
	LCD1602_EN = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;   //д��ʱ��
	Lcd1602_Delay1ms(5);   //����ʱ��
	LCD1602_EN = 0;
}
void delay_ms(unsigned char ms);
/* LCD1602��ʼ�� */	   
void Lcd1602Init(void)						  //LCD��ʼ���ӳ���
{
 	LcdWriteCom(0x38);  //����ʾ 5*8,8λ����
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	//LcdWriteCom(0x0f); // ��ʾ��겢��˸
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����

	//LcdWriteCom(0x80);
	LcdWriteStr(" Welcome To Use ");
	LcdWriteCom(0x80+0x40);
	LcdWriteStr("Electronic Scale");
	delay_ms(100);	
	LcdWriteCom(0x80);
	LcdWriteStr("value:          ");
	LcdWriteCom(0x80+0x40);
	LcdWriteStr("                ");
}

/* �������� */
void LcdSetCursor(unsigned char X,unsigned char Y){
	Y &= 0x1;
	X &= 0xF; //����X���ܴ���15��Y���ܴ���1
	if(Y) 
		X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
	X |= 0x80; //���ָ���� 
	LcdWriteCom(X);
}
 

/* ��ָ��λ����ʾ�ַ��� */
void LcdWriteStr(unsigned char * str){
	while(*str != '\0'){
		LcdWriteData(*str++);
	}	
}



