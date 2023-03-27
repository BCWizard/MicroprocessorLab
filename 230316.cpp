/*******KEY3******* 按鍵控制實習 *************************
*動作：由KEY1按鍵開關輸入具防止機械彈跳，令LED遞加輸出
*接線：PC0~7-->JP13(LEDx8)，PD11-->JP24(0), GND-->JP24(4)
*操作：按KEY1令LEDx8遞加
*************************************************************/
#include  "config.h" //組態及暫存器定義
#define F 6000
#define T 600
#define STOP1 300

int main(void)
 {
	u8 i;
	u16 j,dly;
	Buzzer_DIR;
	 
  LEDx8_DIR;  			//設定LEDx8為輸出
  KEY1_DIR; 				//致能KEY1輸入及提升電阻
	KEY2_DIR;
	KEY3_DIR;
	RGB_DIR;
	
	while(1){
		LEDx8_Data=~i;
	
		
		if(KEY1_0){
			i++;
			R_LED_1; G_LED_0; B_LED_0; Delay_ms(100);
			LEDx8_Data=~i;
		}
		//while(KEY1_1);
		
		if(KEY2_0){
			i--;
			R_LED_0; G_LED_1; B_LED_0; Delay_ms(100);
			LEDx8_Data=~i;
		}
		//while(KEY2_1);
		
		if(KEY3_0){
			i = 0;
			R_LED_0; G_LED_1; B_LED_0; Delay_ms(100);
			LEDx8_Data=~i;
			for(j=0;j<T;j++){
				Buzzer_T;
				dly = F; while(dly--);
			}
		}
		//while(KEY3_1);
	}
}
