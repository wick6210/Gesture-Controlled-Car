/*RAHUL MURALI
  STUDENT AT SRI JAYACHAMARAJENDRA COLLEGE OF ENGINEERING
  MYSURU
  ELECTRONICS AND COMMUNICATION ENGINEERING SECOND YEAR
  COMMUNICATION SYSTEMS - I AND ENGINEERING ELECTROMAGNETICS PROJECT CODE

  This is the receiver code for the Gesture Controlled Car
  
  The connections are as below:
  ESP8266 GND --> LM298N GND --> GND Of Power Supply
  ESP8266 Vin --> 5V Output of LM298N
  ESP8266 D1 --> LM298N IN1
  ESP8266 D2 --> LM298N IN2
  ESP8266 D6 --> LM298N IN3
  ESP8266 D7 --> LM298N IN4
  MOTOR 1 --> LM298N OUT1
  MOTOR 2 --> LM298N OUT2
  MOTOR 3 --> LM298N OUT3
  MOTOR 4 --> LM298N OUT4
  ESP8266 D5 --> 1KOHM RESISTOR --> LED 1 --> GND
  ESP8266 D8 -- 1KOHM RESISTOR --> LED 2 --> GND

  The LED act as indicators for the car movement. It also makes it look like a car which follows proper driving laws, which is necssary for safe driving. The indicator logic has
  been coded in such a way that the delay needed to imitate the flashing of an LED will not interrupt the transmission between the receiver and the transmitter. This is done
  using non-blocking delays like millis().
  
  If the required output is not seen, like the car moves in the wrong direction, then change the motor connections. There is no error as such in this program
  Any debugging on any sorts should be done in the Transmitter Program.
  
  */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define m1 5 //D1
#define m2 4 //D2
#define m3 12 //D6
#define m4 13 //D7

const char* ssid = "Transmitter";      // SSID of transmitter ESP AP
const char* password = "Password";     // Password of transmitter ESP AP

WiFiUDP udp;
unsigned int udpPort = 4210; //Port at which communication occurs
char incomingPacket[255];

void setup() {
  pinMode(m3, OUTPUT); //You must define all of the pins as output, or the ESP8266 will not send a signal to the LM298N
  pinMode(m4, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); //Start serial communication
  delay(100);

  WiFi.begin(ssid, password);  // Connect to transmitter's AP

   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to AP");
  digitalWrite(LED_BUILTIN, HIGH);
  udp.begin(udpPort);
}

void loop() {
  
      int packetSize = udp.parsePacket(); //Parse the incming packet
  if (packetSize) {
    int len = udp.read(incomingPacket, 255); //Read the parsed packet up to 255 bits
    if (len > 0) incomingPacket[len] = 0;
    Serial.print("Received: ");
    Serial.println(incomingPacket); //Print the received packet
    int gesture = atoi(incomingPacket); //Converts the string value into an integer value

    // Optional: Print readable label
    //The below code snippet can be replaced with a switch case statement for easier reading
   
   if (gesture == 0) {
      Serial.println("STOP");
      CarStop();
    }
    else if (gesture == 2){
      Reverse();
    }
    else if (gesture == 1) {
      Forward();
    }
    else if (gesture == 3) {
      Right();
    }
    else if (gesture == 4) {
      Left();
    }
    else Serial.println("UNKNOWN GESTURE");
}
}

/*The LM298N Motor Driver has a Dual H-Bridge which allows effiecient and better control of the motors. This logic below involves adjusting the outputs and inputs using this logic.
Change the values if required*/
void CarStop(){
  Serial.print("STOP");
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}

void Forward(){
  Serial.print("Forward");
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}

void Reverse(){
  Serial.print("Reverse");
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void Left(){
  Serial.print("Left");
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}

void Right(){
  Serial.print("Right");
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}
/*
END OF PROGRAM
*/
