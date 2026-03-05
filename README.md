# Gesture-Controlled-Car
An IoT Project that wirelessly controls a car chassis over WiFi Connectivity.

Components Needed:
1. MPU6050
2. ESP8266 NodeMCU x 2
3. Breadboards
4. 12V Battery Power Supply
5. L298N Motor Driver
6. Jumper Wires
7. Motors
8. Car Chassis

The transmitter part of the system has an ESP8266 and the MPU6050. The 2 are connected via I2C Interface and the transmitter code is uploaded to the ESP8266. This records the serial transmission of values from the MPU6050 and based on the values and the threshold value, the NodeMCU sends a value from 0 to 4 over WiFi in UDP Setup.

The receiver part of the system has an ESP8266, L298N, 12V Battery Pack, Motors and Car Chassis. Power the Motor Driver with 12V and connect the pics specified from the motor driver to the NodeMCU. Ensure that both ESP8266 and 12V batter share the same GND in the motor driver.

The car can STOP, move FORWARD and REVERSE and turn LEFT or RIGHT.
