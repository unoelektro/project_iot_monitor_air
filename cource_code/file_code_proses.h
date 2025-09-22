// Fungsi untuk menginisialisasi serial hardware esp.
void initSerial(){
  Serial.begin(115200);
  delay(1000); 
  for( int i = 0 ; i < 10 ; i++ ){
    Serial.println();
    delay(100);
  }
}

// Fungsi untuk menginisialisasi koneksi WiFi
void initWiFiConnection(){
  if( searchSSIDWifi(WIFI_SSID) == true ){
    if( koneksi_Wifi() ){
      view_oled_server_status( stat_status_loading_start  ,IpAddress2String(WiFi.localIP())  );
      setup_ota();
      view_oled_server_status( stat_status_loading_process ,IpAddress2String(WiFi.localIP())  );
      setup_server();
      server.begin();
      view_oled_server_status( stat_status_loading_success ,IpAddress2String(WiFi.localIP())  );
    }else{
      view_oled_wifi_connect( stat_status_loading_error   ,SSID, "", IpAddress2String(WiFi.localIP())  );
      while(true){delay(10);}
    }
  }else{
    view_oled_wifi_scan( stat_status_loading_error   ,SSID );
    while(true){delay(10);}
  }
}

// Fungsi loop utama untuk ESP8266 Web Server dan OTA
void loopESPServer(){
  ota_code_loop();        // Menjalankan proses OTA (Over-The-Air update).
  server.handleClient();  // Menangani permintaan (request) HTTP dari client.
}


// Fungsi pengecekan timer, dipanggil di loop
void checkSensorTimer() {
  unsigned long currentMillis = millis();

  // Jika sudah 5 detik sejak terakhir baca sensor
  if (currentMillis - sensorReadTimer >= sensorInterval) {
    sensorReadTimer = currentMillis;  // reset timer
    readSensor();                     // panggil fungsi baca sensor
  }
}

