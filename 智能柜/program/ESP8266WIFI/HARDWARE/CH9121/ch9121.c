#include "ch9121.h"
/*********************************************************************************	 
*                              YOMOO---�̵���Զ�̿�����
*                                 ������STM32ZET6                                         
*CH9121��������	   
*����Ա@XURAN
*�޸�����:2017/11/3
*�汾��V1.0
*˵����
*      
*      
*      
********************************************************************************/ 	

void ch9121_Init(void)                                   //CH9121��ʼ��
{
    
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PF,PE,PG,PD�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;	 //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);				 //�����趨������ʼ��IO
  GPIO_SetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_4);			 //IO�����  
    
}



