/*******KEY3******* ���䱱���� *************************
*�ʧ@�G��KEY1����}����J�㨾�����u���A�OLED���[��X
*���u�GPC0~7-->JP13(LEDx8)�APD11-->JP24(0), GND-->JP24(4)
*�ާ@�G��KEY1�OLEDx8���[
*************************************************************/
#include  "config.h" //�պA�μȦs���w�q
#define F 6000
#define T 600
#define STOP1 300

int main(void)
 {
	u8 i;
	u16 j,dly;
	Buzzer_DIR;
	 
  LEDx8_DIR;  			//�]�wLEDx8����X
  KEY1_DIR; 				//�P��KEY1��J�δ��ɹq��
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
