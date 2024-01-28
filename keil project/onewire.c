#include <REGX52.H>

// 引脚定义
sbit OneWire_DQ = P1^7;

/**
  * @brief  单总线初始化
  * @param  无
  * @retval 从机响应位，0为响应，1为未响应
  */
unsigned char OneWire_Init(void)
{
    unsigned char i;
    unsigned char AckBit;
    
    // 拉低总线，产生复位脉冲
    OneWire_DQ = 1;
    OneWire_DQ = 0;
    i = 247; while (--i);       // Delay 500us
    OneWire_DQ = 1;
    i = 32; while (--i);        // Delay 70us
    AckBit = OneWire_DQ;
    i = 247; while (--i);       // Delay 500us
    return AckBit;
}

/**
  * @brief  单总线发送一位
  * @param  Bit 要发送的位
  * @retval 无
  */
void OneWire_SendBit(unsigned char Bit)
{
    unsigned char i;
    
    // 拉低总线，发送数据位
    OneWire_DQ = 0;
    i = 4; while (--i);         // Delay 10us
    OneWire_DQ = Bit;
    i = 24; while (--i);        // Delay 50us
    OneWire_DQ = 1;
}

/**
  * @brief  单总线接收一位
  * @param  无
  * @retval 读取的位
  */
unsigned char OneWire_ReceiveBit(void)
{
    unsigned char i;
    unsigned char Bit;
    
    // 拉低总线，准备接收数据位
    OneWire_DQ = 0;
    i = 2; while (--i);         // Delay 5us
    OneWire_DQ = 1;
    i = 2; while (--i);         // Delay 5us
    Bit = OneWire_DQ;
    i = 24; while (--i);        // Delay 50us
    return Bit;
}

/**
  * @brief  单总线发送一个字节
  * @param  Byte 要发送的字节
  * @retval 无
  */
void OneWire_SendByte(unsigned char Byte)
{
    unsigned char i;
    
    // 逐位发送字节数据
    for(i = 0; i < 8; i++)
    {
        OneWire_SendBit(Byte & (0x01 << i));
    }
}

/**
  * @brief  单总线接收一个字节
  * @param  无
  * @retval 接收的一个字节
  */
unsigned char OneWire_ReceiveByte(void)
{
    unsigned char i;
    unsigned char Byte = 0x00;
    
    // 逐位接收字节数据
    for(i = 0; i < 8; i++)
    {
		
        if(OneWire_ReceiveBit()) { Byte |= (0x01 << i); }
    }
    return Byte;
}
