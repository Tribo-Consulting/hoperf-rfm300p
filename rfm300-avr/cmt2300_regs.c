//;---------------------------------------
//;  CMT2300A Configuration File
//;  Generated by CMOSTEK RFPDK_V1.59
//;  2025.05.09 12:31
//;---------------------------------------
//; Mode                      = Advanced
//; Part Number               = CMT2300A
//; Frequency                 = 915.000 MHz
//; Xtal Frequency            = 26.0000 MHz
//; Demodulation              = OOK
//; AGC                       = On
//; Data Rate                 = 2.0 kbps
//; Deviation                 = NA
//; Tx Xtal Tol.              = 20 ppm
//; Rx Xtal Tol.              = 20 ppm
//; TRx Matching Network Type = 20 dBm
//; Tx Power                  = +20 dBm
//; Gaussian BT               = NA
//; Bandwidth                 = Auto-Select kHz
//; Demod Method              = Middle
//; Long-Zero Number          = 31
//; CDR Type                  = Counting
//; CDR DR Range              = NA
//; Rx Duty-Cycle             = Off
//; Tx Duty-Cycle             = Off
//; Sleep Timer               = Off
//; Sleep Time                = NA
//; Rx Timer                  = Off
//; Rx Time T1                = NA
//; Rx Time T2                = NA
//; Rx Exit State             = SLEEP
//; Tx Exit State             = SLEEP
//; SLP Mode                  = Disable
//; RSSI Valid Source         = PJD
//; PJD Window                = 8 Jumps
//; LFOSC Calibration         = On
//; Xtal Stable Time          = 155 us
//; RSSI Compare TH           = NA
//; Data Mode                 = Packet
//; Whitening                 = Disable
//; Whiten Type               = NA
//; Whiten Seed Type          = NA
//; Whiten Seed               = NA
//; Manchester                = Disable
//; Manchester Type           = NA
//; FEC                       = Disable
//; FEC Type                  = NA
//; Tx Prefix Type            = 0
//; Tx Packet Number          = 1
//; Tx Packet Gap             = 32
//; Packet Type               = Variable Length
//; Node-Length Position      = First Node, then Length
//; Payload Bit Order         = Start from msb
//; Preamble Rx Size          = 1
//; Preamble Tx Size          = 4
//; Preamble Value            = 170
//; Preamble Unit             = 8-bit
//; Sync Size                 = 2-byte
//; Sync Value                = 50490
//; Sync Tolerance            = None
//; Sync Manchester           = Disable
//; Node ID Size              = NA
//; Node ID Value             = NA
//; Node ID Mode              = None
//; Node ID Err Mask          = Disable
//; Node ID Free              = Disable
//; Payload Length            = 10
//; CRC Options               = None
//; CRC Seed                  = NA
//; CRC Range                 = NA
//; CRC Swap                  = NA
//; CRC Bit Invert            = NA
//; CRC Bit Order             = NA
//; Dout Mute                 = Off
//; Dout Adjust Mode          = Disable
//; Dout Adjust Percentage    = NA
//; Collision Detect          = Off
//; Collision Detect Offset   = NA
//; RSSI Detect Mode          = Always
//; RSSI Filter Setting       = No Filtering
//; RF Performance            = High
//; LBD Threshold             = 2.4 V
//; RSSI Offset               = 0
//; RSSI Offset Sign          = 0
//;---------------------------------------
//;  The following are the Register contents
//;---------------------------------------
//;---------------------------------------
//;  The following is the CRC result for
//;  the above Register contents
//;---------------------------------------
#include <arduino.h>

word CMTBank[12] = {
0x0000,
0x0166,
0x02EC,
0x031D,
0x04F0,
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
0x0E30,
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
0x202A,
0x2114,
0x2290,
0x23DD,
0x2400,
0x2500,
0x2600,
0x2700,
0x2800,
0x2900,
0x2A00,
0x2B29,
0x2CC0,
0x2DC8,
0x2E32,
0x2F4B,
0x3005,
0x3100,
0x3250,
0x332D,
0x3400,
0x3501,
0x3605,
0x3705,
};

word BasebandBank[29] = {
0x380A,
0x3904,
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
0x4609,
0x4700,
0x4800,
0x4900,
0x4A00,
0x4B00,
0x4C00,
0x4D00,
0x4E00,
0x4F60,
0x50FF,
0x5100,
0x5200,
0x531F,
0x5410,
};

word TXBank[11] = {
0x5551,
0x564D,
0x5706,
0x5800,
0x5913,
0x5AB0,
0x5B00,
0x5CC8,
0x5D10,
0x5E3F,
0x5F7F,
};
