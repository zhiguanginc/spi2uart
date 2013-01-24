/*
 * SPI2UART program for HT45B0F
 *
 * Wrote by Michael Li
 * QQ:13458499
 * Mail: michael_li@dspa.com.tw
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <asm/types.h>
#include <linux/fs.h>
#include <signal.h>

#include "My_Type.h"
#include "spi2uart.h"

int giDevFD;

/******************************************************************************
Function Name :
Description   :
******************************************************************************/
void SPI_Init(void)
{
	/* default to high */
	SPI_PinHigh(SPI2UART_PIN_SCS);
	SPI_Delay();
	SPI_PinHigh(SPI2UART_PIN_CLK);
	SPI_Delay();
	SPI_PinHigh(SPI2UART_PIN_DI);
	SPI_Delay();
}

/******************************************************************************
Function Name :
Description   :
******************************************************************************/
void SPI_Delay(void)
{
	int i, j, x;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 1000; j++)
		{
			x = 0;
		}
	}

}

/******************************************************************************
Function Name :
Description   :
******************************************************************************/
unsigned long SPI_PinRead(unsigned char ucPin)
{
	ST_GPIO stGPIO;

	switch (ucPin)
	{
	case SPI2UART_PIN_DO:
		/* GPIOA31 */
		stGPIO.iPin = 31;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_READ, &stGPIO);

		if (stGPIO.iVal == 0)
		{
			return IS_FAIL;
		}
		break;

	default:
		printf("SPI_PinRead get a incorrect value\n");
		break;
	}

	return IS_OK;
}

/******************************************************************************
Function Name :
Description   :
!!!
GPIOB21: 0 means pull high; 1 means pull down
******************************************************************************/
unsigned long SPI_PinHigh(unsigned char ucPin)
{
	ST_GPIO stGPIO;

	switch (ucPin)
	{
	case SPI2UART_PIN_DI:
		/* GPIOA29 */
		stGPIO.iPin = 29;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_SYSMUX, &stGPIO);
		stGPIO.iPin = 29;
		stGPIO.iVal = 0x01;
		ioctl(giDevFD, DSPG_GPIOA_WRITE, &stGPIO);

		//printf("SPI2UART_PIN_DI has been pulled high");
		break;
#if 0
	case SPI2UART_PIN_DO:
		/* GPIOA31 */
		stGPIO.iPin = 31;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_SYSMUX, &stGPIO);
		stGPIO.iPin = 31;
		stGPIO.iVal = 0x01;
		ioctl(giDevFD, DSPG_GPIOA_WRITE, &stGPIO);

		//printf("SPI2UART_PIN_DO has been pulled high");
		break;
#endif

	case SPI2UART_PIN_CLK:
		/* GPIOA19 */
		stGPIO.iPin = 19;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_SYSMUX, &stGPIO);
		stGPIO.iPin = 19;
		stGPIO.iVal = 0x01;
		ioctl(giDevFD, DSPG_GPIOA_WRITE, &stGPIO);

		//printf("SPI2UART_PIN_CLK has been pulled high");
		break;

	case SPI2UART_PIN_SCS:
		/* GPIOB21 */
		stGPIO.iPin = 21;
		stGPIO.iVal = 0x01;
		ioctl(giDevFD, DSPG_GPIOB_SYSMUX, &stGPIO);
		stGPIO.iPin = 21;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOB_WRITE, &stGPIO);

		//printf("SPI2UART_PIN_SCS has been pulled high");
		break;

	default:
		printf("SPI_PinHigh get a incorrect value\n");
		return IS_FAIL;
	}

	return IS_OK;
}

/******************************************************************************
Function Name :
Description   :
******************************************************************************/
unsigned long SPI_PinLow(unsigned char ucPin)
{
	ST_GPIO stGPIO;

	switch (ucPin)
	{
	case SPI2UART_PIN_DI:
		/* GPIOA29 */
		stGPIO.iPin = 29;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_SYSMUX, &stGPIO);
		stGPIO.iPin = 29;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_WRITE, &stGPIO);

		//printf("SPI2UART_PIN_DI has been pulled down");
		break;

#if 0
	case SPI2UART_PIN_DO:
		/* GPIOA31 */
		stGPIO.iPin = 31;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_SYSMUX, &stGPIO);
		stGPIO.iPin = 31;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_WRITE, &stGPIO);

		//printf("SPI2UART_PIN_DO has been pulled down");
		break;
#endif

	case SPI2UART_PIN_CLK:
		/* GPIOA19 */
		stGPIO.iPin = 19;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_SYSMUX, &stGPIO);
		stGPIO.iPin = 19;
		stGPIO.iVal = 0x00;
		ioctl(giDevFD, DSPG_GPIOA_WRITE, &stGPIO);

		//printf("SPI2UART_PIN_CLK has been pulled down");
		break;

	case SPI2UART_PIN_SCS:
		/* GPIOB21 */
		stGPIO.iPin = 21;
		stGPIO.iVal = 0x01;
		ioctl(giDevFD, DSPG_GPIOB_SYSMUX, &stGPIO);
		stGPIO.iPin = 21;
		stGPIO.iVal = 0x01;
		ioctl(giDevFD, DSPG_GPIOB_WRITE, &stGPIO);

		//printf("SPI2UART_PIN_SCS has been pulled down");
		break;

	default:
		printf("SPI_PinLow get a incorrect value\n");
		return IS_FAIL;
	}

	return IS_OK;

}

/******************************************************************************
Function Name :
Description   :
******************************************************************************/
unsigned long SPI_DoWrite(unsigned char ucCmd, unsigned char ucData)
{
	int i;
	unsigned char ucTransData;

	SPI_PinLow(SPI2UART_PIN_SCS);
	SPI_Delay();

	/* !!! make the 8-bit command */
	ucTransData = ucCmd;
	printf("Send cmd [0x%x]\r\n", ucTransData);

	/* Transfer MSB first */
	for (i = 0; i < 8; i++)
	{
		if (ucTransData & (0x80 >> i))
		{
			SPI_PinHigh(SPI2UART_PIN_DI);
			SPI_PinLow(SPI2UART_PIN_CLK);
			SPI_Delay();
			SPI_PinHigh(SPI2UART_PIN_CLK);
			SPI_Delay();
		}
		else
		{
			SPI_PinLow(SPI2UART_PIN_DI);
			SPI_PinLow(SPI2UART_PIN_CLK);
			SPI_Delay();
			SPI_PinHigh(SPI2UART_PIN_CLK);
			SPI_Delay();
		}
	}

	/* !!! make the 8-bit data */
	ucTransData = ucData;
	printf("Send data [0x%x]\r\n", ucTransData);

	for (i = 0; i < 8; i++)
	{
		if (ucTransData & (0x80 >> i))
		{
			SPI_PinHigh(SPI2UART_PIN_DI);
			SPI_PinLow(SPI2UART_PIN_CLK);
			SPI_Delay();
			SPI_PinHigh(SPI2UART_PIN_CLK);
			SPI_Delay();
		}
		else
		{
			SPI_PinLow(SPI2UART_PIN_DI);
			SPI_PinLow(SPI2UART_PIN_CLK);
			SPI_Delay();
			SPI_PinHigh(SPI2UART_PIN_CLK);
			SPI_Delay();
		}
	}

	SPI_PinHigh(SPI2UART_PIN_DI);
	SPI_Delay();
	SPI_PinHigh(SPI2UART_PIN_SCS);

	return IS_OK;
}

/******************************************************************************
Function Name :
Description   : Not ready now.
******************************************************************************/
unsigned long SPI_DoRead(unsigned char ucCmd, unsigned char *pucData)
{
	int i;
	unsigned short ucTransData;

	SPI_PinLow(SPI2UART_PIN_SCS);
	SPI_Delay();

	/* !!! make the 8-bit command */
	ucTransData = ucCmd;
	printf("Send data [0x%x]\r\n", ucTransData);

	/* Transfer MSB first */
	for (i = 0; i < 8; i++)
	{
		if (ucTransData & (0x80 >> i))
		{
			SPI_PinHigh(SPI2UART_PIN_DI);
			SPI_PinLow(SPI2UART_PIN_CLK);
			SPI_Delay();
			SPI_PinHigh(SPI2UART_PIN_CLK);
			SPI_Delay();
		}
		else
		{
			SPI_PinLow(SPI2UART_PIN_DI);
			SPI_PinLow(SPI2UART_PIN_CLK);
			SPI_Delay();
			SPI_PinHigh(SPI2UART_PIN_CLK);
			SPI_Delay();
		}
	}

	/* !!! make the 8-bit data*/
	ucTransData = 0;

	for (i = 0; i < 8; i++)
	{
		SPI_PinHigh(SPI2UART_PIN_DI);
		SPI_PinLow(SPI2UART_PIN_CLK);
		SPI_Delay();
		SPI_PinHigh(SPI2UART_PIN_CLK);
		SPI_Delay();

		if (IS_OK == SPI_PinRead(SPI2UART_PIN_DO))
		{
			ucTransData |= (0x80 >> i);
		}
	}

	SPI_PinHigh(SPI2UART_PIN_DI);
	SPI_Delay();
	SPI_PinHigh(SPI2UART_PIN_SCS);

	printf("Get data [0x%x]\r\n", ucTransData);
	*pucData = ucTransData & (0x00ff);

	return IS_OK;
}

/******************************************************************************
Function Name :
Description   : !!! ony for test purpose
******************************************************************************/
void SPI_SendDataToUART(void)
{
	unsigned char ucData = 0;
	
	while (1)
	{
		SPI_DoRead(ReadUSR, &ucData);

		if (0 == ucData)
		{
			continue;
		}

		Register.usr = ucData;
		
		if (Register.Flag.txif == 1)
		{
			SPI_DoWrite(WriteFIFO, 'A');
			SPI_Delay();
			return;
		}
	}
}

/******************************************************************************
Function Name :
Description   :
******************************************************************************/
void UART_Init(void)
{
	/* UART Reset */
	SPI_DoWrite(WriteUCR3, UCR3Data);

	/* Set Data Transfer Format */
	SPI_DoWrite(WriteUCR1, UCR1_8_N_1);

	/* Set Baud Rate */
	SPI_DoWrite(WriteBRG, BRGData);

	/* Write UCR2 */
	SPI_DoWrite(WriteUCR2, UCR2Data);
}

/******************************************************************************
Function Name   :main()
Description     :
******************************************************************************/
int main(void)
{
	char acCmd[100];

	printf("Welcome to the SPI2UART demo application!\nPress '?' or 'h' for help.\n");
	giDevFD = open(DEVICE_NAME, O_RDWR);

	if (giDevFD == -1)
	{
		printf("open device %s error\n", DEVICE_NAME);
		return -1;
	}
	else
	{
		SPI_Init();
		UART_Init();

		while (1)
		{
			fflush(stdin);
			memset(acCmd, 0x00, sizeof(acCmd));
			fgets(acCmd, 100, stdin);

			switch (acCmd[0])
			{
				/* below parameters 1 to 9 for port testing */
			case '1':
			{
				SPI_PinLow(SPI2UART_PIN_SCS);
				break;
			}

			case '2':
			{
				SPI_PinHigh(SPI2UART_PIN_SCS);
				break;
			}

			case '3':
			{
				SPI_PinLow(SPI2UART_PIN_CLK);
				break;
			}

			case '4':
			{
				SPI_PinHigh(SPI2UART_PIN_CLK);
				break;
			}

			case '5':
			{
				SPI_PinLow(SPI2UART_PIN_DO);
				break;
			}

			case '6':
			{
				SPI_PinHigh(SPI2UART_PIN_DO);
				break;
			}

			case '7':
			{
				SPI_PinLow(SPI2UART_PIN_DI);
				break;
			}

			case '8':
			{
				SPI_PinHigh(SPI2UART_PIN_DI);
				break;
			}

			case '9':
			{
				SPI_PinRead(SPI2UART_PIN_DO);
				break;
			}

			case 'o':
			{
				int i;
				for (i = 0; i < 50; i++)
				{
					SPI_SendDataToUART();
				}
				break;
			}

			case 'w':
			{
				SPI_SendDataToUART();
				break;
			}

			case 'q':
				close(giDevFD);
				return 0;

			case '?':
			case 'h':
				printf("'1' '2'\tLow or High SPI2UART_PIN_SCS\n");
				printf("'3' '4'\tLow or High SPI2UART_PIN_CLK\n");
				printf("'5' '6'\tLow or High SPI2UART_PIN_DO\n");
				printf("'7' '8'\tLow or High SPI2UART_PIN_DI\n");
				printf("'9'\tRead SPI2UART_PIN_DO\n");
				printf("'o'\tSPI sends several 'A' to UART\n");
				printf("'w'\tSPI sends 'A' to UART\n");
				printf("'q'\tquit\n");
				break;

			default:
				printf("Unknown command / not implemented yet\n");
				printf("Welcome to the SPI2UART demo application!\nPress '?' or 'h' for help.\n");
				break;
			}
		}
	}

	printf("\n");
	close(giDevFD);

	return 0;
}


