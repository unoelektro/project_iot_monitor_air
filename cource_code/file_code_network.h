// Fungsi untuk mencari SSID wifi tertentu
bool searchSSIDWifi(String SSIDWifi) {

  view_oled_wifi_scan( stat_status_loading_start   ,SSIDWifi );

  int scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);
  Serial.println("Scanning WIFI :....");
  if (scanResult <= 0) {
    Serial.println(F("Tidak ada jaringan WiFi ditemukan"));
    view_oled_wifi_scan( stat_status_loading_error   ,SSIDWifi );
    return false;
  }

  view_oled_wifi_scan( stat_status_loading_process  ,SSIDWifi );

  for (int i = 0; i < scanResult; i++) {
    String ssid = WiFi.SSID(i);  // ambil SSID per index
    Serial.print("Wifi tersedia : " + ssid);
    if (ssid == SSIDWifi) {
      Serial.print(F(" , SSID Sesuai : "));
      Serial.print(ssid);
      view_oled_wifi_scan( stat_status_loading_success  ,SSIDWifi );
      return true;
    }
    Serial.println();
  }

  view_oled_wifi_scan( stat_status_loading_error    ,SSIDWifi );
  Serial.print(F("SSID tidak ditemukan: "));
  Serial.println(SSIDWifi);
  return false;
}

String codeWifi2Keterangan( byte codeNumber ){
  if( codeNumber == 0 ) return "IDLE.." ;
  else if( codeNumber == 1 ) return "NO SSID.." ;
  else if( codeNumber == 3 ) return "CONNECT.." ;
  else if( codeNumber == 4 ) return "FAILED.." ;
  else if( codeNumber == 6 ) return "WRONG PASS.." ;
  else if( codeNumber == 7 ) return "DISCONNECT.." ;
  return "none" ;
}

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}

bool isDeviceConnectWifi(){
  return (WiFi.localIP() == IPAddress(0, 0, 0, 0)) == false ;
}

void display_ipesp(){
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

int nDot = 0 ;
void dot_loading_wifi(){
  Serial.print(".");
  if( nDot > 30 ){
    nDot = 0 ;
    Serial.println();
  }
}

bool koneksi_Wifi(){
  // 
  view_oled_wifi_connect( stat_status_loading_start   ,WIFI_SSID, "", IpAddress2String(WiFi.localIP()) );
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.println("Connecting to Wi-Fi");
  Serial.println("...");
  //
  nDot = 0 ; // reset counter dot to 0.
  unsigned long tmUpdateWaitWifi      = millis()  ;
  unsigned long tmTimerWifiSetup      = millis()  ;

  view_oled_wifi_connect( stat_status_loading_process  ,WIFI_SSID, "", IpAddress2String(WiFi.localIP())  );
  while (isDeviceConnectWifi() == false)
  {
    float timer = (millis()-tmTimerWifiSetup) / 1000.0 ;
    view_oled_wifi_connect( stat_status_loading_process  ,WIFI_SSID, String(timer,1), IpAddress2String(WiFi.localIP())  );
    if( (millis()-tmUpdateWaitWifi) > 1000 ){
      dot_loading_wifi();
      tmUpdateWaitWifi = millis();
    }
    delay(10);
  }

  if(isDeviceConnectWifi() == true ){
    view_oled_wifi_connect( stat_status_loading_success  ,WIFI_SSID, "", IpAddress2String(WiFi.localIP())  );
  }else{
    view_oled_wifi_connect( stat_status_loading_error   ,WIFI_SSID, "", IpAddress2String(WiFi.localIP())  );
  }

  display_ipesp();
  return isDeviceConnectWifi() ;
}

