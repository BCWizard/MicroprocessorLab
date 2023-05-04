/********ADC1A.C******AD轉換範例***************************
*動作︰啟動通道AD0轉換，並將一數位資料由LCD顯示
*接線：PC0~7-->JP19(DB0~7),PC10~12-->JP19(RS、RW、EN) 
*      PA0(ADC_IN0)-->JP16(Analog Output)，調整VR令0~3.3V->PA0(ADC_IN0)           
******************************************************************/
#include "arminno.h"
#include  "config.h"
void LCD_Disp(uint16 count);
uint8 const   Table[]="ADC_IN0="; //第一行陣列字元
void LCD_Disp(int16 count);
int main(void) 
{ 
	 uint16 Value; 
	 uint8 i;
	 LCD_init();        //重置及清除LCD    
   LCD_Cmd(0x80);     //游標由第一行開始顯示  
   for(i=0; i< sizeof(Table); i++) //讀取陣列字元到LCD顯示出來 
      LCD_Data(Table[i]);  
	
	SetAdc(0);  //設定ADC Channel 0，並啟動ADC
	while(1) 
	{
		Value = GetAdc(0)*330/4095;  //讀取ADC0數位資料
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
 	LCD_Cmd(0x88);    //游標由第一行第8字開始顯示  
	if(disp>999)  LCD_Data(disp /1000+'0');       //顯示千位數
    else        LCD_Data(' ');
  if(disp>99)   LCD_Data(disp % 1000/100+'0');  //顯示百位數
    else        LCD_Data(' ');
  if(disp>9)    LCD_Data(disp % 100/10+'0');    //顯示十位數
    else        LCD_Data(' ');            
                LCD_Data(disp % 10+'0');        //顯示個位數
}
/********adc_7seg.C******AD轉換範例***************************
*動作︰啟動通道AD0轉換，並將一數位資料由7段顯示器顯示
*接線：PC0~6-->JP7(a~g)，PC10~13-->JP8(com1~4) 
*      PA0(ADC_IN0)-->JP16(Analog Output)，調整VR令0~3.3V->PA0(ADC_IN0)           
******************************************************************/
/*
#include "arminno.h"
#include  "config.h"

void	Seg_Disp(uint16 count);

int main(void) 
{ 
	 uint16 Value; 
	 uint8 i;
     SEG_DIR;       //設定SEG接腳為輸出
	
	SetAdc(0);  //設定ADC Channel 0，並啟動ADC
	while(1) 
	{
		Value = GetAdc(0);  //讀取ADC0數位資料
    	Seg_Disp(Value);    //顯示4位數十進制計數
		Pause(10000);
	}
}
*/
/************ SEG2 ****七段顯示器範例*************
*動作：四位數掃描計數器，以10進制顯示0000~9999
*接線：PC0~6-->JP7(a~g)，PC10~13-->JP8(com1~4)
***********************************************/
/*
void Seg_Disp(uint16 count) 
{
  u8 scan;       //掃描次數  
  u8 i;          //擷取計數的個、十、百、千位數

     for(scan=0;scan<200;scan++)  //重覆掃描次數 
     {
       i=count/1000;    			//取出千位數
       SEG_Data=SEG_Table[i]; //千位數輸出
       if(count>999) SEG_C1; 	//若計數>999，顯示千位數
       Delay_ms(1);           //掃描延時	     
				
	   i=(count % 1000)/100; 	//取出百位數 
       SEG_Data=SEG_Table[i]; //百位數輸出
       if(count>99) SEG_C2;		//若計數>99，顯示百位數
       Delay_ms(1);           //掃描延時			 

 	   i=(count % 100)/10;		//取出十位數 
       SEG_Data=SEG_Table[i]; //十位數輸出
       if(count>9) SEG_C3;		//若計數>9，顯示十位數
       Delay_ms(1);           //掃描延時       
				
	   i=count % 10;    			//取出個位數
       SEG_Data=SEG_Table[i];//個位數輸出
       //SEG_Mask; 
	   SEG_C4;     	//選擇個位數顯示器
       Delay_ms(1);         	//掃描延時  
     }//end of for loop   
}
*/


