/*** How to use
 ・DIPSW2 が ONのとき設定モード
 　ESP32が、SSIDが ”esp_wifi0”（0は設定モード時の暫定デバイスID） のWIFIを発信
 　接続してブラウザで
   http://esp32can0（0は設定モード時の暫定デバイスID）にアクセス可能
    
  まずはDIPSW2がOFFのときのノーマルモードのための
  アクセスモード、IPやサブネット、SSID・パスワードを設定する
  　
  DIPスイッチは
   DIP1：CANピンの終端抵抗のOn/Off、Onのときに物理的に抵抗を接続
   DIP2：On：設定モード、Off：ノーマルモード
   DIP3：On：CAN送信テストモード、適当なIDのメッセージを送信 Off：ノーマルモード
   DIP4：On：CAN受信テストモード、シリアルに受信メッセを表示 Off：ノーマルモード

*/

#include <Arduino.h>

#include <CAN_app.h>

#include "AsyncUDP.h"
#include <WiFiUdp.h>

#include "wifi_Server.h"
#include "eep.h"
#include "pcb_setting.h"


#include "ArduinoJson-v6.19.4.h"
#include <SPIFFS.h>

#include <ArduinoOTA.h>

int pcb_SettingSw = 1;
int pcb_TestsendSw = 0;


void ota_setup(){
  // ArduinoOTA.setHostname("esp32can");

  // ArduinoOTA
  //   .onStart([]() {
  //     String type;
  //     if (ArduinoOTA.getCommand() == U_FLASH)
  //       type = "sketch";
  //     else // U_SPIFFS
  //       type = "filesystem";
  //     Serial.println("Start updating " + type);
  //   })
  //   .onEnd([]() {
  //     Serial.println("\nEnd");
  //   })
  //   .onProgress([](unsigned int progress, unsigned int total) {
  //     Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  //   })
  //   .onError([](ota_error_t error) {
  //     Serial.printf("Error[%u]: ", error);
  //     if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
  //     else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
  //     else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
  //     else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
  //     else if (error == OTA_END_ERROR) Serial.println("End Failed");
  //   });

  // ArduinoOTA.begin();

}

void ota_loop() {
  ArduinoOTA.handle();
}

//セッティングONのときの設定
const char* set_ssid = "EspWiFi";
const char* set_password = "98765432";
int set_ip[] ={ 192, 168, 0, 123 };
int set_gt[] ={ 192, 168, 0, 1 };
int set_subnet[] ={ 255,255,255,0 };

int eep_ip[] = { 0, 0, 0, 0 };
int eep_gt[] = { 0, 0, 0, 0 };
int eep_subnet[] = { 0, 0, 0, 0 };

int eep_id   = 0;
int eep_mode = MODE_AP_ONLY;
// char eep_ssid[] = "safari_wifi";
// char eep_pass[] = "87654321";
char eep_ssid[EEP_SIZE_ST_SSID] = {0};
char eep_pass[EEP_SIZE_ST_PASS] = {0};

// const char* eep_ssid = "safari_wifi";
// const char* eep_password = "87654321";

void setup() {

  Serial.begin(115200);
  Serial.println("[ Start ]");
  while (!Serial);
  pcb_init();
  can_init();
  eep_init();

  eep_read_wifi_setting( &eep_id, &eep_mode, eep_ip, eep_gt, eep_subnet, eep_ssid, eep_pass, EEP_SIZE_CHAR );

  char set_ssid_withid[EEP_SIZE_CHAR];
  char id_char[3];  
  char ip_char[4];  

  snprintf( id_char, sizeof(id_char), "%d", eep_id );  // 数値を文字列に変換

  strcpy(set_ssid_withid, set_ssid);  // ベースの文字列をコピー
  strcat(set_ssid_withid, "-id");  // 数値を追加
  strcat(set_ssid_withid, id_char);  // 数値を追加
  if( eep_mode == MODE_AP_ONLY ){
    strcat(set_ssid_withid, "-AP");  // 数値を追加
  }else if( eep_mode == MODE_STA_ONLY  ){
    strcat(set_ssid_withid, "-STA");  // 数値を追加
  }else if( eep_mode == MODE_STA_TO_AP  ){
    strcat(set_ssid_withid, "-S2A");  // 数値を追加
  }
    strcat(set_ssid_withid, "-");  // 数値を追加

  for( int i=0; i<4; i++ ){
    snprintf( ip_char, sizeof(ip_char), "%d", eep_ip[i] );  // 数値を文字列に変換
    strcat(set_ssid_withid, ip_char);  // 数値を追加

  }




  if( digitalRead(DIPSW_PIN2) == HIGH ){
    pcb_SettingSw = 1;
  }else{
    pcb_SettingSw = 0;
  }

  //DIPスイッチからの入力がOFFのときは通常モード
  if( pcb_SettingSw == 0 ){
    wifi_setup_input( eep_id, eep_mode,
       eep_ip, eep_gt, eep_subnet, const_cast<char*>(eep_ssid), const_cast<char*>( eep_pass ), EEP_SIZE_ST_SSID, EEP_SIZE_ST_PASS);

  }
  //DIPスイッチからの入力がONのときはセッティングモード
  else{ // pcb_SettingSw == 1
    wifi_setup_input( 0, MODE_AP_ONLY,
       set_ip, set_gt, set_subnet, const_cast<char*>( set_ssid_withid ), const_cast<char*>( set_password ), EEP_SIZE_ST_SSID, EEP_SIZE_ST_PASS);

  }

  server_setup();


  //ota_setup();
  Serial.println("");
  Serial.println("[ SetUp End ]");

}

void loop_test(){
  if( digitalRead(DIPSW_PIN2) == HIGH || digitalRead(DIPSW_PIN3) == HIGH || digitalRead(DIPSW_PIN4) == HIGH ){
    digitalWrite( LED_PIN, HIGH );
  }
  else{
    digitalWrite( LED_PIN, LOW );    
  }

  

  //canbuf_send();

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

  loop_test();

  can_setTestFlag( digitalRead(DIPSW_PIN3) , digitalRead(DIPSW_PIN4) );
  can_loop();

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



