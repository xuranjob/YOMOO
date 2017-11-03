#ifndef __RELAY_H
#define __RELAY_H 
#include "main.h"


#define K1 PEout(9)// 
#define K2 PEout(8)// 	
#define K3 PEout(7)// 
#define K4 PGout(1)// 
#define K5 PGout(0)// 
#define K6 PFout(15)// 
#define K7 PFout(14)//
#define K8 PFout(13)//
#define K9 PGout(14)//
#define K10 PGout(13)//
#define K11 PGout(12)//
#define K12 PGout(11)//
#define K13 PGout(10)//
#define K14 PGout(9)//
#define K15 PDout(7)//
#define K16 PDout(6)//

void Relay_Init(void);//继电器IO初始化
void Relay_test(void);//继电器测试函数，隔一秒轮流设置一路继电器
		 				    
#endif


