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
float TempHighLimit = 30; // ค่าเริ่มต้น ควบคุมอุณหภูมิด้านสูงที่ 30 องศาเซลเซียส
float TempLowLimit = 25; // ค่าเริ่มต้น ควบคุมอุณหภูมิด้านต่ำที่ 25 องศาเซลเซียส

int AutoMode;
int StartButton = A1; 
int StopButton = A2;



void setup()
{
 lcd.begin(16, 2);
 lcd.setCursor(0,0); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
 lcd.print("Modela LAB14"); // ข้อความที่แสดง
 lcd.setCursor(0,1); // บรรทัดที่ 2  ( 0 แรกคือตำแหน่ง , 1 หลังคือ บรรทัดที่ 2)
 lcd.print("TEMPERATURE CONTROL:"); // ข้อความที่แสดง

pinMode(LED,OUTPUT);
pinMode(Buzzer,OUTPUT);
pinMode(StartButton,INPUT);
pinMode(StopButton,INPUT);
delay(500);
Serial.begin(115200);
Serial.println("Dallas Temperature IC Control Library");

AutoMode = 1; // โหมดอัตโนมัติให้ปั๊มน้ำทำงานตามอุณหภูมิที่กำหนดเป็นค่าเริ่มต้น
lcd.setCursor(10,0);
lcd.print("AT    "); // แสดงว่าปั๊มทำงาน
dht.begin();
}


void loop()
{

 {
  int x;
 x = analogRead (0); // อ่านสัญญาณ 
 Serial.print("X");
 Serial.print(x);
 //lcd.setCursor(10,1);
 if (x < 80) {  // ถ้า 1-79 แสดงว่ากดปุ่ม ขวา RIGHT
   TempLowLimit = TempLowLimit + 1;
 }
 else if (x < 200) { // ถ้า 80 - 199 แสดงว่ากดปุ่ม บน UP
   TempHighLimit = TempHighLimit + 1;
 }
 else if (x < 340){ // ถ้า 200 - 339 แสดงว่ากดปุ่ม ล่าง DOWN
   TempHighLimit = TempHighLimit - 1;
 }
 else if (x < 530){ // ถ้า 340 - 539 แสดงว่ากดปุ่ม ซ้าย LEFT
    TempLowLimit = TempLowLimit - 1;
 }
 else if (x < 800){ // ถ้า 530 - 799 แสดงว่่ากดปุ่ม เลือก SELECT
    AutoMode = 1; // หากมีการกดสวิตช์ที่ Select จะเป๋นการเลือกใช้โหมดอัตโนมัติให้ปั๊มน้ำทำงานตามอุณหภูมิที่กำหนด
    lcd.clear();
    lcd.setCursor(0,0); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
    lcd.print("You Select Auto Mode"); // ข้อความที่แสดง

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
 lcd.print("Now "); // ข้อความที่แสดง
 lcd.setCursor(4,0); // บรรทัดที่ 2  ( 0 แรกคือตำแหน่ง , 1 หลังคือ บรรทัดที่ 2)
 lcd.print(TempValue); // 
 lcd.setCursor(8,0); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
 lcd.print("C    "); // ข้อความที่แสดง
 lcd.setCursor(10,0);
 lcd.setCursor(0,1); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
 lcd.print("Limit"); // ข้อความที่แสดง
 lcd.setCursor(6,1); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
  lcd.print(TempLowLimit); 
 lcd.setCursor(10,1); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
lcd.print("<>");  
lcd.setCursor(12,1); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
lcd.print(TempHighLimit);  

  if (AutoMode == 1) {
    lcd.setCursor(10,0);
    lcd.print("AT    ");   
    } else {
    lcd.setCursor(10,0);
    lcd.print("MT    ");  
    }
}



// Control Temperature 
{
if ((TempValue > TempHighLimit) && (AutoMode ==1)) // ถ้าอุณหภูมิสูงกว่ามี่กำหนดและอยู่โหมดอัตโนมัติให้รีเลย์ต่อวงจร NO ให้ปั๊มทำงาน
 { 
digitalWrite(Pumppin, HIGH); // ส่ง trigger ให้รีเลย์ทำงาน
digitalWrite(Buzzer, HIGH); // ให้แจ้งเตือนอุณหภูมิ
lcd.setCursor(10,0);
lcd.print("AT ON "); // แสดงว่าปั๊มทำงาน
Serial.println("Temp Upper Status");
Serial.println(Buzzer);
  } else {
digitalWrite(Buzzer, LOW);
Serial.println("Temp Upper Status");
Serial.println(Buzzer);
  }

}

{
if (( TempValue < TempLowLimit) && (TempValue > 0) && (AutoMode ==1)) // ถ้าอุณหภูมิต่ำกว่ามี่กำหนดและอยู่โหมดอัตโนมัติให้รีเลย์ตัดวงจร NO ให้ปั๊มหยุดทำงาน
 { 
digitalWrite(Pumppin, LOW); // ส่ง trigger ให้รีเลยไม่ทำงาน
digitalWrite(LED, HIGH); // ให้ LED ตัวที่ 2 แจ้งเตือนอุณหภูมิต่ำสว่าง
lcd.setCursor(10,0);
lcd.print("AT OFF"); // แสดงว่าปั๊มหยุดทำงาน
Serial.println("Temp Lower Status");
Serial.println(LED);
  } else {
digitalWrite(LED, LOW);
Serial.println("Temp Lower Status");
Serial.println(LED);
  }

}


// Control Manual by Start/Stop Button การใช้สวิตชืหน้างานเปิดปิดปั๊ม จะเป็นการเข้าโหมดเมนวลทันที ปั๊มจะทำงานแบบไม่ขึ้นกับอุณหภูมิ
  int ManualStart = analogRead(StartButton); // อ่านค่าสวิตช์แบบ Analog
  int ManualStop = analogRead(StopButton); // อ่านค่าสวิตช์แบบ Analog

{
if (ManualStart > 800) {
digitalWrite(Pumppin, HIGH); // ส่ง trigger ให้รีเลย์ทำงาน
AutoMode = 0; // เข้าโหมดเมนวลทันที
lcd.setCursor(10,0);
lcd.print("MN ON "); // แสดงว่าปั๊มทำงาน
}
if (ManualStop > 800) {
digitalWrite(Pumppin, LOW); // ส่ง trigger ให้รีเลย์หยุดทำงาน
AutoMode = 0; // เข้าโหมดเมนวลทันที
lcd.setCursor(10,0);
lcd.print("MN OFF"); // แสดงว่าปั๊มทำงาน
}
}
delay(3000);

  }
}
