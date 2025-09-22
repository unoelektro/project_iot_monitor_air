
 
String name_user = "=== unobengkel ===" ;
String Ip        = "178.15.1.5"         ;
String SSID      = "ESP8266"            ;

void blank_view(){
    set_text_oled_holdon(
      name_user,"","","",
      delay_each_loading
    );
}



void view_oled_loading_sensor( int status ){
  if( status == stat_status_loading_start ){
    set_text_oled_holdon(
      name_user ,
      "Loading sensor..." ,
      "Please wait a moment.",
      "" ,
      delay_each_loading
    );
  }
  else if( status == stat_status_loading_success ){
    set_text_oled_holdon(
      name_user ,
      "Loading sensor..." ,
      "Scanning..Done",
      "Success"  ,
      delay_each_loading
    );
  }
  else if( status == stat_status_loading_error ){
    set_text_oled_holdon(
      name_user ,
      "Loading sensor..." ,
      "Scanning..Done",
      "Error" ,
      delay_each_loading
    );
  }
}









// Fungsi untuk menampilkan status pemindaian WiFi di OLED
void view_oled_wifi_scan(int status, String ssid_name) {
  if (status == stat_status_loading_start) {
    set_text_oled_holdon(
      name_user,
      "Scanning for",
      "WiFi networks...",
      "SSID: " + ssid_name ,
      delay_each_loading
    );
  } else if (status == stat_status_loading_process) {
    set_text_oled_holdon(
      name_user,
      "Scanning Wifi...",
      "Please wait.",
      "",
      delay_each_loading
    );
  } else if (status == stat_status_loading_success) {
    set_text_oled_holdon(
      name_user,
      "Scan complete.",
      "Network found!",
      "SSID: " + ssid_name, // Menampilkan nama SSID yang ditemukan
      delay_each_loading
    );
  } else if (status == stat_status_loading_error) {
    set_text_oled_holdon(
      name_user,
      "Scan failed.",
      "No networks found.",
      "Please check ....",
      delay_each_loading
    );
  }
}




// Fungsi untuk menampilkan status koneksi WiFi di OLED
void view_oled_wifi_connect(int status, String ssid_name, String timer, String Ip) {
  if (status == stat_status_loading_start) {
    set_text_oled_holdon(
      name_user,
      "Connecting to",
      ssid_name,
      "",
      delay_each_loading
    );
  } else if (status == stat_status_loading_process) {
    set_text_oled_realtime(
      name_user,
      "Connecting...",
      "Please wait.",
      "Time : " + timer,
      600
    );
  } else if (status == stat_status_loading_success) {
    set_text_oled_holdon(
      name_user,
      "Connected!",
      "IP Address:",
      Ip, // Ganti dengan IP Address yang sebenarnya
      delay_each_loading
    );
  } else if (status == stat_status_loading_error) {
    set_text_oled_holdon(
      name_user,
      "Connection failed!",
      "Check password & -.",
      "network",
      delay_each_loading
    );
  }
}







// Fungsi untuk menampilkan status server di OLED
void view_oled_server_status(int status, String server_ip) {
  if (status == stat_status_loading_start) {
    set_text_oled_holdon(
      name_user,
      "Starting server...",
      "",
      "",
      delay_each_loading
    );
  } else if (status == stat_status_loading_process) {
    set_text_oled_holdon(
      name_user,
      "Initializing...",
      "Please wait.",
      "",
      delay_each_loading
    );
  } else if (status == stat_status_loading_success) {
    set_text_oled_holdon(
      name_user,
      "Server started!",
      "IP Address:",
      server_ip, // Menampilkan alamat IP server
      delay_each_loading
    );
  } else if (status == stat_status_loading_error) {
    set_text_oled_holdon(
      name_user,
      "Server failed!",
      "Check network & -.",
      "Wifi Terminal",
      delay_each_loading
    );
  }
}