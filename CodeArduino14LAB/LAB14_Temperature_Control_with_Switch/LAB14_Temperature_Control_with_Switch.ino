#include <DHT.h>


#define DHTPIN 3 // ส่งค่าเซนเซอร์วัดอุณหภูมิไปขา 3

#define DHTTYPE DHT11 // ประกาศว่าใช้ Library ของ DHT11

//#define DHTTYPE DHT22 // ประกาศว่าใช้ Library ของ DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal.h>
//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7); // ประกาศ Charactor

int Buzzer = 12; // ต่อกับ Buzzer แจ้งเตือนอุณหภมิูสูงกว่าค่าที่กำหนด
int LED = 13; // ต่อกับ LED สำหรับแจ้งเตือนอุณหภูมิต่ำกว่าที่กำหนด
int Pumppin = 2;

float TempValue;
float TempHighLimit = 50; // ค่าเริ่มต้น ควบคุมอุณหภูมิด้านสูงที่ 50 องศาเซลเซียส
float TempLowLimit = 20; // ค่าเริ่มต้น ควบคุมอุณหภูมิด้านต่ำที่ 20 องศาเซลเซียส



void setup()
{
 lcd.begin(16, 2);
 lcd.setCursor(0,0); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
 lcd.print("Modela LAB14"); // ข้อความที่แสดง
 lcd.setCursor(0,1); // บรรทัดที่ 2  ( 0 แรกคือตำแหน่ง , 1 หลังคือ บรรทัดที่ 2)
 lcd.print("TEMPERATURE CONTROL:"); // ข้อความที่แสดง

pinMode(LED,OUTPUT);
pinMode(Buzzer,OUTPUT);
delay(500);
Serial.begin(9600);
dht.begin();

}


void loop()
{

 {
  int x;
 x = analogRead (0); // อ่านสัญญาณ 
 lcd.setCursor(10,1);
 if (x < 60) {  // ถ้า 1-59 แสดงว่ากดปุ่ม ขวา
   TempLowLimit = TempLowLimit + 1;
 }
 else if (x < 200) { // ถ้า 60 - 199 แสดงว่ากดปุ่ม บน
   TempHighLimit = TempHighLimit + 1;
 }
 else if (x < 400){ // ถ้า 200 - 399 แสดงว่ากดปุ่ม ล่าง
   TempHighLimit = TempHighLimit - 1;
 }
 else if (x < 600){ // ถ้า 400 - 599 แสดงว่ากดปุ่ม ซ้าย
    TempLowLimit = TempLowLimit - 1;
 }
 else if (x < 800){ // ถ้า 600 - 799 แสดงว่่ากดปุ่ม เลือก
 }
}


//Temp Display

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
    TempValue = t;

 lcd.clear();
 lcd.setCursor(0,0); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
 lcd.print("Now Temp"); // ข้อความที่แสดง
 lcd.setCursor(10,0); // บรรทัดที่ 2  ( 0 แรกคือตำแหน่ง , 1 หลังคือ บรรทัดที่ 2)
 lcd.print(TempValue); // 
 lcd.setCursor(15,0); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
 lcd.print("C"); // ข้อความที่แสดง

 lcd.setCursor(0,1); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
 lcd.print("Limit"); // ข้อความที่แสดง
 lcd.setCursor(6,1); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
  lcd.print(TempLowLimit); 
 lcd.setCursor(10,1); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
lcd.print("<>");  
 lcd.setCursor(12,1); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
lcd.print(TempHighLimit);  
}



// Control Temperature 
{
if (TempValue > TempHighLimit)  // ถ้าอุณหภูมิสูงกว่ามี่กำหนดให้รีเลย์ต่อวงจร NO ให้ปั๊มทำงาน
 { 
digitalWrite(Pumppin, HIGH); // ส่ง trigger ให้รีเลย์ทำงาน
digitalWrite(Buzzer, HIGH); // ให้ LED ตัวที่ 1 แจ้งเตือนอุณหภูมิสูงสว่าง
Serial.println("Temp Upper Status");
Serial.println(Buzzer);
  } else {
digitalWrite(Buzzer, LOW);
Serial.println("Temp Upper Status");
Serial.println(Buzzer);
  }

}

{
if (TempValue < TempHighLimit)  // ถ้าอุณหภูมิต่ำกว่ามี่กำหนดให้รีเลย์ตัดวงจร NO ให้ปั๊มหยุดทำงาน
 { 
digitalWrite(Pumppin, LOW); // ส่ง trigger ให้รีเลยไม่ทำงาน
digitalWrite(LED, HIGH); // ให้ LED ตัวที่ 2 แจ้งเตือนอุณหภูมิต่ำสว่าง
Serial.println("Temp Lower Status");
Serial.println(LED);
  } else {
digitalWrite(LED, LOW);
Serial.println("Temp Lower Status");
Serial.println(LED);
   }

  }

delay(500);

 }
}
