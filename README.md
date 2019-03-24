### VisibleLightCommunication

##### This is a demo setup made as a proof of concept for the IISc Open Day event held on the 23rd of March 2019.
##### The IISc Open Day attracts hundreds of school going and engineering undergraduates from colleges in Bangalore and nearby cities.

##### How does it work?
- The user enters a string to be transmitted on the Serial Terminal of an Arduino used for transmitting.
This Arduino modulates and LED using On-Off keying based on the character's ASCII binary pattern.

- A photo-receiver (Light Dependent Receiver - LDR) is used on the receiving end to determine the On-Off state of the LED and decode the binary ASCII code back into a character. Another Arduino is used to determine the state from the Analog Voltage read from the LDR.

##### Tx-Circuit
- Arduino PIN_12 ----- LED ----- {220 Ohm} ----- GND

##### Rx-Circuit
- Arduino 5V_VCC ----- LDR ----- (CONNECTION XXX) ----- {4.7 KOhm} ----- GND

- (CONNECTION XXX) ----- ARDUINO PIN_A0


- Upload the **vlcrx** to the the Arduino connected to the LDR and the **vlctx** to the Arduino connected to the LED.

- Point the LED to the LDR and keep them apart by about 5cm.

##### Automatic Threshold Detection
- As there is going to be Ambient light falling on the LDR, we need to find the appropriate threshold for what ADC values (read form the LDR voltage devider throught the Arduino PIN_A0) such that when our LED is on, we should read bit 1 (after comparing the threshold with the Analog Read from PIN_A0) and when LED is off, we should read 0.

- To find the appropriate threshold, we need to reset the two Arduinos simultaneously. The **vlcrx** and **vlctx** codes contain an initial synchronised and known LED On-Off cycle which helps in calibrating and finding the right threshold. 

- One can manually reset the two Arduinos simultaneorsly by releasing the reset button at the same time.
Another way is to connect the the reset(RST) pin of both the Arduinos together and hit reset any one of the Arduino.

- This needs to be done everytime the ambient light changes or when you see unknown characters being received instead of the characters sent from the transmitter.

##### A few pointers

- The defined value BIT_PERIOD is set to 20 milliseconds by default and works well most of the time. If the LED's response or the LDR voltage devider's response is too sluggish, one might not be able to transmit and receive the right characters and in which case one might see different characters being received inplace of the ones sent.

- Try increasing the value of BIT_PERIOD in both the **vlctx** and **vlcrx** code. NOTE: both codes need to have the same value set for BIT_PERIOD.
