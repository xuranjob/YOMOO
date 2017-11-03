#include "relay.h"
/*********************************************************************************	 
*                              YOMOO---�̵���Զ�̿�����
*                                 ������STM32ZET6                                         
*�̵�����������	   
*����Ա@XURAN
*�޸�����:2017/11/3
*�汾��V1.0
*˵����
*      ����16·�̵���IO�ڣ���ʼ�ߵ�ƽ��
*      �͵�ƽ�������ߵ�ƽ�Ͽ���
*      ���Ժ������������øߵ�ƽ�����Լ̵����Ƿ���
********************************************************************************/ 	   
		    

void Relay_Init(void)                                                            //�̵���IO��ʼ��
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PF,PE,PG,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7;				 //�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					                         //�����趨������ʼ��IO
 GPIO_ResetBits(GPIOE,GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7);						     //IO�����
    
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOF, &GPIO_InitStructure);					                         //�����趨������ʼ��IO
 GPIO_ResetBits(GPIOF,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //IO�����  
    
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;				 //�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					                         //�����趨������ʼ��IO
 GPIO_ResetBits(GPIOG,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);						 //IO����� 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				             //�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					                         //�����趨������ʼ��IO
 GPIO_ResetBits(GPIOD,GPIO_Pin_6|GPIO_Pin_7);						                 //IO�����  
}
 

void Relay_test(void)                                                            //�̵������Ժ�������һ����������һ·�̵���
{
  u8 i;
  while(1)
  {
      for(i=0;i<16;i++){
          switch(i){
              case 0: K1=1;break;                                                //����K1�̵����������Դ�����
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
          GPIO_ResetBits(GPIOE,GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7);               //�������м̵����͵�ƽ
          GPIO_ResetBits(GPIOF,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
          GPIO_ResetBits(GPIOG,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);
          GPIO_ResetBits(GPIOD,GPIO_Pin_6|GPIO_Pin_7);
      }
  }    
}


