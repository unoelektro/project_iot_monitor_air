//
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ElegantOTA.h>
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Parameter setting wifi.
#define WIFI_SSID       "sakha"
#define WIFI_PASSWORD   "prime468328"

// Buat objek server di port 80
ESP8266WebServer server(80);

// Parameter Ukuran dan Alamat LCD.
const byte n_rows_lcd   = 16    ;
const byte n_cols_lcd   = 2     ;
const byte address_lcd  = 0x27  ;

// Variabel Status.
String stat_wifi    = "" ;
String stat_sensor  = "" ;

// Variabel Timer Koneksi Client Web.
unsigned long lastAccessTime  = 0     ;   // menyimpan waktu terakhir akses (ms)
unsigned long timerDuration   = 8000  ;   // contoh durasi 30 detik


// Variabel timer pengambilan sensor.
unsigned long sensorReadTimer = 0;    // menyimpan waktu terakhir baca sensor
const unsigned long sensorInterval = 50;  // interval 5 detik (5000 ms)

// file code display.
void inisial_oled();
void set_text_oled_holdon( String val_1, String val_2, String val_3, String val_4, int time );
void set_text_oled_realtime( String val_1, String val_2, String val_3, String val_4, int time );

void view_oled_loading_sensor( int status );
void view_oled_wifi_scan(int status, String ssid_name);
void view_oled_wifi_connect(int status, String ssid_name, String timer, String Ip);
void view_oled_server_status(int status, String server_ip) ;

// File Code Input Output.
String generateDataEndPoint();

// Parameter Status OLED.
int stat_status_loading_start     = 0 ;
int stat_status_loading_process   = 1 ;
int stat_status_loading_success   = 2 ;
int stat_status_loading_error     = 3 ;

int delay_each_loading          = 2000 ;



//-------| Code Sensor Water Flow Meter - Start - |--------//

// Parameter komponen sensor.
const byte pin_sensor     = D6 ;


//~>
volatile int  pulseCount    = 0   ;  // Variabel untuk menghitung jumlah pulsa
unsigned long oldTime       = 0   ;  // Variabel untuk mencatat waktu sebelumnya
float         flowRate      = 0   ;  // Laju aliran air dalam liter per menit (LPM)
float         totalLiters   = 0   ;  // Total volume air dalam liter

//~>
const float calibrationFactor = 4.5; 

//-------| Code Sensor Water Flow Meter - End - |--------//




//-------| Code Sensor DS18B20 - Start - |--------//

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS D5

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress deviceAddress_ds18b20;

// Parameter Sensor DS18b20.
float temp_celcius      = 0.0 ;
float temp_fahrenhite   = 0.0 ;

// Parameter Apakah Sensor Terdeteksi.
bool isSensorDeteksi = true ;

//-------| Code Sensor DS18B20 - End - |--------//