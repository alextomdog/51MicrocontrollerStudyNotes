#include <REGX52.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void I2C_Start(void)
{
    // 默认开始时候，数据和时钟都被拉高处于高电平状态
    I2C_SDA=1;
    I2C_SCL=1;
    
    // 数据先拉低，时钟然后再拉低
    I2C_SDA=0;
    I2C_SCL=0;
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void I2C_Stop(void)
{
    // 先将数据线拉低，确保有一个拉高的优先级顺序
    I2C_SDA=0;
    
    // 时钟先拉高，数据再拉高
    I2C_SCL=1;
    I2C_SDA=1;
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的字节
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        // 设置数据线数据
        I2C_SDA=Byte&(0x80>>i);
        
        // 时钟线起始阶段处于低电平
        // 所以先拉高电平，再拉低电平，模拟一个高电平时钟信号
        I2C_SCL=1;
        I2C_SCL=0;
    }
}

/**
  * @brief  I2C接收一个字节
  * @param  无
  * @retval 接收到的一个字节数据
  */
unsigned char I2C_ReceiveByte(void)
{
    unsigned char i,Byte=0x00;
    I2C_SDA=1;
    for(i=0;i<8;i++)
    {
        // 接收数据应在时钟信号处于高电平期间进行接收
        I2C_SCL=1;
        if(I2C_SDA){Byte|=(0x80>>i);}
        I2C_SCL=0;
    }
    return Byte;
}

/**
  * @brief  I2C发送应答
  * @param  AckBit 应答位，0为应答，1为非应答
  * @retval 无
  */
void I2C_SendAck(unsigned char AckBit)
{
    // 起始条件：时钟信号处于低电平
    I2C_SDA=AckBit;
    // 保证时钟信号高电平期间，数据线中的数据已经准备到位
    I2C_SCL=1;
    I2C_SCL=0;
}

/**
  * @brief  I2C接收应答位
  * @param  无
  * @retval 接收到的应答位，0为应答，1为非应答
  */
unsigned char I2C_ReceiveAck(void)
{
    unsigned char AckBit;
    
    // 先将数据线拉高，确保ack信号来源于从机
    // 此时数据线拉低智能由从机来实现
    I2C_SDA=1;
    
    // 拉高时钟信号，拉高后将数据保留下来，然后拉低时钟
    I2C_SCL=1;
    AckBit=I2C_SDA;
    I2C_SCL=0;
    // 保存到的信号就是由从机发出的
    
    return AckBit;
}