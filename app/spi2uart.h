/*
 * SPI2UART program for HT45B0F
 *
 * Wrote by Michael Li
 * QQ:13458499
 * Mail: michael_li@dspa.com.tw
 *
 */
#ifndef __SPI2UART_H__
#define __SPI2UART_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "My_Type.h"
#define DEVICE_NAME		"/dev/pin_dev"

	union
	{
		uint8	usr;
		struct
		{
			uint8 txif	: 1;
			uint8 tidle	: 1;
			uint8 rxif	: 1;
			uint8 ridle	: 1;
			uint8 oerr	: 1;
			uint8 ferr	: 1;
			uint8 nf	: 1;
			uint8 perr	: 1;
		} Flag;
	} Register;


	/* return value */
	typedef enum
	{
		IS_OK,
		IS_FAIL,
		IS_CONTINUE
	}
	EN_RETURN_VAL;

	typedef struct
	{
		int  iPin;
		int  iVal;
	} ST_GPIO;

#define DSPG_PORT_IOC_MAGIC	'k'
#define DSPG_GPIOA_WRITE        _IOWR(DSPG_PORT_IOC_MAGIC,1,ST_GPIO)
#define DSPG_GPIOB_WRITE        _IOWR(DSPG_PORT_IOC_MAGIC,2,ST_GPIO)
#define DSPG_GPIOC_WRITE        _IOWR(DSPG_PORT_IOC_MAGIC,3,ST_GPIO)
#define DSPG_GPIOA_SYSMUX       _IOWR(DSPG_PORT_IOC_MAGIC,4,ST_GPIO)
#define DSPG_GPIOB_SYSMUX       _IOWR(DSPG_PORT_IOC_MAGIC,5,ST_GPIO)
#define DSPG_GPIOC_SYSMUX       _IOWR(DSPG_PORT_IOC_MAGIC,6,ST_GPIO)
#define DSPG_GPIOA_SYSPAD       _IOWR(DSPG_PORT_IOC_MAGIC,7,ST_GPIO)
#define DSPG_GPIOB_SYSPAD       _IOWR(DSPG_PORT_IOC_MAGIC,8,ST_GPIO)
#define DSPG_GPIOC_SYSPAD       _IOWR(DSPG_PORT_IOC_MAGIC,9,ST_GPIO)
#define DSPG_GPIOA_READ         _IOWR(DSPG_PORT_IOC_MAGIC,10,ST_GPIO)
#define DSPG_GPIOB_READ         _IOWR(DSPG_PORT_IOC_MAGIC,11,ST_GPIO)
#define DSPG_GPIOC_READ         _IOWR(DSPG_PORT_IOC_MAGIC,12,ST_GPIO)



	/**********************************************************************/

	//                          UART Read/Write Command Definition
	//--------------------------------------------------------------------------------------
	// Command Type | Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
	//--------------------------------------------------------------------------------------
	//   Read FIFO  |   0   |   0    |   0    |   0    |   0    |    X   |    X   |    X   |
	//--------------------------------------------------------------------------------------
	//Read Register |   0   |   0    |   0    |   1    |   0    |   A2   |   A1   |   A0   |
	//--------------------------------------------------------------------------------------
	//  Write FIFO  |   0   |   0    |   0    |   0    |   1    |    X   |    X   |    X   |
	//--------------------------------------------------------------------------------------
	//Write Register|   0   |   0    |   0    |   1    |   1    |   A2   |   A1   |   A0   |
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	//  Register Address  |
	//---------------------
	//  A2~A0  |   Name   |
	//---------------------
	//   00H   |   USR    |
	//---------------------
	//   01H   |   UCR1   |
	//---------------------
	//   02H   |   UCR2   |
	//---------------------
	//   03H   |   BRG    |
	//---------------------
	//   04H   |   UCR3   |
	//---------------------
	// 05H~07H |  Unused  |
	//---------------------

#define    ReadFIFO      0x00
#define    ReadUSR       0x10
#define    ReadUCR1      0x11
#define    ReadUCR2      0x12
#define    ReadBRG       0x13
#define    ReadUCR3      0x14

#define    WriteFIFO     0x08
#define    WriteUCR1     0x19
#define    WriteUCR2     0x1a
#define    WriteBRG      0x1b
#define    WriteUCR3     0x1c

	//--------------------------------------------------------------------------------
	//                           UART Register Setting Value
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//                                   UCR1 Setting
	//--------------------------------------------------------------------------------
	//   |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
	//--------------------------------------------------------------------------------
	//   | UARTEN |   BNO  |  PREN  |  PRT   |  STOPS |  TXBRK |  RX8   |   TX8  |
	//--------------------------------------------------------------------------------

#define    UCR1_8_N_1    0x80     //8bits-Data  NONE-Parity 1bit-Stop Format
#define    UCR1_7_O_1    0xB0     //7bits-Data  Odd-Parity  1bit-Stop Format
#define    UCR1_7_E_1    0xA0     //7bits-Data  Even-Parity 1bit-Stop Format
#define    UCR1_9_N_1    0xC0     //9bits-Data  NONE-Parity 1bit-Stop Format
#define    UCR1_8_O_1    0xF0     //8bits-Data  Odd-Parity  1bit-Stop Format
#define    UCR1_8_E_1    0xE0     //8bits-Data  Even-Parity 1bit-Stop Format
#define    UCR1_8_N_2    0x88     //8bits-Data  NONE-Parity 2bits-Stop Format
#define    UCR1_7_O_2    0xB8     //7bits-Data  Odd-Parity  2bits-Stop Format
#define    UCR1_7_E_2    0xA8     //7bits-Data  Even-Parity 2bits-Stop Format
#define    UCR1_9_N_2    0xC8     //9bits-Data  NONE-Parity 2bits-Stop Format
#define    UCR1_8_O_2    0xF8     //8bits-Data  Odd-Parity  2bits-Stop Format
#define    UCR1_8_E_2    0xE8     //8bits-Data  Even-Parity 2bits-Stop Format

	//--------------------------------------------------------------------------------
	//                                     UCR2 Setting
	//--------------------------------------------------------------------------------
	//  Bit   |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
	//--------------------------------------------------------------------------------
	//  Name  |  TXEN  |  RXEN  |  BRGH  |  ADDEN |  WAKE  |  RIE   |  TIIE  |  TEIE  |
	//--------------------------------------------------------------------------------

#define    UCR2Data      0xE5     //Enable TXEN RXEN BRGH RIE 

	//--------------------------------------------------------------------------------
	//                                     UCR3 Setting
	//--------------------------------------------------------------------------------
	//  Bit   |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
	//--------------------------------------------------------------------------------
	//  Name  |  URST  |   --   |   --   |   --   |   --   |   --   |   --   |   --   |
	//--------------------------------------------------------------------------------

#define    UCR3Data       0x80      //Enbale Reset

	//--------------------------------------------------------------------------------
	//                                     BRG Setting
	//--------------------------------------------------------------------------------
	//  Bit   |  Bit7  |  Bit6  |  Bit5  |  Bit4  |  Bit3  |  Bit2  |  Bit1  |  Bit0  |
	//--------------------------------------------------------------------------------
	//  Name  |  BRG7  |  BRG6  |  BRG5  |  BRG4  |  BRG3  |  BRG2  |  BRG1  |  BRG0  |
	//--------------------------------------------------------------------------------

#define    BRGData        0x19      //Baud=9600,BRGH=1,N=25 

	/**********************************************************************/

	/* spi pin define */
	typedef enum
	{
		SPI2UART_PIN_DI,
		SPI2UART_PIN_DO,
		SPI2UART_PIN_CLK,
		SPI2UART_PIN_SCS,
		SPI2UART_NULL
	}
	EN_SPI2UART_PIN;



	/**********************************************************************/

	void SPI_Init(void);
	void SPI_Delay(void);
	unsigned long SPI_PinRead(unsigned char ucPin);
	unsigned long SPI_PinHigh(unsigned char ucPin);
	unsigned long SPI_PinLow(unsigned char ucPin);
	unsigned long SPI_DoWrite(unsigned char ucCmd, unsigned char ucData);
	unsigned long SPI_DoRead(unsigned char ucCmd, unsigned char *pucData);
	void SPI_SendDataToUART(void);
	void UART_Init(void);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

