#include "common.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ATK-ESP8266 WIFIģ�� WIFI STA��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2015/4/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//ATK-ESP8266 WIFI STA����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������
u8 netpro=1;	//����ģʽ
u8 atk_8266_wifista_test(void)
{
	u8 ipbuf[16]; 	//IP����
	u8 *p;
	u16 t=999;		//���ٵ�һ�λ�ȡ����״̬
	u8 res=0;
	u16 rlen=0;
	u8 constate=0;	//����״̬
	p=mymalloc(SRAMIN,32);							//����32�ֽ��ڴ�
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);		//����WIFI STAģʽ
	atk_8266_send_cmd("AT+RST","OK",20);		//DHCP�������ر�(��APģʽ��Ч) 
	delay_ms(1000);         //��ʱ3S�ȴ������ɹ�
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
    delay_ms(1000);
	//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//�������߲���:ssid,����
	while(atk_8266_send_cmd(p,"WIFI GOT IP",300));					//����Ŀ��·����,���һ��IP
    
	if(netpro&0X02)   //UDP
	{ 
				printf("��������ATK-ESPģ��,���Ե�...\r\n");
				sprintf((char*)p,"AT+CIPSTART=\"UDP\",\"%s\",%s",(u8*)ipaddr,(u8*)portnum);    //����Ŀ��UDP������
				delay_ms(200);
				atk_8266_send_cmd("AT+CIPMUX=0","OK",20);  //������ģʽ
				delay_ms(200);
				while(atk_8266_send_cmd(p,"OK",500));
	}
	else     //TCP
	{
		if(netpro&0X01)     //TCP Client    ͸��ģʽ����
		{
			printf("��������ATK-ESPģ��,���Ե�...\r\n");
			atk_8266_send_cmd("AT+CIPMUX=0","OK",20);   //0�������ӣ�1��������
			sprintf((char*)p,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)ipaddr,(u8*)portnum);    //����Ŀ��TCP������
			while(atk_8266_send_cmd(p,"OK",200))
			{
			   printf("ATK-ESP ����TCP Serverʧ��"); //����ʧ��	
			}	
			atk_8266_send_cmd("AT+CIPMODE=1","OK",200);      //����ģʽΪ��͸��			
		}
		else					//TCP Server
		{
            printf("��������ATK-ESPģ��,���Ե�...\r\n");
			atk_8266_send_cmd("AT+CIPMUX=1","OK",20);   //0�������ӣ�1��������
			sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)serverportnum);    //����Serverģʽ(0���رգ�1����)���˿ں�Ϊportnum
			atk_8266_send_cmd(p,"OK",50);    
		}
	}   
    atk_8266_get_wanip(ipbuf);//������ģʽ,��ȡWAN IP
    sprintf((char*)p,"������IP��ַ:%s �˿�:%s",ipbuf,(u8*)serverportnum);
    printf("%s\r\n",p);				//��ʾIP��ַ�Ͷ˿�	
    USART3_RX_STA=0;
    delay_ms(1000);
    while(1)
    {
        if(t==0)
        {    
            atk_8266_quit_trans();                           //�˳�͸��ģʽ
            atk_8266_send_cmd("AT+CIPSEND","OK",20);         //��ʼ͸�� 
            delay_ms(500);
            sprintf((char*)p,"ATK-8266%s����%d\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],t);//��������
            u3_printf("%s",p);
            USART3_RX_STA=0;
        }
        t++;
        delay_ms(10);
        if(USART3_RX_STA&0X8000)		//���յ�һ��������
        { 
            rlen=USART3_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
            USART3_RX_BUF[rlen]=0;		//��ӽ����� 
            printf("�յ�%d�ֽ�,��������\r\n",rlen);//���յ����ֽ��� 
            printf("%s\r\n",USART3_RX_BUF);	//���͵�����   
            USART3_RX_STA=0;
            if(constate!='+')t=1000;		//״̬Ϊ��δ����,������������״̬
            else t=0;                   //״̬Ϊ�Ѿ�������,10����ټ��
        }  
        if(t==1000)//����10����û���յ��κ�����,��������ǲ��ǻ�����.
        {
            constate=atk_8266_consta_check();//�õ�����״̬
            if(constate=='+')printf("���ӳɹ�\r\n");  //����״̬
            else printf("����ʧ��....\r\n"); 	 
            t=0;
        }
        //atk_8266_at_response(1);
    }
	myfree(SRAMIN,p);		//�ͷ��ڴ� 
	return res;		
} 




























