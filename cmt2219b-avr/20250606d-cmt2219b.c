//;---------------------------------------
//;  CMT2219B Configuration File
//;  Generated by CMOSTEK RFPDK_V1.59
//;  2025.06.06 15:50
//;---------------------------------------
//; Mode                    = Advanced
//; Part Number             = CMT2219B
//; Frequency               = 915.000 MHz
//; Xtal Frequency          = 26.0000 MHz
//; Demodulation            = OOK
//; AGC                     = On
//; Data Rate               = 10.0 kbps
//; Deviation               = NA
//; Rx Xtal Tol.            = 40 ppm
//; Bandwidth               = Auto-Select kHz
//; CDR Type                = Counting
//; CDR DR Range            = NA
//; Rx Duty-Cycle           = Off
//; Sleep Timer             = Off
//; Sleep Time              = NA
//; Rx Timer                = Off
//; Rx Time T1              = NA
//; Rx Time T2              = NA
//; Rx Exit State           = STBY
//; SLP Mode                = Disable
//; RSSI Valid Source       = PJD
//; PJD Window              = 8 Jumps
//; LFOSC Calibration       = On
//; Xtal Stable Time        = 2480 us
//; RSSI Compare TH         = NA
//; Data Mode               = Packet
//; Whitening               = Enable
//; Whiten Type             = PN9 CCITT
//; Whiten Seed Type        = NA
//; Whiten Seed             = 511
//; Manchester              = Disable
//; Manchester Type         = NA
//; FEC                     = Disable
//; FEC Type                = NA
//; Packet Type             = Variable Length
//; Node-Length Position    = First Node, then Length
//; Payload Bit Order       = Start from msb
//; Preamble Rx Size        = 2
//; Preamble Value          = 170
//; Preamble Unit           = 8-bit
//; Sync Size               = 2-byte
//; Sync Value              = 50490
//; Sync Tolerance          = None
//; Sync Manchester         = Disable
//; Node ID Size            = NA
//; Node ID Value           = NA
//; Node ID Mode            = None
//; Node ID Err Mask        = Disable
//; Node ID Free            = Disable
//; Payload Length          = 32
//; CRC Options             = CCITT-16
//; CRC Seed                = 0 crc_seed
//; CRC Range               = Entire Payload
//; CRC Swap                = Start from MSB
//; CRC Bit Invert          = Normal
//; CRC Bit Order           = Start from bit 15
//; Dout Mute               = Off
//; Dout Adjust Mode        = Disable
//; Dout Adjust Percentage  = NA
//; Collision Detect        = Off
//; Collision Detect Offset = NA
//; RSSI Detect Mode        = Always
//; RSSI Filter Setting     = No Filtering
//; RF Performance          = High
//; LBD Threshold           = 2.4 V
//; RSSI Offset             = 0
//; RSSI Offset Sign        = 0
//;---------------------------------------
//;  The following are the Register contents
//;---------------------------------------
//;---------------------------------------
//;  The following is the CRC result for
//;  the above Register contents
//;---------------------------------------
#include <arduino.h>

word CMTBank[12] = {
0x0002,
0x0166,
0x02EC,
0x031C,
0x0470,
0x0580,
0x0614,
0x0708,
0x0811,
0x0902,
0x0A02,
0x0B00,
};

word SystemBank[12] = {
0x0CAE,
0x0DE0,
0x0E71,
0x0F00,
0x1000,
0x11F4,
0x1210,
0x13E2,
0x1442,
0x1520,
0x1600,
0x1781,
};

word FrequencyBank[8] = {
0x1846,
0x196D,
0x1A80,
0x1B86,
0x1C46,
0x1D62,
0x1E27,
0x1F16,
};

word DataRateBank[24] = {
0x20D3,
0x2164,
0x22A0,
0x2399,
0x2400,
0x2500,
0x2600,
0x2700,
0x2800,
0x2900,
0x2A00,
0x2B29,
0x2CC0,
0x2D28,
0x2E0A,
0x2F5B,
0x3007,
0x3100,
0x3250,
0x332D,
0x3400,
0x3501,
0x3605,
0x3705,
};

word BasebandBank[29] = {
0x3812,
0x3908,
0x3A00,
0x3BAA,
0x3C02,
0x3D00,
0x3E00,
0x3F00,
0x4000,
0x4100,
0x4200,
0x433A,
0x44C5,
0x4501,
0x461F,
0x4700,
0x4800,
0x4900,
0x4A00,
0x4B00,
0x4C01,
0x4D00,
0x4E00,
0x4F64,
0x50FF,
0x5101,
0x5200,
0x531F,
0x5410,
};

word TXBank[11] = {
0x5551,
0x564D,
0x5706,
0x5800,
0x5903,
0x5A70,
0x5B00,
0x5C2A,
0x5D05,
0x5E3F,
0x5F7F,
};
