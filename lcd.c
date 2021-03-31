 
/*
	FileName	: lcd.c
	Author		: Tkz
	Date		: 2021.02.5
*/

#include "lcd.h"


unsigned char code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值 （共阴极）


void ReadBusy(void)           //忙检测函数，判断bit7是0，允许执行；1禁止
{
    unsigned char statu;      //
    LCD1602_DATAPINS = 0xff;
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do
    {
        LCD1602_EN = 1;
        statu = LCD1602_DATAPINS;
        LCD1602_EN = 0;    //使能，用完就拉低，释放总线
    }while(statu & 0x80);
}

void Lcd1602_Delay1ms(unsigned int c)   //误差 0us
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

/* LCD1602写入命令 */
void LcdWriteCom(unsigned char com)	  //写入命令
{
	ReadBusy();
	LCD1602_EN = 0;     //使能
	LCD1602_RS = 0;	   //选择写入命令 数据/命令选择端(H/L) 1/0
	LCD1602_RW = 0;	   //选择写入 读/写选择端(H\L)     1/0
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_EN = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_EN = 0;
}

/* LCD1602写入数据 */		   		   
void LcdWriteData(unsigned char dat)			//写入数据
{
	ReadBusy();
	LCD1602_EN = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_EN = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_EN = 0;
}
void delay_ms(unsigned char ms);
/* LCD1602初始化 */	   
void Lcd1602Init(void)						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示 5*8,8位数据
	LcdWriteCom(0x0c);  //开显示不显示光标
	//LcdWriteCom(0x0f); // 显示光标并闪烁
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点

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

/* 设置坐标 */
void LcdSetCursor(unsigned char X,unsigned char Y){
	Y &= 0x1;
	X &= 0xF; //限制X不能大于15，Y不能大于1
	if(Y) 
		X |= 0x40; //当要显示第二行时地址码+0x40;
	X |= 0x80; //算出指令码 
	LcdWriteCom(X);
}
 

/* 按指定位置显示字符串 */
void LcdWriteStr(unsigned char * str){
	while(*str != '\0'){
		LcdWriteData(*str++);
	}	
}



