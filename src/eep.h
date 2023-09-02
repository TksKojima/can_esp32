#ifndef EPP_H
#define EPP_H

#include <Arduino.h>
#include <EEPROM.h>
#include "ArduinoJson-v6.19.4.h"

#define EEP_SIZE_ALL 512

#define EEP_SIZE_ID    8
#define EEP_SIZE_MODE  8

#define EEP_SIZE_ST_IP 4
#define EEP_SIZE_ST_GW 4 // gate wey
#define EEP_SIZE_ST_SN 4 // sub net
#define EEP_SIZE_ST_SSID 32
#define EEP_SIZE_ST_PASS 32

#define EEP_SIZE_AP_IP 4
#define EEP_SIZE_AP_GW 4 // gate wey
#define EEP_SIZE_AP_SN 4 // sub net
#define EEP_SIZE_AP_SSID 32
#define EEP_SIZE_AP_PASS 32


#define EEP_ADDR_ID    0
#define EEP_ADDR_MODE  (EEP_ADDR_ID   + EEP_SIZE_ID)
#define EEP_ADDR_ST_IP     (EEP_ADDR_MODE    + EEP_SIZE_MODE)             
#define EEP_ADDR_ST_GW     (EEP_ADDR_ST_IP   + EEP_SIZE_ST_IP)           
#define EEP_ADDR_ST_SN     (EEP_ADDR_ST_GW   + EEP_SIZE_ST_GW)             
#define EEP_ADDR_ST_SSID   (EEP_ADDR_ST_SN   + EEP_SIZE_ST_SN)            
#define EEP_ADDR_ST_PASS   (EEP_ADDR_ST_SSID + EEP_SIZE_ST_SSID)            
#define EEP_ADDR_AP_IP     (EEP_ADDR_ST_PASS + EEP_SIZE_ST_PASS)          
#define EEP_ADDR_AP_GW     (EEP_ADDR_AP_IP   + EEP_SIZE_AP_IP)           
#define EEP_ADDR_AP_SN     (EEP_ADDR_AP_GW   + EEP_SIZE_AP_GW)           
#define EEP_ADDR_AP_SSID   (EEP_ADDR_AP_SN   + EEP_SIZE_AP_SN)            
#define EEP_ADDR_AP_PASS   (EEP_ADDR_AP_SSID + EEP_SIZE_AP_SSID)            


void eep_init();
void eep_loop();

void eep_write();
void eep_write_num( int addrOffset, int num );
void eep_write_str( int addrOffset, char* str, int size );

void eep_read();
int  eep_read_num( int addrOffset );
void eep_read_str( int addrOffset, char* str, int size );


// void eep_write_mode( int mode );
// void eep_write_espid( int id );
// void eep_write_pass();
// void eep_write_ssid();

// void eep_read_mode();
// void eep_read_espid();
// void eep_read_pass();
// void eep_read_ssid();



#endif
