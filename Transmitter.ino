/*RAHUL MURALI
  STUDENT AT SRI JAYACHAMARAJENDRA COLLEGE OF ENGINEERING
  MYSURU
  ELECTRONICS AND COMMUNICATION ENGINEERING SECOND YEAR
  COMMUNICATION SYSTEMS - I AND ENGINEERING ELECTROMAGNETICS PROJECT CODE

This is the TRANSMITTER Code for the Gesture Controlled Car using LM298N Motor Driver, ESP8266 NodeMCU, MPU6050 Accelerometer and Buttons for the Record Playback

TRANSMITTER Connections
MPU6050 VCC --> ESP8266 3.3V
MPU6050 GND --> ESP8266 GND
MPU6050 SDA --> ESP8266 D1
MPU6050 SCL --> ESP8266 D2

The MPU6050 Accelerometer is a sensor used to digitally give out the orientation of the current device. This ESP8266 works in AP [Access Point] mode to act as a server for the data
transmission. The values will be sent in the form of integers. 0 - STOP, 1 - FORWARD, 2 - REVERSE, 3 - LEFT, 4 - RIGHT.
This program uses UDP[User Datagram Protocol] over TCP[Transmission Control Protocol] for better reliability and speed.
TCP is more focused on the connection status and sending data without any error.
UDP is more focused on sending the data as fast as possible without establishing connection. The error rate is more but transmission speed is also faster.

TCP was meant to be integrated, but due to technical issues, we are using UDP Protocol.

Before uploading the code, please make sure the required drivers are installed for the ESP8266 and that the required libraries are installed (listed below).
Hold onto the Flash Button on the ESP8266 while uploading. Once "Uploading.." appears on the screen, you can release the button.

In case watchdog timer reset appears at the output, then just leave the set up and take a 30 minite break. After that, it should be working properly.
*/

#include <WiFiUdp.h> //UDP Library
#include<ESP8266WiFi.h> // This is for the WiFi Transmission
#include<Wire.h> // This is for the MPU connection
#include<Adafruit_MPU6050.h> // This is for the MPU Connection
#include<Adafruit_Sensor.h> //This is for the MPU Connection
#include <SoftwareSerial.h>



Adafruit_MPU6050 mpu;

const char *ssid = "Transmitter"; // This is the SSID of the AP Point
const char *password = "Password"; // This is the Password of the AP Point

WiFiUDP udp;
IPAddress receiverIP(192, 168, 4, 2);  // STA IP
unsigned int udpPort = 4210;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Serial Communication start
  uploaderSerial.begin(9600);  // Start Tx serial to uploader at 9600 baud
  Wire.begin(0, 2); //Wire communication to MPU start
  udp.begin(4211); // Local port for sender (any unused port)
  delay(200);
  Serial.println("\n");
  
  WiFi.softAP(ssid, password); //Set WiFi and Password to the ESP
  Serial.print("Access Point ");
  Serial.print(ssid);
  Serial.print(" started");
  Serial.println("\n");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP()); //Print IP Address of the WiFi Point


  if(!mpu.begin()){ //In case MPU is connected wrong, this message will display
    Serial.print("failed to connect to the MPU!");
    while(1);
  }

  Serial.println("MPU Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); //Set Ranges for all parameters
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {

  int gesture = detectGesture();  // Function to read the MPU6050 Values
  Serial.println(gesture);
udp.beginPacket(receiverIP, udpPort);
udp.print(gesture);              // Or udp.write((uint8_t*)&gesture, sizeof(gesture));
udp.endPacket();                 //  This sends the packet
uploaderSerial.println(gesture);
delay(1);
  
}

int detectGesture() {
  const float threshold = 5.0;
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float x = a.acceleration.x;
  float y = a.acceleration.y;
  float z = a.acceleration.z;

  if (z > threshold) return 1;       // FORWARD
  else if (z < -threshold) return 2; // REVERSE
  else if (x > threshold && y < threshold) return 0; // STOP
  else if (y >= threshold) return 3; // RIGHT
  else return 4;                     // LEFT

}

