#line 1 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\init_Codec.c"








 


#line 1 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\board.h"








 







#line 1 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"






 







 

#pragma language=extended
#line 37 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 73 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"





 
#line 97 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"




 







 

 
__sfr __no_init volatile union { unsigned char P0; struct { unsigned char P0_0 : 1; unsigned char P0_1 : 1; unsigned char P0_2 : 1; unsigned char P0_3 : 1; unsigned char P0_4 : 1; unsigned char P0_5 : 1; unsigned char P0_6 : 1; unsigned char P0_7 : 1; }; } @ 0x80;
__sfr __no_init volatile unsigned char SP @ 0x81;    
__sfr __no_init volatile unsigned char DPL0 @ 0x82;    
__sfr __no_init volatile unsigned char DPH0 @ 0x83;    
__sfr __no_init volatile unsigned char DPL1 @ 0x84;    
__sfr __no_init volatile unsigned char DPH1 @ 0x85;    
__sfr __no_init volatile unsigned char U0CSR @ 0x86;    
__sfr __no_init volatile unsigned char PCON @ 0x87;    

 
__sfr __no_init volatile union { unsigned char TCON; struct { unsigned char _TCON0 : 1; unsigned char RFTXRXIF : 1; unsigned char _TCON2 : 1; unsigned char URX0IF : 1; unsigned char _TCON4 : 1; unsigned char ADCIF : 1; unsigned char _TCON6 : 1; unsigned char URX1IF : 1; }; } @ 0x88;
__sfr __no_init volatile unsigned char P0IFG @ 0x89;    
__sfr __no_init volatile unsigned char P1IFG @ 0x8A;    
__sfr __no_init volatile unsigned char P2IFG @ 0x8B;    
__sfr __no_init volatile unsigned char PICTL @ 0x8C;    
__sfr __no_init volatile unsigned char P1IEN @ 0x8D;    
__sfr __no_init volatile unsigned char _SFR8E @ 0x8E;    
__sfr __no_init volatile unsigned char P0INP @ 0x8F;    

 
__sfr __no_init volatile union { unsigned char P1; struct { unsigned char P1_0 : 1; unsigned char P1_1 : 1; unsigned char P1_2 : 1; unsigned char P1_3 : 1; unsigned char P1_4 : 1; unsigned char P1_5 : 1; unsigned char P1_6 : 1; unsigned char P1_7 : 1; }; } @ 0x90;
__sfr __no_init volatile unsigned char RFIM @ 0x91;    
__sfr __no_init volatile unsigned char DPS @ 0x92;    
__sfr __no_init volatile unsigned char MPAGE @ 0x93;    
__sfr __no_init volatile unsigned char _SFR94 @ 0x94;    
__sfr __no_init volatile unsigned char _SFR95 @ 0x95;    
__sfr __no_init volatile unsigned char _SFR96 @ 0x96;    
__sfr __no_init volatile unsigned char _SFR97 @ 0x97;    

 
__sfr __no_init volatile union { unsigned char S0CON; struct { unsigned char ENCIF_0 : 1; unsigned char ENCIF_1 : 1; unsigned char _SOCON2 : 1; unsigned char _SOCON3 : 1; unsigned char _SOCON4 : 1; unsigned char _SOCON5 : 1; unsigned char _SOCON6 : 1; unsigned char _SOCON7 : 1; }; } @ 0x98;
__sfr __no_init volatile unsigned char _SFR99 @ 0x99;    
__sfr __no_init volatile unsigned char IEN2 @ 0x9A;    
__sfr __no_init volatile unsigned char S1CON @ 0x9B;    
__sfr __no_init volatile unsigned char T2CT @ 0x9C;    
__sfr __no_init volatile unsigned char T2PR @ 0x9D;    
__sfr __no_init volatile unsigned char T2CTL @ 0x9E;    
__sfr __no_init volatile unsigned char _SFR9F @ 0x9F;    

 
__sfr __no_init volatile union { unsigned char P2; struct { unsigned char P2_0 : 1; unsigned char P2_1 : 1; unsigned char P2_2 : 1; unsigned char P2_3 : 1; unsigned char P2_4 : 1; unsigned char _P2_5 : 1; unsigned char _P2_6 : 1; unsigned char _P2_7 : 1; }; } @ 0xA0;
__sfr __no_init volatile unsigned char WORIRQ @ 0xA1;    
__sfr __no_init volatile unsigned char WORCTRL @ 0xA2;    
__sfr __no_init volatile unsigned char WOREVT0 @ 0xA3;    
__sfr __no_init volatile unsigned char WOREVT1 @ 0xA4;    
__sfr __no_init volatile unsigned char WORTIME0 @ 0xA5;    
__sfr __no_init volatile unsigned char WORTIME1 @ 0xA6;    
__sfr __no_init volatile unsigned char _SFRA7 @ 0xA7;    

 
__sfr __no_init volatile union { unsigned char IEN0; struct { unsigned char RFTXRXIE : 1; unsigned char ADCIE : 1; unsigned char URX0IE : 1; unsigned char URX1IE : 1; unsigned char ENCIE : 1; unsigned char STIE : 1; unsigned char _IEN06 : 1; unsigned char EA : 1; }; } @ 0xA8;
__sfr __no_init volatile unsigned char IP0 @ 0xA9;    
__sfr __no_init volatile unsigned char _SFRAA @ 0xAA;    
__sfr __no_init volatile unsigned char FWT @ 0xAB;    
__sfr __no_init volatile unsigned char FADDRL @ 0xAC;    
__sfr __no_init volatile unsigned char FADDRH @ 0xAD;    
__sfr __no_init volatile unsigned char FCTL @ 0xAE;    
__sfr __no_init volatile unsigned char FWDATA @ 0xAF;    

__sfr __no_init volatile unsigned char _SFRB0 @ 0xB0;    
__sfr __no_init volatile unsigned char ENCDI @ 0xB1;    
__sfr __no_init volatile unsigned char ENCDO @ 0xB2;    
__sfr __no_init volatile unsigned char ENCCS @ 0xB3;    
__sfr __no_init volatile unsigned char ADCCON1 @ 0xB4;    
__sfr __no_init volatile unsigned char ADCCON2 @ 0xB5;    
__sfr __no_init volatile unsigned char ADCCON3 @ 0xB6;    
__sfr __no_init volatile unsigned char _SFRB7 @ 0xB7;    

 
__sfr __no_init volatile union { unsigned char IEN1; struct { unsigned char DMAIE : 1; unsigned char T1IE : 1; unsigned char T2IE : 1; unsigned char T3IE : 1; unsigned char T4IE : 1; unsigned char P0IE : 1; unsigned char _IEN16 : 1; unsigned char _IEN17 : 1; }; } @ 0xB8;
__sfr __no_init volatile unsigned char IP1 @ 0xB9;    
__sfr __no_init volatile unsigned char ADCL @ 0xBA;    
__sfr __no_init volatile unsigned char ADCH @ 0xBB;    
__sfr __no_init volatile unsigned char RNDL @ 0xBC;    
__sfr __no_init volatile unsigned char RNDH @ 0xBD;    
__sfr __no_init volatile unsigned char SLEEP @ 0xBE;    
__sfr __no_init volatile unsigned char _SFRBF @ 0xBF;    

 
__sfr __no_init volatile union { unsigned char IRCON; struct { unsigned char DMAIF : 1; unsigned char T1IF : 1; unsigned char T2IF : 1; unsigned char T3IF : 1; unsigned char T4IF : 1; unsigned char P0IF : 1; unsigned char _IRCON6 : 1; unsigned char STIF : 1; }; } @ 0xC0;
__sfr __no_init volatile unsigned char U0DBUF @ 0xC1;    
__sfr __no_init volatile unsigned char U0BAUD @ 0xC2;    
__sfr __no_init volatile unsigned char _SFRC3 @ 0xC3;    
__sfr __no_init volatile unsigned char U0UCR @ 0xC4;    
__sfr __no_init volatile unsigned char U0GCR @ 0xC5;    
__sfr __no_init volatile unsigned char CLKCON @ 0xC6;    
__sfr __no_init volatile unsigned char MEMCTR @ 0xC7;    

__sfr __no_init volatile unsigned char _SFRC8 @ 0xC8;    
__sfr __no_init volatile unsigned char WDCTL @ 0xC9;    
__sfr __no_init volatile unsigned char T3CNT @ 0xCA;    
__sfr __no_init volatile unsigned char T3CTL @ 0xCB;    
__sfr __no_init volatile unsigned char T3CCTL0 @ 0xCC;    
__sfr __no_init volatile unsigned char T3CC0 @ 0xCD;    
__sfr __no_init volatile unsigned char T3CCTL1 @ 0xCE;    
__sfr __no_init volatile unsigned char T3CC1 @ 0xCF;    

  
__sfr __no_init volatile union { unsigned char PSW; struct { unsigned char P : 1; unsigned char F1 : 1; unsigned char OV : 1; unsigned char RS0 : 1; unsigned char RS1 : 1; unsigned char F0 : 1; unsigned char AC : 1; unsigned char CY : 1; }; } @ 0xD0;
__sfr __no_init volatile unsigned char DMAIRQ @ 0xD1;    
__sfr __no_init volatile unsigned char DMA1CFGL @ 0xD2;    
__sfr __no_init volatile unsigned char DMA1CFGH @ 0xD3;    
__sfr __no_init volatile unsigned char DMA0CFGL @ 0xD4;    
__sfr __no_init volatile unsigned char DMA0CFGH @ 0xD5;    
__sfr __no_init volatile unsigned char DMAARM @ 0xD6;    
__sfr __no_init volatile unsigned char DMAREQ @ 0xD7;    

 
__sfr __no_init volatile union { unsigned char TIMIF; struct { unsigned char T3OVFIF : 1; unsigned char T3CH0IF : 1; unsigned char T3CH1IF : 1; unsigned char T4OVFIF : 1; unsigned char T4CH0IF : 1; unsigned char T4CH1IF : 1; unsigned char OVFIM : 1; unsigned char _TIMIF7 : 1; }; } @ 0xD8;
__sfr __no_init volatile unsigned char RFD @ 0xD9;    
__sfr __no_init volatile unsigned char T1CC0L @ 0xDA;    
__sfr __no_init volatile unsigned char T1CC0H @ 0xDB;    
__sfr __no_init volatile unsigned char T1CC1L @ 0xDC;    
__sfr __no_init volatile unsigned char T1CC1H @ 0xDD;    
__sfr __no_init volatile unsigned char T1CC2L @ 0xDE;    
__sfr __no_init volatile unsigned char T1CC2H @ 0xDF;    

__sfr __no_init volatile unsigned char ACC @ 0xE0;    
__sfr __no_init volatile unsigned char RFST @ 0xE1;    
__sfr __no_init volatile unsigned char T1CNTL @ 0xE2;    
__sfr __no_init volatile unsigned char T1CNTH @ 0xE3;    
__sfr __no_init volatile unsigned char T1CTL @ 0xE4;    
__sfr __no_init volatile unsigned char T1CCTL0 @ 0xE5;    
__sfr __no_init volatile unsigned char T1CCTL1 @ 0xE6;    
__sfr __no_init volatile unsigned char T1CCTL2 @ 0xE7;    

 
__sfr __no_init volatile union { unsigned char IRCON2; struct { unsigned char P2IF : 1; unsigned char UTX0IF : 1; unsigned char UTX1IF : 1; unsigned char P1IF : 1; unsigned char WDTIF : 1; unsigned char _IRCON25 : 1; unsigned char _IRCON26 : 1; unsigned char _IRCON27 : 1; }; } @ 0xE8;
__sfr __no_init volatile unsigned char RFIF @ 0xE9;    
__sfr __no_init volatile unsigned char T4CNT @ 0xEA;    
__sfr __no_init volatile unsigned char T4CTL @ 0xEB;    
__sfr __no_init volatile unsigned char T4CCTL0 @ 0xEC;    
__sfr __no_init volatile unsigned char T4CC0 @ 0xED;    
__sfr __no_init volatile unsigned char T4CCTL1 @ 0xEE;    
__sfr __no_init volatile unsigned char T4CC1 @ 0xEF;    

__sfr __no_init volatile unsigned char B @ 0xF0;    
__sfr __no_init volatile unsigned char PERCFG @ 0xF1;    
__sfr __no_init volatile unsigned char ADCCFG @ 0xF2;    
__sfr __no_init volatile unsigned char P0SEL @ 0xF3;    
__sfr __no_init volatile unsigned char P1SEL @ 0xF4;    
__sfr __no_init volatile unsigned char P2SEL @ 0xF5;    
__sfr __no_init volatile unsigned char P1INP @ 0xF6;    
__sfr __no_init volatile unsigned char P2INP @ 0xF7;    

 
__sfr __no_init volatile union { unsigned char U1CSR; struct { unsigned char U1ACTIVE : 1; unsigned char U1TX_BYTE : 1; unsigned char U1RX_BYTE : 1; unsigned char U1ERR : 1; unsigned char U1FE : 1; unsigned char U1SLAVE : 1; unsigned char U1RE : 1; unsigned char U1MODE : 1; }; } @ 0xF8; 
__sfr __no_init volatile unsigned char U1DBUF @ 0xF9;    
__sfr __no_init volatile unsigned char U1BAUD @ 0xFA;    
__sfr __no_init volatile unsigned char U1UCR @ 0xFB;    
__sfr __no_init volatile unsigned char U1GCR @ 0xFC;    
__sfr __no_init volatile unsigned char P0DIR @ 0xFD;    
__sfr __no_init volatile unsigned char P1DIR @ 0xFE;    
__sfr __no_init volatile unsigned char P2DIR @ 0xFF;    





 

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   





 

 







 
#line 464 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"





 
#line 479 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"





 












 
#line 506 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 515 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 524 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 533 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 542 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 551 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 560 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 569 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 578 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 587 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 596 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 605 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 614 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 623 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 632 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"

#line 641 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 5.4 Evaluation\\8051\\INC\\ioCC1110.h"


 

#pragma language=default



 
#line 18 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\board.h"
#line 1 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"










 


























 
typedef unsigned char       BOOL;


typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;


typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;


typedef signed char         INT8;
typedef signed short        INT16;
typedef signed long         INT32;












































 



























































#line 166 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"











#line 184 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"











#line 202 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"










#line 236 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"











#line 254 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"







 
















#line 301 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"










#line 334 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"

#line 358 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"





#line 370 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"







#line 383 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"









#line 439 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"






#line 491 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"







 











#line 516 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"









#line 556 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"























#pragma bitfields=reversed
typedef struct {
   BYTE SRCADDRH;
   BYTE SRCADDRL;
   BYTE DESTADDRH;
   BYTE DESTADDRL;
   BYTE VLEN      : 3;
   BYTE LENH      : 5;
   BYTE LENL      : 8;
   BYTE WORDSIZE  : 1;
   BYTE TMODE     : 2;
   BYTE TRIG      : 5;
   BYTE SRCINC    : 2;
   BYTE DESTINC   : 2;
   BYTE IRQMASK   : 1;
   BYTE M8        : 1;
   BYTE PRIORITY  : 2;
} DMA_DESC;
#pragma bitfields=default














#line 618 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"

#line 643 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"













































 































 
#line 756 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"


#line 791 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"

#line 825 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"






















#line 893 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"



#line 911 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"





































 









#line 1002 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"



#line 1013 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"











 


#line 1033 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"



#line 1057 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"






































 
void halFlashWritePage(BYTE *pSrcAddr, BYTE *pBuffer, BYTE page);





















 
void halFlashErasePage(BYTE* buffer, BYTE page);









 















#line 1157 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"









#line 1174 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"








#line 1197 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"


#line 1216 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"

#line 1234 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"






















 






















 
WORD halSetTimer1Period(DWORD period);




#line 1293 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"



#line 1316 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"














#line 1350 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"





                       






#line 1421 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"


#line 1469 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"

























 
BYTE halSetTimer34Period(BYTE timer, DWORD period);



#line 1507 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"








#line 1535 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"









#line 1564 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"



#line 1574 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"


#line 1584 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"

#line 1606 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"












 




























 






















#line 1681 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"















































 
INT16 halAdcSampleSingle(BYTE reference, BYTE resolution, UINT8 input);
















 
INT16 halGetAdcValue(void);











 



















 
BYTE halRfSendPacket(BYTE* pData, BYTE length);

























 
BYTE halRfReceivePacket(BYTE* pData, BYTE*pRssi, BYTE* pLqi, BYTE timeOut);



















 
BOOL halRfConfig(UINT32 frequency);















 
void halRfSetRadioFrequency(UINT32 frequency);

#line 1881 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"


#line 1932 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"



#line 1949 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"

#line 1989 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"



#line 2000 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"






 



















 




















 
void halAesLoadKeyOrInitVector(BYTE* pData, BOOL key);




























 
void halAesEncrDecr(BYTE* pDataIn, UINT16 length, BYTE* pDataOut, BYTE* pInitVector, BOOL decr);










#line 2095 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"





















 





















































 
void halInitRandomGenerator(void);

#line 2203 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"



 















 
void halWait(BYTE wait);

















 
char getkey(void);





















 
int putchar(int i);

#line 2302 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\hal.h"

































 


#line 19 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\board.h"















































































  

                                                  













































typedef struct{
  BYTE macPayloadLen;                     
  BYTE macField;                          
  UINT16 payload[96];                 
} __xdata TX_MASTER_STRUCT;






void init_peripherals(void);
void macTimer3Init(void);


void init_codec(void);


void I2Cwrite(char page_addr, char reg_addr, char data);


void dmaAudio(void);
void dmaToRadio(WORD length, WORD srcAddr);
void dmaMemtoMem(UINT8 length);


void rfConfigRadio(void);
BOOL initRf(void);
BOOL rfSendPacket(UINT8 timeout, UINT8 multiplier);


void macsetT3TimeoutAndWait(UINT8 timeout, UINT8 multiplier);
void setChannel(UINT8 ch);



extern TX_MASTER_STRUCT __xdata MAStxData;      

extern volatile BYTE __xdata txStatus;          

extern UINT16 __xdata audioOut[2][96];     
extern UINT8  __xdata activeOut;                    


extern DMA_DESC __xdata DmaDesc0;
extern DMA_DESC __xdata DmaDesc1_4[];

extern UINT8 audioInindx;
extern UINT8 audioOutindx;
extern UINT16 timerSampleRate;
extern BOOL __xdata audioFrameReady;

































 

#line 13 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\init_Codec.c"
#line 1 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\TLV320AIC3104.h"





















































#line 63 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\TLV320AIC3104.h"









#line 83 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\TLV320AIC3104.h"











 

















































#line 150 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\TLV320AIC3104.h"

#line 157 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\TLV320AIC3104.h"







































 













#line 14 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\init_Codec.c"

void init_codec(void)
{

  


  T4CTL |= 0x10;        



  I2Cwrite(0, 1, 0x80);
  

  
#line 36 "C:\\Users\\Chris\\Desktop\\wireless\\CC1110_AIC3104_16kHz16bits_96\\src\\init_Codec.c"
  I2Cwrite(0, 2, 0x44);                





  I2Cwrite(0, 3, 0x80 | 0x11);   
  I2Cwrite(0, 4, 0x13);            
  I2Cwrite(0, 5, 0x57);            
  I2Cwrite(0, 6, 0xC8);        
  

  
  I2Cwrite(0, 9, 0x00);                        


  
  I2Cwrite(0, 25, 0x40);              





  
  I2Cwrite(0, 19, 0x84);                   
  I2Cwrite(0, 15, 0x3C);                
  
  return;
}































 


