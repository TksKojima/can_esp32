#include <Arduino.h>

#include <CAN_app.h>

#include "AsyncUDP.h"
#include <WiFiUdp.h>

#include "wifi_Server.h"

#include "ArduinoJson-v6.19.4.h"
#include <SPIFFS.h>




void setup() {
  Serial.begin(115200);
  Serial.println("Start ");
  while (!Serial);
  can_init();

  wifi_setup( WIFI_AP );  //自分がWifi発信
  //wifi_setup( WIFI_STA );  //ルータ等がWifi発信

}


void loop() {
  static unsigned long curr_prev=0;
  unsigned long curr = millis(); // 現在時刻を更新

  if( curr - curr_prev < 25 ){
    return;
  }
  curr_prev = curr;

  // canbuf_send();
  // delay(1);

  printRecv();
  delay(1);

  wifi_loop();
 
}






void setup_Recv() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop_Recv() {
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  }
}




void loop_CallBack() {
  // do nothing
}



