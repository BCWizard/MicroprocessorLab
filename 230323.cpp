/************ SEG2 ****�C�q��ܾ��d��*************
*�ʧ@�G�|��Ʊ��y�p�ƾ��A�H10�i�����0000~9999
*���u�GPC0~6-->JP7(a~g)�APC10~13-->JP8(com1~4)
***********************************************/
//seg??; RGB; K1->stopCount,beep1,R; K2->startCount,beep2,G; K3->reset,beep3,B;
#include "config.h"  // �պA�μȦs���]�w 
#define F 6000
#define T 600
#define STOP1 300
#define STOP2 1000

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
  u8 scan;       //���y����  
  u16 count=65280;   //�p�ƤQ�i���� 
		bool countCtrl = 0;
  u8 i;          //�^���p�ƪ��ӡB�Q�B�ʡB�d���
  SEG_DIR;       //�]�wSEG���}����X
	//u16 j,dly;
	Buzzer_DIR;
	
	KEY1_DIR; 				//�P��KEY1��J�δ��ɹq��
	KEY2_DIR;
	KEY3_DIR;
	RGB_DIR;
	
   while(1)     //���а���
    {
			if(KEY1_0){
				countCtrl = 0;
				R_LED_1; G_LED_0; B_LED_0; Delay_ms(100);
				beep(1);        //�ͤ@�n
				Buzzer_0; Delay_ms(STOP2); //���ﾹ����A���j�ɶ�
			}
		
			if(KEY2_0){
				countCtrl = 1;
				R_LED_0; G_LED_1; B_LED_0; Delay_ms(100);
				beep(2);        //�ͤ@�n
				Buzzer_0; Delay_ms(STOP2); //���ﾹ����A���j�ɶ�
			}
		
			if(KEY3_0){
				count = 0;
				countCtrl = 0;
				R_LED_0; G_LED_0; B_LED_1; Delay_ms(100);
				beep(3);        //�ͤ@�n
				Buzzer_0; Delay_ms(STOP2); //���ﾹ����A���j�ɶ�
			}
			
     for(scan=0;scan<200;scan++)  //���б��y���� 
      {
       i=count/4096;    			//���X�d���
       SEG_Data=SEG_Table[i]; //�d��ƿ�X
       //if(count>4095) 
				 SEG_C1; 	//�Y�p��>999�A��ܤd���
       Delay_ms(1);           //���y����	     
				
			 i=(count % 4096)/256; 	//���X�ʦ�� 
       SEG_Data=SEG_Table[i]; //�ʦ�ƿ�X
       //if(count>255) 
				 SEG_C2;		//�Y�p��>99�A��ܦʦ��
       Delay_ms(1);           //���y����			 

 			 i=(count % 256)/16;		//���X�Q��� 
       SEG_Data=SEG_Table[i]; //�Q��ƿ�X
       //if(count>15) 
				 SEG_C3;		//�Y�p��>9�A��ܤQ���
       Delay_ms(1);           //���y����       
				
			 i=count % 16;    			//���X�Ӧ��
			 SEG_Data=SEG_Table[i];//�Ӧ�ƿ�X
       SEG_Mask; SEG_C4;     	//��ܭӦ����ܾ�
       Delay_ms(1);         	//���y����  
      }	   
			if(countCtrl)
				count++;          				//�p��+1 
	 if(count>65535) count=0; 		//�Y�p�ƶW�L9999�A�p��=0
   } 
}

