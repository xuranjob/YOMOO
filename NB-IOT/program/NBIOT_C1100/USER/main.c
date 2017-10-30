 #include "main.h"  
 
/************************************************
NB-IOT C1100模块
TCP/IP测试
************************************************/


 int main(void)
 {	      
	delay_init();	    	                        //延时函数初始化	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	                        //串口初始化为115200
 	usmart_dev.init(72);		                    //初始化USMART		
 	LED_Init();		  		  	                    //初始化与LED连接的硬件接口
	usart3_init(115200);		                    //初始化串口3 
 	my_mem_init(SRAMIN);		                    //初始化内部内存池
	exfuns_init();				                    //为fatfs相关变量申请内存 
     
	sim800c_test();                               //GSM测试  
}


















