
// Arduino UNO <---> LCD i2C 
// A5 = SCL
// A4 = SDA
// 5V = VCC
// G = GND

//Arduino UNO <---> DHT11 
// 2 = Data
// 5V = VCC
// G = GND

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 // ส่งค่าเซนเซอร์ไปขา 2

#define DHTTYPE DHT11 // ประกาศว่าใช้ Library ของ DHT11

//#define DHTTYPE DHT22 // ประกาศว่าใช้ Library ของ DHT22


LiquidCrystal_I2C lcd(0x3F  ,20,4);  // set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display


DHT dht(DHTPIN, DHTTYPE);


void setup()
{
  Serial.begin(9600); 
  Serial.println("DHT1 LAB");
  dht.begin();
  
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("LAB5");
  lcd.setCursor(2,1);
  lcd.print("Temp Sensor");

}


void loop()
{
  
    float h = dht.readHumidity(); // รับค่าอุณหภูมิบันทึกในตัวแรป h
    float t = dht.readTemperature(); // รับค่าความชื้นบันทึกในตัวแปร t
    
    // สามารถดูค่าเซนเซอร์ที่วัดได้้จากเมนู Tool / Serial Monitor
    if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT"); 
      } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
            }

   
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Temp"); 
  lcd.setCursor(6,0);
  lcd.print(t); // พิมพ์ค่าอุณหภูมิออกทางจอ LCD
  lcd.setCursor(10,0);
  lcd.print("C");
  lcd.setCursor(1,1);
  lcd.print("Humidity");
  lcd.setCursor(10,1);
  lcd.print(h); // พิมพ์ค่าความชื้นออกทางจอ LCD
  lcd.setCursor(14,1);
  lcd.print("%");
  
  delay(2000);

}
