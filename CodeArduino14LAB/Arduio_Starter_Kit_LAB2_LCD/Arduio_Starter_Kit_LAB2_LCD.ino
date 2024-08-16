#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ตั้งค่าที่อยู่ของจอ LCD (0x27 หรือ 0x3F ขึ้นอยู่กับจอที่ใช้)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // สำหรับจอ LCD ขนาด 16x2

void setup() {
  // เริ่มต้นการทำงานของจอ LCD
  lcd.init();
  
  // เปิดไฟแบคไลท์
  lcd.backlight();
  
  // แสดงข้อความบนจอ
  lcd.setCursor(0, 0);  // ตั้งตำแหน่งเคอร์เซอร์ (คอลัมน์, แถว)
  lcd.print("Hello, world!      Hello, world!");
  
  lcd.setCursor(0, 1);  // ตั้งเคอร์เซอร์ที่แถวล่าง
  lcd.print("I2C LCD Display    I2C LCD Display");
}

void loop() {
  lcd.scrollDisplayLeft(); // เลื่อนข้อความไปทางซ้าย
  delay(500);
}
