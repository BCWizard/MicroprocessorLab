/************ SEG3 *****�C�q��ܾ��d��**********************
*�ʧ@�G�ѥ|��ƤC�q��ܾ���ܹq�l�����ɡB���ά��{�{
*      �A��KEY1�ծɡA��KEY2�դ�
*���u�GPC0~6-->JP7(a~g)�APC7-->JP8(dps)�APC10~13-->JP8(C1~C4)
*      PD11~12-->JP24(0~1)�AGND-->JP24(4)
************************************************************/
#include "config.h"  // �պA�μȦs���]�w 

#define F 6000
#define T 600
#define STOP1 300

void Display(void); //�|��ƤC�q��ܾ����y
int8 hor=23,min=2,sec=18; //�]�w�ɡB���B��ɶ�

void beep(u8 i)
{
  u16  j,dly;		//Buzzer�Ϭۦ���
  while(i--)   	//���n����
   {
     for(j=0;j<T;j++) //��X�Ϭۦ��ơA�M�w����
      {		
				while(KEY1_0) Buzzer_0; //�Y��KEY1��A���ﾹ����
				Buzzer_T; 							//Buzzer�Ϭ�,�O���ﾹ�o�X�n��
				dly=F; while(dly--);		//���W����
      }
	  Buzzer_0; Delay_ms(STOP1);	//���ﾹ����A���n�����j�ɶ�
  }
}

int main(void) 
{
	bool countDown = 0;
  SEG_DIR;        	 //�]�wSEG���}����X
	KEY1_DIR; KEY2_DIR; KEY3_DIR;//�]�wKEY���}����J
	Buzzer_DIR;
  while(1)
  {
		if(KEY2_0){
			sec--;  //��KEY2��sec  
			if(sec<0) {
				min--;
				sec=59;
			}
		}
		if(KEY1_0){ 
			min--;  //��KEY1��min
			if(min<0) {
				hor--;
				min=59;				
			}
		}
		if(KEY3_0) 
			countDown=~countDown; 
		
		Display(); //�C�q��ܾ���ܮɶ�
		
		if(countDown){
			if(sec+min*60 == 135){
				countDown = 0;
				beep(1);        //�ͤ@�n
				Buzzer_0; Delay_ms(STOP1); //���ﾹ����A���j�ɶ�
			}
			sec--;               //��[�@
			if (sec >= 0) continue; //�Y��p��60�A�q�Y����   
				sec=59; min--;        //����60�h�O��=0�A���[�@
			if (min >= 0) continue; //�Y���p��60�A�q�Y����    
				min=59; hor--;        //�Y������60�h�O��=0�A�ɥ[�@
			if (hor >= 0) continue; //�Y�ɤp��24�A�q�Y���� 
				hor=0; min=0; sec=0; //�Y�ɵ���24�h�O�ɡB���B��=0
		}
   }
 }	 
//***************************************************	 
void Display(void)  //�|��ƤC�q��ܾ����y	 
{  
  u8 scan=100;     //�C�q��ܾ����y���ơA�M�ɩ��ɮɶ�
	while(scan--)    //���б��y���� 
    {
			SEG_Data=SEG_Table[min/10];//�ɤQ��ƿ�X
      SEG_C1; Delay_ms(1); 			 //��ܤd�����ܾ� 

      if(scan<100) 	SEG_Data=SEG_Table[min%10];//�ɭӼƿ�X
				else SEG_Data=SEG_Table[min%10]|0x80;//�ɭӼƿ�X+��G
      SEG_C2; Delay_ms(1); 			 //��ܦʦ����ܾ� 
			
			SEG_Data=SEG_Table[sec/10];//���Q��ƿ�X
      SEG_C3;  Delay_ms(1);      //��ܤQ�����ܾ�			 
			 
			SEG_Data=SEG_Table[sec%10];//���Ӧ�ƿ�X
      SEG_C4; Delay_ms(1);    	 //��ܭӦ����ܾ�
    }	   
}
