

#ifndef _UART_H_
#define _UART_H_

extern unsigned char flag_recv;		/* �������Ϊ1 */
extern unsigned char flag_send;		/* �������Ϊ1 */

/* ���ڳ�ʼ�� */
void uartInit(void);
/* ���ڷ���һ���ֽ� */
void uartSendChr(unsigned char chr);
/* ���ڷ����ַ��� */
void uartSendStr(unsigned char *str);


#endif
