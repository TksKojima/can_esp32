#include "wifi_Server.h"

#include "ArduinoJson-v6.19.4.h"

#include "index_html.h" // web server root index

//SPIFFSアップロード
//C:\Users\user\.platformio\penv\Scripts\platformio.exe run --target uploadfs 

// input 
int dat0_input = 0;
int dat1_input = 0;
int dat2_input = 0;
int dat3_input = 0;

int plotMode = 0;

WebServer server(80);
// Websocketサーバー IPアドレス:81
WebSocketsServer webSocket = WebSocketsServer(81); // 81番ポート

//char* webSocketOutput ="";

const char* ssid_ap = "wifi";
const char* password_ap = "12345678";

// const char* ssid_sta = "MYASUS";
// const char* password_sta = "12345678";

const char* ssid_sta = "safari_wifi";
const char* password_sta = "87654321";


// AP mode
// const IPAddress ip(192, 168, 0, 55);
// const IPAddress gateway(192, 168, 0, 55); //gatewayのIPアドレス

// MYASUS
// const IPAddress ip(192, 168, 43, 149);
// const IPAddress gateway(192, 168, 43, 149); //gatewayのIPアドレス
// const IPAddress subnet(255,255,255,0);

// Kojima Rooter
const IPAddress ip(192, 168, 10, 108);
const IPAddress gateway(192, 168, 10, 108); //gatewayのIPアドレス
const IPAddress subnet(255,255,255,0);


// センサのデータ(JSON形式)
//const char SENSOR_JSON[] PROGMEM = R"=====({"val1":%.1f})=====";
//const char SENSOR_JSON[] PROGMEM = R"=====({"val0":%.1f, "val1":%.1f, "val2":%.1f, "str0":"%s", "str1":"%s", "str2":"%s"})=====";
//const char SENSOR_JSON[] PROGMEM = R"=====({"val0":%.1f, "val1":%.1f, "val2":%.1f, "mode":%d})=====";




// // Webコンテンツのイベントハンドラ
// // センサのデータ(JSON形式)
// const char SENSOR_JSON[] PROGMEM = R"=====({"val1":%.1f})=====";

// // データの更新
// void sensor_loop() {
//   char payload[16];
// //=============================================
// // (4) センシング
//   float temp = 3;//htu21d.readTemperature();
//   snprintf_P(payload, sizeof(payload), SENSOR_JSON, temp);
// //============================================= 

//   // WebSocketでデータ送信(全端末へブロードキャスト)
//   webSocket.broadcastTXT(payload, strlen(payload));
// //  Serial.println(payload);
// }



//  MIMEタイプを推定
String getContentType(String filename){
  if(filename.endsWith(".html") || filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else return "text/plain";
}
//  SPIFSS のファイルをクライアントに転送する
bool handleFileRead(String path) {
  Serial.println("handleFileRead: trying to read " + path);
  // パス指定されたファイルがあればクライアントに送信する

  String contentType = getContentType(path);
  if (SPIFFS.exists(path)) {
    Serial.println("handleFileRead: sending " + path);    
    File file = SPIFFS.open(path, "r");
    server.send(200,contentType,file.readString());
    file.close();
    Serial.println("handleFileRead: sent " + path);
    return true;
  }
  else {
    Serial.println("handleFileRead: 404 not found");
    server.send (404, "text/plain", "ESP: 404 not found");
    return false;
  }
}



void wifi_setup( int wifi_mode ){
  delay(500);

  if(  wifi_mode == WIFI_STA ){
    int cnt = 0;
    do{
      if( cnt == 0){
        if (!WiFi.config(ip,gateway,subnet)){
            Serial.println("Failed to configure!");
        }  
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid_sta, password_sta);
        Serial.print("Connecting to ");
        Serial.println(ssid_sta);
      }
      delay(500);
      Serial.print(".");
      cnt++;
      if( cnt >= 10 ){ cnt = 0; }

    }while (WiFi.status() != WL_CONNECTED);

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());    
  }
  else if( wifi_mode == WIFI_AP ){
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid_ap, password_ap, 3, 0, 6);
    delay(200);
    WiFi.softAPConfig( ip,gateway,subnet );
    Serial.println("");
    Serial.print("AP IP address: ");
    Serial.print(WiFi.softAPIP());    

  }
    
  Serial.println();
  delay(100);
    
  if (MDNS.begin("esp32led")) {
    Serial.println("MDNS responder started");
  }


  // Webサーバーのコンテンツ設定
  // favicon.ico, Chart.min.jsは dataフォルダ内に配置
  SPIFFS.begin();
  server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico");
  server.serveStatic("/Chart.min.js", SPIFFS, "/Chart.min.js");
  server.serveStatic("/axios.min.js", SPIFFS, "/axios.min.js");
  server.serveStatic("/vue.js", SPIFFS, "/vue.js");
  server.serveStatic("/can.html", SPIFFS, "/can.html");
  // server.serveStatic("/hoge", SPIFFS, "/Chart.min.jshogehoge");

  server.on("/", handleRoot);
  
  server.on("/rc", handleRC); 
  server.onNotFound(handleNotFound);
  server.on("/inputPad", handleInputPad);
  server.on("/plot", handlePlot);
  server.on("/plot0", handlePlot0);
  server.on("/plot1", handlePlot1);
  server.on("/plot2", handlePlot2);
  server.on("/plot3", handlePlot3);
  server.on("/plot4", handlePlot4);
  // server.on("/vue.js", handleVueJs);
  // server.on("/axios.min.js", handleAxiosJs);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  // WebSocketサーバー開始
  webSocket.begin();

}


//StaticJsonDocument<2000> doc;

void wifi_loop(){
  server.handleClient();

//StaticJsonDocument<2000> doc;
// doc.clear();

// JsonArray mssges = doc.createNestedArray("mssges");

// int rndfornum = random(1,3);
// for(int k=0;k<rndfornum;k++){
//   JsonObject mssges_0 = mssges.createNestedObject();
// //  int rndID = random(1,0x7ff);
//   int rndID = random(1,0x7ff);

//   mssges_0["id"] = rndID;
//   mssges_0["dlc"] = (rndID%8) + 1;

//   JsonArray mssges_0_data = mssges_0.createNestedArray("data");
//   mssges_0_data.add(random(0,255));
//   mssges_0_data.add(random(0,127));
//   mssges_0_data.add(random(0,63));
//   mssges_0_data.add(random(0,31));
//   mssges_0_data.add(random(0,15));
//   mssges_0_data.add(random(0,7));
//   mssges_0_data.add(random(0,3));
//   mssges_0_data.add(1);

// };

// serializeJson(doc, output);
//Serial.println(output);
//webSocket.broadcastTXT( webSocketOutput, strlen(websocketOutput));

}

void wifi_websocket_loop( char* websocket_txt, size_t len ){
  webSocket.loop();
  //webSocket.broadcastTXT( websocket_txt, strlen(websocket_txt));
  webSocket.broadcastTXT( websocket_txt, len);

}

// Webコンテンツのイベントハンドラ
void handlePlot() {
// can.htmlより読み込み
  handleFileRead("/can.html");

}

void handleVueJs() {
  handleFileRead("/vue.js");
  // File file = SPIFFS.open("/vue.js", "r");
  // server.send(200, "application/javascript", file.readString());
  // file.close();

}
void handleAxiosJs() {
  handleFileRead("/axios.min.js");
  // File file = SPIFFS.open("/axios.min.js", "r");
  // server.send(200, "application/javascript", file.readString());
  // file.close();  
}
void handleChartJs() {
  handleFileRead("/Chart.min.js");
}

void handlePlot0() {
  plotMode = 0;
  handlePlot();
}
void handlePlot1() {
  String s = INDEX_HTML; // index_html.hより読み込み
  server.send(200, "text/html", s);
  
}
void handlePlot2() {
  plotMode = 2;
  handlePlot();
  
}
void handlePlot3() {
  plotMode = 3;
  handlePlot();
  
}
void handlePlot4() {
  plotMode = 4;
  handlePlot();
  
}


void handleRoot() { //ブラウザのUI
  //String s = INDEX_HTML; // index_html.hより読み込み
  //server.send(200, "text/html", s);
  handlePlot4();

}

void handleInputPad() { //ブラウザのUI
  server.send(200, "text/html", ""); 
}

void handleRC() { //ブラウザのUIを操作した結果のJSからアクセスされる
  for (int i = 0; i < server.args(); i++) {
    int Val_i = server.arg(i).toInt();
    Serial.print(server.argName(i) + "=" + server.arg(i) + ", ");
    
    if(      server.argName(i) == "D0" ) { dat0_input = Val_i; }
    else if( server.argName(i) == "D1" ) { dat1_input = Val_i; }

  }
  Serial.println();
  server.send(200, "text/plain", "\n\n\n");
}
 
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


