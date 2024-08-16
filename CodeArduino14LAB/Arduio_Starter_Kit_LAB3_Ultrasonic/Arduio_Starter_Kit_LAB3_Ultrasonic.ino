
// Arduino UNO <---> LCD i2C 
// A5 = SCL
// A4 = SDA
// 5V = VCC
// G = GND

//Arduino UNO <---> Ultrasonic  
// 5 = Trig
// 4 = Echo
// 5V = VCC
// G = GND

#include <LiquidCrystal_I2C.h>

#define TRIGGERPIN 5
#define ECHOPIN    4

LiquidCrystal_I2C lcd(0x3F  ,20,4);  // set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("LAB3");
  lcd.setCursor(2,1);
  lcd.print("Ultrasonic");

  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}


void loop()
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println("Cm");
  lcd.setCursor(2,1);
  lcd.print(distance);
  
  delay(3500);
}
