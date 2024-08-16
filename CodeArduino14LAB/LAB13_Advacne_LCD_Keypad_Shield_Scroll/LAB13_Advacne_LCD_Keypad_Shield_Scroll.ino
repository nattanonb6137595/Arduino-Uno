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
const int RS = 8;
const int EN = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int pin_BL = 10; // arduino pin wired to LCD backlight circuit
LiquidCrystal lcd( RS,  EN,  d4,  d5,  d6,  d7);
void setup() {
 lcd.begin(16, 2);
 lcd.print("LAB13");
 delay(1000);
}
void loop() {
 // scroll 11 positions ("Express Bus to Rayong" length) to the left
 for (int positionCounter = 0; positionCounter < 11; positionCounter++) {
   lcd.scrollDisplayLeft();
   delay(400);  //Scrolling speed
 }
 // scroll 27 positions ("Express Bus to Rayong" length + display length) to the right
 for (int positionCounter = 0; positionCounter < 27; positionCounter++) {
   lcd.scrollDisplayRight();
   delay(400);
 }
 // scroll 16 positions (display length) to the left
 for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
   lcd.scrollDisplayLeft();
   delay(50);
 }
 delay(1000);
} 
