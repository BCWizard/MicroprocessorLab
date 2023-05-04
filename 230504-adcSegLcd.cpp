/********ADC1A.C******AD�ഫ�d��***************************
*�ʧ@�J�Ұʳq�DAD0�ഫ�A�ñN�@�Ʀ��ƥ�LCD���
*���u�GPC0~7-->JP19(DB0~7),PC10~12-->JP19(RS�BRW�BEN) 
*      PA0(ADC_IN0)-->JP16(Analog Output)�A�վ�VR�O0~3.3V->PA0(ADC_IN0)           
******************************************************************/
#include "arminno.h"
#include  "config.h"
void LCD_Disp(uint16 count);
uint8 const   Table[]="ADC_IN0="; //�Ĥ@��}�C�r��
void LCD_Disp(int16 count);
int main(void) 
{ 
	 uint16 Value; 
	 uint8 i;
	 LCD_init();        //���m�βM��LCD    
   LCD_Cmd(0x80);     //��ХѲĤ@��}�l���  
   for(i=0; i< sizeof(Table); i++) //Ū���}�C�r����LCD��ܥX�� 
      LCD_Data(Table[i]);  
	
	SetAdc(0);  //�]�wADC Channel 0�A�ñҰ�ADC
	while(1) 
	{
		Value = GetAdc(0)*330/4095;  //Ū��ADC0�Ʀ���
    LCD_Disp(Value);    //���4��ƤQ�i��p��
		Pause(10000);
	}
}
/********************************************************
*��ƦW��: LCD_Disp
*�\��y�z: LCD���4��ƤQ�i��Ʀr
*��J�ѼơGdisp
*******************************************************/
void LCD_Disp(uint16 disp) 
{
 	LCD_Cmd(0x88);    //��ХѲĤ@���8�r�}�l���  
	if(disp>999)  LCD_Data(disp /1000+'0');       //��ܤd���
    else        LCD_Data(' ');
  if(disp>99)   LCD_Data(disp % 1000/100+'0');  //��ܦʦ��
    else        LCD_Data(' ');
  if(disp>9)    LCD_Data(disp % 100/10+'0');    //��ܤQ���
    else        LCD_Data(' ');            
                LCD_Data(disp % 10+'0');        //��ܭӦ��
}
/********adc_7seg.C******AD�ഫ�d��***************************
*�ʧ@�J�Ұʳq�DAD0�ഫ�A�ñN�@�Ʀ��ƥ�7�q��ܾ����
*���u�GPC0~6-->JP7(a~g)�APC10~13-->JP8(com1~4) 
*      PA0(ADC_IN0)-->JP16(Analog Output)�A�վ�VR�O0~3.3V->PA0(ADC_IN0)           
******************************************************************/
/*
#include "arminno.h"
#include  "config.h"

void	Seg_Disp(uint16 count);

int main(void) 
{ 
	 uint16 Value; 
	 uint8 i;
     SEG_DIR;       //�]�wSEG���}����X
	
	SetAdc(0);  //�]�wADC Channel 0�A�ñҰ�ADC
	while(1) 
	{
		Value = GetAdc(0);  //Ū��ADC0�Ʀ���
    	Seg_Disp(Value);    //���4��ƤQ�i��p��
		Pause(10000);
	}
}
*/
/************ SEG2 ****�C�q��ܾ��d��*************
*�ʧ@�G�|��Ʊ��y�p�ƾ��A�H10�i�����0000~9999
*���u�GPC0~6-->JP7(a~g)�APC10~13-->JP8(com1~4)
***********************************************/
/*
void Seg_Disp(uint16 count) 
{
  u8 scan;       //���y����  
  u8 i;          //�^���p�ƪ��ӡB�Q�B�ʡB�d���

     for(scan=0;scan<200;scan++)  //���б��y���� 
     {
       i=count/1000;    			//���X�d���
       SEG_Data=SEG_Table[i]; //�d��ƿ�X
       if(count>999) SEG_C1; 	//�Y�p��>999�A��ܤd���
       Delay_ms(1);           //���y����	     
				
	   i=(count % 1000)/100; 	//���X�ʦ�� 
       SEG_Data=SEG_Table[i]; //�ʦ�ƿ�X
       if(count>99) SEG_C2;		//�Y�p��>99�A��ܦʦ��
       Delay_ms(1);           //���y����			 

 	   i=(count % 100)/10;		//���X�Q��� 
       SEG_Data=SEG_Table[i]; //�Q��ƿ�X
       if(count>9) SEG_C3;		//�Y�p��>9�A��ܤQ���
       Delay_ms(1);           //���y����       
				
	   i=count % 10;    			//���X�Ӧ��
       SEG_Data=SEG_Table[i];//�Ӧ�ƿ�X
       //SEG_Mask; 
	   SEG_C4;     	//��ܭӦ����ܾ�
       Delay_ms(1);         	//���y����  
     }//end of for loop   
}
*/


