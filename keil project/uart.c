#include <REGX52.H>

/**
 * @brief  串口初始化，4800bps@12.000MHz
 * @param  无
 * @retval 无
 */
void UART_Init()
{
	SCON = 0x50;  // 0101 0000
	PCON |= 0x80; // 1000 0000
	TMOD &= 0x0F; // 0000 1111，清除定时器模式位
	TMOD |= 0x20; // 0010 0000，设置定时器模式
	TL1 = 0xF3;	  // 设定定时初值
	TH1 = 0xF3;	  // 设定定时器重装值
	ET1 = 0;	  // 禁止定时器1中断
	TR1 = 1;	  // 启动定时器1
	EA = 1;		  // 允许总中断
	ES = 1;		  // 允许串口中断
}

/**
 * @brief  串口发送一个字节数据
 * @param  Byte 要发送的一个字节数据
 * @retval 无
 */
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while (TI == 0)
		;
	TI = 0;
}

/* 串口中断函数模板
void UART_Routine() interrupt 4
{
	if (RI == 1)
	{
		RI = 0; // 处理接收中断标志，可以读取接收到的数据
	}
}
*/
