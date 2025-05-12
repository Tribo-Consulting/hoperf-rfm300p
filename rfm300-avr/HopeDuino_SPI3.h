#ifndef HopeDuino_SPI3_h
#define HopeDuino_SPI3_h

#include <arduino.h>
#include <util/delay.h>


#ifndef	byte
typedef unsigned char byte;
#endif

#ifndef word
typedef unsigned int  word;
#endif

#define SPI3_SPEED	1

/** Hardware brief **/

#define NC2				4
#define NC1				5
#define GPO3 		  4 //6
#define GPO2			7
#define GPO1			8
#define FCSB			7 //12
#define SDIO			16 //11
#define SCLK		  15 //13
#define CSB			  8 //10
#define NC0			  9

#define	SetCSB()	digitalWrite(CSB,HIGH)
#define	ClrCSB()	digitalWrite(CSB,LOW)

#define	SetFCSB()	digitalWrite(FCSB,HIGH)
#define	ClrFCSB()	digitalWrite(FCSB,LOW)

#define	SetSDCK()	digitalWrite(SCLK,HIGH)
#define	ClrSDCK()	digitalWrite(SCLK,LOW)

#define	SetSDIO()	digitalWrite(SDIO,HIGH)
#define	ClrSDIO()	digitalWrite(SDIO,LOW)

#define OutputCSB()		pinMode(CSB,OUTPUT)
#define OutputFCSB()	pinMode(FCSB,OUTPUT)
#define OutputSDCK()	pinMode(SCLK,OUTPUT)

#define	OutputSDIO()	pinMode(SDIO,OUTPUT)
#define InputSDIO()     pinMode(SDIO,INPUT)

#define	SDIO_H()	(digitalRead(SDIO)==1)
#define	SDIO_L()	(digitalRead(SDIO)==0)


void vSpi3Init(void);				/** initialize software SPI-3 **/
void vSpi3Write(word dat);			/** SPI-3 send one word **/
byte bSpi3Read(byte addr);			/** SPI-3 read one byte **/

void vSpi3WriteFIFO(byte dat);		/** SPI-3 send one byte to FIFO **/
byte bSpi3ReadFIFO(void);			/** SPI-3 read one byte from FIFO **/
void vSpi3BurstWriteFIFO(byte ptr[], byte length);			/** SPI-3 burst send N byte to FIFO**/
void vSpi3BurstReadFIFO(byte ptr[], byte length);			/** SPI-3 burst read N byte to FIFO**/

void vSpi3WriteByte(byte dat);		/** SPI-3 send one byte **/
byte bSpi3ReadByte(void);			/** SPI-3 read one byte **/


#else
#warning "HopeDuino_SPI3.h have been defined!"
#endif
