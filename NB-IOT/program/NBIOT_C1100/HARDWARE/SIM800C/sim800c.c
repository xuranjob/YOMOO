#include "sim800c.h"
//////////////////////////////////////////////////////////////////////////////////	   
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103������ 
//ATK-SIM800C GSM/GPRSģ������	  
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/4/1
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//******************************************************************************** 
//��
 	
u8 Scan_Wtime = 0;//��������ɨ����Ҫ��ʱ��
u8 BT_Scan_mode=0;//����ɨ���豸ģʽ��־

//usmart֧�ֲ���
//���յ���ATָ��Ӧ�����ݷ��ظ����Դ���
//mode:0,������USART2_RX_STA;
//     1,����USART2_RX_STA;
void sim_at_response(u8 mode)
{
	if(USART2_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//��ӽ�����
		printf("%s",USART2_RX_BUF);	//���͵�����
		if(mode)USART2_RX_STA=0;
	} 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//ATK-SIM800C �������(���Ų��ԡ����Ų��ԡ�GPRS����,��������)���ô���

//SIM800C���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//����,�ڴ�Ӧ������λ��(str��λ��)
u8* sim800c_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART2_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//��ӽ�����
		strx=strstr((const char*)USART2_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}
//SIM800C��������
//cmd:���͵������ַ���(����Ҫ��ӻس���),��cmd<0XFF��ʱ��,��������(���緢��0X1A),���ڵ�ʱ�����ַ���.
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
u8 sim800c_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART2_RX_STA=0;
	if((u32)cmd<=0XFF)
	{
		while((USART2->SR&0X40)==0);//�ȴ���һ�����ݷ������  
		USART2->DR=(u32)cmd;
	}else u2_printf("%s\r\n",cmd);//��������
	
	 if(waittime==1100)//11s����ش�������(���������õ�)
	 {
		 Scan_Wtime = 11;//��Ҫ��ʱ��ʱ��
		 TIM2_SetARR(9999);//����1S��ʱ�ж�
		 
	 }
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{ 
			delay_ms(10);
			if(USART2_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(sim800c_check_cmd(ack))break;//�õ���Ч���� 
				USART2_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 
//����SIM800C�������ݣ���������ģʽ��ʹ�ã�
//request:�ڴ����������ַ���
//waittimg:�ȴ�ʱ��(��λ��10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
u8 sim800c_wait_request(u8 *request ,u16 waittime)
{
	 u8 res = 1;
	 if(request && waittime)
	 {
	    while(--waittime)
		{   
		   delay_ms(10);
		   if(USART2_RX_STA &0x8000)//���յ��ڴ���Ӧ����
		   {
				if(sim800c_check_cmd(request)) break;//�õ���Ч����
				USART2_RX_STA=0;
		   }
		}
		if(waittime==0)res=0;
	 }
	 return res;
}

//��1���ַ�ת��Ϊ16��������
//chr:�ַ�,0~9/A~F/a~F
//����ֵ:chr��Ӧ��16������ֵ
u8 sim800c_chr2hex(u8 chr)
{
	if(chr>='0'&&chr<='9')return chr-'0';
	if(chr>='A'&&chr<='F')return (chr-'A'+10);
	if(chr>='a'&&chr<='f')return (chr-'a'+10); 
	return 0;
}
//��1��16��������ת��Ϊ�ַ�
//hex:16��������,0~15;
//����ֵ:�ַ�
u8 sim800c_hex2chr(u8 hex)
{
	if(hex<=9)return hex+'0';
	if(hex>=10&&hex<=15)return (hex-10+'A'); 
	return '0';
}

//SIM800C�����Գ���
void sim800c_test(void)
{
//	while(sim800c_send_cmd("AT","OK",200))//����Ƿ�Ӧ��ATָ�� 
//	{
//		printf ("%s\r\n","fail");//��������       
//	} 	 
//    printf("%s\r\n",USART2_RX_BUF);//�������� 
//    sim800c_send_cmd("AT+CSQ","",200);//����Ƿ�Ӧ��ATָ�� 
//    printf("%s\r\n",USART2_RX_BUF);  
//    sim800c_send_cmd("AT+CEREG=1","",200);//����Ƿ�Ӧ��ATָ��  
//    printf("%s\r\n",USART2_RX_BUF);   
//    sim800c_send_cmd("AT+CGREG=1","",200);
//    printf("%s\r\n",USART2_RX_BUF); 
//    sim800c_send_cmd("AT+COPS?","",200);
//    printf("%s\r\n",USART2_RX_BUF);
//    while(sim800c_send_cmd("AT+LSIPPROFILE=1,"CTNB"","OK",200))
//    {
//      printf ("%s\r\n","TCP,fail");
//    }
}







