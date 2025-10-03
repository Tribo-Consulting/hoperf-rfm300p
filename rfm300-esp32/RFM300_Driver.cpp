#include "RFM300_Driver.h"

byte  FixedPktLength;						//false: for contain packet length in Tx message, the same mean with variable lenth
											//true : for doesn't include packet length in Tx message, the same mean with fixed length
word  PayloadLength;						//unit: byte  range: 1-2047                                      
byte  node_id_size=0;			//0: none,disable,  max:4
word  node_id=0;			   //16bit, for testing

/**********************************************************
State Ctrl
**********************************************************/
/**********************************************************
**Name:     bGoTx
**Function: Entry Tx Mode
**Input:    none
**Output:   none
**********************************************************/
byte bGoTx(void)
{
	byte status1, i, status2;

	vSpi3Write(((word)CMT23_MODE_CTL<<8)+MODE_GO_TX);		
	for(i=0; i<50; i++){
		delayMicroseconds(100);	
		status2 = (MODE_MASK_STA & bSpi3Read(CMT23_MODE_STA));	
		if(status2 == MODE_STA_TX) //status bits go to 0x09 before TX?
			break;
	}
	if(i>=50)
		return(false);
	else
		return(true);
}

/**********************************************************
**Name:     bGoRx
**Function: Entry Rx Mode
**Input:    none
**Output:   none
**********************************************************/
byte bGoRx(void)
{
	byte tmp, i;
	vSpi3Write(((word)CMT23_MODE_CTL<<8)+MODE_GO_RX);		
	for(i=0; i<50; i++){
		delayMicroseconds(100);	
		tmp = (MODE_MASK_STA & bSpi3Read(CMT23_MODE_STA));	
		if(tmp==MODE_STA_RX)
			break;
	}
	if(i>=50)
		return(false);
	else
		return(true);
}

/**********************************************************
**Name:     bGoSleep
**Function: Entry Sleep Mode
**Input:    none
**Output:   none
**********************************************************/
byte bGoSleep(void)
{
	byte tmp;

	vSpi3Write(((word)CMT23_MODE_CTL<<8)+MODE_GO_SLEEP);	
	delayMicroseconds(100);		
	tmp = (MODE_MASK_STA & bSpi3Read(CMT23_MODE_STA));	
	if(tmp==MODE_STA_SLEEP)
		return(true);
	else
		return(false);
}

/**********************************************************
**Name:     bGoStandby
**Function: Entry Standby Mode
**Input:    none
**Output:   none
**********************************************************/
byte bGoStandby(void)
{
	byte tmp, i;	

	vSpi3Write(((word)CMT23_MODE_CTL<<8)+MODE_GO_STBY);	
	for(i=0; i<50; i++){
		delayMicroseconds(100);	
		tmp = (MODE_MASK_STA & bSpi3Read(CMT23_MODE_STA));	
		if(tmp==MODE_STA_STBY)break;
	}
	if(i>=50)
		return(false);
	else
		return(true);
}

/**********************************************************
**Name:     vSoftReset
**Function: Software reset Chipset
**Input:    none
**Output:   none
**********************************************************/
void vSoftReset(void)
{
	vSpi3Write(((word)CMT23_SOFTRST<<8)+0xFF); 
	delay(1);				//enough?
}

/**********************************************************
**Name:     bReadStatus
**Function: read chipset status
**Input:    none
**Output:   none
**********************************************************/
byte bReadStatus(void)
{
	return(MODE_MASK_STA & bSpi3Read(CMT23_MODE_STA));		
}

/**********************************************************
**Name:     bReadRssi
**Function: Read Rssi
**Input:    true------dBm;
            false-----Code;
**Output:   none
**********************************************************/
byte bReadRssi(byte unit_dbm)
{
	if(unit_dbm)
		return(bSpi3Read(CMT23_RSSI_DBM));
	else		
		return(bSpi3Read(CMT23_RSSI_CODE));
}

void set_node_id(word node)
{
	vSpi3Write((word)(CMT23_NODE_ADDR_3<<8)| (node>>8)&0x00FF);
	vSpi3Write((word)(CMT23_NODE_ADDR_2<<8)| (node&0x00FF));	

	//vSpi3Write((word)(CMT23_NODE_ADDR_3<<8)|node&0x00FF);
}

word get_node_id(void)
{
	word node;
	node = bSpi3Read(CMT23_NODE_ADDR_3);	   //msb first
	node <<= 8;
	node |= bSpi3Read(CMT23_NODE_ADDR_2);    //second byte
	return node;
}

byte get_node_setting(void)
{
	 return bSpi3Read(0x47);	//node condigure register
}

/**********************************************************
GPIO & Interrupt CFG
**********************************************************/
/**********************************************************
**Name:     vGpioFuncCfg
**Function: GPIO Function config
**Input:    none
**Output:   none
**********************************************************/
void vGpioFuncCfg(byte io_cfg)
{
	vSpi3Write(((word)CMT23_IO_SEL<<8)+io_cfg);
}

/**********************************************************
**Name:     vIntSrcCfg
**Function: config interrupt source  
**Input:    int_1, int_2
**Output:   none
**********************************************************/
void vIntSrcCfg(byte int_1, byte int_2)
{
	byte tmp;
	tmp = INT_MASK & bSpi3Read(CMT23_INT1_CTL);
	vSpi3Write(((word)CMT23_INT1_CTL<<8)+(tmp|int_1));

	tmp = INT_MASK & bSpi3Read(CMT23_INT2_CTL);
	vSpi3Write(((word)CMT23_INT2_CTL<<8)+(tmp|int_2));
}

void vInt1SrcCfg(byte int_1)
{
	byte tmp;
	tmp = INT_MASK & bSpi3Read(CMT23_INT1_CTL);
	vSpi3Write(((word)CMT23_INT1_CTL<<8)+(tmp|int_1));
}

void vInt2SrcCfg(byte int_2)
{
	byte tmp;
	tmp = INT_MASK & bSpi3Read(CMT23_INT2_CTL);
	vSpi3Write(((word)CMT23_INT2_CTL<<8)+(tmp|int_2));
}

/**********************************************************
**Name:     vEnableDIN
**Function: for direct mode, add by vison
**Input:    none
**Output:   
**********************************************************/
void vEnableDIN(byte pin)
{
	byte tmp;
	tmp = 0x1F & bSpi3Read(CMT23_FIFO_CTL);
	vSpi3Write(((word)CMT23_FIFO_CTL<<8)+(tmp|DIN_EN|pin));
}

/**********************************************************
**Name:     vEnableDIN
**Function: for direct mode, add by vison
**Input:    none
**Output:   
**********************************************************/
void vDisableDIN(void)
{
  byte tmp;
  tmp = 0x1F & bSpi3Read(CMT23_FIFO_CTL);
  vSpi3Write(((word)CMT23_FIFO_CTL<<8)+(tmp|DIN_DIS));
}
/**********************************************************
**Name:     vEnableAntSwitch
**Function:  
**Input:    
**Output:   none
**********************************************************/
void vEnableAntSwitch(byte mode)
{
	byte tmp;
	tmp = bSpi3Read(CMT23_INT1_CTL);
	tmp&= 0x3F;
	switch(mode)
	{
		case 1:
			tmp |= RF_SWT1_EN; break;		//GPO1=RxActive; GPO2=TxActive	
		case 2:
			tmp |= RF_SWT2_EN; break;		//GPO1=RxActive; GPO2=!RxActive
		case 0:
		default:
			break;							//Disable	
	}
	vSpi3Write(((word)CMT23_INT1_CTL<<8)+tmp);
}


/**********************************************************
**Name:     vIntSrcEnable
**Function: enable interrupt source 
**Input:    en_int
**Output:   none
**********************************************************/
void vIntSrcEnable(byte en_int)
{
	vSpi3Write(((word)CMT23_INT_EN<<8)+en_int);				
}

/********* ***************/
void vSetClockDiv(byte div, byte enable)
{
	byte tmp;
	tmp = bSpi3Read(CMT23_CLK_CTL);
	vSpi3Write(((word)CMT23_CLK_CTL<<8)+(tmp&0xC0|(enable<<5)|div)); 
}

/**********************************************************
**Name:     vIntSrcFlagClr
**Function: clear flag
**Input:    none
**Output:   equ CMT23_INT_EN
**********************************************************/
byte bIntSrcFlagClr(void)
{
	byte flg = 0;

	vSpi3Write(((word)CMT23_INT_CLR1<<8)+0x07); //Clear flag 
	vSpi3Write(((word)CMT23_INT_CLR2<<8)+0xFF);	//Clear flag 

	return(flg);
}

/**********************************************************
**Name:     bClearFIFO
**Function: clear FIFO buffer
**Input:    none
**Output:   FIFO state
**********************************************************/
byte vClearFIFO(void)
{
	byte tmp;	
	tmp = bSpi3Read(CMT23_FIFO_FLG);
	vSpi3Write(((word)CMT23_FIFO_CLR<<8)+FIFO_CLR_RX+FIFO_CLR_TX);
	return(tmp);
}

#if 1		//splite fifo, tx:32bytes, rx:32bytes;
void vEnableWrFifo(void)
{
	byte tmp;
	tmp = bSpi3Read(CMT23_FIFO_CTL);
	tmp |= (SPI_FIFO_RD_WR_SEL|FIFO_RX_TX_SEL);
	vSpi3Write(((word)CMT23_FIFO_CTL<<8)+tmp);
}

void vEnableRdFifo(void)
{
	byte tmp;
	tmp = bSpi3Read(CMT23_FIFO_CTL);
	tmp &= (~(SPI_FIFO_RD_WR_SEL|FIFO_RX_TX_SEL));
	vSpi3Write(((word)CMT23_FIFO_CTL<<8)+tmp);
}
#endif

#if 0		//merged fifo, modify by vison
void vEnableWrFifo(void)
{
	byte tmp;
	tmp = bSpi3Read(CMT23_FIFO_CTL);
	tmp |= (SPI_FIFO_RD_WR_SEL|FIFO_RX_TX_SEL);
	vSpi3Write(((word)CMT23_FIFO_CTL<<8)+tmp|FIFO_SHARE_EN);	//enbale merge fifo
}

void vEnableRdFifo(void)
{
	byte tmp;
	tmp = bSpi3Read(CMT23_FIFO_CTL);
	tmp &= (~(SPI_FIFO_RD_WR_SEL|FIFO_RX_TX_SEL));
	vSpi3Write(((word)CMT23_FIFO_CTL<<8)+tmp|FIFO_SHARE_EN);	//enable merge fifo
}
#endif

/**********************************************************
CFG
**********************************************************/
/**********************************************************
**Name:     vInit
**Function: Init. CMT2300A
**Input:    none
**Output:   none
**********************************************************/
void vInit(void)
{
	byte tmp;
	vSpi3Init();
	GPO1In();
	GPO2In();
	GPO3In();
	TX_ANTOut();
	RX_ANTOut();
	vSoftReset();
	bGoStandby();
	tmp = bSpi3Read(CMT23_MODE_STA);
	tmp|= EEP_CPY_DIS;
	tmp&= (~RSTN_IN_EN);					//Disable RstPin	
	vSpi3Write(((word)CMT23_MODE_STA<<8)+tmp);
	bIntSrcFlagClr();
}

void vCfgBank(word cfg[], byte length)
{
	byte i;

	if(length!=0){	
		for(i=0; i<length; i++)	
			vSpi3Write(cfg[i]);
	}	
}

byte bGetMessage(byte msg[])
{
	byte i;	

	vEnableRdFifo();	
	if(FixedPktLength){
		vSpi3BurstReadFIFO(msg, PayloadLength);
		i = PayloadLength;
	}else{
		i = bSpi3ReadFIFO();
		vSpi3BurstReadFIFO(msg, i);
	}
	return(i);
}

byte bSendMessage(byte msg[], byte length)
{
	bIntSrcFlagClr();
#if 1	
	//mode1
	bGoStandby();
	vSetTxPayloadLength(length);
	vEnableWrFifo();	
	vSpi3BurstWriteFIFO(msg, length);
	bGoTx();
#else
	//mode2
	vSetTxPayloadLength(length);
	bGoTx();
	vEnableWrFifo();	
	vSpi3BurstWriteFIFO(msg, length);
#endif	
	return(true);
}

void vSetTxPayloadLength(word length)
{
	byte tmp;	
	byte len;
	tmp = bSpi3Read(CMT23_PKT_CTRL1);
	len = bSpi3Read(CMT23_PKT_LEN);
	tmp&= 0x8E;
	
	if(length!=0){
		if(FixedPktLength){
		  tmp &= ~(1<<0);		//clear bit0
		  len = length - 1;
		}
		else{
		  tmp |= (1<<0);	   //set bit0
		  len = length;
		}
	}else
		len = 0;

	tmp|= (((byte)(len>>8)&0x07)<<4);
	vSpi3Write(((word)CMT23_PKT_CTRL1<<8)+tmp);
	vSpi3Write(((word)CMT23_PKT_LEN<<8)+(byte)len);	//Payload length
}
