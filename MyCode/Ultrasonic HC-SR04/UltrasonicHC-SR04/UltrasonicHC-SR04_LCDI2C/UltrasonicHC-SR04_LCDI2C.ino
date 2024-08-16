#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

LiquidCrystal_I2C lcd(0x27, 16, 2); // กำหนดที่อยู่ I2C ของจอ LCD

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.init(); // เริ่มต้นการทำงานของจอ LCD
  lcd.backlight(); // เปิดไฟหลังจอ LCD
}

void loop() {
  // ส่งสัญญาณเสียง
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // วัดเวลาที่สัญญาณเสียงใช้ในการเดินทางไปกลับ
  duration = pulseIn(echoPin, HIGH);
  
  // คำนวณระยะทาง
  distance = duration * 0.034 / 2;
  
  // แสดงผลระยะทางบน Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // แสดงผลระยะทางบนจอ LCD
  lcd.clear();
  lcd.setCursor(0, 0); //เว้นบรรทัด
  lcd.print("Distance:");
  lcd.print(distance);
  lcd.print(" cm");
  
  // หน่วงเวลา 500 มิลลิวินาที
  delay(500);
}
