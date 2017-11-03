#include "ch9121.h"
/*********************************************************************************	 
*                              YOMOO---继电器远程控制器
*                                 控制器STM32ZET6                                         
*CH9121驱动代码	   
*程序员@XURAN
*修改日期:2017/11/3
*版本：V1.0
*说明：
*      
*      
*      
********************************************************************************/ 	

void ch9121_Init(void)                                   //CH9121初始化
{
    
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PF,PE,PG,PD端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;	 //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);				 //根据设定参数初始化IO
  GPIO_SetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_4);			 //IO输出高  
    
}



