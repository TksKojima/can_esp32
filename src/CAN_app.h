// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CAN_APP_H
#define CAN_APP_H

#include <Arduino.h>
#include <CAN.h>

// typedef struct canApp{
// }canApp;

typedef struct canBuffer
{
    static const int NON = 0;
    static const int TX = 1;
    static const int RX = 2;

    char  txrxFlag;
    char  dlc;
    short id;  
    unsigned long prevTime;
    short cycleTime;  

	union {
		unsigned char  u1[8];   /**< \brief Payload byte access*/
		unsigned short u2[4]; /**< \brief Payload u32 access*/
		unsigned long  u4[2];    /**< \brief Payload u64 access*/
	} data;

    unsigned char noRecvCnt[8];
    unsigned char noChangeCnt[8];


}canBuffer;

//canBuffer canbuf[0x800];

void can_init();
void canbuf_init();
void canbuf_sendSingle( int id );
void canbuf_send();
void canbuf_sendSingle( int id );
void onReceive(int packetSize);
void printRecv();
void setup_CallBack();


#endif
