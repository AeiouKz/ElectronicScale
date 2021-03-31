

#ifndef _UART_H_
#define _UART_H_

extern unsigned char flag_recv;		/* 接收完成为1 */
extern unsigned char flag_send;		/* 发送完成为1 */

/* 串口初始化 */
void uartInit(void);
/* 串口发送一个字节 */
void uartSendChr(unsigned char chr);
/* 串口发送字符串 */
void uartSendStr(unsigned char *str);


#endif
