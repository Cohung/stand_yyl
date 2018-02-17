//指定PCD接收缓冲值
#ifndef FSDI
#define FSDI 4
#endif


/*本版程序适用于主机板3，电机控制端口无复用，芯片远离电源端*/
#define uchar unsigned char
#define uint unsigned int
/////////////////////////////////////////////////////////////////////
//89C54RD特殊寄存器定义
/////////////////////////////////////////////////////////////////////
//sfr16    RCAP2LH    =    0xCA;
//sfr16    T2LH       =    0xCC;

//sfr      CHPENR     =    0xF6;
//sfr      CHPCON     =    0xBF;


/////////////////////////////////////////////////////////////////////
//端口定义
/////////////////////////////////////////////////////////////////////

sbit     RC531_CE   =    P2^7;                   //RC531片选
sbit     RC531_RST  =    P3^4;                   //RC531ALE


sbit     buzz       =    P4^3;
//sbit     flesh      =    P1^1;


sbit 	 RS         =    P4^6;
sbit 	 RW         =    P1^1;                      
sbit 	 E          =    P1^0; 

sbit     RST		=	 P1^2;
sbit     SCLK		=	 P1^4;
sbit 	 SDA		=	 P1^3;
//用户设置按键
sbit 	 SET		=	 P2^0;
sbit 	 TAB		=	 P2^1;
sbit 	 INC		=	 P2^2;
sbit 	 SUB		=	 P2^3;

//sbit     P47        =    P4^7;//样板里一条缺货检测通道用作人体感应，故单片机RST脚补充一个缺货检测；批量中应使得RST担当人体感应的角色。
//通道选择按键
sbit     SCH1       =    P2^4;
//sbit 	 ch1 		= 	 P4^3;
//sbit 	 ch2 		= 	 P1^0;
sbit 	 sc_data 		=	 P3^1;
sbit 	 sc_rst 		=	 P3^0;
//4路电机输出
sbit     m1         =    P3^5;
sbit     m2         =    P1^5;
sbit     L298N_EA         =    P4^4;
sbit     L298N_EB         =    P3^3;
sbit     HC139_EN         =    P2^6;
//行程开关触点到达信号
sbit     pos1       =    P2^5;
//sbit   pos3        =    P2^6;//此管脚冗余，因不再使用电机正反转控制，转供74hc139的使能

sbit     lcdak      =    P4^7;
//缺货通道的缺货信号输出
sbit     out1       =    P1^6;
sbit  	 out2 		= 	 P1^7;
sbit     out3		=  	 P4^0;
sbit	 out4		=	 P4^1;
//LED灯管输出控制信号
sbit     mled       =    P4^2;
/////////////////////////////////////////////////////////////////////
//RC500的EEPROM定义
/////////////////////////////////////////////////////////////////////
#define  ICDEV_RC500_ADR 0x30
/////////////////////////////////////////////////////////////////////
//延时常数及波特率定义
/////////////////////////////////////////////////////////////////////
/*#define  OSC_FREQ        11059200L//22118400L
#define  RCAP2_50us      65536L - OSC_FREQ/240417L
#define  RCAP2_1ms       65536L - OSC_FREQ/12021L
#define  RCAP2_10ms      65536L - OSC_FREQ/1200L
#define  TIME0_500us     65536L - OSC_FREQ/48000L
#define  TIME0_10ms      65536L - OSC_FREQ/1200L

#define  BOUND4800       256 - 24
#define  BOUND9600       256 - 12
#define  BOUND14400      256 - 8
#define  BDOUN19200      256 - 6
#define  BOUND28800      256 - 4
#define  BOUND38400      256 - 3
#define  BOUND57600      256 - 2
#define  BOUND115200     256 - 1			 */

#define OSC_FREQ                22118400L	 
#define BOUND115200             256 - (OSC_FREQ/192L)/115200L   // 255
#define BOUND57600              256 - (OSC_FREQ/192L)/57600L    // 254
#define BOUND38400              256 - (OSC_FREQ/192L)/38400L    // 253
#define BOUND28800              256 - (OSC_FREQ/192L)/28800L    // 252
#define BOUND19200              256 - (OSC_FREQ/192L)/19200L    // 250
#define BOUND14400              256 - (OSC_FREQ/192L)/14400L    // 248
#define BOUND9600               256 - (OSC_FREQ/192L)/9600L     // 244
#define  BOUND4800       256 - 24
#define RCAP2_50us             65536L - OSC_FREQ/240417L
#define RCAP2_1ms              65536L - OSC_FREQ/12021L
#define RCAP2_10ms             65536L - OSC_FREQ/1200L
#define RCAP2_1s             65536L - OSC_FREQ/12L

#define CH1   0X01
#define CH2   0X02
#define CH3   0X03
#define CH4   0X04

#define               USER_STATE               0X0A
#define               USER_STATE_ERR           0X0B
#define               POS_ON				   0x0c
#define				  POS_ON_OUT               0X09
#define               GET_INV_STATE            0X0D
#define 			        NO_INV_STATE	  0X0E
#define						THANKS	0x0f
#define						TO_THANKS		0X10
/////////////////////////////////////////////////////////////////////
//和上位机的通讯错误代码定义
/////////////////////////////////////////////////////////////////////
//#define  FAULT10  10                                      //通用错误
//#define  FAULT11  11                                      //不支持该命令
//#define  FAULT12  12                                      //命令参数错
//#define  FAULT13  13                                      //无卡
//#define  FAULT14  14                                      //射频基站损坏
//
//#define  FAULT20  20                                      //寻卡失败
//#define  FAULT21  21                                      //卡复位失败
//#define  FAULT22  22                                      //密码验证失败
//#define  FAULT23  23                                      //读卡失败
//#define  FAULT24  24                                      //写卡失败

/////////////////////////////////////////////////////////////////////
//函数原型
/////////////////////////////////////////////////////////////////////
void InitializeSystem();                                   
void Rc632Ready();                                         
void AnswerCommandOk();
void AnswerCommandOk1();
void AnswerOk(unsigned char *answerdata,unsigned int answernum);          
void AnswerErr(char faultcode);                            
void DelayMs(unsigned int j);                                      
void Delay_50us(unsigned char j);                                  


void BEEP(unsigned char i);
void Write_E(uchar n,uint x,uchar dat);
void Write_EE_rec(uchar y,uchar m,uchar d);
//uchar runnian(uchar y);
uchar panduan(uchar y,uchar m, uchar d);
void request();
void flesh_clr();
void flesh_set();
void select_ch(unsigned channel);
void user_ch();
void deselect_ch();

void ComPcdAntenna();
//void ComRequestA();
//void ComAnticoll();
//void ComSelect();
//void ComHlta();
//void ComAuthentication();
//void ComM1Read();
//void ComM1Write();
//void ComM1Initval();
//void ComM1Readval();
//void ComM1Decrement();
//void ComM1Increment();
//void ComM1Restore();
//void ComM1Transfer();
//
//void ComTypeARst();
//void ComTypeBRst();
//void ComCL_Deselect();
//void ComHltb();
//void ComRF020Check();  
//void ComRF020Read();  
//void ComRF020Write();
//void ComRF020Lock();	
//void ComRF020Count();	
//void ComRF020Deselect();
//void ComLight();
//void ComSelectSR();     
//void ComReadSR176(); 
//void ComWriteSR176();
//void ComProtectSR176();
//void ComCompletionSR();
//void ComReadSR4K();  
//void ComWriteSR4K();      
//void ComAuthSR4K();
//void ComGetUIDSR4K();
//void ComProtectSR4K();
//void ComTypeACOS();

	



