### VisibleLightCommunication

##### This is a demo setup made as a proof of concept for the IISc Open Day event held on the 23rd of March 2019.
##### The IISc Open Day attracts hundreds of school going and engineering undergraduates from colleges in Bangalore and nearby cities.

##### How does it work?
The user enters a string to be transmitted on the Serial Terminal of an Arduino used for transmitting.
This Arduino modulates and LED using On-Off keying based on the character's ASCII binary pattern.

A photo-receiver (Light Dependent Receiver - LDR) is used on the receiving end to determine the On-Off state of the LED and decode the binary ASCII code back into a character. Another Arduino is used to determine the state from the Analog Voltage read from the LDR.

##### Tx-Circuit
Arduino PIN_12 ----- LED ----- {220 Ohm} ----- GND

##### Rx-Circuit
Arduino 5V_VCC ----- LDR ----- (CONNECTION XXX) ----- {4.7 KOhm} ----- GND

(CONNECTION XXX) ----- ARDUINO_A0

