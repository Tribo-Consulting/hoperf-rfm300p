#include <arduino.h>
#include "RFM300_Driver.h"
#include "cmt2300_regs.h"
#include <stdio.h>

int serial_putc(char c, struct __file *)
{
	Serial.write(c);
	return c;
}
void printf_begin(void)
{
	fdevopen(&serial_putc, 0);
}

char strBase[] = "CMT2219B test";
byte rx_buf[32] = {0};

#define LED1 A0 //3 // arduino pin 3 for led indicate

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
	vGpioFuncCfg(/*GPIO1_DCLK + GPIO2_INT1 +*/ GPIO3_INT2); // GPIO Maping
	vSpi3Write((word)(CMT23_DUTY_CTL << 8) | (bSpi3Read(CMT23_DUTY_CTL) & DUTY_MASK)); // disable low power mode
}

void start_rx(void)
{
	vSpi3Write((word)(CMT23_DUTY_CTL << 8) | (bSpi3Read(CMT23_DUTY_CTL) & DUTY_MASK)); // first disable low power mode
	vInt2SrcCfg(INT_PKT_DONE); // IRQ  Maping
	vIntSrcEnable(CRC_PASS_EN | PKT_DONE_EN | PREAMBLE_PASS_EN | SYNC_PASS_EN);
	bIntSrcFlagClr();

	if(bGoRx())
	{
		printf("RX mode ready.\r\n");
	}
}

void setup(void)
{
	// system resource setting
	//pinMode(LED1, OUTPUT);
	//digitalWrite(LED1, LOW);
	Serial.begin(115200);
	printf_begin();
	
	// radio configure
	FixedPktLength = false;
	init_2300a();
	start_rx();
}

void loop(void)
{
	static uint16_t rx_cnt = 0;
	byte tmp, i, flg;
	int8_t rssi;
	unsigned long currentMillis;

	if (GPO3_H())
	{
		flg = bSpi3Read(CMT23_INT_FLG);
		rssi = bReadRssi(1) - 128;
		tmp = bGetMessage(rx_buf);

		printf("RX [%u]: ", tmp);

		for (i = 0; i < tmp; i++)
		{
			printf("%c", rx_buf[i]);
		}
		printf("\r\n ");

		for (i = 0; i < tmp; i++)
		{
			printf("%02X ", rx_buf[i]);
		}
		Serial.println();
		
		printf(" RSSI: %d\r\n", rssi);
		printf(" INT_FLG: %02X\n", flg);
		bIntSrcFlagClr();

		//digitalWrite(LED1, (rx_cnt%2)); //toggle rx indicator.
		printf("%u\r\n", rx_cnt++);
	}
}
