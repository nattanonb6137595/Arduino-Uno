#include <IRremote.h>
   int RECV_PIN = 7;
  int led = 13;
  IRrecv irrecv(RECV_PIN);
  decode_results results;
  void setup()
  {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  }
  void loop() {
  if (irrecv.decode(&results)) {
  Serial.print("รหัสปุ่มกด: ");
  Serial.println(results.value);
  
  irrecv.resume(); // Receive the next value
  }
  }
  
  
