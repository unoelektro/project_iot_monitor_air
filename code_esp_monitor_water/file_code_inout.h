//------------ Kode Sensor Water Flow - start -------------//

//
void IRAM_ATTR pulseCounter() {
  pulseCount++;  // Interupsi yang menghitung setiap pulsa dari sensor
}

//
void inisial_flowmeter(){
  pinMode(pin_sensor, INPUT);   // Atur pin flow meter sebagai input
  attachInterrupt(digitalPinToInterrupt(pin_sensor), pulseCounter, FALLING);
}


void baca_sensor_flowmeter(){

    unsigned long currentTime = millis();
    if(currentTime - oldTime >= 1000) {
      //
      detachInterrupt(digitalPinToInterrupt(pin_sensor));  // Hentikan interupsi sementara

      // Hitung laju aliran air dalam liter per menit (LPM)
      flowRate = ((1000.0 / (currentTime - oldTime)) * pulseCount) / calibrationFactor;

      // Hitung total volume air yang mengalir (dalam liter)
      float flowLiters   = (pulseCount / calibrationFactor) / 60.0  ;  // Volume dalam liter per detik
      totalLiters       += flowLiters                               ;  // Tambahkan ke total volume

      //
      pulseCount  = 0             ;        // Reset hitungan pulsa
      oldTime     = currentTime   ;        // Simpan waktu saat ini
      attachInterrupt(digitalPinToInterrupt(pin_sensor), pulseCounter, FALLING);
    }


}


unsigned long display_tmShow = millis();
void show_data_flowmeter() {
  if( (millis()-display_tmShow) > 2000 ){
    Serial.println();
    Serial.println("-------> ");

    Serial.print(F("Pulsa = "));
    Serial.print(pulseCount, DEC);
    Serial.println("");
    
    Serial.print(F("Aliran Air  = "));
    Serial.print(flowRate, 2);
    Serial.println(" LPM");

    Serial.print(F("Total Volume = "));
    Serial.print(totalLiters, 2);
    Serial.println(" Liter");

    display_tmShow = millis();
  }
}
//------------ Kode Sensor Water Flow- end -------------//




//-------| Code Sensor DS18B20 - Start - |--------//

// function to print a device address
void printAddress(DeviceAddress list_deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (list_deviceAddress[i] < 16) Serial.print("0");
    Serial.print(list_deviceAddress[i], HEX);
  }
}

void inisial_ds18b20()
{
  // locate devices on the bus
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  if (!sensors.getAddress(deviceAddress_ds18b20, 0)){
    isSensorDeteksi = false ;
    view_oled_loading_sensor(stat_status_loading_error);
    Serial.println("Unable to find address for Device 0");
    delay(3000);
  }

  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(deviceAddress_ds18b20);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(deviceAddress_ds18b20, 9);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress_ds18b20), DEC);
  Serial.println();
}




void baca_sensor_ds18b20(){
  sensors.requestTemperatures(); 
  temp_celcius     = sensors.getTempC(deviceAddress_ds18b20);
  temp_fahrenhite  = sensors.getTempF(deviceAddress_ds18b20);
}


void show_data_bmp280() {
  Serial.println();
  Serial.println("-------> ");
  
  Serial.print(F("Temperature = "));
  Serial.print(temp_celcius, 2);
  Serial.println(" *C");

  Serial.print(F("Temperature = "));
  Serial.print(temp_fahrenhite, 2);
  Serial.println(" *F");
}

//-------| Code Sensor DS18B20 - End - |--------//

unsigned long tmView = millis();

// Contoh fungsi baca sensor
void readSensor() {

  // Code Proses Sensor.
  baca_sensor_flowmeter();
  if( isSensorDeteksi == true ){
    baca_sensor_ds18b20();
  }

  if( (millis()-tmView) > 3000 ){
    // Code View Sensor.
    show_data_flowmeter();
    show_data_bmp280();
    tmView = millis();
  }

  // Informasi Sensor.
  if( flowRate < 0.2 )
    stat_sensor = "Air Berhenti." ;
  else if( flowRate < 10 )
    stat_sensor = "Debit air rendah." ;
  else if( flowRate < 20 )
    stat_sensor = "Debit air normal." ;
  else
    stat_sensor = "Debit air tinggi!" ;
}


// Fungsi setup data awal.
void initInOutDeviceExt(){
  // Code Inisial Sensor.
  view_oled_loading_sensor(stat_status_loading_start);
  inisial_flowmeter();
  inisial_ds18b20();
  view_oled_loading_sensor(stat_status_loading_success);
}

// Fungsi Endpoint
String generateDataEndPoint(){
  return String(flowRate,2) + "x" + String(temp_celcius,2) + "x" + String(totalLiters,2)  + "x" + stat_sensor + "x#" ;
}