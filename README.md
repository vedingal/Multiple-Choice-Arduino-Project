# Multiple Choice Arduino Project

## Description:
This project uses 4 photo resistors signifying choices A, B, C, and D. Right answer is set by the color being picked up by Color Sensor.
Starting from line 294, you can see the answer sheet by color;

```
LINE 294:
if (pinState_1 == 0 && // for A - 1st photoresistor
  pinState_2 == 1 && // for B - 2nd photoresistor
  pinState_3 == 1 && // for C - 3rd photoresistor
  nState_4 == 1){ ... // for D - 4th photoresistor
  
  // pinState vaue of 0 signifies that Photoresistor is being blocked, therefore is the chosen answer.
  // This means that 4 photoresitors need to have 4-bit 0111 logic for the answer to be considered as correct, 
  // thus lighting up the LED indicator for correct answer.
  
  ---------------------------------
  ANSWER SHEET PHOTORESISTOR LOGIC
  ---------------------------------
  
  0111 - DARK GREEN (line 294)
  1011 - LIGHT GREEN (line 313)
  1101 - RED (line 331)
  1110 - ORANGE (line 348)
  0111 - YELLOW (line 365)
  
  // 4-bit logic and color should match for the circuit to know the right answer.
  
  --------------------------------------
  STOP: ANSWER SHEET PHOTORESISTOR LOGIC
  --------------------------------------
```

## Materials
* 1 Arduino Board
* 1 Power Supply
* 1 RGB LED (Common Anode)
* 10 18 ohm resistor
* 1 Color Sensor
* 4 Photoresistors
* 4 10k ohm resistors
* Connecting Wires

# Schematic Diagram
![alt text](https://raw.githubusercontent.com/venndingal/Photoresistor-Enabled-Color-Sensor-with-RGB-LED-Indicator/master/Schematic%20Diagram.png "Fig 1. Schematic Diagram of Multiple Choice Project")

# Color Calibrator
![alt text](https://github.com/venndingal/Photoresistor-Enabled-Color-Sensor-with-RGB-LED-Indicator/blob/master/Color%20Calibration.jpg?raw=true "Fig 2. Color Calibrator")

