#include <Wire.h>

//Master code

const int SLAVE_ADDR = 9;

#define ANSWERSIZE 5

int incoming;
bool instructie;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing...\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);

  //Event handler for serial connection & input from connection.
  if (Serial.available() > 0) {
    incoming = Serial.read();

    if (incoming == '1') {
      instructie = true;
      verzendInstructie(SLAVE_ADDR, instructie);
      Serial.print("Instruction has been sent.\n");

    } else if (incoming == '0') {
      instructie = false;
      verzendInstructie(SLAVE_ADDR, instructie);
      Serial.print("Instruction sent.\n");

    }

    //In case no serial communication is available.
  } else {
    Serial.println("No serial connection available. Try again.");
  }

  //Request an answer from the Slave.
  Wire.requestFrom(SLAVE_ADDR, ANSWERSIZE);

  String response = "";
  while (Wire.available()) {

    //Read the ouput as characters, combine it with response, and print to Serial.
    char output = Wire.read();
    response += output;

    Serial.println(response);
  }
}

//Event handler for sending instructions to Slave node(s).
void verzendInstructie(int SLAVE_ADDR, bool instructie) {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(instructie);
  Wire.endTransmission();
}
