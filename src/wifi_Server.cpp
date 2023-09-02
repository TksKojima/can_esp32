
#include "wifi_Server.h"


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

const char* ssid_ap = "wifi-wifi";
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
// const IPAddress ip(192, 168, 10, 108);
// const IPAddress gateway(192, 168, 10, 108); //gatewayのIPアドレス
// const IPAddress subnet(255,255,255,0);

IPAddress ip(192, 168, 10, 108);
IPAddress gateway(192, 168, 10, 108); //gatewayのIPアドレス
IPAddress subnet(255,255,255,0);



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

int wifi_setup_input(  int device_id, int connect_mode,  
  int in_ip[], int in_gw[], int in_subnet[], char* in_ssid, char* in_password, int MAX_SSID_LENGTH, int MAX_PASSWORD_LENGTH ){

  IPAddress ip(     in_ip[0], in_ip[1], in_ip[2], in_ip[3] );
  IPAddress gateway( in_gw[0], in_gw[1], in_gw[2], in_gw[3] ); //gatewayのIPアドレス
  IPAddress subnet( in_subnet[0], in_subnet[1], in_subnet[2], in_subnet[3]);

  int cnt = 0;
  unsigned long connectTimeout = 10000; //10 seconds
  unsigned long timer_ms = millis();

  Serial.println("");
  Serial.println("[ WiFi setup ]");
    
  if( connect_mode == MODE_STA_ONLY  ){
    // Station mode
    Serial.println("STA mode started");
    WiFi.mode(WIFI_STA);
    //WiFi.config(ip, gateway, subnet);

    // Connect to WiFi network
    Serial.print("Connecting to ");
    Serial.println(in_ssid);

    WiFi.begin(in_ssid, in_password);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED ) {
      delay(500);
      Serial.print(".");

      if( millis() - start > connectTimeout ){
        Serial.print("Time Out!");

      }

    }
    Serial.println("");
    Serial.println("Connected! ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Subnet: ");
    Serial.println(WiFi.subnetMask());

  }
  else{  //if( connect_mode == MODE_AP_ONLY ){
    Serial.println("AP mode started");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(in_ssid, in_password, 1, 0, 4);
    delay(200);
    WiFi.softAPConfig( ip,gateway,subnet );

    // Connect to WiFi network
    Serial.print("AP SSID: ");
    Serial.println( in_ssid);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
  
  }

  char name[20];
  sprintf(name, "esp32can%d", device_id);
  if (MDNS.begin( name  ) ) {
    Serial.print("MDNS: ");
    Serial.println( name );
  }

  
  return 0;  
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

  server_setup();  
}

void server_setup(){

  // Webサーバーのコンテンツ設定
  // favicon.ico, Chart.min.jsは dataフォルダ内に配置
  SPIFFS.begin();
  server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico");
  server.serveStatic("/Chart.min.js", SPIFFS, "/Chart.min.js");
  server.serveStatic("/axios.min.js", SPIFFS, "/axios.min.js");
  server.serveStatic("/vue.js", SPIFFS, "/vue.js");
  server.serveStatic("/js", SPIFFS, "/js");
  server.serveStatic("/css", SPIFFS, "/css");

  server.serveStatic("/index.html", SPIFFS, "/index.html");
  server.serveStatic("/test.html", SPIFFS, "/test.html");
  // server.serveStatic("/hoge", SPIFFS, "/Chart.min.jshogehoge");

  server.enableCORS(); //This is the magic

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
  server.on("/post",  handlePost);
  server.on("/posteep",  handlePostEep);
  server.on("/postcheck",  handlePostCheck);



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

void wifi_websocket_loop( ){
  webSocket.loop();
  
}

void wifi_websocket_broad_loop( char* websocket_txt, size_t len ){
  //webSocket.broadcastTXT( websocket_txt, strlen(websocket_txt));
  webSocket.broadcastTXT( websocket_txt, len);

}

// Webコンテンツのイベントハンドラ
void handlePlot() {
// index.htmlより読み込み
  handleFileRead("/index.html");

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

void handlePostCheck() { //
  IPAddress nowIP;
  if( WiFi.getMode() == WIFI_STA ){
    nowIP = WiFi.localIP();
  }else{
    nowIP = WiFi.softAPIP();
  }
   
  server.send(200, "text/html", nowIP.toString() ); 

  // IPアドレスを取得し、シリアルモニターに表示
  // Serial.print("IP address: ");
  // Serial.println( nowIP.toString() );    
  //Serial.println( WiFi.localIP().toString() );    
  
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

void handlePost() {
  if (server.method() == HTTP_POST) {
    String postData = server.arg("plain");  // POSTデータを文字列として取得

    // JSONパーサーを使用してJSONデータを解析する
    DynamicJsonDocument doc(6144);   // 解析用のJSONオブジェクトを生成
    DeserializationError error = deserializeJson(doc, postData);  // JSONデータを解析する
    //Serial.println( postData );

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());

    } else {
      // 配列要素を1つずつ処理する
      JsonArray array = doc.as<JsonArray>();
      for (JsonVariant obj : array) {
        int id = obj["canid"];                 // "id"プロパティを取得
        int cycle = obj["cycle"];           // "cycle"プロパティを取得
        int dlc = obj["dlc"];           // "cycle"プロパティを取得
        JsonArray data = obj["data"];       // "data"プロパティを取得
        int trans = obj["trans"];           // "cycle"プロパティを取得

        //  Serial.print("canid: ");
        //  Serial.print(id);
        //  Serial.print(", dlc: ");
        //  Serial.print(dlc);
        //  Serial.print(", cycle: ");
        //  Serial.print(cycle);
        //  Serial.print(", trans: ");
        //  Serial.print(trans);
        //  Serial.print(", data: ");
        unsigned char inputdata[8];
        int i=0;
        for (JsonVariant value : data) {
          unsigned char v = value.as<int>();          // 配列要素をint型に変換
          // ここで取得したデータを処理する
        //  Serial.print(v);
        //  Serial.print(", ");
         inputdata[i] = v; i++;

        }
       // Serial.print("posted ");

        canTxbuf_set( id, dlc, cycle, inputdata, trans);
        //  Serial.println("");
      }
    }

    //Serial.println("data recv");
    //CROSエラー回避のヘッダを追加
    // server.sendHeader("Access-Control-Allow-Origin", "http://localhost:8080/");
    // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
     
    server.send(200, "text/plain", "Data received");
    //http.StatusOK
  } else {
    //server.send(405, "text/plain", "Method Not Allowed");
    server.send(200, "text/plain", "Method Not Allowed");

  }
}

void handlePostEep() {
  if (server.method() == HTTP_POST) {
    String postData = server.arg("plain");  // POSTデータを文字列として取得

    // JSONパーサーを使用してJSONデータを解析する
    DynamicJsonDocument doc(6144);   // 解析用のJSONオブジェクトを生成
    DeserializationError error = deserializeJson(doc, postData);  // JSONデータを解析する

    Serial.println( "[ POST EEP Data ]" );
    Serial.println( postData );

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());

    } else {
      int deviceId = doc["device_id"];  // int型の値を取得
      int connect_mode = doc["connect_mode"]; 

      int ip_addr[]={0,0,0,0};
      int subnet_mask[]={0,0,0,0};
      int def_gateway[]={0,0,0,0};
      const char*  ssid_str = doc["ssid"]; 
      const char*  password_str = doc["password"];  

      ip_addr[0] = doc["ip_addr0"];
      ip_addr[1] = doc["ip_addr1"];
      ip_addr[2] = doc["ip_addr2"];
      ip_addr[3] = doc["ip_addr3"];

      subnet_mask[0] = doc["subnet0"];
      subnet_mask[1] = doc["subnet1"];
      subnet_mask[2] = doc["subnet2"];
      subnet_mask[3] = doc["subnet3"];

      def_gateway[0] = doc["gateway0"];
      def_gateway[1] = doc["gateway1"];
      def_gateway[2] = doc["gateway2"];
      def_gateway[3] = doc["gateway3"];

      Serial.print("DeviceID: ");
      Serial.println(deviceId);
      Serial.print("connect_mode: ");
      Serial.println(connect_mode);
      Serial.print("ip_addr: ");
      Serial.print(ip_addr[0]);
      Serial.print(ip_addr[1]);
      Serial.print(ip_addr[2]);
      Serial.println(ip_addr[3]);
      Serial.print("subnet: ");
      Serial.print(subnet_mask[0]);
      Serial.print(subnet_mask[1]);
      Serial.print(subnet_mask[2]);
      Serial.println(subnet_mask[3]);
      Serial.print("gateway: ");
      Serial.print(def_gateway[0]);
      Serial.print(def_gateway[1]);
      Serial.print(def_gateway[2]);
      Serial.println(def_gateway[3]);
      Serial.print( "pass: ");
      Serial.println( password_str);
      Serial.print( "ssid: ");
      Serial.println( ssid_str);


      eep_write_num( EEP_ADDR_ID,   deviceId );
      eep_write_num( EEP_ADDR_MODE, connect_mode );

      for( int i=0; i<4; i++ ){
        eep_write_num( EEP_ADDR_ST_IP + i,   ip_addr[i] );
        eep_write_num( EEP_ADDR_ST_SN + i,   subnet_mask[i] );
        eep_write_num( EEP_ADDR_ST_GW + i,   def_gateway[i] );
      }

      eep_write_str( EEP_ADDR_ST_PASS, password_str, EEP_SIZE_ST_PASS );
      eep_write_str( EEP_ADDR_ST_SSID, ssid_str, EEP_SIZE_ST_SSID );

      Serial.println( "EEP Wrote ");

      // Serial.println( "EEP Read ");

      // eep_read_str( EEP_ADDR_AP_PASS, char* str, int size) 


    }

    //Serial.println("data recv");
    //CROSエラー回避のヘッダを追加
    // server.sendHeader("Access-Control-Allow-Origin", "http://localhost:8080/");
    // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
     
    server.send(200, "text/plain", "Data received");
    //http.StatusOK

  } else {
    //server.send(405, "text/plain", "Method Not Allowed");
    server.send(200, "text/plain", "Method Not Allowed");

  }
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


