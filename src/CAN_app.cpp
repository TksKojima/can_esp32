#include <CAN_app.h>

//canBuffer canbuf[10];
const int bufNum = 0x800; 
canBuffer canbuf[bufNum];

int countInterval = 1000;
int countMax = 5;

void can_init(){
   Serial.println("CAN Sender");
   CAN.setPins(26, 27);
   //CAN.setPins(4, 5);

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  canbuf_init();

  // register the receive callback
  CAN.onReceive(onReceive);
}

void can_loop(){
  
}


void canbuf_init(){
//  for( int i=0; i<0x800; i++){
  for( int i=0; i<bufNum; i++){
    canbuf[i].id = i;
    canbuf[i].dlc = i%8 + 1;
    //canbuf[i].txrxFlag = 1;

    if( i<(0x300) ) canbuf[i].txrxFlag = 1;
    else  canbuf[i].txrxFlag = 0;
    
    canbuf[i].cycleTime = canbuf[i].dlc * 100;
    if( i<10 ) {
        canbuf[i].cycleTime = canbuf[i].dlc  * 10;
    }

    canbuf[i].data.u2[0] = 0x1234;
    canbuf[i].data.u2[1] = 0x5678;
    canbuf[i].data.u2[2] = 0x9abc ;
    canbuf[i].data.u2[3] = 0;

    canbuf[i].prevTime = millis();

  }
}


void canbuf_sendSingle( int id ){
  CAN.beginPacket( id );
  for( int i=0; i<canbuf[id].dlc; i++){
    CAN.write( canbuf[id].data.u1[i] );    
  }
  CAN.endPacket();
}


void canbuf_send(){

//  for( int i=0; i<0x800; i++){
  for( int i=0; i<bufNum; i++){
    if( canbuf[i].txrxFlag == canBuffer::TX){
      if( millis() - canbuf[i].prevTime >= canbuf[i].cycleTime ){
        canbuf_sendSingle(i);
        canbuf[i].prevTime = millis();
        canbuf[i].data.u2[3]++; 
        // Serial.print("send id: ");
        // Serial.println(i);


      }
    }
  }
}


void onReceive(int packetSize) {
  // received a packet
  //Serial.print("Received ");

  if (CAN.packetExtended()) {
    Serial.print("extended ");
  }

  if (CAN.packetRtr()) {
    // Remote transmission request, packet contains no data
    //Serial.print("RTR ");
  }

 // Serial.print("packet with id 0x");
  //Serial.print(CAN.packetId(), HEX);

  if (CAN.packetRtr()) {
    //Serial.print(" and requested length ");
    //Serial.println(CAN.packetDlc());
  } else {
    //Serial.print(" and length ");
    //Serial.println(packetSize);

    int rx_id  = CAN.packetId();
    int rx_dlc = CAN.packetDlc();
    canbuf[rx_id].dlc = rx_dlc;
    canbuf[rx_id].cycleTime = millis() - canbuf[rx_id].prevTime;
    canbuf[rx_id].prevTime  = millis();
    canbuf[rx_id].txrxFlag = canBuffer::RX;

    // only print packet data for non-RTR packets
    int idx = 0;
    while (CAN.available()) {
      //Serial.print((char)CAN.read(), HEX );
      //Serial.print(", ");
      char readData = (char)CAN.read();
      if( canbuf[rx_id].data.u1[idx] != readData){
          canbuf[rx_id].noChangeCnt[idx] = 0;
      }
      canbuf[rx_id].data.u1[idx] = readData;
      canbuf[rx_id].noRecvCnt[idx] = 0;
      idx++;
    }
    //Serial.println();
  }
  //Serial.println();
}

void recvDataTimeCount(){
  static unsigned long prevtime=millis();
  if( millis() - prevtime > countInterval ){
    for( int i=0; i<bufNum; i++){
      if( canbuf[i].txrxFlag == canBuffer::RX ){
        for( int k=0; k<canbuf[i].dlc; k++){
          canbuf[i].noChangeCnt[k] += ( canbuf[i].noChangeCnt[k] >= countMax ? 0 : 1 );
          canbuf[i].noRecvCnt[k] += ( canbuf[i].noRecvCnt[k] >= countMax ? 0 : 1 );

        }
      }
    }
    prevtime =  millis();
  }
}

void printRecv(){
   Serial.println("printRecv");
//    for( int i=0; i<0x800; i++){
    for( int i=0; i<bufNum; i++){
      if( canbuf[i].txrxFlag == canBuffer::RX ){
        canbuf[i].txrxFlag =  canBuffer::NON;
        Serial.print(" ID: ");
        Serial.print(i, HEX);
        Serial.print(" cycl: ");
        Serial.print(canbuf[i].cycleTime);

        Serial.print(" data: ");
        for( int k=0; k<canbuf[i].dlc; k++){
          Serial.print(canbuf[i].data.u1[k], HEX);
          Serial.print(", ");

        }
        Serial.println("");
      }
    }

}
void setup_CallBack() {
  Serial.println("CAN Receiver Callback");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // register the receive callback
  CAN.onReceive(onReceive);
}

StaticJsonDocument<4000> candoc;
char can_json[3000];

void makeCanMsgJson(){
  int cnt=0;
  for( int i=0; i<bufNum; i++){
    if( canbuf[i].txrxFlag == canBuffer::RX ){
      cnt++;
    }
  }

  candoc.clear();
  JsonArray canmsgs = candoc.createNestedArray("canmsg");
  canmsgs[0]["rxnum"] = cnt;

  for( int i=0; i<bufNum; i++){
    if( canbuf[i].txrxFlag == canBuffer::RX ){
      canbuf[i].txrxFlag =  canBuffer::NON;
      JsonObject canmsg = canmsgs.createNestedObject();
      canmsg["id"]  = canbuf[i].id;
      canmsg["dlc"] = canbuf[i].dlc;
      canmsg["cycle"] = canbuf[i].cycleTime;

      JsonArray canmsg_data = canmsg.createNestedArray("data");
    
      for( int k=0; k<canbuf[i].dlc; k++){
        canmsg_data.add( canbuf[i].data.u1[k] );    
      }
    }
  }

  serializeJson(candoc, can_json);
  //Serial.print("RX_ID_num:"); Serial.println(cnt);
}

void makeCanMsgJsonDummy(){
  //
  candoc.clear();

  JsonArray canmsg = candoc.createNestedArray("canmsg");

  int rndfornum = random(1,3);
  for(int k=0;k<rndfornum;k++){
    JsonObject canmsg_0 = canmsg.createNestedObject();
    int rndID = random(1,0x7ff);

    canmsg_0["id"] = rndID;
    canmsg_0["dlc"] = (rndID%8) + 1;
    canmsg_0["cycle"] = rndID*10;


    JsonArray canmsg_0_data = canmsg_0.createNestedArray("data");
    canmsg_0_data.add(random(0,255));
    canmsg_0_data.add(random(0,127));
    canmsg_0_data.add(random(0,63));
    canmsg_0_data.add(random(0,31));
    canmsg_0_data.add(random(0,15));
    canmsg_0_data.add(random(0,7));
    canmsg_0_data.add(random(0,3));
    canmsg_0_data.add(1);

  };

  serializeJson(candoc, can_json);

}

