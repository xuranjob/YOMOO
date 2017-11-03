#include "relay.h"
/*********************************************************************************	 
*                              YOMOO---继电器远程控制器
*                                 控制器STM32ZET6                                         
*继电器驱动代码	   
*程序员@XURAN
*修改日期:2017/11/3
*版本：V1.0
*说明：
*      配置16路继电器IO口，初始高电平。
*      低电平常开，高电平断开。
*      测试函数，挨个设置高电平，测试继电器是否工作
********************************************************************************/ 	   
		    

void Relay_Init(void)                                                            //继电器IO初始化
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PF,PE,PG,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7;				 //端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					                         //根据设定参数初始化IO
 GPIO_ResetBits(GPIOE,GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7);						     //IO输出高
    
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO口速度为50MHz
 GPIO_Init(GPIOF, &GPIO_InitStructure);					                         //根据设定参数初始化IO
 GPIO_ResetBits(GPIOF,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //IO输出高  
    
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;				 //端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO口速度为50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					                         //根据设定参数初始化IO
 GPIO_ResetBits(GPIOG,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);						 //IO输出高 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				             //端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					                         //根据设定参数初始化IO
 GPIO_ResetBits(GPIOD,GPIO_Pin_6|GPIO_Pin_7);						                 //IO输出高  
}
 

void Relay_test(void)                                                            //继电器测试函数，隔一秒轮流设置一路继电器
{
  u8 i;
  while(1)
  {
      for(i=0;i<16;i++){
          switch(i){
              case 0: K1=1;break;                                                //开启K1继电器，下面以此类推
              case 1: K2=1;break;
              case 2: K3=1;break;
              case 3: K4=1;break;
              case 4: K5=1;break;
              case 5: K6=1;break;
              case 6: K7=1;break;
              case 7: K8=1;break;
              case 8: K9=1;break;
              case 9: K10=1;break;
              case 10: K11=1;break;
              case 11: K12=1;break;
              case 12: K13=1;break;
              case 13: K14=1;break;
              case 14: K15=1;break;
              case 15: K16=1;break;
              default: break;
          }
          delay_ms(800);
          GPIO_ResetBits(GPIOE,GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7);               //设置所有继电器低电平
          GPIO_ResetBits(GPIOF,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
          GPIO_ResetBits(GPIOG,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);
          GPIO_ResetBits(GPIOD,GPIO_Pin_6|GPIO_Pin_7);
      }
  }    
}


