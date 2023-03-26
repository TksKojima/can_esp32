#include <Arduino.h>

#include <CAN_app.h>

#include "AsyncUDP.h"
#include <WiFiUdp.h>

#include "wifi_Server.h"

#include "ArduinoJson-v6.19.4.h"
#include <SPIFFS.h>


#include <ArduinoOTA.h>



void ota_setup(){
  ArduinoOTA.setHostname("esp32can");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

}

void ota_loop() {
  ArduinoOTA.handle();

}

void setup() {
  Serial.begin(115200);
  Serial.println("Start ");
  while (!Serial);
  can_init();

  wifi_setup( WIFI_AP );  //自�?がWifi発信
  //wifi_setup( WIFI_STA );  //ルータ等がWifi発信

  
  ota_setup();

  Serial.println("SetUpEnd");
}


void loop() {
  static unsigned long curr_prev=0;
  static unsigned long curr_prev2=0;  
  unsigned long curr = millis(); // 現在時刻を更新
  unsigned long proctime=0; 
  ota_loop();

  if( curr - curr_prev > 25 ){
    makeCanMsgJson();
    //makeCanMsgJsonDummy();  
    wifi_websocket_broad_loop( can_json, strlen(can_json) );
    curr_prev = curr;
    proctime = millis() - curr;

    if( curr - curr_prev2 > 1000 ){
      //Serial.println(proctime);
      curr_prev2 = curr;
    }

  }

  canbuf_send();
  //delay(50);

  //printRecv();
 

  //Serial.println(can_json);
  wifi_websocket_loop();
   wifi_loop();
  delay(1);

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



