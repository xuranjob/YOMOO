 #include "main.h"  
 
/************************************************
NB-IOT C1100ģ��
TCP/IP����
************************************************/


 int main(void)
 {	      
	delay_init();	    	                        //��ʱ������ʼ��	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	                        //���ڳ�ʼ��Ϊ115200
 	usmart_dev.init(72);		                    //��ʼ��USMART		
 	LED_Init();		  		  	                    //��ʼ����LED���ӵ�Ӳ���ӿ�
	usart3_init(115200);		                    //��ʼ������3 
 	my_mem_init(SRAMIN);		                    //��ʼ���ڲ��ڴ��
	exfuns_init();				                    //Ϊfatfs��ر��������ڴ� 
     
	sim800c_test();                               //GSM����  
}


















