/************ SEG2 ****七段顯示器範例*************
*動作：四位數掃描計數器，以10進制顯示0000~9999
*接線：PC0~6-->JP7(a~g)，PC10~13-->JP8(com1~4)
***********************************************/
//seg??; RGB; K1->stopCount,beep1,R; K2->startCount,beep2,G; K3->reset,beep3,B;
#include "config.h"  // 組態及暫存器設定 
#define F 6000
#define T 600
#define STOP1 300
#define STOP2 1000

void beep(u8 i)
{
  u16  j,dly;		//Buzzer反相次數
  while(i--)   	//嗶聲次數
   {
     for(j=0;j<T;j++) //輸出反相次數，決定音長
      {		
				while(KEY1_0) Buzzer_0; //若按KEY1鍵，蜂鳴器停止
				Buzzer_T; 							//Buzzer反相,令蜂鳴器發出聲音
				dly=F; while(dly--);		//音頻延時
      }
	  Buzzer_0; Delay_ms(STOP1);	//蜂鳴器停止，嗶聲的間隔時間
  }
}

int main(void) 
{
  u8 scan;       //掃描次數  
  u16 count=65280;   //計數十進制初值 
		bool countCtrl = 0;
  u8 i;          //擷取計數的個、十、百、千位數
  SEG_DIR;       //設定SEG接腳為輸出
	//u16 j,dly;
	Buzzer_DIR;
	
	KEY1_DIR; 				//致能KEY1輸入及提升電阻
	KEY2_DIR;
	KEY3_DIR;
	RGB_DIR;
	
   while(1)     //重覆執行
    {
			if(KEY1_0){
				countCtrl = 0;
				R_LED_1; G_LED_0; B_LED_0; Delay_ms(100);
				beep(1);        //嗶一聲
				Buzzer_0; Delay_ms(STOP2); //蜂鳴器停止，間隔時間
			}
		
			if(KEY2_0){
				countCtrl = 1;
				R_LED_0; G_LED_1; B_LED_0; Delay_ms(100);
				beep(2);        //嗶一聲
				Buzzer_0; Delay_ms(STOP2); //蜂鳴器停止，間隔時間
			}
		
			if(KEY3_0){
				count = 0;
				countCtrl = 0;
				R_LED_0; G_LED_0; B_LED_1; Delay_ms(100);
				beep(3);        //嗶一聲
				Buzzer_0; Delay_ms(STOP2); //蜂鳴器停止，間隔時間
			}
			
     for(scan=0;scan<200;scan++)  //重覆掃描次數 
      {
       i=count/4096;    			//取出千位數
       SEG_Data=SEG_Table[i]; //千位數輸出
       //if(count>4095) 
				 SEG_C1; 	//若計數>999，顯示千位數
       Delay_ms(1);           //掃描延時	     
				
			 i=(count % 4096)/256; 	//取出百位數 
       SEG_Data=SEG_Table[i]; //百位數輸出
       //if(count>255) 
				 SEG_C2;		//若計數>99，顯示百位數
       Delay_ms(1);           //掃描延時			 

 			 i=(count % 256)/16;		//取出十位數 
       SEG_Data=SEG_Table[i]; //十位數輸出
       //if(count>15) 
				 SEG_C3;		//若計數>9，顯示十位數
       Delay_ms(1);           //掃描延時       
				
			 i=count % 16;    			//取出個位數
			 SEG_Data=SEG_Table[i];//個位數輸出
       SEG_Mask; SEG_C4;     	//選擇個位數顯示器
       Delay_ms(1);         	//掃描延時  
      }	   
			if(countCtrl)
				count++;          				//計數+1 
	 if(count>65535) count=0; 		//若計數超過9999，計數=0
   } 
}

