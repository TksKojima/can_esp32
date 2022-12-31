#ifndef _H_WIFISERVER_
#define _H_WIFISERVER_

#include <Arduino.h>
#include <WebSocketsServer.h> // arduinoWebSocketsƒ‰ƒCƒuƒ‰ƒŠ
#include <SPIFFS.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <CAN_app.h>

extern int plotMode;
extern int dat0_input;
extern int dat1_input;
extern char* websocketOutput; 
extern  WebSocketsServer webSocket;

void wifi_setup( int wifi_mode );
void wifi_loop();
void wifi_websocket_loop(); // 2nd prameter: strlen( websocket_txt )
void wifi_websocket_broad_loop( char* websocket_txt, size_t  strlen_websocket_txt ); // 2nd prameter: strlen( websocket_txt )

void handleRoot();
void handleRC();
void handleNotFound();
void handleInputPad();
void handlePlot();
void handlePlot0();
void handlePlot1();
void handlePlot2();
void handlePlot3();
void handlePlot4();

void handleVueJs();
void handleAxiosJs();
void handleChartJs();


void wifi_data_loop( double data0, double data1, double data2);

#endif




