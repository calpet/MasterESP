#include <Wire.h>

//Master code

const int SLAVE_ADDR = 9;
const char * host = "192.168.1.1";
const uint16_t port = 80;

#define ANSWERSIZE 5

int incoming;
bool instructie;



void setup() {
  // put your setup code here, to run once:
  
  Wire.begin();
  Serial.begin(115200);
  wifiSetup();
  Serial.println("Initializing...\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

  Serial.print("Connecting to ");
  Serial.println(host);

  //Create TCP connection.
  WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("Connection failed.");
        Serial.println("Retrying in 2 seconds...");
        delay(2000);
        return;
    }

    //Send string to server.
    //client.print("Hello World");

    tcpCommunication();

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

//Method to setup a client for connection to a router/access point.
void wifiSetup(){
   WiFiMulti.addAP("SecHome", "1nsan3lyS3cur3@!");

   Serial.println();
   Serial.print("Waiting for WiFi... ");

   while(WiFiMulti.run() != WL_CONNECTED) {
       Serial.print(".");
       delay(500);
   }

   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());

   delay(500);
}

void tcpCommunication(){
  int retries = 0;

  //wait for the server's reply to become available
  while (!client.available() && retries < 1000)
  {
    retries++;
    delay(1);
  }
  if (client.available() > 0)
  {
    //read back one line from the server
    String line = client.readStringUntil('\r');
    Serial.println(line);
  }
  else
  {
    Serial.println("client.available() timed out ");
  }

    Serial.println("Closing connection.");
    client.stop();

    Serial.println("Waiting 5 seconds before restarting...");
    delay(5000);
}
