#include "STC89C5xRC_RDP.h"
#include "string.h"
#include "main.h"
#include "12864.h"

unsigned char code which_channel[]={"��ѡ����"};
unsigned char code error[]={"�Բ��𣬳�����������"};
unsigned char code no_inv[]={"�Բ��𣬴˻���ȱ����ѡ������������"};
unsigned char code get_inv[]={"��ȡ����"};
	  
///////��ʱ����//////////////////////////////////
//void delay1(unsigned int z)
//{
//	unsigned int x,y;
//	for(x=z;x>0;x--)
//	for(y=110;y>0;y--);	
//}
/*-----------------------------------
 д��һ�ֽ�����/����
 -----------------------------------*/
 void WriteByte_S(unsigned char byte)
 {
 	unsigned char i;
	 Delay_50us(5);
	for (i=0; i<8; i++)
	{
		E = 0;
		
		if(byte&0x80)	  //�趨�����������ϵ���ֵ
		RW = 1;
		else
		RW = 0;
	  
		byte <<= 1;
		
		
		E = 1;
	   
	}  
	Delay_50us(5);
 }
///////////////////////////////////////////////
//////д����////////////////////////////////////
void WriteCommand(unsigned char Cmd)
{



unsigned char cmd;
cmd = 0xf8;
RS = 1;



WriteByte_S(cmd);
WriteByte_S(Cmd&0xf0);
WriteByte_S(Cmd<<4);  //Delay_50us(10);
}
//////////////////////////////////////////////////


//////д����//////////////////////////////////////
void WriteData(unsigned char Data)  
{

//����
     
unsigned char cmd;
cmd = 0xfa;
RS = 1;



WriteByte_S(cmd);
WriteByte_S(Data&0xf0);
WriteByte_S(Data<<4);
//Delay_50us(10);
}
//////////////////////////////////////////////////



///////��ʼ��////////////////////////////////////
void initial_LCD()      
{   


	 WriteCommand(0x01);  //����
	 WriteCommand(0x30);  //�������á�8�ֽڽ��棬����ָ�����0011 x0xx��
	 WriteCommand(0x0c);  //��ʾ���á�������ʾ����겻��ʾ����겻���򡣣�0000 1110��
	 WriteCommand(0x06);   //���뷽ʽ���á�������ƣ���ַλ��1���������ơ���0000 0110)
	 DelayMs(10);
	// WriteCommand(0x14);   //������ơ�
}
/////////////////////////////////////////////////
/*------------------------------------------------
                   ��ʾ�ַ���
x:������ֵ����Χ0~7
y:������ֵ����Χ1~4
------------------------------------------------*/
void LCD_PutString(unsigned char x,unsigned char y,unsigned char code *s)
{ 
	WriteCommand(0x30);
 switch(y)
     {
	  case 1: WriteCommand(0x80+x);break;
	  case 2: WriteCommand(0x90+x);break;
	  case 3: WriteCommand(0x88+x);break;
	  case 4: WriteCommand(0x98+x);break;
      default:break;
	 }
 while(*s>0)
   { 
      WriteData(*s);
      s++;
     
   }
 //Delay_50us(20);
  
}
/*------------------------------------------------
                      ����
------------------------------------------------*/
void ClrScreen()
{ 
   WriteCommand(0x01);
   DelayMs(20);
}
void Clean_12864_GDRAM(void)
{
    unsigned char x,y;

    WriteCommand(0x34);
    WriteCommand(0x30);     //����ָ�����(����ָ�����Ϊ:0x34)
	WriteCommand(0x0C);     //������ʾON���α�OFF���α�λ��OFF
	WriteCommand(0x06);  	 //�������,DDRAMλַ������(AC)��1,�������ƶ�
	ClrScreen();           //���� (��DDRAM)

    WriteCommand(0x36);	//��Ҫ���Σ�����������չָ�

    for (y=0;y<32;y++)
    {
        WriteCommand(0x80+y);  //����y=1000+00xx��y+1������һ��
        WriteCommand(0x80);	//����x=1000 0000
        for (x=0;x<16;x++)
        {
            WriteData(0x00);   //���ֽ�����
            WriteData(0x00);	//���ֽ�����
        }
    }
}

//void LCD_1616Graphic(unsigned char x,unsigned char y, unsigned char code *img)
//{ 
//
//
//    int i;
// 
//    WriteCommand(0x36);
////DelayMs(2); 
//	   for(i=0;i<16;i++)            
//	    { 	 
//		   switch(y)
//		   {
//	         case 1:
//			         WriteCommand(0x80 + i); //���费ֱ��ַ
//	                 WriteCommand(0x80 + x);     //����ˮƽ��ַ,��ʾ�ڵ�1��
//					 break;
//			 case 2:
//			         WriteCommand(0x90 + i); //���费ֱ��ַ
//	                 WriteCommand(0x80 + x);     //����ˮƽ��ַ,��ʾ�ڵ�2��
//					 break;
//		     case 3:
//			         WriteCommand(0x80 + i); //���费ֱ��ַ
//	                 WriteCommand(0x88 + x);     //����ˮƽ��ַ,��ʾ�ڵ�3��
//					 break;
//		     case 4:
//			         WriteCommand(0x90 + i); //���费ֱ��ַ
//	                 WriteCommand(0x88 + x);     //����ˮƽ��ַ,��ʾ�ڵ�4��
//					 break;	
//			 default:break;		 		 			 		 	
//		   }     	    
//	         WriteData(*img);
//			 img++;
//			 WriteData(*img);
//	         img++;   
//	    }
//
////	WriteCommand(0x36);
//	WriteCommand(0x30);
//
//	//DelayMs(5);
//           
//}

/*------------------------------------------------
                   ��ʾ�Զ���16*128ͼƬ
------------------------------------------------*/

void LCD_16128Graphic(unsigned char x,unsigned char y, unsigned char  *img)
{ 


 int i;

WriteCommand(0x36);

   for(i=0;i<16;i++)            
    { 
	 switch(y)
	 { case 1:
	          WriteCommand(0x80 + i); //���费ֱ��ַ
              WriteCommand(0x80 + x);     //����ˮƽ��ַ
			  break;
	   case 2:
	         WriteCommand(0x90 + i); //���费ֱ��ַ
              WriteCommand(0x80 + x);     //����ˮƽ��ַ
			  break;
	   case 3:
	         WriteCommand(0x80 + i); //���费ֱ��ַ
              WriteCommand(0x88 + x);     //����ˮƽ��ַ
			  break;
	   case 4:
              WriteCommand(0x90 + i); //���费ֱ��ַ
              WriteCommand(0x98 + x);     //����ˮƽ��ַ
			  break;
	   default:break;
     }

		  Delay_50us(10);
          WriteData(img[x*2+i*16]);
		  Delay_50us(10);
		  WriteData(img[x*2+1+i*16]);								
   
    }
	Delay_50us(10);
	WriteCommand(0x36);
	
   	WriteCommand(0x30);

	Delay_50us(20);
           
}



 void  Draw_Graphic(unsigned char hang_shu,unsigned char *img)
 {
   unsigned char i;
   for(i=0;i<8;i++)
     LCD_16128Graphic(i,hang_shu,img);
 }

void Draw_LOGO(unsigned char *img_1,unsigned char *img_2,unsigned char *img_3)
{
  Draw_Graphic(1,img_1);
  Draw_Graphic(2,img_2);
  Draw_Graphic(3,img_3);
  DelayMs(20);
}

/*------------------------------------------------
                  ���廭�㺯��
--------------------------------------------------*/
 

 void set(unsigned char x,unsigned char y, unsigned char xdata *img)
{
  unsigned char byte_index, bit_index,temp,temp_bit;
  byte_index=x/8;
  bit_index=x%8;
  temp=*(img+y*16+byte_index);
  temp_bit=(temp>>(7-bit_index))&0x01;//����Ҫ���õĵ�ԭ���Ƿ�Ϊ1����1�Ͳ�����
  if(temp_bit==0)//���Եĵ���0���������Ϊ1
    {
      temp=0x01;
      temp=temp<<(7-bit_index);
      *(img+y*16+byte_index)=(*(img+y*16+byte_index)|temp);
	}
 }

void clr(unsigned char x,unsigned char y,unsigned char *img)
{
  unsigned char byte_index, bit_index,temp,temp_bit;
  byte_index=x/8;
  bit_index=x%8;
  temp=*(img+y*16+byte_index);
  temp_bit=(temp>>(7-bit_index))&0x01;//����Ҫ���õĵ�ԭ���Ƿ�Ϊ1 
  if(temp_bit==1)//���Եĵ���1���������Ϊ0
    {
    temp=0x01;
    temp=temp<<(7-bit_index);
    *(img+y*16+byte_index)=(*(img+y*16+byte_index)-temp);
	}
//   else			  //���Եĵ���0���������Ϊ1
//	{
//    temp=0x01;
//    temp=temp<<(7-bit_index);
//    *(img+y*16+byte_index)=(*(img+y*16+byte_index)+temp);
//	}


 }


 /*------------------------------------------------
                 ������
------------------------------------------------*/
 void Draw_Dig(unsigned char add,unsigned char num,unsigned char *dig,unsigned char *img)
 {
   unsigned char temp,rol;
   unsigned char i,j;
   for(i=0;i<16;i++)
     for(j=0;j<6;j++)
	    clr(add*6+j,i,img);
   for(i=0;i<10;i++)
     {
	  rol=0x80; 
	  for(j=0;j<8;j++)
	    {
		  temp=*(dig+i+num*10);
		  temp=temp & rol;
		  if(temp!=0)
		  {
		    set(j+add*6,i+5,img);
		  }
		  rol=rol>>1;
		}
	 }	 
 }
   
void DisplayLcd(unsigned char type)
{
	 unsigned char i;

	 if(type == SEL_CHAN){
	 WriteCommand(0x92);  		
	 for (i=1;i<=8;i++)		
	 WriteData(which_channel[i-1])  ;} 
	 else if (type == ERR_MES){
	 WriteCommand(0x92);  		
	 for (i=1;i<=8;i++)		
	 WriteData(error[i-1])  ;
	 WriteCommand(0x89);
	 for (i=9;i<=20;i++)		
	 WriteData(error[i-1])  ; }
	 else if (type == NO_INV){
	 WriteCommand(0x82);  		
	 for (i=1;i<=8;i++)		
	 WriteData(no_inv[i-1])  ;
	 WriteCommand(0x91);
	 for (i=9;i<=18;i++)		
	 WriteData(no_inv[i-1])  ;
	 WriteCommand(0x88);
	 for (i=19;i<=34;i++)		
	 WriteData(no_inv[i-1])  ;
	 }
	 else if (type == GET_INV){
	 WriteCommand(0x92);  		
	 for (i=1;i<=8;i++)		
	 WriteData(get_inv[i-1])  ;
	 }
	
}

//void DispalyLcd1()
//{
//	 unsigned char i;
//	 WriteCommand(0x01);  //����
//	 WriteCommand(0x80);  		
//	 for (i=1;i<=15;i++)		
//	 WriteData(table_3[i-1])  ; 
//
//
//}

///////Ҫ��ʾ������//////////////////////////////
   /*
void DispalyLcd()
{
	 unsigned char i;
	 WriteCommand(0x81);  		//ҳ��ַ,��80��ʼ,����μ�����//
	 for (i=1;i<=14;i++)		//��һ����ʾ����7������,1������Ϊ2���ֽ�,��������Ҫ����14���ֽ�//
	 WriteData(table_1[i-1])  ;   
 
	 WriteCommand(0x90);  		//ҳ��ַ,��92��ʼ,����μ�����//
	 for (i=1;i<=5;i++)		
	 WriteData(table_2[i-1])  ; 


	 WriteCommand(0x88);  		//ҳ��ַ,��88��ʼ,����μ�����//
	 for (i=1;i<=5;i++)		    //������
	 WriteData(table_3[i-1])  ; 


	 WriteCommand(0x98);  	
	 for (i=1;i<=16;i++)		
	 WriteData(table_9[i-1])  ; 




	 WriteCommand(0x98);  		//ҳ��ַ,��88��ʼ,����μ�����//
	 for (i=1;i<=5;i++)		
	 WriteData(table_4[i-1])  ; 

}		*/
/////////////////////////////////////////////////////

//////////��ֵ��ת����ʽ  \ ��ʾ��ֵ ////////////////

//void LCD_Data(unsigned char LCDbyte )
//{
//	 unsigned char count;
//	 count=(LCDbyte&0xf0)>>4;
//	 if (count>0x9) WriteData(count%9+0x40);
//	 else WriteData(count+0x30);
//	 count=LCDbyte&0x0f;
//	 if (count>9) WriteData(count%9+0x40);
//	 else WriteData(count+0x30);
//}
/////////////////////////////////////////////////////
//void disCardId(unsigned char *gID)
//{
//	unsigned char i;
//
//	ClrScreen();
//	DelayMs(50);
//	//DispalyLcd1();
//	for(i=0;i<8;i++)
//	{
//
//	    WriteCommand(0x88+i);
//		LCD_Data(gID[0+i]); //4���ֽڵ����к�
//		
//	}
//	
//}

