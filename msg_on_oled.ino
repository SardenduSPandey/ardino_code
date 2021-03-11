#include <WiFi.h>
#include <Wire.h> 
#include "SSD1306Wire.h"

#define WIFI_SSID "iot"
#define WIFI_PASSWORD "12345678"

SSD1306Wire  display(0x3c, 21, 22);
void setup() {
  Serial.begin(9600);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "IOT BASED");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 16, "CROP");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "MONITORING");
  display.display();
  delay(5000);
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Connecting");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 16, "to ");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "Internet");
  display.display();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
    display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Connected");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 16, "Success. ");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "========");
  display.display();

  
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "PLEASE WAIT...");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, "SENSORS");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "INITIALIZING...");
  display.display();
  delay(5000);

}

void loop() {
  int h = 20;
  int t = 30;
  int d = 1;

  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "TEMPERATURE");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, String(t));
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "Celcius");
  display.display();
  delay(1000);
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "HUMIDITY");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, String(h));
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "%");
  display.display();
  delay(1000);
  
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Door");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, String(d));
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "Status");
  display.display();
  delay(1000);
}
