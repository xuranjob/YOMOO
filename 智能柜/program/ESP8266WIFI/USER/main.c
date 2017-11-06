#include "main.h"
/************************************************
 ALIENTEK STM32F103开发板 扩展实验5
 ATK-RM04 WIFI模块测试实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
 
 //usmart_config.c 注释了WiFi函数 需要更改回来
************************************************/

 int main(void)
 {	 
	delay_init();	    	 //延时函数初始化	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	usmart_dev.init(72);		//初始化USMART		
 	Relay_Init();               //继电器IO初始化
    ch9121_Init();              //CH9121初始化
	usart3_init(115200);		//初始化串口3 
 	my_mem_init(SRAMIN);		//初始化内部内存池

 //   GPIO_ResetBits(GPIOD,GPIO_Pin_3);
//    Relay_test();
    atk_8266_test();
}


















