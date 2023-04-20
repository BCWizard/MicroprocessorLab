/*********** TEST_A *****AMA¤¤¯Å»{µý-´¼¼z­·®°Arminno½d¨Ò*********
*°Ê§@¡G¥ÑKEY1~3±±¨î°¨¹F¡A¨Ã¦b¤C¬qÅã¥Ü¾¹Åã¥Ü°Ê§@
*±µ½u¡GPC0~6-->JP7(a~g)¡A3.3V-->JP8(COM4)¡APA10-->JP9(Buzzer)¡A
*      PA12-->JP3(IN1)¡APA13-->JP3(IN2)¡AGND-->JP3(IN3)
*      PD11-->JP24(0)¡APD12-->JP24(1)¡APD13-->JP24(2)¡AGND-->JP24(4) 
*¾Þ§@¡G«öKEY1°¨¹F¥¿Âà¡AÅã¥Ü'F'¡A¹Í0.3¬í¤@¦¸
*      «öKEY2°¨¹F°±¤î¡AÅã¥Ü'S'¡A¹Í1¬í¤@¦¸¡C
*      «öKEY3°¨¹F¤ÏÂà¡AÅã¥Ü'b'¡A¹Í0.3¬í¨â¦¸¡A¶¡¹j0.1¬í¡C
***********************************************************/
#include "arminno.h"
u8 inputFSB;
void Display(u8 inputFSB);
void beep(u8 i);   //«Å§i¹ÍÁn¨ç¼Æ
#define KEY1  	PC11
#define KEY2  	PC12 
#define KEY3  	PC13 

#define Buzzer 	PA13
#define IN1  		PA8
#define IN2  		PA9

#define  SEG   PORTE
#define  com1  PD0
#define  com2  PD1
#define  com3  PD2
#define  com4  PD3

#define  SEG_S  0x6d  //Åã¥Ü'S'¼Æ½X
#define  SEG_b  0x7c  //Åã¥Ü'b'¼Æ½X
#define  SEG_F  0x71  //Åã¥Ü'F'¼Æ½X
#define	 SEG_2  0x5b
#define	 SEG_0  0x3f

int main(void) 
{
  InitialGpioState(KEY1,0,2);  //¿é¤J§t´£¤É¹qªý 
	InitialGpioState(KEY2,0,2);  //¿é¤J§t´£¤É¹qªý
	InitialGpioState(KEY3,0,2);  //¿é¤J§t´£¤É¹qªý
	Output(Buzzer);   		//³]©wBuzzer¬°¿é¥X
 	Output(IN1);   				//³]©wIN1¬°¿é¥X
	Output(IN2);   				//³]©wIN2¬°¿é¥X
  SetDirPort(SEG,0);    //³]©wSEG¬°¿é¥X	
	//WritePort(SEG,SEG_S); //Åã¥Ü'S'
	inputFSB=SEG_S;
	Low(IN1);Low(IN2);		//°¨¹F°±¤î
	Low(Buzzer);   
  while(1)     		//­«ÂÐ°õ¦æ
   {
		 Display(inputFSB);
     if(!In(KEY1)) //«öKEY1°¨¹F¥¿Âà¡AÅã¥Ü'F'¡A¹Í0.3¬í¤@Án
       //{High(IN1);Low(IN2); WritePort(SEG,SEG_F); beep(1);}
		 {High(IN1);Low(IN2); inputFSB=SEG_F; beep(1);} 
		 
		 if(!In(KEY2)) //«öKEY2°¨¹F°±¤î¡AÅã¥Ü'S'¡A¹Í1¬í¤@Án
        //{Low(IN1);Low(IN2);WritePort(SEG,SEG_S);beep(1);}  
		 {Low(IN1);Low(IN2); inputFSB=SEG_S;beep(1);} 
		 
		 if(!In(KEY3))//«öKEY3°¨¹F¤ÏÂà¡AÅã¥Ü'b'¡A¹Í0.3¬í¨âÁn
        //{Low(IN1);High(IN2);WritePort(SEG,SEG_b);beep(2);}	
		 {Low(IN1);High(IN2); inputFSB=SEG_b;beep(1);} 
	 } 
}
//*****************¹ÍÁn¨ç¼Æ***************************
void beep(u8 i)
{
  u16  j;		//Buzzer¤Ï¬Û¦¸¼Æ=­µªø
  while(i--)	//¹Í¹ÍÁn¦¸¼Æ
	{	
	 if(In(KEY2)==0) j=1000; //­Y«öKEY2­µªø=1¬í
              else j=300;	 //­Y«D«öKEY2­µªø=0.3¬í
		while(j--) 
    {		
			Toggle(Buzzer); //Buzzer¤Ï¬Û,¥O¸Á»ï¾¹µo¥XÁn­µ
			Pause(10);	//­µÀW©µ®É=500Hz
    }
	 Low(Buzzer);
	 Pause(1000);	//¹Í¹ÍÁn¶¡¹j0.1¬í
	}		
  while(!(In(KEY1) && In(KEY2) && In(KEY3)));	//µ¥«Ý©ñ¶}«öÁä
  Pause(10);	
}
void Display(u8 inputFSB)  //¥|¦ì¼Æ¤C¬qÅã¥Ü¾¹±½´y	 
{  
  u8 scan=200;     //¤C¬qÅã¥Ü¾¹±½´y¦¸¼Æ¡A¨M®É©µ®É®É¶¡
	while(scan--)    //­«ÂÐ±½´y¦¸¼Æ 
   {
     WritePort(SEG,SEG_2); //®É¤Q¦ì¼Æ¿é¥X
     High(com1);  Pause(10); 			//¿ï¾Ü¤d¦ì¼ÆÅã¥Ü¾¹ 
		 Low(com1);
        
     WritePort(SEG,SEG_2); //®É­Ó¦ì¼Æ¿é¥X
		 High(com2); Pause(10); 			//¿ï¾Ü¦Ê¦ì¼ÆÅã¥Ü¾¹
		 Low(com2);

		 WritePort(SEG,SEG_0);//¤À¤Q¦ì¼Æ¿é¥X
     High(com3); Pause(10);    	//¿ï¾Ü¤Q¦ì¼ÆÅã¥Ü¾¹
		 Low(com3);

		 WritePort(SEG,inputFSB);//¤À­Ó¦ì¼Æ¿é¥X
		 High(com4);  Pause(10);  //¿ï¾Ü­Ó¦ì¼Æ
		 Low(com4);
   }	   
}

/*
void Display(u8 inputFSB)  //¥|¦ì¼Æ¤C¬qÅã¥Ü¾¹±½´y	 
{  
  u8 scan=200;     //¤C¬qÅã¥Ü¾¹±½´y¦¸¼Æ¡A¨M®É©µ®É®É¶¡
	while(scan--)    //­«ÂÐ±½´y¦¸¼Æ 
   {
		 Low(com1);Low(com2);Low(com3);Low(com4);
     WritePort(SEG,SEG_2); //®É¤Q¦ì¼Æ¿é¥X
     High(com1);  Pause(10); 			//¿ï¾Ü¤d¦ì¼ÆÅã¥Ü¾¹ 
        
		 Low(com1);Low(com2);Low(com3);Low(com4);
     WritePort(SEG,SEG_2); //®É­Ó¦ì¼Æ¿é¥X
		 High(com2); Pause(10); 			//¿ï¾Ü¦Ê¦ì¼ÆÅã¥Ü¾¹
			
		 Low(com1);Low(com2);Low(com3);Low(com4);
		 WritePort(SEG,SEG_0);//¤À¤Q¦ì¼Æ¿é¥X
     High(com3); Pause(10);    	//¿ï¾Ü¤Q¦ì¼ÆÅã¥Ü¾¹
			
		 Low(com1);Low(com2);Low(com3);Low(com4);
		 WritePort(SEG,inputFSB);//¤À­Ó¦ì¼Æ¿é¥X
		 High(com4);  Pause(10);  //¿ï¾Ü­Ó¦ì¼Æ
   }	   
}
*/