
// Arduino UNO <---> LCD i2C 
// A5 = SCL
// A4 = SDA
// 5V = VCC
// G = GND

// Arduino UNO <---> LDR  
// 3 = LED บวก
// A0 = LDR ขาลบ
// 5V = VCC , LDR ขาบวก
// G = GND




#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F  ,20,4);  // set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display

//int ldr = A0;  // ตัวแปร LDR ต่อขา A0
#define ldr A0
int led = 3; //  ตัวแปร LED ต่อขา 3

void setup()
{
  Serial.begin(9600); 
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("LAB5");
  lcd.setCursor(2,1);
  lcd.print("LDR");

}


void loop()
{
  
  int ldrVal = analogRead(ldr);

  Serial.println("LDR Sensor");
  Serial.println(ldrVal);

  if (ldrVal > 200) {          // ถ้าความเข้มแสงมีค่ามากกว่า 200 ให้สั่งให้ LED ปิด ต่ำกว่าให้เปิด
    digitalWrite(led,  LOW);
  } else {
    digitalWrite(led, HIGH);
  }
   
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Light Value"); 
  lcd.setCursor(7,1);
  lcd.print(ldrVal); // แสดงค่าความเข้มแสงออกจอ LCD
  
  delay(2000);

}
