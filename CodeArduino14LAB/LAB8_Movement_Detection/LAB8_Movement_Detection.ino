//Arduino UNO <---> LCD i2C 
// A5 = SCL
// A4 = SDA
// 5V = VCC
// G = GND

// Arduino UNO <---> PIR Sensor
// 5V = VCC
// G = GND
// A0 = OUT

// Arduino UNO <---> Switch Button
// A2 = Switch
// 5V = Switch ด้านเยื้อง

// Arduino UNO <---> Buzzer
// 12 = ขา +
// G = -

#define Sensorpin A0   
#define Alarmpin 12      

int Button = A2;
int  Buttonstatus;
int Sensorvalue;
int Alarmstatus;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F  ,20,4);  // set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display



void setup() {
 Serial.begin(115200);
pinMode(Sensorpin, INPUT);
pinMode(Alarmpin, OUTPUT);
pinMode(Button, INPUT);

  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("LAB8");
  lcd.setCursor(1,1);
  lcd.print("Movement Detect");
}


void loop() {
Sensorvalue = analogRead(Sensorpin); // อ่านค่าอะนาลอกจากเซนเซอร์
Buttonstatus = analogRead(Button);
Serial.println("Sensor Value");
Serial.println(Sensorvalue);
delay(100) ;
  
if (Sensorvalue > 500)  { // ค่ามากกว่า 500 แสดงว่ามีการเคลื่อนไหวเกิดขึ้น
Alarmstatus = 1;
digitalWrite(Alarmpin, HIGH);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("Warning!!!"); 
lcd.setCursor(0,1);
lcd.print("Detect Movement"); 
delay(1000) ;
  } else {
Alarmstatus = 0;   
  }

  
if (Buttonstatus > 1000) { // กดสวิตช์ปิดเสียงเตือน
digitalWrite(Alarmpin, LOW);
Serial.println("Button Status");
Serial.println(Buttonstatus);
Buttonstatus = 0;
Alarmstatus = 0;
lcd.clear();
lcd.setCursor(1,0);
lcd.print("Acknowledge"); // ข้อความรับทราบเสียงเตือนแล้ว
delay(5000) ; // หน่วงการตรวจสอบ 5 วินาที
   }


}
