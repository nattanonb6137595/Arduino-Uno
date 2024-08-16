
// Arduino UNO <--> LCD Keypad Shield
// D4 = 4
// D5 = 5
// D6 = 6
// D7 = 7
// D8 = 8
// D9 = 9
// 10 = 10
// Vin = Cin
// 5V = 5V
// GND = GND
// A0 = A0
// RST = RST




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

void setup() {
 lcd.begin(16, 2);
 lcd.setCursor(0,0); // บรรทัดที่ 1  ( 0 แรกคือตำแหน่ง , 0 หลังคือ บรรทัดที่ 1)
 lcd.print("Modela LAB 13"); // ข้อความที่แสดง
 lcd.setCursor(0,1); // บรรทัดที่ 2  ( 0 แรกคือตำแหน่ง , 1 หลังคือ บรรทัดที่ 2)
 lcd.print("Press Key:"); // ข้อความที่แสดง
}

void loop() {
 int x;
 x = analogRead (0); // อ่านสัญญาณ 
 lcd.setCursor(10,1);
 if (x < 60) {  // ถ้า 1-59 แสดงว่ากดปุ่ม ขวา
   lcd.print ("Right "); 
 }
 else if (x < 200) { // ถ้า 60 - 199 แสดงว่ากดปุ่ม บน
   lcd.print ("Up    ");
 }
 else if (x < 400){ // ถ้า 200 - 399 แสดงว่ากดปุ่ม ล่าง
   lcd.print ("Down  ");
 }
 else if (x < 600){ // ถ้า 400 - 599 แสดงว่ากดปุ่ม ซ้าย
   lcd.print ("Left  ");
 }
 else if (x < 800){ // ถ้า 600 - 799 แสดงว่่ากดปุ่ม เลือก
   lcd.print ("Select");
 }
} 
