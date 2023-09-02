#include <Arduino.h>

#include <CAN_app.h>

#include "AsyncUDP.h"
#include <WiFiUdp.h>

#include "wifi_Server.h"
#include "eep.h"

#include "ArduinoJson-v6.19.4.h"
#include <SPIFFS.h>

#include <ArduinoOTA.h>

int pcb_SettingSw = 0;
int pcb_TestsendSw = 0;


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

const char* ssid_ap_main = "Espwifi";
const char* password_ap_main = "98765432";

const char* ssid_sta_main = "safari_wifi";
const char* password_sta_main = "87654321";

// char* ssid_sta_main = "MYASUS";
// char* password_sta_main = "soseken2013";

void setup() {

  Serial.begin(115200);
  Serial.println("Start ");
  while (!Serial);
  can_init();
  eep_init();
  
  //wifi_setup( WIFI_AP );  //自分がWifi発信
  //wifi_setup( WIFI_STA );  //ルータ等がWifi発信
  int sta_ip[] ={ 192, 168, 10, 200 };
  int sta_gt[] ={ 192, 168, 10, 1 };
  int sta_subnet[] ={ 255,255,255,0 };

  int ap_ip[] ={ 192, 168, 1, 200 };
  int ap_gt[] ={ 192, 168, 1, 1 };
  int ap_subnet[] ={ 255,255,255,0 };

  int in_ip[] ={ 192, 168, 1, 200 };
  int in_gt[] ={ 192, 168, 1, 1 };
  int in_subnet[] ={ 255,255,255,0 };

  int eep_id   = 0;
  int eep_mode = MODE_AP_ONLY;

  if( pcb_SettingSw == 0 ){
    // wifi_setup_withEep( 7, 0,
    //   sta_ip, sta_gt, sta_subnet, const_cast<char*>(ssid_sta_main), const_cast<char*>(password_sta_main), 
    //   ap_ip, ap_gt, ap_subnet, const_cast<char*>(ssid_ap_main), const_cast<char*>(password_ap_main), EEP_SIZE_ST_SSID, EEP_SIZE_ST_PASS);

    wifi_setup_input( 1, 0,
       in_ip, in_gt, in_subnet, const_cast<char*>(ssid_ap_main), const_cast<char*>(password_ap_main), EEP_SIZE_ST_SSID, EEP_SIZE_ST_PASS);

  }
  else{ // pcb_SettingSw == 1
    wifi_setup( WIFI_AP );  //自分がWifi発信

  }

  ota_setup();

  Serial.println("SetUpEnd");

// PCB Use
  pinMode( 21, INPUT); 
  pinMode( 22, INPUT); 
  pinMode( 25, INPUT); 
  pinMode( 26, INPUT); 
  pinMode( 33, INPUT); 
  gpio_set_pull_mode(GPIO_NUM_21, GPIO_PULLDOWN_ONLY);
  gpio_set_pull_mode(GPIO_NUM_22, GPIO_PULLDOWN_ONLY);
  gpio_set_pull_mode(GPIO_NUM_25, GPIO_PULLDOWN_ONLY);
  gpio_set_pull_mode(GPIO_NUM_26, GPIO_PULLDOWN_ONLY);
  gpio_set_pull_mode(GPIO_NUM_33, GPIO_PULLDOWN_ONLY);

  pinMode( 13, INPUT); 
  pinMode( 16, INPUT); 
  pinMode( 17, INPUT); 
  gpio_set_pull_mode(GPIO_NUM_13, GPIO_PULLDOWN_ONLY);
  gpio_set_pull_mode(GPIO_NUM_16, GPIO_PULLDOWN_ONLY);
  gpio_set_pull_mode(GPIO_NUM_17, GPIO_PULLDOWN_ONLY);


}

void loop(){
  if( digitalRead(17) == HIGH ){
    canTxbuf_test();
  }
  canbuf_send();

  // Serial.print(" 21: ");
  // Serial.print(digitalRead(21));
  // Serial.print(" 22: ");
  // Serial.print(digitalRead(22));
  // Serial.print(" 25: ");
  // Serial.print(digitalRead(25));
  // Serial.print(" 26: ");
  // Serial.print(digitalRead(26));
  // Serial.print(" 33: ");
  // Serial.print(digitalRead(33));


  // Serial.print(" 13: ");
  // Serial.print(digitalRead(13));
  // Serial.print(" 16: ");
  // Serial.print(digitalRead(16));
  // Serial.print(" 17: ");
  // Serial.print(digitalRead(17));

  // Serial.println("");

  delay(1);
}

void loop_bu() {
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

  if( digitalRead(17) == true ){
    canTxbuf_test();
  }

  canbuf_send();
  //delay(50);

  //printRecv();
   //Serial.println(can_json);

  // 230508 
  // wifi_websocket_loop();
  // wifi_loop();

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



