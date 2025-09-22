// Fungsi reset timer (panggil saat user akses endpoint)
void resetTimer() {
  lastAccessTime = millis();
}

// Fungsi cek sisa waktu sejak terakhir akses
unsigned long getElapsedTime() {
  return millis() - lastAccessTime;
}

// Fungsi cek apakah timer sudah lewat
bool isTimerExpired() {
  return getElapsedTime() >= timerDuration;
}


void handleRoot() {
  resetTimer();
  server.send(200, "text/html", htmlPage );
}

void handleRoot_Tablet() {
  resetTimer();
  server.send(200, "text/html", htmlPage_Tablet );
}


void handleGet() {
  resetTimer();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", generateDataEndPoint() );
}

// http://192.168.100.201/set?value=30
void handleSet() {
  resetTimer();
  if (server.hasArg("value")) {          // cek apakah ada parameter "value"
    String value = server.arg("value");  // ambil nilai parameter
    Serial.print("Value: ");
    Serial.println(value);
    server.send(200, "text/plain", "OK, value=" + value);
  } else {
    server.send(400, "text/plain", "Parameter 'value' missing");
  }
}

// http://192.168.100.201/set?value=30&mode=auto&time=10
void handleSet3Param() {
  resetTimer();
  String value = server.hasArg("value") ? server.arg("value") : "";
  String mode  = server.hasArg("mode")  ? server.arg("mode")  : "";
  String time  = server.hasArg("time")  ? server.arg("time")  : "";

  Serial.println("Received parameters:");
  Serial.println("Value: " + value);
  Serial.println("Mode:  " + mode);
  Serial.println("Time:  " + time);

  server.send(200, "text/plain", "Parameters received");
}

void setup_server(){
  server.on("/"           , handleRoot      );
  server.on("/tablet"     , handleRoot_Tablet      );
  server.on("/get"        , handleGet       );
  server.on("/set"        , handleSet       );
  server.on("/set3"       , handleSet3Param );
}