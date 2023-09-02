#include <eep.h>


void eep_init(){
    EEPROM.begin(EEP_SIZE_ALL); // EEPROMのサイズを指定
    int value = EEPROM.read(0); // アドレス0から値を読み取る
    Serial.println(value);
    if (value == 0xFF) { // EEPROMが初期化されていない場合は、初期化する
        Serial.println("Initializing EEPROM...");
        for (int i = 0; i < EEP_SIZE_ALL; i++) {
        EEPROM.write(i, 0);
        }
        EEPROM.commit(); // EEPROMの変更を保存
    }


    eep_read();
    eep_write();
}

void eep_loop(){

}


void eep_write_num( int addrOffset, int num ){
  EEPROM.write(addrOffset, num);
  EEPROM.commit();
}

void eep_write_str( int addrOffset, const char* str, int size ){
  for (int i = 0; i < size; i++) {
    EEPROM.write(addrOffset + i, str[i]);
  }
  EEPROM.commit();
}


void eep_write(){
  Serial.println( "Write" );
  int write_id = random(100);
  int write_mode = random(100);

  const char* st_ssid_str = "ssidstrstr!";
  const char* st_pass_str = "pass!_pass!";
  const char* ap_ssid_str = "ap!ssidstrstr!";
  const char* ap_pass_str = "ap!pass!_pass!";


  std::string ssid_with_id = std::string(st_ssid_str) + "_" + std::to_string(write_id);
  const char* ssid_id_str = ssid_with_id.c_str();

  std::string pass_with_id = std::string(st_pass_str) + "_" + std::to_string(write_mode);
  const char* pass_id_str = pass_with_id.c_str();

  
  Serial.println(write_id);    
  eep_write_num( EEP_ADDR_ID,   write_id );

  Serial.println(write_mode);
  eep_write_num( EEP_ADDR_MODE, write_mode );

  eep_write_num( EEP_ADDR_ST_IP,   192 );
  eep_write_num( EEP_ADDR_ST_IP+1, 168 );
  eep_write_num( EEP_ADDR_ST_IP+2, 10 );
  eep_write_num( EEP_ADDR_ST_IP+3, 200 );

  eep_write_num( EEP_ADDR_ST_GW,   192 );
  eep_write_num( EEP_ADDR_ST_GW+1, 168 );
  eep_write_num( EEP_ADDR_ST_GW+2, 10 );
  eep_write_num( EEP_ADDR_ST_GW+3, 200 );

  eep_write_num( EEP_ADDR_ST_SN,   255 );
  eep_write_num( EEP_ADDR_ST_SN+1, 255 );
  eep_write_num( EEP_ADDR_ST_SN+2, 255);
  eep_write_num( EEP_ADDR_ST_SN+3, 0 );

  Serial.println(pass_id_str);    
  eep_write_str( EEP_ADDR_ST_PASS, pass_id_str, EEP_SIZE_ST_PASS );

  Serial.println(ssid_id_str);
  eep_write_str( EEP_ADDR_ST_SSID, ssid_id_str, EEP_SIZE_ST_SSID );


}

void eep_read(){
    char ssid[EEP_SIZE_ST_SSID] = {0};
    char password[EEP_SIZE_ST_PASS] = {0};

    Serial.println( "Read" );
    Serial.println( eep_read_num( EEP_ADDR_ID ) );
    Serial.println( eep_read_num( EEP_ADDR_MODE ) );

    eep_read_str( EEP_ADDR_ST_PASS, password, EEP_SIZE_ST_PASS );
    eep_read_str( EEP_ADDR_ST_SSID, ssid,     EEP_SIZE_ST_SSID );    
    Serial.println( password );
    Serial.println( ssid );
}

int eep_read_num( int addrOffset ){
  return  EEPROM.read( addrOffset );

}
void eep_read_str(int addrOffset, char* str, int size) {
  for (int i = 0; i < size; i++) {
    str[i] = EEPROM.read(addrOffset + i);
  }
}


// void eep_write_wifimode( int mode ){
// }
// void eep_write_espid(){}
// void eep_write_pass(){}
// void eep_write_ssid(){}

// void eep_read(){}
// void eep_read_wifimode(){}
// void eep_read_espid(){}
// void eep_read_pass(){}
// void eep_read_ssid(){}

