/****************************************************************/ 
#ifndef __STC12EROM_H__
#define __STC12EROM_H__ 

#include <intrins.h>
#define  uchar unsigned char    
#define  uint  unsigned int  
										  //������ISP/IAP����ʱ��궨��ѡ��
//#define  EN_IAP        0x80             //ϵͳʱ�� �� 30MHz
//#define  EN_IAP        0x81             //ϵͳʱ�� �� 24MHz
#define  EN_IAP        0x82             //ϵͳʱ�� �� 20MHz
//  #define  EN_IAP        0x83             //ϵͳʱ�� �� 12MHz
//#define  EN_IAP        0x84             //ϵͳʱ�� �� 6MHz
//#define  EN_IAP        0x85             //ϵͳʱ�� �� 3MHz
//#define  EN_IAP        0x86             //ϵͳʱ�� �� 2MHz
//#define  EN_IAP        0x87             //ϵͳʱ�� �� 1MHz



//ʹ��˵����
//ÿ��д��֮ǰ��Ҫ�������������ݲ��ԡ�




/****************�����û����õ�3��������****************/
 void Q0();
 uchar R_EROM(uchar n,uint x);			  //����n��������x�ֽڵ�����
 void  W_EROM(uchar n,uint x,uchar dat);  //���n��������x�ֽ�д������dat
 void  C_EROM(uchar n);					  //������n����



#endif
