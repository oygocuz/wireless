#line 1 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\src\\codec_TLV320AIC26.c"


















 

#line 1 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\twoway.h"






 







#line 1 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

























 












#line 1 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"






 







 

#pragma language=extended
#line 37 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 73 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"





 
#line 97 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"




 







 

 
__sfr __no_init volatile union { unsigned char P0; struct { unsigned char P0_0 : 1; unsigned char P0_1 : 1; unsigned char P0_2 : 1; unsigned char P0_3 : 1; unsigned char P0_4 : 1; unsigned char P0_5 : 1; unsigned char P0_6 : 1; unsigned char P0_7 : 1; }; } @ 0x80;
__sfr __no_init volatile unsigned char SP @ 0x81;    
__sfr __no_init volatile unsigned char DPL0 @ 0x82;    
__sfr __no_init volatile unsigned char DPH0 @ 0x83;    
__sfr __no_init volatile unsigned char DPL1 @ 0x84;    
__sfr __no_init volatile unsigned char DPH1 @ 0x85;    
__sfr __no_init volatile unsigned char U0CSR @ 0x86;    
__sfr __no_init volatile unsigned char PCON @ 0x87;    

 
__sfr __no_init volatile union { unsigned char TCON; struct { unsigned char IT0 : 1; unsigned char RFTXRXIF : 1; unsigned char IT1 : 1; unsigned char URX0IF : 1; unsigned char _TCON5 : 1; unsigned char ADCIF : 1; unsigned char _TCON6 : 1; unsigned char URX1IF : 1; }; } @ 0x88;
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
__sfr __no_init volatile unsigned char ENDIAN @ 0x95;    
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
__sfr __no_init volatile unsigned char WORCTL @ 0xA2;    
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

__sfr __no_init volatile unsigned char U1CSR @ 0xF8;    
__sfr __no_init volatile unsigned char U1DBUF @ 0xF9;    
__sfr __no_init volatile unsigned char U1BAUD @ 0xFA;    
__sfr __no_init volatile unsigned char U1UCR @ 0xFB;    
__sfr __no_init volatile unsigned char U1GCR @ 0xFC;    
__sfr __no_init volatile unsigned char P0DIR @ 0xFD;    
__sfr __no_init volatile unsigned char P1DIR @ 0xFE;    
__sfr __no_init volatile unsigned char P2DIR @ 0xFF;    





 

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   

 
   
   
   
   
   
   
   
   





 

 







 
#line 453 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"





 
#line 468 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"





 










 
#line 493 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 502 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 511 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 520 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 529 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 538 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 547 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 556 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 565 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 574 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 583 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 592 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 601 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 610 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 619 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"

#line 628 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\ioCC1110.h"


 

#pragma language=default



 
#line 41 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"












 
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












































 



























































#line 181 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"











#line 199 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"











#line 217 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"










#line 251 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"











#line 269 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"







 
















#line 316 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"










#line 349 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

#line 373 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"





#line 385 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"







#line 398 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"









#line 452 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"








#line 506 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"







 











#line 531 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"









#line 571 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"























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














#line 633 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

#line 658 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"













































 































 
#line 771 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"


#line 789 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

#line 806 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

#line 840 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"






















#line 908 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"



#line 926 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"





































 









#line 1017 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"



#line 1028 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"











 


#line 1048 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"



#line 1072 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"






































 
void halFlashWritePage(BYTE *pSrcAddr, BYTE *pBuffer, BYTE page);





















 
void halFlashErasePage(BYTE* buffer, BYTE page);









 















#line 1172 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"









#line 1189 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"








#line 1212 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"










#line 1231 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

#line 1249 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"






















 






















 
WORD halSetTimer1Period(DWORD period);




#line 1308 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"



#line 1331 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"














#line 1365 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"





                       






#line 1436 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

























 
BOOL halSetTimer2Period(UINT32 period, UINT8* cnt, UINT8* presc);

#line 1470 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

#line 1479 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"






























 
BYTE halSetTimer34Period(BYTE timer, DWORD period);



#line 1522 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"








#line 1550 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"









#line 1579 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"



#line 1589 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"


#line 1599 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"





#line 1611 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"






















 




























 






















#line 1696 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"















































 
INT16 halAdcSampleSingle(BYTE reference, BYTE resolution, UINT8 input);
















 
INT16 halGetAdcValue(void);











 



















 
BYTE halRfSendPacket(BYTE* pData, BYTE length);

























 
BYTE halRfReceivePacket(BYTE* pData, BYTE*pRssi, BYTE* pLqi, BYTE timeOut);



















 
BOOL halRfConfig(UINT32 frequency);















 
void halRfSetRadioFrequency(UINT32 frequency);

#line 1896 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"


#line 1913 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"























#line 1947 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"








#line 1962 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"



#line 2004 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"



#line 2015 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"






 



















 




















 
void halAesLoadKeyOrInitVector(BYTE* pData, BOOL key);




























 
void halAesEncrDecr(BYTE* pDataIn, UINT16 length, BYTE* pDataOut, BYTE* pInitVector, BOOL decr);










#line 2110 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"





















 





















































 
void halInitRandomGenerator(void);

#line 2218 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"



 















 
void halWait(BYTE wait);

















 
char getkey(void);





















 
int putchar(int i);

#line 2317 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\hal.h"

#line 16 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\twoway.h"



































































































































  

                                                  












































































#line 234 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\twoway.h"



#line 248 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\twoway.h"




typedef struct{
  BYTE macPayloadLen;                     
  BYTE macField;                          
  BYTE statusField;                       
  UINT16 payload[54];                 
  BYTE append[2];   
} __xdata RX_SLAVE_STRUCT;







void init_peripherals(void);


void initCodec(void);
void writeCodecRegister(BYTE pageaddress, BYTE address, INT16 data);


void dmaAudio(void);
void dmaToRadio(WORD length, WORD srcAddr);
void dmaFromRadio(WORD length, WORD dstAddr);
void dmaMemtoMem(UINT8 length);


BOOL initRf(void);
BOOL rfSendPacket(UINT8 timeout, UINT8 multiplier);

void rfReceivePacket(RX_SLAVE_STRUCT __xdata * rxData, UINT8 synctimeout, UINT8 t3_multiplier, BYTE dmaNumber, UINT8 packetlen, UINT8 timeout);
void ListenforMaster(RX_SLAVE_STRUCT __xdata * rxData, UINT8 timeout, UINT8 t3_multiplier, BYTE dmaNumber, UINT8 packetlen);



void initFrameTimer(void);
void startFrameTimer(UINT8 cnt);
void macTimer3Init(void);
void macsetT3TimeoutAndWait(UINT8 timeout, UINT8 multiplier);
void setChannel (UINT8 ch);









extern RX_SLAVE_STRUCT __xdata SLVrxData;       


extern volatile BYTE __xdata txStatus;          
extern volatile BYTE __xdata rxStatus;
extern volatile UINT8 __xdata rxPacketStatus;

extern UINT8  __xdata activeTable[4];

extern UINT16 __xdata audioIn[2][54];      
extern UINT8  __xdata activeIn;                     
extern UINT16 __xdata audioOut[2][54];     
extern UINT8  __xdata activeOut;                    
extern UINT8  __xdata SendPacket;                   


extern DMA_DESC __xdata DmaDesc0;
extern DMA_DESC __xdata DmaDesc1_4[];

extern UINT8 audioInindx;
extern UINT8 audioOutindx;
extern UINT16 timerSampleRate;
extern BOOL __xdata audioFrameReady;
extern BOOL __xdata rx1Ready;
extern BOOL __xdata rx2Ready;
extern UINT8 sampleCount;
extern UINT8 __xdata ActiveChIdx;
extern BOOL sfdDetected;
extern BOOL dmaDone;
extern UINT8 headerByte;
#line 22 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\src\\codec_TLV320AIC26.c"
#line 1 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\codec_TLV320AIC26.h"






 




#line 24 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\INC\\codec_TLV320AIC26.h"

































 



#line 23 "C:\\CodecEVM_One_Way_CC1110_12kHz16bits\\src\\codec_TLV320AIC26.c"



extern UINT16 __xdata audiocontrol1; 
extern UINT16 __xdata adcgainctrl; 










INT16 __xdata tmpRegRead;

INT16 readCodecRegister(BYTE pageaddress, BYTE address) {
  INT16 returnValue;
  P0_4 = 0;                       

  U0CSR &= ~0x02;

  
  U0DBUF = (0x80|(pageaddress&0x07)<<3|(address&0x38)>>3);   
  while(!((U0CSR & 0x02) == 0x02));
  U0CSR &= ~0x02;
  returnValue = U0DBUF;           

  
  U0DBUF = (address&0x07)<<5;     
  while(!((U0CSR & 0x02) == 0x02));
  U0CSR &= ~0x02;
  returnValue = U0DBUF;           

  
  U0DBUF = 0x00;                  
  while(!((U0CSR & 0x02) == 0x02));
  U0CSR &= ~0x02;
  returnValue = U0DBUF<<8;

  
  U0DBUF = 0x00;                  
  while(!((U0CSR & 0x02) == 0x02));
  U0CSR &= ~0x02;
  returnValue |= U0DBUF;
  P0_4 = 1;                       

  return returnValue;
}

void writeCodecRegister(BYTE pageaddress, BYTE address, INT16 data) {
  P0_4 = 0;                       

  U0CSR &= ~0x02;

  
  
  
  
  U0DBUF = ((pageaddress&0x07)<<3|(address&0x38)>>3);   
  while(!((U0CSR & 0x02) == 0x02));
  U0CSR &= ~0x02;

  
  
  
  U0DBUF = (address&0x07)<<5;     
  while(!((U0CSR & 0x02) == 0x02));
  U0CSR &= ~0x02;

  
  
  U0DBUF = (data&0xFF00)>>8;      
  while(!((U0CSR & 0x02) == 0x02));
  U0CSR &= ~0x02;

  
  
  U0DBUF = (data&0x00FF);         
  while(!((U0CSR & 0x02) == 0x02));
  U0CSR &= ~0x02;

  P0_4 = 1;                       
}


void initCodec (void) {

  
  
  
  
 
  P0 &= ~0x80;
  P0 |= 0x80;           
   


  T4CTL |= 0x10;        
  
  
  
  writeCodecRegister(1,0x04,0xBB00);

  
  
  
  
  
  
  







  
  
  audiocontrol1 = 0x0024;

  





  





  
  writeCodecRegister(2, 0x00, audiocontrol1);
  
  
  
  
  
  
  
  
  adcgainctrl = 0x3400;
  writeCodecRegister(2, 0x01, adcgainctrl);

  
  
  
  
  
  writeCodecRegister(2,0x02,0x0000);

  
  
  
  
  
  
  writeCodecRegister(2,0x03,0xC580);

  
  
  
  
  
  
  
  
  
  
  writeCodecRegister(2,0x04,0x44F0);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  writeCodecRegister(2,0x05,0x2020);

  
  
  
  
  
  
  
  
  
  
  
  
  writeCodecRegister(2,0x06,0x3430);






  
  
  
  
  
  
  
  writeCodecRegister(2,0x1B,0x911C);

  
  
  writeCodecRegister(2,0x1C,0x57C8);

  
  
  
  
  
  
  
  writeCodecRegister(2,0x1E,0x8030);

  return;
}


