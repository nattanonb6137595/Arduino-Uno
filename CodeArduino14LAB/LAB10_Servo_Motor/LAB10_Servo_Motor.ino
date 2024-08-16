//Arduino UNO <---> LCD i2C 
// A5 = SCL
// A4 = SDA
// 5V = VCC
// G = GND

// Arduino UNO <---> Servo motor
// 5V = VCC
// G = GND
// ขา 9 = OUT

// Arduino UNO <---> Adjustable Resistance
// 5V = ขา 3
// G = ขา 1
// A3 = ขา 2 (กลาง)

#include  <Servo.h>
Servo myservo;         // create servo object to control a servo 
int degree;  
int controlpin = A3;        // Pin to potentiometer
int value;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F  ,20,4);  // set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display

void setup() 
{ 
  Serial.begin(9600);
  delay(500);
  myservo.attach(9);  // ต่อขา 9 Arduino เข้ากับ Servo motor สายสีส้ม

  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("LAB10");
  lcd.setCursor(2,1);
  lcd.print("Servo Motor");
  
  delay(3000);
} 
  
void loop() 
{  
   value = analogRead(controlpin); 
   degree = analogRead(controlpin);         // define analog read pin
   degree = map(degree, 0, 1023, 0, 180);  // scaling input to 0 - 180 degree
   Serial.println("Analog Value");
   Serial.println(value);
   Serial.println("Servo Degree");
   Serial.println(degree);
   Serial.println("...");
   myservo.write(degree);               // position of servo arm

   lcd.clear();
   lcd.setCursor(1,0);
   lcd.print("Value"); 
   lcd.setCursor(7,0);
   lcd.print(value); 
   lcd.setCursor(1,1);
   lcd.print("Degree"); 
   lcd.setCursor(8,1);
   lcd.print(degree); 

   delay(500);                        // adjust for selecting movement speed
}
