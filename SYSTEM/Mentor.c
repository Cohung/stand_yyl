#include "STC89C5xRC_RDP.h"
#include "main.h"
#include "Mentor.h"


void MENTOR(uchar channel,uchar orientation)
{
		if(channel==0x01)
		{
			HC139_EN = 0;
			L298N_EA = 0;
			L298N_EB = 0;
			if(orientation == ZHEN)
			{m2=0;m1=1;}
			else
			{m2=0;m1=1;}
		}
		if(channel==0x02)
		{
			HC139_EN = 0;
			L298N_EA = 1;
			L298N_EB = 0;
			if(orientation == ZHEN)
			{m2=1;m1=0;}
			else
			{m2=0;m1=1;}
		}
		if(channel==0x03)
		{
			HC139_EN = 0;
			L298N_EA = 0;
			L298N_EB = 1;
			if(orientation == ZHEN)
			{m2=1;m1=1;}
			else
			{m2=1;m1=0;}
		}
		if(channel==0x04)
		{
			HC139_EN = 0;
			L298N_EA = 1;
			L298N_EB = 1;
			if(orientation == ZHEN)
			{m2=0;m1=0;}
			else
			{m2=1;m1=1;}
		}
}
void M_OFF()
{HC139_EN = 1;}





