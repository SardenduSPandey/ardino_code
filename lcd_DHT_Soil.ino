#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include<DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN , DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  pinMode(13,INPUT);
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Hello");
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
float val = analogRead(0);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Soil Moisture");
lcd.setCursor(0,1);
lcd.print(val);
delay(1000);

float val1 = dht.readHumidity();
float val2 = dht.readTemperature();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TEMP :");
lcd.setCursor(0,1);
lcd.print(val2);
delay(1000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Humidity:");
lcd.setCursor(0,1);
lcd.print(val1);
delay(1000);


}
