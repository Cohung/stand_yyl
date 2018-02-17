#include "STC89C5xRC_RDP.h"
#include "MAIN.H"
#include "12864.H"
#include "DS1302.H"
//��������	 �ܽ�SDA��SCLK��RST��MAIN.H�ж���

//�� �� �� ʱ �� �� ����
unsigned char Chinese_1[17]={0xc4,0xea,  0xd4,0xc2,  0xc8,0xd5,  0xca,0xb1,  0xb7,0xd6,  0xc3,0xeb,  0xd0,0xc7,  0xc6,0xda};
//����һ������������
//unsigned char Chinese_2[15]={0xd2,0xbb,  0xb6,0xfe,  0xc8,0xfd,  0xcb,0xc4,  0xce,0xe5,  0xc1,0xf9,  0xcc,0xec,' '};
//�������ƶ���λ��
unsigned char Cursor[6]={0x81,0x83,0x85,0x90,0x92,0x94};

unsigned char DS1302_YEAR_READ=0X8d;
unsigned char DS1302_MONTH_READ=0X89;
unsigned char DS1302_DAY_READ=0X87;
unsigned char DS1302_HOUR_READ=0X85;
unsigned char DS1302_MINUTE_READ=0X83;
unsigned char DS1302_SECOND_READ=0X81;
unsigned char DS1302_WEEK_READ=0X8b;

unsigned char DS1302_YEAR_WRITE=0X8c;
unsigned char DS1302_MONTH_WRITE=0X88;
unsigned char DS1302_DAY_WRITE=0X86;
unsigned char DS1302_HOUR_WRITE=0X84;
unsigned char DS1302_MINUTE_WRITE=0X82;
unsigned char DS1302_SECOND_WRITE=0X80;
unsigned char DS1302_WEEK_WRITE=0X8a;
extern unsigned int led_start,led_end;
extern unsigned char set_num;
extern unsigned char TIME[6];
extern unsigned char code dig_9[12];
extern unsigned char xdata dd_1[256];
extern bit led_on;
//extern unsigned char set_led_time[4];
/*************************************************************/
/*************************************************************/
//��λд
void DS1302WriteByte(unsigned char dat)
{
  unsigned char i;
  SCLK=0;
  Delay_50us(1);
  for(i=0;i<8;i++)
  {
    SDA=dat&0x01; //�ȵ�λ���λ
//	Delay_50us(1);
	SCLK=1;		  //һ��������дһλ
	Delay_50us(1);
	SCLK=0;
	dat>>=1;	 //���ƣ���λ����λ��
  }
}


/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/


//��λ��
unsigned char DS1302ReadByte()
{
  	unsigned char i,dat;
	//SCLK=1;
	//Delay_50us(1);
	for(i=0;i<8;i++)
	{
	   dat>>=1;		 //��Ҳ���ȵ�λ���λ
	   if(SDA==1)
	   dat|=0x80;	 //
	   SCLK=1;
	   Delay_50us(1);
	   SCLK=0;
	   //Delay_50us(1);
	}
	return dat;
}


/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/

//������
unsigned char DS1302Read(unsigned char cmd)
{
  unsigned char dat;
  RST=0;
   //Delay_50us(1);	  
  SCLK=0;	  //��ʱ������
   	  
  RST=1;	 //���������λ��׼���������������	 
  //Delay_50us(1);
  DS1302WriteByte(cmd);	 //cmd�п���λ�е�ַλ
  dat=DS1302ReadByte();
  SCLK=1;
  RST=0;
  SDA = 0;
  return dat;
}
/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/

//д����
void DS1302Write(unsigned char cmd, unsigned char dat)
{
  RST=0;
  SCLK=0; //DelayMs(10);
   Delay_50us(1);
  RST=1;
  DS1302WriteByte(cmd);
  DS1302WriteByte(dat);
  SCLK=1;
  RST=0;
  
}
/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/
// void Initialize_device(unsigned char *t)
// {
//    Init_ST7920();
//	DelayMs(10);
//	Init_DS1302();
//	DelayMs(10);
//	Display_Menu(t);
// }
/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/
//��ʼ��
void RE_DS1302()
{		
        TIME[0]=DS1302Read(DS1302_YEAR_READ);
		if((TIME[0]/16>4)||(TIME[0]%16>9))
			TIME[0]=0;
		TIME[1]=DS1302Read(DS1302_MONTH_READ);
		if((TIME[1]/16>1)||(TIME[1]%16>9)||(TIME[1]>18)) //��һԤ����λ>9,�ڶ�Ԥ����λ>9,����Ԥ��>12�µķǷ�������13��14��15
			TIME[1]=0;
		TIME[2]=DS1302Read(DS1302_DAY_READ);
		if((TIME[2]/16>3)||(TIME[2]%16>9)||(TIME[2]>49))
			TIME[2]=0;
		TIME[3]=DS1302Read(DS1302_HOUR_READ);
		if((TIME[3]/16>2)||(TIME[3]%16>9)||(TIME[3]>36))
			TIME[3]=0;
	    TIME[4]=DS1302Read(DS1302_MINUTE_READ);
		if((TIME[4]/16>5)||(TIME[4]%16>9))
			TIME[4]=0;
 
}
void Init_DS1302()
{
   DS1302Write(0x8e,0x00);	//д��������д����
   DS1302Write(DS1302_SECOND_WRITE,0x30);	//��ʼ���룬0x80����ֵ��DS1302�ĵ�ַ
//   DS1302Write(DS1302_MINUTE_WRITE,0x20);	//��
//   DS1302Write(DS1302_HOUR_WRITE,0x05);	//ʱ
//   DS1302Write(DS1302_DAY_WRITE,0x25);  //��
//   DS1302Write(DS1302_MONTH_WRITE,0x12);	//��
//   DS1302Write(DS1302_WEEK_WRITE,0x02);  //����
//   DS1302Write(DS1302_YEAR_WRITE,0x13);	//��
   DS1302Write(0x90,0x01);	//���
   DS1302Write(0xc0,0xf0);	//��ʼ����ʾ
   DS1302Write(0x8e,0x80);	//��д����
}
/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/


//void Split_Display(unsigned char address)
//{
//	unsigned char i;
//	i=DS1302Read(address);
//	i=i/16+'0';   
//	WriteData(i);
//	DelayMs(10);
//	i=DS1302Read(address);
//	i=i%16+'0';
//	WriteData(i);
//	DelayMs(10);
//}


/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/
void Display_Menu(unsigned char *ti)
{
	WriteCommand(0x90);
	WriteData('2');
	WriteData('0');
	WriteData('0'+ti[0]/16);
	WriteData('0'+ti[0]%16);
	WriteData(Chinese_1[0]);
	WriteData(Chinese_1[1]);

    WriteData('0'+ti[1]/16);
	WriteData('0'+ti[1]%16);
	WriteData(Chinese_1[2]);
	WriteData(Chinese_1[3]);

    WriteData('0'+ti[2]/16);
	WriteData('0'+ti[2]%16);
	WriteData(Chinese_1[4]);
	WriteData(Chinese_1[5]);

	WriteCommand(0x88);
    WriteData('0'+ti[3]/16);
	WriteData('0'+ti[3]%16);
	WriteData(Chinese_1[6]);
	WriteData(Chinese_1[7]);

    WriteData('0'+ti[4]/16);
	WriteData('0'+ti[4]%16);
	WriteData(Chinese_1[8]);

	WriteData(Chinese_1[9]);
}
/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/
  void LCD_Display_Clock(unsigned char *dig,unsigned char *img)
  {
    unsigned char i;
	unsigned int led_now;
	
	i=DS1302Read(DS1302_SECOND_READ);
	
	if(i!=TIME[5])
	{ 
		  TIME[5]=i;
		  if(i%2==0){
		  Draw_Dig(17,11,dig_9,dd_1);
		  
		  LCD_16128Graphic(6,4,dd_1);
		 
		  }
		  else{
		  Draw_Dig(17,12,dig_9,dd_1);
		  
		  LCD_16128Graphic(6,4,dd_1);
		
		}
		led_now = (TIME[3]/16*10+TIME[3]%16)*60+TIME[4]/16*10+TIME[4]%16;
	   
	   
	   if(led_start>led_end){
	   		if(led_now>=led_start||led_now<=led_end)
				{led_on=1;mled=1;
				//lcdak = 0;
				//cs_573 = 1;Delay_50us(1);cs_573=0;
				}
			else
				{led_on=0;mled=0;
				//lcdak = 1;
				//cs_573 = 1;Delay_50us(1);cs_573=0;
				}
				}
		else if(led_start==led_end)
			{led_on=1;mled=1;
			//lcdak = 0;
			//cs_573 = 1;Delay_50us(1);cs_573=0;
			}
		else
		{
			  if(led_now>=led_start&&led_now<=led_end)
				{led_on=1;mled=1;
				//lcdak = 0;
				//cs_573 = 1;Delay_50us(1);cs_573=0;
				}
			else
				{led_on=0;mled=0;
				//lcdak = 1;
				//cs_573 = 1;Delay_50us(1);cs_573=0;
				}
				
		}
			i=DS1302Read(DS1302_MINUTE_READ);
	if(i!=TIME[4])
	{
	   TIME[4]=i;
	   Draw_Dig(18,TIME[4]/16,dig,img);
	   Draw_Dig(19,TIME[4]%16,dig,img);
	  
	   LCD_16128Graphic(6,4,img); 
	   LCD_16128Graphic(7,4,img);
	 

	   i=DS1302Read(DS1302_HOUR_READ);
	   if(i!=TIME[3])
		{
		   TIME[3]=i;
		   Draw_Dig(15,TIME[3]/16,dig,img);
		   Draw_Dig(16,TIME[3]%16,dig,img);
		   
		   LCD_16128Graphic(5,4,img); 
		   LCD_16128Graphic(6,4,img);
		   
		    
		   i=DS1302Read(DS1302_DAY_READ);
		   if(i!=TIME[2])
			{
			   TIME[2]=i;
			   Draw_Dig(9,TIME[2]/16,dig,img);
			   Draw_Dig(10,TIME[2]%16,dig,img);
			   
			   LCD_16128Graphic(3,4,img); 
			   LCD_16128Graphic(4,4,img); 
			    

			   i=DS1302Read(DS1302_MONTH_READ);
			   if(i!=TIME[1])
				{
				   TIME[1]=i;
				   Draw_Dig(6,TIME[1]/16,dig,img);
				   Draw_Dig(7,TIME[1]%16,dig,img);
				   LCD_16128Graphic(2,4,img); 

				   i=DS1302Read(DS1302_YEAR_READ);
				   if(i!=TIME[0])
					{
					   TIME[0]=i;
					   Draw_Dig(3,TIME[0]/16,dig,img);
					   Draw_Dig(4,TIME[0]%16,dig,img);
					   
					   LCD_16128Graphic(1,4,img);
					   LCD_16128Graphic(2,4,img); 
					   		   
				
					}
		    	}	
			}	
		}
	   		
	   	
				

	  }
	}

	
  }