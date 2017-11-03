#include "sim800c.h"
//////////////////////////////////////////////////////////////////////////////////	   
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F103开发板 
//ATK-SIM800C GSM/GPRS模块驱动	  
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/4/1
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//******************************************************************************** 
//无
 	
u8 Scan_Wtime = 0;//保存蓝牙扫描需要的时间
u8 BT_Scan_mode=0;//蓝牙扫描设备模式标志

//usmart支持部分
//将收到的AT指令应答数据返回给电脑串口
//mode:0,不清零USART2_RX_STA;
//     1,清零USART2_RX_STA;
void sim_at_response(u8 mode)
{
	if(USART2_RX_STA&0X8000)		//接收到一次数据了
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//添加结束符
		printf("%s",USART2_RX_BUF);	//发送到串口
		if(mode)USART2_RX_STA=0;
	} 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//ATK-SIM800C 各项测试(拨号测试、短信测试、GPRS测试,蓝牙测试)共用代码

//SIM800C发送命令后,检测接收到的应答
//str:期待的应答结果
//返回值:0,没有得到期待的应答结果
//其他,期待应答结果的位置(str的位置)
u8* sim800c_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART2_RX_STA&0X8000)		//接收到一次数据了
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//添加结束符
		strx=strstr((const char*)USART2_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}
//SIM800C发送命令
//cmd:发送的命令字符串(不需要添加回车了),当cmd<0XFF的时候,发送数字(比如发送0X1A),大于的时候发送字符串.
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 sim800c_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART2_RX_STA=0;
	if((u32)cmd<=0XFF)
	{
		while((USART2->SR&0X40)==0);//等待上一次数据发送完成  
		USART2->DR=(u32)cmd;
	}else u2_printf("%s\r\n",cmd);//发送命令
	
	 if(waittime==1100)//11s后读回串口数据(蓝牙测试用到)
	 {
		 Scan_Wtime = 11;//需要定时的时间
		 TIM2_SetARR(9999);//产生1S定时中断
		 
	 }
	if(ack&&waittime)		//需要等待应答
	{
		while(--waittime)	//等待倒计时
		{ 
			delay_ms(10);
			if(USART2_RX_STA&0X8000)//接收到期待的应答结果
			{
				if(sim800c_check_cmd(ack))break;//得到有效数据 
				USART2_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 
//接收SIM800C返回数据（蓝牙测试模式下使用）
//request:期待接收命令字符串
//waittimg:等待时间(单位：10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 sim800c_wait_request(u8 *request ,u16 waittime)
{
	 u8 res = 1;
	 if(request && waittime)
	 {
	    while(--waittime)
		{   
		   delay_ms(10);
		   if(USART2_RX_STA &0x8000)//接收到期待的应答结果
		   {
				if(sim800c_check_cmd(request)) break;//得到有效数据
				USART2_RX_STA=0;
		   }
		}
		if(waittime==0)res=0;
	 }
	 return res;
}

//将1个字符转换为16进制数字
//chr:字符,0~9/A~F/a~F
//返回值:chr对应的16进制数值
u8 sim800c_chr2hex(u8 chr)
{
	if(chr>='0'&&chr<='9')return chr-'0';
	if(chr>='A'&&chr<='F')return (chr-'A'+10);
	if(chr>='a'&&chr<='f')return (chr-'a'+10); 
	return 0;
}
//将1个16进制数字转换为字符
//hex:16进制数字,0~15;
//返回值:字符
u8 sim800c_hex2chr(u8 hex)
{
	if(hex<=9)return hex+'0';
	if(hex>=10&&hex<=15)return (hex-10+'A'); 
	return '0';
}

//SIM800C主测试程序
void sim800c_test(void)
{
//	while(sim800c_send_cmd("AT","OK",200))//检测是否应答AT指令 
//	{
//		printf ("%s\r\n","fail");//发送命令       
//	} 	 
//    printf("%s\r\n",USART2_RX_BUF);//发送命令 
//    sim800c_send_cmd("AT+CSQ","",200);//检测是否应答AT指令 
//    printf("%s\r\n",USART2_RX_BUF);  
//    sim800c_send_cmd("AT+CEREG=1","",200);//检测是否应答AT指令  
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







