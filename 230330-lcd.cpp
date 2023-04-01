/************** LCD1 ******LCD��߽d��********
*�ʧ@�G�bLCD���"COUNT="�A�A�������-9999~+9999
*���u�GPC0~7-->JP19(DB0~7),PC10~12-->JP19(RS�BRW�BEN) 
**********************************************************/
#include  "config.h"
uint8 const   Table[]="COUNT="; //�Ĥ@��}�C�r��
void LCD_Disp(int16 count);

int main(void)
{
   int16 count=-88; //��ܭp�ƤQ�i����
   uint8 i;   		  //�}�C��ƭp��
   LCD_init();        //���m�βM��LCD    
   LCD_Cmd(0xC0);     //��ХѲĤ@��}�l��� 											//00-0F,0x80
   for(i=0; i< sizeof(Table); i++) //Ū���}�C�r����LCD��ܥX�� 
      LCD_Data(Table[i]);   
   while(1)         //���а���
   {
     LCD_Cmd(0xC6);    //��ХѲĤ@���6�r�}�l���  							//40-4F,0xC0
     LCD_Disp(count--);//���4��ƤQ�i��p�Ƥέp�ƻ���
	 if(count > 9999) count=-9999; 
	 if(count < -9999) count=9999;
     Delay_ms(100);
   }
 }
/********************************************************
*��ƦW��: LCD_Disp
*�\��y�z: LCD���4��Ʀ����t�Ÿ��Q�i��Ʀr
*��J�ѼơGdisp
*******************************************************/
void LCD_Disp(int16 disp) 
{
 if(disp<0) {LCD_Data('-');disp=-disp;}
    else     LCD_Data('+');
 if(disp>999)  LCD_Data(disp /1000+'0');       //��ܤd���
    else       LCD_Data(' ');
 if(disp>99)   LCD_Data(disp % 1000/100+'0');  //��ܦʦ��
   else        LCD_Data(' ');
if(disp>9)     LCD_Data(disp % 100/10+'0');    //��ܤQ���
   else        LCD_Data(' ');            
               LCD_Data(disp % 10+'0');        //��ܭӦ��
} 
