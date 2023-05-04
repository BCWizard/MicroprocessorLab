/********ADC1A.C******AD�ഫ�d��***************************
*�ʧ@�J�Ұʳq�DAD0�ഫ�A�ñN�@�Ʀ��ƥ�LCD���
*���u�GPC0~7-->JP19(DB0~7),PC10~12-->JP19(RS�BRW�BEN) 
*      PA0(ADC_IN0)-->JP16(Analog Output)�A�վ�VR�O0~3.3V->PA0(ADC_IN0)           
******************************************************************/
#include "arminno.h"
#include "config.h"
void LCD_Disp(uint16 count);
uint8 const   Table[]="C0="; //�Ĥ@��}�C�r��
uint8 const   Table1[]="C1="; //�ĤG��}�C�r��
uint8 const   Table2[]="C2="; //�Ĥ@��}�C�r��
uint8 const   Table3[]="C3="; //�Ĥ@��}�C�r��
void LCD_Disp(int16 count);

int main(void) 
{ 
	 uint16 Value; 
	 uint8 i;
	 LCD_init();        //���m�βM��LCD    
	while(1) 
	{
		SetAdc(0);  //�]�wADC Channel 0�A�ñҰ�ADC
		SetAdc(1);  //�]�wADC Channel 0�A�ñҰ�ADC
		SetAdc(2);  //�]�wADC Channel 0�A�ñҰ�ADC
		SetAdc(3);  //�]�wADC Channel 0�A�ñҰ�ADC
		
		LCD_Cmd(0x80);     //��ХѲĤ@��}�l���   
		for(i=0; i < sizeof(Table); i++) //Ū���}�C�r����LCD��ܥX�� 
      LCD_Data(Table[i]);
		LCD_Cmd(0x88);     //��ХѲĤ@��}�l���  
			for(i=0; i< sizeof(Table1); i++) //Ū���}�C�r����LCD��ܥX�� 
				LCD_Data(Table1[i]); 
		LCD_Cmd(0xC0);     //��ХѲĤ@��}�l���  
			for(i=0; i< sizeof(Table2); i++) //Ū���}�C�r����LCD��ܥX�� 
				LCD_Data(Table2[i]); 
		LCD_Cmd(0xC8);     //��ХѲĤ@��}�l���  
			for(i=0; i< sizeof(Table3); i++) //Ū���}�C�r����LCD��ܥX�� 
				LCD_Data(Table3[i]); 
		
		LCD_Cmd(0x83);
		Value = GetAdc(0);  //Ū��ADC0�Ʀ���
    LCD_Disp(Value);    //���4��ƤQ�i��p��
		Pause(10000);
		
		LCD_Cmd(0x8B);
		Value = GetAdc(1);  //Ū��ADC0�Ʀ���
    LCD_Disp(Value);    //���4��ƤQ�i��p��
		Pause(10000);
		
		LCD_Cmd(0xC3);
		Value = GetAdc(2);  //Ū��ADC0�Ʀ���
    LCD_Disp(Value);    //���4��ƤQ�i��p��
		Pause(10000);
		
		LCD_Cmd(0xCB);
		Value = GetAdc(3);  //Ū��ADC0�Ʀ���
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
	if(disp>999)  LCD_Data(disp /1000+'0');       //��ܤd���
    else        LCD_Data(' ');
  if(disp>99)   LCD_Data(disp % 1000/100+'0');  //��ܦʦ��
    else        LCD_Data(' ');
  if(disp>9)    LCD_Data(disp % 100/10+'0');    //��ܤQ���
    else        LCD_Data(' ');            
                LCD_Data(disp % 10+'0');        //��ܭӦ��
}
