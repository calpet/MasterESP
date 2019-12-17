#include <Wire.h>

#define SLAVE_ADDR 9
#define ANSWERSIZE 5 //Size of response in bytes.
int led = 13;
int val = 0;
String answer;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Wire.begin(SLAVE_ADDR);

  //Start requestEvent function when a request is made from the Master.
  Wire.onRequest(requestEvent);

  //Start receiveEvent when an instruction is received from the Master.
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  Serial.println("Initializing...\n");

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}

//Simple function to send instructions to actuators.
void receiveEvent(int recvData) {
  while (0 < Wire.available()) {
    bool x = Wire.read();
    
    if (x == true){
      digitalWrite(led, HIGH);
      
    } else if (x == false){
      digitalWrite(led, LOW);
    }
  }
}

void requestEvent() {
  byte response[ANSWERSIZE];

  //Format responsedata as an Array.
  for (byte i = 0; i < ANSWERSIZE; i++) {
    response[i] = (byte)answer.charAt(i);
  }

  Wire.write(response, sizeof(response));
  Serial.println("Request sent.");

}
