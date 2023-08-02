#include"dht11.h"
#include "stm32f10x.h"

 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 GPIO_InitTypeDef GPIO_InitStructure;

 void TIM2_Init(void)
 {
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能TIM2时钟
	 TIM_TimeBaseStructure.TIM_Period = 0xFFFF; //设置计数器自动重装值
	 TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 1000000 - 1; //设置预分频值，定时器时钟为1MHz
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分频
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //设置计数器为向上计数模式
	 TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化TIM2
 }
 
 void Delay_us(__IO uint32_t nCount)
 {
	 TIM_SetCounter(TIM2, 0); //将计数器清零
	 TIM_Cmd(TIM2, ENABLE); //使能TIM2
	 while (TIM_GetCounter(TIM2) < nCount); //等待计数器达到设定值
	 TIM_Cmd(TIM2, DISABLE); //关闭TIM2
 }
 
 void DHT11_Start(void)
 {
	 GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; //将DHT11所在引脚设置为输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
	 GPIO_WriteBit(DHT11_PORT, DHT11_PIN, Bit_RESET); //将DHT11引脚拉低至少18ms
	 Delay_us(18000);
	 GPIO_WriteBit(DHT11_PORT, DHT11_PIN, Bit_SET); //将DHT11引脚拉高20~40us
	 Delay_us(30);
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //将DHT11所在引脚设置为输入
	 GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
 }
 
 uint8_t DHT11_Check(void)
 {
	 uint8_t response = 0;
	 Delay_us(40);
	 if(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == Bit_RESET) //DHT11响应信号为低电平，检测引脚电平是否为低电平
	 {
		 Delay_us(80);
		 if(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == Bit_SET) //DHT11响应信号为高电平，检测引脚电平是否为高电平
		 {
 Delay_us(80);
			 if(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == Bit_RESET) //DHT11响应信号为低电平，检测引脚电平是否为低电平
			 {
				 response = 1; //DHT11正常响应
			 }
		 }
	 }
	 while(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == Bit_RESET); //等待DHT11响应信号结束
	 return response;
 }
 
 uint8_t DHT11_Read_Bit(void)
 {
	 uint8_t response = 0;
	 while(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == Bit_RESET); //等待DHT11发送数据
	 Delay_us(40);
	 if(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == Bit_SET) //DHT11发送1的信号为高电平，检测引脚电平是否为高电平
	 {
		 response = 1;
	 }
	 while(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == Bit_SET); //等待DHT11发送数据结束
	 return response;
 }
 
 uint8_t DHT11_Read_Byte(void)
 {
	 uint8_t i, byte = 0;
	 for(i =0; i < 8; i++)
	 {
		 byte |= (DHT11_Read_Bit() << (7 - i)); //将读取到的8位数据组合成一个字节
	 }
	 return byte;
 }
 
 void DHT11_Read_Data1(uint8_t *temp, uint8_t *humi)
 {
	 uint8_t data[5], i;
	 for(i = 0; i < 5; i++)
	 {
		 data[i] = DHT11_Read_Byte(); //读取5个字节的数据
	 }
	 *humi = data[0]; //湿度值为第1个字节
	 *temp = data[2]; //温度值为第3个字节
 }
