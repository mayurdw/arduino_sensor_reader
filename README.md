Reading Sensors using Arduino
==

Back in college, during my third year undergraduate's degree we tried building a green house monitoring system. We never finished it and also at the time we were using a different sensor. I decided to reproduce that project.

Granted, the entire project is amatuerish, but I really wanted to finish. Here I am using three sensors

- LM 37 type Temperature sensor
- An LDR
- A soil moisture sensor

In my software, I integrated [Arduino-Log](https://github.com/thijse/Arduino-Log). It is pretty great!

Since I don't have the circuit diagram up, here are the connections: 
1. Button is connected to Digital Pin 2, other end of the button is connected to ground. 
2. For the LDR, Vcc is connected to a 10K resistor -> LDR -> Ground. Output voltage is taken from LDR -> Ground.
3. Soil and temperature sensors are connected according to their pinout.

_Future Plans_
--
Attach a LCD. Commiting myself to do that in April.