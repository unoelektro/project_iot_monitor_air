// Panggil library akses OLED.
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Parameter ukuran OLED.
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

// Parameter setting I2C Oled.
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 

// Parameter baris OLED.
const byte row_oled_1 = 0 ;
const byte row_oled_2 = 17 ;
const byte row_oled_3 = 32 ;
const byte row_oled_4 = 47 ;

// Parameter Timer Untuk OLED Realtime.
unsigned long tm_oled_changes_display = millis();

// Inisial Objeck OLED.
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Fungsi inisial OLED.
void inisial_oled(){

  // Inisial Pin I2C.
  Wire.begin(D2,D1);

  // Periksa ketersediaan OLED.
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}


// Fungsi setting font oled 
void set_font_oled(){
  display.setTextSize(1);    
  display.setTextColor(WHITE);
}

int number_row_to_row_pixel( int number_row ){
  if( number_row == 1 ) return  row_oled_1 ;
  else if( number_row == 2 ) return  row_oled_2 ;
  else if( number_row == 3 ) return  row_oled_3 ;
  else return  row_oled_4 ;
}

// Fungsi untuk menampilkan text pada oled.
void set_text_oled( int column, int no_row , String value ){
  display.setCursor( column, number_row_to_row_pixel( no_row ));
  display.println(value);
}

// Fungsi untuk menampilkan text di OLED.
void set_text_oled_holdon( String val_1, String val_2, String val_3, String val_4, int time ){
  // Kode untuk menghapus tampilan layar oled. sebelum di isi ulang.
  display.clearDisplay();
  // Set font text oled.
  set_font_oled();
  // Tampilkan text Oled sesuai dengan baris.
  set_text_oled( 0, 1, val_1 );
  set_text_oled( 0, 2, val_2 );
  set_text_oled( 0, 3, val_3 );
  set_text_oled( 0, 4, val_4 );
  display.display();
  // Delay Tampilan, Sesuai dengan parameter 'time'
  delay( time );
}

// Fungsi untuk menampilkan text realtime.
void set_text_oled_realtime( String val_1, String val_2, String val_3, String val_4, int time ){
  // Kode timer update display oled.
  if( (millis()-tm_oled_changes_display) > time ){
    // Update tampilan oled.
    set_text_oled_holdon( val_1, val_2, val_3, val_4, 5 );
    // Reset Timer.
    tm_oled_changes_display = millis();
  }
}