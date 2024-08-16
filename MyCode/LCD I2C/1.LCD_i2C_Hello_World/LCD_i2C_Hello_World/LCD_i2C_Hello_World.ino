#include <Wire.h>                // ไลบรารี I2C
#include <LiquidCrystal_I2C.h>   // ไลบรารี LCD I2C

// กำหนดที่อยู่ I2C ของจอ LCD (เช่น 0x27 หรือ 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();                     // เริ่มต้นการทำงานของ LCD
  lcd.backlight();                // เปิดไฟแบ็คไลท์ของ LCD
  lcd.setCursor(2, 0);            // ตั้งค่าตำแหน่ง cursor ที่ตำแหน่งแรกของบรรทัดแรก
  lcd.print("Hello, World!");     // แสดงข้อความ "Hello, World!"
}

void loop() {
  // วนลูปไม่มีอะไรทำ
}

