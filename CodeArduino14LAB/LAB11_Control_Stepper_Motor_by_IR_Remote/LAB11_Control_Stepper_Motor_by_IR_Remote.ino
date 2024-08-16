#include <IRremote.h>
int RECV_PIN = 7;

int motorPin1 = 8;// Blue   - 28BYJ48 pin 1
int motorPin2 = 9;// Pink   - 28BYJ48 pin 2
int motorPin3 = 10;// Yellow - 28BYJ48 pin 3
int motorPin4 = 11;// Orange - 28BYJ48 pin 4
int motorSpeed = 10;     //variable to set stepper speed

char val = '0';

  #define buttonLeft 16734885 // แก้ค่าปุ่มกดที่ 1 ตามรีโมตที่ใช้ // ปุ่มสั่งไว้หมุนวนซ้าย
  #define buttonRight 16716015 // แก้ค่าปุ่มกดที่ 2 ตามรีโมตที่ใช // ปุ่มสั่งหมุนวนขวา
  #define buttonUp 16718055 // แก้ค่าปุ่มกดที่ 3 ตามรีโมตที่ใช้ // ปุ่มเพิ่มความเร็ว
  #define buttonDown 16730805 // แก้ค่าปุ่มกดที่ 4 ตามรีโมตที่ใช้ // ปุ่มลดความเร็ว  

  IRrecv irrecv(RECV_PIN);
  decode_results results; 
 
  
void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  irrecv.enableIRIn(); // Start the receiverirrecv.enableIRIn();
  
  Serial.begin(9600);
}
void loop() {
  
  if (Serial.available() > 0)
  {
    val = Serial.read();
    Serial.println(val);
  }
  if (val == '1') {
    counterclockwise(); //หมุนวนขวา
  }
  if (val == '2') {
    clockwise();  //หมุนวนซ้าย
  }
  if (val == '0') {  //หยุดหมุน
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
  }

  remotecontrol(); // ใช้รีโมต
}
void clockwise () {
  // 1
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay (motorSpeed);
  // 3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 5
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 6
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delay (motorSpeed);
  // 7
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
  // 8
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
}
void counterclockwise() {
  // 1
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay (motorSpeed);
  // 3
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 5
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 6
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  delay (motorSpeed);
  // 7
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
  // 8
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
}

void remotecontrol() {
  if (irrecv.decode(&results)) {
  Serial.print("รหัสปุ่มกด: ");
  Serial.println(results.value);
  
  
  if (results.value == buttonRight) { // ถ้าค่าที่ส่งมาตรงกับ ค่าในตัวแปร code1 ให้ทำใน ปีกกา if
   Serial.println("หมุนขวา");
   clockwise();
  }

  if (results.value == buttonLeft) { // ถ้าค่าที่ส่งมาตรงกับ ค่าในตัวแปร code1 ให้ทำใน ปีกกา if
   Serial.println("หมุนขวา");
   counterclockwise();
  }

   if (results.value == buttonUp) { // ถ้าค่าที่ส่งมาตรงกับ ค่าในตัวแปร code1 ให้ทำใน ปีกกา if
   Serial.println("เพิ่มความเร็ว");
   Serial.println("MotorSpeed");
   Serial.println(motorSpeed);
     if  (3 < motorSpeed) {
         motorSpeed = motorSpeed-1;
        }
   }
   
    if (results.value == buttonDown) { // ถ้าค่าที่ส่งมาตรงกับ ค่าในตัวแปร code1 ให้ทำใน ปีกกา if
   Serial.println("ลดความเร็ว");
   Serial.println("MotorSpeed");
   Serial.println(motorSpeed);
     if  ( 3 <= motorSpeed ) {
         motorSpeed = motorSpeed+1;
        }
   }
   
  irrecv.resume(); // Receive the next value
  }
  
  }
