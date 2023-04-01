/************ SEG3 *****七段顯示器範例**********************
*動作：由四位數七段顯示器顯示電子鐘的時、分及秒為閃爍
*      ，按KEY1調時，按KEY2調分
*接線：PC0~6-->JP7(a~g)，PC7-->JP8(dps)，PC10~13-->JP8(C1~C4)
*      PD11~12-->JP24(0~1)，GND-->JP24(4)
************************************************************/
#include "config.h"  // 組態及暫存器設定 

#define F 6000
#define T 600
#define STOP1 300

void Display(void); //四位數七段顯示器掃描
int8 hor=23,min=2,sec=18; //設定時、分、秒時間

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
	bool countDown = 0;
  SEG_DIR;        	 //設定SEG接腳為輸出
	KEY1_DIR; KEY2_DIR; KEY3_DIR;//設定KEY接腳為輸入
	Buzzer_DIR;
  while(1)
  {
		if(KEY2_0){
			sec--;  //按KEY2調sec  
			if(sec<0) {
				min--;
				sec=59;
			}
		}
		if(KEY1_0){ 
			min--;  //按KEY1調min
			if(min<0) {
				hor--;
				min=59;				
			}
		}
		if(KEY3_0) 
			countDown=~countDown; 
		
		Display(); //七段顯示器顯示時間
		
		if(countDown){
			if(sec+min*60 == 135){
				countDown = 0;
				beep(1);        //嗶一聲
				Buzzer_0; Delay_ms(STOP1); //蜂鳴器停止，間隔時間
			}
			sec--;               //秒加一
			if (sec >= 0) continue; //若秒小於60，從頭執行   
				sec=59; min--;        //秒等於60則令秒=0，分加一
			if (min >= 0) continue; //若分小於60，從頭執行    
				min=59; hor--;        //若分等於60則令分=0，時加一
			if (hor >= 0) continue; //若時小於24，從頭執行 
				hor=0; min=0; sec=0; //若時等於24則令時、分、秒=0
		}
   }
 }	 
//***************************************************	 
void Display(void)  //四位數七段顯示器掃描	 
{  
  u8 scan=100;     //七段顯示器掃描次數，決時延時時間
	while(scan--)    //重覆掃描次數 
    {
			SEG_Data=SEG_Table[min/10];//時十位數輸出
      SEG_C1; Delay_ms(1); 			 //選擇千位數顯示器 

      if(scan<100) 	SEG_Data=SEG_Table[min%10];//時個數輸出
				else SEG_Data=SEG_Table[min%10]|0x80;//時個數輸出+秒亮
      SEG_C2; Delay_ms(1); 			 //選擇百位數顯示器 
			
			SEG_Data=SEG_Table[sec/10];//分十位數輸出
      SEG_C3;  Delay_ms(1);      //選擇十位數顯示器			 
			 
			SEG_Data=SEG_Table[sec%10];//分個位數輸出
      SEG_C4; Delay_ms(1);    	 //選擇個位數顯示器
    }	   
}
