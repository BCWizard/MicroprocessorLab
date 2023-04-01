/************** LCD1 ******LCD¹ê²ß½d¨Ò********
*°Ê§@¡G¦bLCDÅã¥Ü"COUNT="¡A¦A­«ÂÐÅã¥Ü-9999~+9999
*±µ½u¡GPC0~7-->JP19(DB0~7),PC10~12-->JP19(RS¡BRW¡BEN) 
**********************************************************/
#include  "config.h"
uint8 const   Table[]="COUNT="; //²Ä¤@¦æ°}¦C¦r¤¸
void LCD_Disp(int16 count);

int main(void)
{
   int16 count=-88; //Åã¥Ü­p¼Æ¤Q¶i¨îªì­È
   uint8 i;   		  //°}¦C¸ê®Æ­p¼Æ
   LCD_init();        //­«¸m¤Î²M°£LCD    
   LCD_Cmd(0xC0);     //´å¼Ð¥Ñ²Ä¤@¦æ¶}©lÅã¥Ü 											//00-0F,0x80
   for(i=0; i< sizeof(Table); i++) //Åª¨ú°}¦C¦r¤¸¨ìLCDÅã¥Ü¥X¨Ó 
      LCD_Data(Table[i]);   
   while(1)         //­«ÂÐ°õ¦æ
   {
     LCD_Cmd(0xC6);    //´å¼Ð¥Ñ²Ä¤@¦æ²Ä6¦r¶}©lÅã¥Ü  							//40-4F,0xC0
     LCD_Disp(count--);//Åã¥Ü4¦ì¼Æ¤Q¶i¨î­p¼Æ¤Î­p¼Æ»¼´î
	 if(count > 9999) count=-9999; 
	 if(count < -9999) count=9999;
     Delay_ms(100);
   }
 }
/********************************************************
*¨ç¼Æ¦WºÙ: LCD_Disp
*¥\¯à´y­z: LCDÅã¥Ü4¦ì¼Æ¦³¥¿­t²Å¸¹¤Q¶i¨î¼Æ¦r
*¿é¤J°Ñ¼Æ¡Gdisp
*******************************************************/
void LCD_Disp(int16 disp) 
{
 if(disp<0) {LCD_Data('-');disp=-disp;}
    else     LCD_Data('+');
 if(disp>999)  LCD_Data(disp /1000+'0');       //Åã¥Ü¤d¦ì¼Æ
    else       LCD_Data(' ');
 if(disp>99)   LCD_Data(disp % 1000/100+'0');  //Åã¥Ü¦Ê¦ì¼Æ
   else        LCD_Data(' ');
if(disp>9)     LCD_Data(disp % 100/10+'0');    //Åã¥Ü¤Q¦ì¼Æ
   else        LCD_Data(' ');            
               LCD_Data(disp % 10+'0');        //Åã¥Ü­Ó¦ì¼Æ
} 
