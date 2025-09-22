#include "file_code_parameter.h"
#include "file_code_web.h"
#include "file_code_network.h"
#include "file_code_server.h"
#include "file_code_ota.h"
#include "file_code_display.h"
#include "file_template_display.h"
#include "file_code_inout.h"
#include "file_code_proses.h"


void setup() {
  // Inisial Serial.
  initSerial();

  // Inisial OLED.
  inisial_oled();

  // Inisial External Device.
  initInOutDeviceExt();

  // Fungsi Koneksi WIFI.
  initWiFiConnection();
}

void loop() {
  // Fungsi ESP Handle Server.
  loopESPServer();

  // Pemeriksaan Koneksi WIFI.
  if( isDeviceConnectWifi() == true){
    if( isTimerExpired() )
      stat_wifi = "Disconnect"     ;
    else
      stat_wifi = "Connect Client" ;
  }
  else stat_wifi = "Status:No WIFI" ;

  // Pembacaan sensor dengan timer.
  checkSensorTimer();

  // Fungsi untuk update tampilan layar LCD.
  set_text_oled_realtime(
     name_user ,
     IpAddress2String(WiFi.localIP()),
     stat_wifi, stat_sensor ,
    600
  );

  delay(10);
}
