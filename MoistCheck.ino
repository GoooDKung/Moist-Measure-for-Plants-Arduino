#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <TridentTD_LineNotify.h>

#define SSID        "_________" // wifi name
#define PASSWORD    "_________" // password for the wifi
#define LINE_TOKEN  "_________" // token line via line notify bot
String txt1 = "ความชื้น =  ";  //ข้อความ 1 ที่จะแสดงใน Line
String txt2 = “Need water!”;  //ข้อความ 2 ที่จะแสดงใน Line
String txt3 = “Humidity ok”;
String txt4 = “Moist higher than usual”;
String txt5 = “Too much water!!“;
String txt6 = "Start";
int sensorPin = 36;


void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200); 
  Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
}

void loop() {
  lcd.begin();
    
  int Humidity = analogRead(sensorPin);

  if (Humidity  >=0  && Humidity <=819 ) {
    Serial.print("Moisture Sensor Value:");
    Serial.println(Humidity);
    Serial.println("Water the plants");
     lcd.setCursor(0,0); 
     lcd.print("Moisture :");
    lcd.print(Humidity);
    lcd.setCursor(0,1);
    lcd.print("Water the plants");
    LINE.notify(txt1 + Humidity + txt2);
    delay(3000);
   }
 else if (Humidity >=820  && Humidity <=1639 ) {
    Serial.print("Moisture Sensor Value:");
    Serial.println(Humidity);
    Serial.println("Normal");
    lcd.setCursor(0,0); 
    lcd.print("Moisture :");
    lcd.print(Humidity);
    lcd.setCursor(0,1);
    lcd.print("Normal");
    LINE.notify(txt1 + Humidity + txt3);
    delay(3000);
    }else if (Humidity >=1640  && Humidity <=2459 ) {
    Serial.print("Moisture Sensor Value: ");
    Serial.println(Humidity);
    Serial.println("Humidity Over");
    lcd.setCursor(0,0); 
    lcd.print("Moisture :");
    lcd.print(Humidity);
    lcd.setCursor(0,1);
    lcd.print("Humidity Over");
     LINE.notify(txt1 + Humidity + txt4);
    delay(3000);
  } else if (Humidity >=2460 && Humidity <=4094 ) {
    Serial.print("Moisture Sensor Value:");
    Serial.println(Humidity);
    Serial.println("Dangerous");
    lcd.setCursor(0,0); 
    lcd.print("Moisture :");
    lcd.print(Humidity);
    lcd.setCursor(0,1);
    lcd.print("Dangerous");
    LINE.notify(txt1 + Humidity + txt5);
    delay(3000);
   }  else  {
    Serial.print("Moisture Sensor Value:");
    Serial.println(Humidity);
    lcd.setCursor(0,0); 
    lcd.print("Start");
    lcd.print(Humidity);
    lcd.setCursor(0,1);
    lcd.print("Start");
    LINE.notify(txt1 + Humidity + txt6);
}
}