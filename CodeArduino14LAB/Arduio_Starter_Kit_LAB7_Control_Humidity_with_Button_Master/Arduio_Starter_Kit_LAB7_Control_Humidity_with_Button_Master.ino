 /*
 * โคดแบบ 2 ระบบควบคุมรีเลย์
 * 1. Auto ควบคุมรีเลย์ได้ทั้งกำหนดค่าอุณหภูมิและความชื้น
 * 2. Manual โดยการกดสวิตช์
 * หากไม่ต้องการควบคุมแบบใด ให้ทำการใส่ // หน้าโค้ดที่ไม่ต้องการ
 */



// Arduino UNO <---> LCD i2C 
// A5 = SCL
// A4 = SDA
// 5V = VCC
// G = GND

// Arduino UNO <---> Relay & Switch
// 12 = INT
// 5V = VCC , Switch Button
// G = GND 

//Arduino UNO <---> DHT11 
// 2 = Data
// 5V = VCC
// G = GND

// Arduino UNO <---> Switch Button
// 3 = Switch 1
// 4 = Switch 2
// 5 = Switch 3
// 6 = Switch 4
// 5V = All Switch 


#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 // ส่งค่าเซนเซอร์ไปขา 2

#define DHTTYPE DHT11 // ประกาศว่าใช้ Library ของ DHT11

//#define DHTTYPE DHT22 // ประกาศว่าใช้ Library ของ DHT22

LiquidCrystal_I2C lcd(0x3F  ,20,4);  // set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display

DHT dht(DHTPIN, DHTTYPE);

int button = A1; // ตัวแปรสถานะการกดสวิตช์ ต่อขา A1
int relay = 12;  //  ตัวแปร LED ต่อขา 12
int ledstatus;   // ตัวแปรสถานะ LED
int buttonpin1 = 3;
int buttonpin2 = 4;
int buttonpin3 = 5;
int buttonpin4 = 6;
int highhumidity;
int lowhumidity;


void setup()
{
  Serial.begin(9600); 
  Serial.println("LAB 7");
  dht.begin();
  
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("LAB7");
  lcd.setCursor(2,1);
  lcd.print("Control by Temp");
  pinMode(relay, OUTPUT);
  pinMode(buttonpin1, INPUT);
  pinMode(buttonpin2, INPUT);
  pinMode(buttonpin3, INPUT);
  pinMode(buttonpin4, INPUT);

  highhumidity = 40;
  lowhumidity = 38 ;
  ledstatus = 0;
  

}


void loop()
{

    //  โค้ดจาก LAB DHT11
    float h = dht.readHumidity(); // รับค่าอุณหภูมิบันทึกในตัวแรป h
    float t = dht.readTemperature(); // รับค่าความชื้นบันทึกในตัวแปร t
    
    // สามารถดูค่าเซนเซอร์ที่วัดได้้จากเมนู Tool / Serial Monitor
    if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT"); 
      } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
            }

  

 // โค้ดสำหรับสั่งให้ Relay ทำงานตามอุณหภูมิที่กำหนด
  if (h > highhumidity){  // ตั้งค่าอุณหภูมิที่ต้องการให้รีเลย์ต่อวงจรต้องเกินอุณหภูมิเท่าไหร่
     digitalWrite(relay, HIGH); // สั่งรีเลย์ต่อวงจรให้ LED เปิด
     ledstatus = 1;// ตัวแปรสถานะ LED บันทึกว่า led ติดอยู่
     Serial.println("High Humidity");
     Serial.println(h);
// . lcd.clear();
 //  lcd.setCursor(1,0);
 //  lcd.print("Temp Over"); 
     lcd.setCursor(0,1);
     lcd.print("Hum High:PumpON"); 
     delay(1000);   
    }
  

    if (h < lowhumidity){ // ตั้งค่าอุณหภูมิที่ต้องการให้รีเลย์ตัดวงจร ต้องต่ำกว่าเท่าไหร่
     digitalWrite(relay, LOW); // สั่งรีเลย์ต่อวงจรให้ LED ปิด
     ledstatus = 0;// ตัวแปรสถานะ LED บันทึกว่า led ดับอยู่
     Serial.println("Low Humidity");
     Serial.println(h);
    // lcd.clear();
    // lcd.setCursor(1,0);
   //  lcd.print("Temp Low"); 
     lcd.setCursor(0,1);
     lcd.print("Hum Low:PumpOff"); 
     delay(1000);   
    }

 
// โค้ดจาก LAB Relay */
  int button1 = digitalRead(buttonpin1);
  int button2 = digitalRead(buttonpin2);
  int button3 = digitalRead(buttonpin3);
  int button4 = digitalRead(buttonpin4);

  Serial.println("Button1");
  Serial.println(button1);
  Serial.println("Button2");
  Serial.println(button2);
  Serial.println("Button3");
  Serial.println(button3);
  Serial.println("Button4");
  Serial.println(button4);

 // หากมีการกดสวิทช์ button 
  if (button1==1){  // กดสวิทช์ button 1 จะเพิ่มค่สควบคุมอุณหภูมิฝั่งด้านสูง
     highhumidity = highhumidity+1;
     Serial.println("High Temp");
     Serial.println(highhumidity);
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print("ON"); 
     lcd.setCursor(3,0);
     lcd.print(highhumidity); 
     lcd.setCursor(5,0);
     lcd.print("C"); 
     lcd.setCursor(6,0);
     lcd.print("<->"); 
     lcd.setCursor(9,0);
     lcd.print(lowhumidity);
     lcd.setCursor(11,0);
     lcd.print("C");  
     lcd.setCursor(13,0);
     lcd.print("OFF"); 
     delay(500);   
      } 
// กดสวิทช์ button 1 จะเพิ่มค่สควบคุมอุณหภูมิฝั่งด้านสูง และด้านสูงต้องมีค่ามากกว่าด้านต่ำ
      if ((button2== 1) && (highhumidity > lowhumidity)){  
     highhumidity = highhumidity-1;
     Serial.println("High Temp");
     Serial.println(highhumidity);
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print("ON"); 
     lcd.setCursor(3,0);
     lcd.print(highhumidity); 
     lcd.setCursor(5,0);
     lcd.print("C"); 
     lcd.setCursor(6,0);
     lcd.print("<->"); 
     lcd.setCursor(9,0);
     lcd.print(lowhumidity);
     lcd.setCursor(11,0);
     lcd.print("C");  
     lcd.setCursor(13,0);
     lcd.print("OFF"); 
     delay(500);   
      } 

// กดสวิทช์ button 3 จะเพิ่มค่าควบคุมอุณหภูมิฝั่งด้านต่ำ ่และด้านต่ำต้องไม่มีค่ามากกว่าด้านสูง
      if ((button3== 1) && (lowhumidity < highhumidity)){  
     lowhumidity = lowhumidity+1;
     Serial.println("High Humidity");
     Serial.println(highhumidity);
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print("ON"); 
     lcd.setCursor(3,0);
     lcd.print(highhumidity); 
     lcd.setCursor(5,0);
     lcd.print("%"); 
     lcd.setCursor(6,0);
     lcd.print("<->"); 
     lcd.setCursor(9,0);
     lcd.print(lowhumidity);
     lcd.setCursor(11,0);
     lcd.print("%");  
     lcd.setCursor(13,0);
     lcd.print("OFF"); 
     delay(500);   
      } 

      if ((button4== 1)){  // กดสวิทช์ button 1 จะเพิ่มค่สควบคุมอุณหภูมิฝั่งด้านต่ำ
     lowhumidity = lowhumidity-1;
     Serial.println("High Temp");
     Serial.println(highhumidity);
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print("ON"); 
     lcd.setCursor(3,0);
     lcd.print(highhumidity); 
     lcd.setCursor(5,0);
     lcd.print("%"); 
     lcd.setCursor(6,0);
     lcd.print("<->"); 
     lcd.setCursor(9,0);
     lcd.print(lowhumidity);
     lcd.setCursor(11,0);
     lcd.print("%");  
     lcd.setCursor(13,0);
     lcd.print("OFF"); 
     delay(500);   
      } 
    
   //  lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Now Temp"); 
     lcd.setCursor(9,1);
     lcd.print(t); 
     lcd.setCursor(11,1);
     lcd.print("C:"); 
     lcd.setCursor(13,1);
     lcd.print("H"); 
     lcd.setCursor(14,1);
     lcd.print(h); 
     lcd.setCursor(16,1);
     lcd.print("%"); 
     delay(1000);
     
     
}
