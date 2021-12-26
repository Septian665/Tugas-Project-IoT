#define BLYNK_PRINT Serial 
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#include "TRIGGER_WIFI.h"
#include "TRIGGER_GOOGLESHEETS.h" 

char auth[] = "UyrLonxoFOSaXpmzlGvZCKVmVsh06v-N"; 
//sensor suhu = UyrLonxoFOSaXpmzlGvZCKVmVsh06v-N

char ssid[] = "Wifi.Id_plus";
char pass[] = "septian21";

#define DHTPIN 2          // Digital pin 4
#define DHTTYPE DHT11     // DHT 11

char column_name_in_sheets[ ][20] = {"value1","value2"};
String Sheets_GAS_ID = "AKfycbzz1tpv-GEjW0t2PDUMcAp3BZNSHAZESpKL9bfpx4WqjiiaCjgoPqlIUNH_tkd4CDs";
int No_of_Parameters = 2;

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters );

  // Setup a function to be called every second
  //timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature

  Data_to_Sheets(No_of_Parameters,  t,  h);

  delay(10000);
  timer.run();
}
//tuh cuman tinggal masukin library sama kode auth yang diperluin
//terus masukin di void loop yang buat kirim nya
