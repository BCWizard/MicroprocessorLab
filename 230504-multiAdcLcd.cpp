/********ADC1A.C******AD轉換範例***************************
*動作︰啟動通道AD0轉換，並將一數位資料由LCD顯示
*接線：PC0~7-->JP19(DB0~7),PC10~12-->JP19(RS、RW、EN) 
*      PA0(ADC_IN0)-->JP16(Analog Output)，調整VR令0~3.3V->PA0(ADC_IN0)           
******************************************************************/
#include "arminno.h"
#include "config.h"
void LCD_Disp(uint16 count);
uint8 const   Table[]="C0="; //第一行陣列字元
uint8 const   Table1[]="C1="; //第二行陣列字元
uint8 const   Table2[]="C2="; //第一行陣列字元
uint8 const   Table3[]="C3="; //第一行陣列字元
void LCD_Disp(int16 count);

int main(void) 
{ 
	 uint16 Value; 
	 uint8 i;
	 LCD_init();        //重置及清除LCD    
	while(1) 
	{
		SetAdc(0);  //設定ADC Channel 0，並啟動ADC
		SetAdc(1);  //設定ADC Channel 0，並啟動ADC
		SetAdc(2);  //設定ADC Channel 0，並啟動ADC
		SetAdc(3);  //設定ADC Channel 0，並啟動ADC
		
		LCD_Cmd(0x80);     //游標由第一行開始顯示   
		for(i=0; i < sizeof(Table); i++) //讀取陣列字元到LCD顯示出來 
      LCD_Data(Table[i]);
		LCD_Cmd(0x88);     //游標由第一行開始顯示  
			for(i=0; i< sizeof(Table1); i++) //讀取陣列字元到LCD顯示出來 
				LCD_Data(Table1[i]); 
		LCD_Cmd(0xC0);     //游標由第一行開始顯示  
			for(i=0; i< sizeof(Table2); i++) //讀取陣列字元到LCD顯示出來 
				LCD_Data(Table2[i]); 
		LCD_Cmd(0xC8);     //游標由第一行開始顯示  
			for(i=0; i< sizeof(Table3); i++) //讀取陣列字元到LCD顯示出來 
				LCD_Data(Table3[i]); 
		
		LCD_Cmd(0x83);
		Value = GetAdc(0);  //讀取ADC0數位資料
    LCD_Disp(Value);    //顯示4位數十進制計數
		Pause(10000);
		
		LCD_Cmd(0x8B);
		Value = GetAdc(1);  //讀取ADC0數位資料
    LCD_Disp(Value);    //顯示4位數十進制計數
		Pause(10000);
		
		LCD_Cmd(0xC3);
		Value = GetAdc(2);  //讀取ADC0數位資料
    LCD_Disp(Value);    //顯示4位數十進制計數
		Pause(10000);
		
		LCD_Cmd(0xCB);
		Value = GetAdc(3);  //讀取ADC0數位資料
    LCD_Disp(Value);    //顯示4位數十進制計數
		Pause(10000);
	}
}
/********************************************************
*函數名稱: LCD_Disp
*功能描述: LCD顯示4位數十進制數字
*輸入參數：disp
*******************************************************/
void LCD_Disp(uint16 disp) 
{ 
	if(disp>999)  LCD_Data(disp /1000+'0');       //顯示千位數
    else        LCD_Data(' ');
  if(disp>99)   LCD_Data(disp % 1000/100+'0');  //顯示百位數
    else        LCD_Data(' ');
  if(disp>9)    LCD_Data(disp % 100/10+'0');    //顯示十位數
    else        LCD_Data(' ');            
                LCD_Data(disp % 10+'0');        //顯示個位數
}
