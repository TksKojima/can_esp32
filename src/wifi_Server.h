#ifndef _H_WIFISERVER_
#define _H_WIFISERVER_

#include <Arduino.h>
#include <WebSocketsServer.h> // arduinoWebSockets���C�u����
#include <SPIFFS.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

extern int plotMode;
extern int dat0_input;
extern int dat1_input;


void wifi_setup( int wifi_mode );
void wifi_loop();

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




