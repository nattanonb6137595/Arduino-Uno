
// Arduino UNO <---> LCD i2C 
// A5 = SCL
// A4 = SDA
// 5V = VCC
// G = GND

// Arduino UNO <---> Relay & Switch
// 12 = INT
// A1 = Switch Button
// 5V = VCC , Switch Button
// G = GND 



#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F  ,20,4);  // set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display

int button = A1; // ตัวแปรสถานะการกดสวิตช์ ต่อขา A1
int relay = 12;  //  ตัวแปร LED ต่อขา 12
int ledstatus;   // ตัวแปรสถานะ LED

void setup()
{
  Serial.begin(9600); 
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
  ledstatus = 0;
  
  
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("LAB6");
  lcd.setCursor(2,1);
  lcd.print("Relay");

}


void loop()
{
  
  int buttonpin = analogRead(button);

  Serial.println("Button Status");
  Serial.println(buttonpin);

 // หากมีการกดสวิทช์ button และ LED ดับอยู่ ให้รีเลย์ต่อวงจรให้ LED ติด
  if ((buttonpin > 1000) && (ledstatus == 0)){  // กดสวิทช์ button จะวัดค่าสัญญาณ Analog ได้มากกว่า 1000 
     digitalWrite(relay, HIGH); // สั่งรีเลย์ต่อวงจรให้ LED เปิด
     ledstatus = 1;// ตัวแปรสถานะ LED บันทึกว่า led ติดอยู่
      buttonpin = 0;
     Serial.println("Button Status 0");
     Serial.println(buttonpin);
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print("Turn-On LED"); 
     delay(2000);   
      } 
  // หากมีการกดสวิทช์ button และ LED ติดอยู่ สั่งรีเลย์ตัดวงจรให้ LED ดับ
   if ((buttonpin > 1000) && (ledstatus == 1)){  
     digitalWrite(relay, LOW); // สั่งรีเลย์ตัดวงจรให้ LED ดับ
     ledstatus = 0;// ตัวแปรบันทึกว่า led ดับอยู่
     buttonpin = 0;
     Serial.println("Button Status 1");
     Serial.println(buttonpin);
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print("Turn-Off LED"); 
     delay(2000);   
      }   

}
