/************ SEG3 *****¤C¬qÅã¥Ü¾¹½d¨Ò**********************
*°Ê§@¡G¥Ñ¥|¦ì¼Æ¤C¬qÅã¥Ü¾¹Åã¥Ü¹q¤lÄÁªº®É¡B¤À¤Î¬í¬°°{Ã{
*      ¡A«öKEY1½Õ®É¡A«öKEY2½Õ¤À
*±µ½u¡GPC0~6-->JP7(a~g)¡APC7-->JP8(dps)¡APC10~13-->JP8(C1~C4)
*      PD11~12-->JP24(0~1)¡AGND-->JP24(4)
************************************************************/
#include "config.h"  // ²ÕºA¤Î¼È¦s¾¹³]©w 

#define F 6000
#define T 600
#define STOP1 300

void Display(void); //¥|¦ì¼Æ¤C¬qÅã¥Ü¾¹±½´y
int8 hor=23,min=2,sec=18; //³]©w®É¡B¤À¡B¬í®É¶¡

void beep(u8 i)
{
  u16  j,dly;		//Buzzer¤Ï¬Û¦¸¼Æ
  while(i--)   	//¹ÍÁn¦¸¼Æ
   {
     for(j=0;j<T;j++) //¿é¥X¤Ï¬Û¦¸¼Æ¡A¨M©w­µªø
      {		
				while(KEY1_0) Buzzer_0; //­Y«öKEY1Áä¡A¸Á»ï¾¹°±¤î
				Buzzer_T; 							//Buzzer¤Ï¬Û,¥O¸Á»ï¾¹µo¥XÁn­µ
				dly=F; while(dly--);		//­µÀW©µ®É
      }
	  Buzzer_0; Delay_ms(STOP1);	//¸Á»ï¾¹°±¤î¡A¹ÍÁnªº¶¡¹j®É¶¡
  }
}

int main(void) 
{
	bool countDown = 0;
  SEG_DIR;        	 //³]©wSEG±µ¸}¬°¿é¥X
	KEY1_DIR; KEY2_DIR; KEY3_DIR;//³]©wKEY±µ¸}¬°¿é¤J
	Buzzer_DIR;
  while(1)
  {
		if(KEY2_0){
			sec--;  //«öKEY2½Õsec  
			if(sec<0) {
				min--;
				sec=59;
			}
		}
		if(KEY1_0){ 
			min--;  //«öKEY1½Õmin
			if(min<0) {
				hor--;
				min=59;				
			}
		}
		if(KEY3_0) 
			countDown=~countDown; 
		
		Display(); //¤C¬qÅã¥Ü¾¹Åã¥Ü®É¶¡
		
		if(countDown){
			if(sec+min*60 == 135){
				countDown = 0;
				beep(1);        //¹Í¤@Án
				Buzzer_0; Delay_ms(STOP1); //¸Á»ï¾¹°±¤î¡A¶¡¹j®É¶¡
			}
			sec--;               //¬í¥[¤@
			if (sec >= 0) continue; //­Y¬í¤p©ó60¡A±qÀY°õ¦æ   
				sec=59; min--;        //¬íµ¥©ó60«h¥O¬í=0¡A¤À¥[¤@
			if (min >= 0) continue; //­Y¤À¤p©ó60¡A±qÀY°õ¦æ    
				min=59; hor--;        //­Y¤Àµ¥©ó60«h¥O¤À=0¡A®É¥[¤@
			if (hor >= 0) continue; //­Y®É¤p©ó24¡A±qÀY°õ¦æ 
				hor=0; min=0; sec=0; //­Y®Éµ¥©ó24«h¥O®É¡B¤À¡B¬í=0
		}
   }
 }	 
//***************************************************	 
void Display(void)  //¥|¦ì¼Æ¤C¬qÅã¥Ü¾¹±½´y	 
{  
  u8 scan=100;     //¤C¬qÅã¥Ü¾¹±½´y¦¸¼Æ¡A¨M®É©µ®É®É¶¡
	while(scan--)    //­«ÂÐ±½´y¦¸¼Æ 
    {
			SEG_Data=SEG_Table[min/10];//®É¤Q¦ì¼Æ¿é¥X
      SEG_C1; Delay_ms(1); 			 //¿ï¾Ü¤d¦ì¼ÆÅã¥Ü¾¹ 

      if(scan<100) 	SEG_Data=SEG_Table[min%10];//®É­Ó¼Æ¿é¥X
				else SEG_Data=SEG_Table[min%10]|0x80;//®É­Ó¼Æ¿é¥X+¬í«G
      SEG_C2; Delay_ms(1); 			 //¿ï¾Ü¦Ê¦ì¼ÆÅã¥Ü¾¹ 
			
			SEG_Data=SEG_Table[sec/10];//¤À¤Q¦ì¼Æ¿é¥X
      SEG_C3;  Delay_ms(1);      //¿ï¾Ü¤Q¦ì¼ÆÅã¥Ü¾¹			 
			 
			SEG_Data=SEG_Table[sec%10];//¤À­Ó¦ì¼Æ¿é¥X
      SEG_C4; Delay_ms(1);    	 //¿ï¾Ü­Ó¦ì¼ÆÅã¥Ü¾¹
    }	   
}
