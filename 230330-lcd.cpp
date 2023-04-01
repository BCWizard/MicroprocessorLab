/************** LCD1 ******LCD實習範例********
*動作：在LCD顯示"COUNT="，再重覆顯示-9999~+9999
*接線：PC0~7-->JP19(DB0~7),PC10~12-->JP19(RS、RW、EN) 
**********************************************************/
#include  "config.h"
uint8 const   Table[]="COUNT="; //第一行陣列字元
void LCD_Disp(int16 count);

int main(void)
{
   int16 count=-88; //顯示計數十進制初值
   uint8 i;   		  //陣列資料計數
   LCD_init();        //重置及清除LCD    
   LCD_Cmd(0xC0);     //游標由第一行開始顯示 											//00-0F,0x80
   for(i=0; i< sizeof(Table); i++) //讀取陣列字元到LCD顯示出來 
      LCD_Data(Table[i]);   
   while(1)         //重覆執行
   {
     LCD_Cmd(0xC6);    //游標由第一行第6字開始顯示  							//40-4F,0xC0
     LCD_Disp(count--);//顯示4位數十進制計數及計數遞減
	 if(count > 9999) count=-9999; 
	 if(count < -9999) count=9999;
     Delay_ms(100);
   }
 }
/********************************************************
*函數名稱: LCD_Disp
*功能描述: LCD顯示4位數有正負符號十進制數字
*輸入參數：disp
*******************************************************/
void LCD_Disp(int16 disp) 
{
 if(disp<0) {LCD_Data('-');disp=-disp;}
    else     LCD_Data('+');
 if(disp>999)  LCD_Data(disp /1000+'0');       //顯示千位數
    else       LCD_Data(' ');
 if(disp>99)   LCD_Data(disp % 1000/100+'0');  //顯示百位數
   else        LCD_Data(' ');
if(disp>9)     LCD_Data(disp % 100/10+'0');    //顯示十位數
   else        LCD_Data(' ');            
               LCD_Data(disp % 10+'0');        //顯示個位數
} 
