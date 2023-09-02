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

#define  MODE_STA_ONLY   (0)
#define  MODE_AP_ONLY    (1)
#define  MODE_STA_TO_AP  (2)


void wifi_setup( int wifi_mode );
void wifi_setup_withEep(int device_id, int connect_mode,  
  int sta_ip[], int sta_gw[], int sta_subnet[], char* ssid_sta, char* password_sta, 
  int ap_ip[],   int ap_gw[], int ap_subnet[],  char* ap_ssid,  char* ap_password, int MAX_SSID_LENGTH, int MAX_PASSWORD_LENGTH );

int wifi_setup_input(int device_id, int connect_mode,  
  int in_ip[],   int in_gw[], int in_subnet[],  char* in_ssid,  char* in_password, int MAX_SSID_LENGTH, int MAX_PASSWORD_LENGTH );

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
void handlePost();

void handleVueJs();
void handleAxiosJs();
void handleChartJs();


void wifi_data_loop( double data0, double data1, double data2);

#endif




