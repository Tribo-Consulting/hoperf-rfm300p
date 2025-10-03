#include <arduino.h>
#include "RFM300_Driver.h"
#include "cmt2300_regs.h"
#include <stdio.h>

char strBase[] = "RFM300P test";
byte tx_buf[32] = {0};
byte rx_buf[32] = {0};
byte mode = 0; // 0: receive , 1: transmitter

#define KEY1 7 //2 // arduino pin 2 for select tx/rx mode
#define LED1 8 //3 // arduino pin 3 for led indicate

unsigned long previousMillis = 0;
const long timeout = 1000;

void init_2300a(void)
{
	vInit();
	vCfgBank(CMTBank, 12);
	vCfgBank(SystemBank, 12);
	vCfgBank(FrequencyBank, 8);
	vCfgBank(DataRateBank, 24);
	vCfgBank(BasebandBank, 29);
	vCfgBank(TXBank, 11);
	vEnableAntSwitch(1);
	vGpioFuncCfg(/*GPIO1_DCLK + GPIO2_INT1 +*/ GPIO3_INT2);								   // GPIO Maping
	vSpi3Write((word)(CMT23_DUTY_CTL << 8) | (bSpi3Read(CMT23_DUTY_CTL) & DUTY_MASK)); // disable low power mode
}

void start_rx(void)
{
	vSpi3Write((word)(CMT23_DUTY_CTL << 8) | (bSpi3Read(CMT23_DUTY_CTL) & DUTY_MASK)); // first disable low power mode
	vInt2SrcCfg(INT_PKT_DONE);														   // IRQ  Maping
	vIntSrcEnable(CRC_PASS_EN | PKT_DONE_EN | PREAMBLE_PASS_EN | SYNC_PASS_EN);
	bIntSrcFlagClr();
	if (bGoRx())
	{
		Serial.printf("RX mode ready.\r\n");
	}
}

void setup(void)
{
	// system resource setting
	pinMode(KEY1, INPUT_PULLUP);
	pinMode(LED1, OUTPUT);
	digitalWrite(LED1, LOW);
	Serial.begin(115200);
	Serial.printf("== rfm-300p-esp32 ==\r\n");

	// radio configure
	FixedPktLength = false;
	init_2300a();

	// determine work mode
	if (1) //!digitalRead(KEY1))
	{
		mode = 1;
		//vInt1SrcCfg(INT_TRX_ACTIVE); // IRQ maping
		vInt2SrcCfg(INT_TX_DONE);	 // IRQ maping
		vIntSrcEnable(TX_DONE_EN);
		vClearFIFO();
		Serial.printf("TX mode ready.\r\n");
	}
	else
	{
		mode = 0;
		start_rx();
	}
}

void loop(void)
{
	static uint16_t tx_cnt = 0;
	byte tmp, i, flg;
	int8_t rssi;
	unsigned long currentMillis;
	
	if (mode)
	{
		if (1) //digitalRead(KEY1) == 0)
		{
			//while (digitalRead(KEY1) == 0);

			digitalWrite(LED1, HIGH);

			sprintf((char*)tx_buf, "%s %05d", strBase, tx_cnt++);
			Serial.printf("TX: %s\r\n", tx_buf);

			bIntSrcFlagClr();
			vSetTxPayloadLength(strlen((char*)tx_buf));
			vEnableWrFifo();
			vSpi3BurstWriteFIFO(tx_buf, strlen((char*)tx_buf));
			bGoTx();
		
			previousMillis = millis();
			while(!GPO3_H())
			{
				currentMillis = millis();
				if (currentMillis - previousMillis >= timeout)
				{
					Serial.printf("TX: timeout.\r\n");
					break;
				}
			}
			
			bGoStandby();

			digitalWrite(LED1, LOW);
		}
	}
	else
	{
		if (GPO3_H())
		{
			flg = bSpi3Read(CMT23_INT_FLG);
			rssi = bReadRssi(1) - 128;
			tmp = bGetMessage(rx_buf);

			for (i = 0; i < tmp; i++)
			{
				printf("%c", rx_buf[i]);
			}
			Serial.printf("\r\n ");

			for (i = 0; i < tmp; i++)
			{
				Serial.printf(" %02X", rx_buf[i]);
			}
			Serial.println();

			Serial.printf(" RSSI: %d\r\n", rssi);
			Serial.printf(" INT_FLG: %02X\n", flg);
			bIntSrcFlagClr();
		}
		// mcu can sleep to wait radio event
	}

	delay(1000);
}
