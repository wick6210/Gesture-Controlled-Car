# Gesture-Controlled-Car
An IoT Project that wirelessly controls a car chassis over WiFi Connectivity.

## Components Needed:
1. MPU6050
2. ESP8266 NodeMCU x 2
3. Breadboards
4. 12V Battery Power Supply
5. L298N Motor Driver
6. Jumper Wires
7. Motors
8. Car Chassis

## Working
### Transmitter
The transmitter part of the system has an ESP8266 and the MPU6050. The 2 are connected via I2C Interface and the transmitter code is uploaded to the ESP8266. This records the serial transmission of values from the MPU6050 and based on the values and the threshold value, the NodeMCU sends a value from 0 to 4 over WiFi in UDP Setup.
### Receiver
The receiver part of the system has an ESP8266, L298N, 12V Battery Pack, Motors and Car Chassis. Power the Motor Driver with 12V and connect the pics specified from the motor driver to the NodeMCU. Ensure that both ESP8266 and 12V batter share the same GND in the motor driver. The car can STOP, move FORWARD and REVERSE and turn LEFT or RIGHT.

## Project Technicalities
UDP is protocol of choice here, since it has lower latency than TCP, and it can broadcast to multiple devices, meaning that a fleet of similarly programmed cars can be controlled at once.
The car itself is a 4WD (4 Wheel Drive) which means that all 4 wheels drive the car. This provides more power and better handling, but it also consumes more power than a classic 2WD (2 Wheel Drive Car). The logic for the 4WD was made simple by virtue of the fact that the L298N Motor Driver has a Dual H-Bridge Setup.
The ESP8266 Transmitter has been made into an AP (Access Point), so that the system can work even when WiFi does not exist in the environment. This is because in AP Mode, the ESP8266 acts as its own Access Point and hosts its own network. The Receiver will connect to this ESP8266 AP in STA Mode, which is the standard mode to connect to any available WiFi Network.

## Applications
1. Fleet Vehicle Control (Drones, Warehouse Bots, etc.)
2. Assistive Technology (Can be integrated to mobile systems, say, a wheelchair, to control wirelessly)
3. Wireless Control of Robotic Systems (Robotic Hands in Industrial Scenarios)
