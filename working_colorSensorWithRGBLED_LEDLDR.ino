// INITIALIZING PIN ALLOCATION OF RGB LED.
int redPin = 11; // red pin  of RGB LED is connected to pin 11.
int greenPin = 10; // green pin of RGB LED is connected to pin 10.
int bluePin = 6; // blue pin of RGB LED is connected to pin 6.

// INITIALIZING PIN ALLOCAITON OF COLOR SENSOR.
int S2 = 7; // S2 of ColorSensor connected to pin 7 of Arduino.
int S3 = 8; // S3 of ColorSensor connected to pin 8 of Arduino.
int outPin = 4; // OUT of ColorSensor connected to pin 4 of Arduino.

// INITIALIZING pulseWidth to read number of red, green, blue component.
unsigned int pulseWidth; // unsigned int has a number allocation from 0 to 4,294,967,295.
/*
 * int only allows 0 to 32,768.
 * what the outPin sensor will read is between 0 to 102,400. So using int as data type is insufficient,
 *      that's why we're using unsigned int as data type.
 * RGB colors are often given the value of 0 to 255. This is the same application for choosing colors in Photoshop.
 *      0 as the lightest and 255 as the strongest.
 *      Since pulseWidth will have a maximum value of 102,400, we need to divide it by 400 and subtract 1:
 *
 *      <<REF 1>> colorStrength = pulseWidth/400 - 1;//  to get a maximum number of 255.
 *
 * BUT the circuit measures the pulseWidth as follows;
 *      The lower the value, the stronger the color.
 *      The higher the value, the lighter the color.
 *      Because of this, we need to switch it up so as not to be confusing as we mostly associate 255
 *            as the stronger color value just like in Photoshop.
 *      So what we'll do is:
 *
 *      <<REF 2>> colorStrength = 255 - colorStrength; // Now, 0 will be the lightest while 255 will be the strongest.
*/

// INITIALIZING VARIABLES WHERE WE CAN PUT RGB COMPONENT MEASUREMENT VALUES.
 float rColorStrength;
 float gColorStrength;
 float bColorStrength;

 float maxVal = 1023.00;




 // FOR PHOTORESISTORS
// initializing LDRs
int ldr_1 = A12 ;
int ldr_2 = A13 ;
int ldr_3 = A14 ;
int ldr_4 = A15 ;

// initializing LEDs
int led_1 = 31; 
int led_2 = 33; 
int led_3 = 35; 
int led_4 = 37; 

// initizlizing 'value' variable
int value_1 = 0;
int value_2 = 0;
int value_3 = 0;
int value_4 = 0;

int pinState_1 = 0;
int pinState_2 = 0;
int pinState_3 = 0;
int pinState_4 = 0;

int ledIndicator_right = 39;
int ledIndicator_wrong = 41;

String lastColor = "";
 
void setup() {

  Serial.begin(9600);// Turn on serial port and sets the baud rate to 9600.

  //setting pinModes of the RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // setting pinModes of Color Sensor pins.
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(outPin, INPUT);


  //LEDLDR
  pinMode(ldr_1, INPUT);
  pinMode(led_1, OUTPUT);
  pinMode(ldr_2, INPUT);
  pinMode(led_2, OUTPUT);
  pinMode(ldr_3, INPUT);
  pinMode(led_3, OUTPUT);
  pinMode(ldr_4, INPUT);
  pinMode(led_4, OUTPUT);
  pinMode(ledIndicator_right, OUTPUT);
  pinMode(ledIndicator_wrong, OUTPUT);
}

void loop() {

  LEDLDR();
  // This part will read the red, green, blue components of the paper/material
        //being shown in front of the Color Sensor. Components will be read one by one.


  // Start by reading red component.
  // To read red component, S2 should be set to LOW and S3 should also be set to low.
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  pulseWidth = pulseIn(outPin, LOW); // pulseIn is the function to measure the pulse width.
  /*
   *  How pulseIn works:
   *  pulseIn(whatPinToMeasure, HIGH/LOW); // HIGH/LOW means what pulse you want to measure.
   *        Getting the Low pulse is the way to get the color component.
   *
   *  PULSEWIDTH means how long in micro seconds is that pulse is being read by the sensor.
   *        That pulse is the LOW pulse.
  */
  rColorStrength = pulseWidth; // <<REF 1>>
  rColorStrength = (rColorStrength/maxVal);// <<REF 2>>
  rColorStrength = 1 - rColorStrength;

  // Now, we read the green component.
  // To read green component, we need both S2 and S3 set as HIGH.
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  pulseWidth = pulseIn(outPin, LOW);
  gColorStrength = pulseWidth; // <<REF 1>>
  gColorStrength = (gColorStrength/maxVal); // <<REF 2>>
  gColorStrength = 1 - gColorStrength;

  // Lastly, we read the blue component.
  // To read blue component, we need both S2 as LOW and S3 as HIGH.
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  pulseWidth = pulseIn(outPin, LOW);
  bColorStrength = pulseWidth; // <<REF 1>>
  bColorStrength = (bColorStrength/maxVal); // <<REF 2>>
  bColorStrength = 1 - bColorStrength;
  
  
  // Print out the colors to see if we got things right. :D
  
  if (rColorStrength>gColorStrength && gColorStrength>bColorStrength){
    rColorStrength = 255;
    gColorStrength = 255 * gColorStrength;
    bColorStrength = 0;
    // yellow
    if (gColorStrength >= 190 && gColorStrength <= 200){
      analogWrite(redPin, 255);
      analogWrite(greenPin, 100);
      analogWrite(bluePin, 0);
      lastColor = "YELLOW";
      Serial.println(lastColor);
      delay(1);
    }
  }
  
  if (rColorStrength>bColorStrength && bColorStrength>gColorStrength){
    rColorStrength = 255;
    bColorStrength = 255 * bColorStrength;
    bColorStrength = bColorStrength /50;
    gColorStrength = 0;

    // red
    if (bColorStrength >= 2){
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      lastColor = "RED";
      Serial.println(lastColor);
      delay(1);
    }//orange 
    if (bColorStrength >=3){
      analogWrite(redPin, 100);
      analogWrite(greenPin, 20);
      analogWrite(bluePin, 0);
      lastColor = "ORANGE";
      Serial.println(lastColor);
      delay(250);
    } /*
    else if (bColorStrength >=4){
      analogWrite(redPin, 252);
      analogWrite(greenPin, 20);
      analogWrite(bluePin, 255);
    }else{
      
    }*/
  }

  if (gColorStrength>rColorStrength && rColorStrength>bColorStrength){
    gColorStrength = 255;
    rColorStrength = 255 * rColorStrength;
    bColorStrength = 0;
  }

  if (gColorStrength>bColorStrength && bColorStrength>rColorStrength){
    gColorStrength = 255;
    bColorStrength = 255 * bColorStrength;
    rColorStrength = 0;

    bColorStrength = bColorStrength /10;
    
  }

  if (bColorStrength>rColorStrength && rColorStrength>gColorStrength){
    bColorStrength = 255;
    rColorStrength = 255 * rColorStrength;
    gColorStrength = 0;

    bColorStrength = bColorStrength /5;

    
  }

  if (bColorStrength>gColorStrength && gColorStrength>rColorStrength){
    bColorStrength = 255;
    gColorStrength = 255 * gColorStrength;
    rColorStrength = 0;

    bColorStrength = bColorStrength /5;

    
  
  // dark green
  if (gColorStrength >= 120 && gColorStrength <= 149){
    analogWrite(redPin, 0);
    analogWrite(greenPin, 43);
    analogWrite(bluePin, 12);
    lastColor = "DARK GREEN";
    Serial.println(lastColor);
    delay(1);
  }

  // light green
  if (gColorStrength >= 180 && gColorStrength <= 190){
    analogWrite(redPin, 59);
    analogWrite(greenPin, 98);
    analogWrite(bluePin, 48);
    lastColor = "LIGHT GREEN";
    Serial.println(lastColor);
    
    delay(250);
  }

  // blue
  if (gColorStrength >= 100 && gColorStrength <= 120){
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
    Serial.println("BLUE");

    if (!lastColor.equals("")){
      Serial.print("LAST COLOR >> ");
      Serial.println(lastColor);
        digitalWrite(ledIndicator_right, LOW);
        digitalWrite(ledIndicator_wrong, LOW);
        // PINSTATE 1
        if (pinState_1 == 1){
          Serial.print("pinState1 == ");
          Serial.println(pinState_1);
        }else{
          Serial.print("pinState1 == ");
          Serial.println(pinState_1);
        }
        
        // PINSTATE 2
        if (pinState_2 == 1){
          Serial.print("pinState2 == ");
          Serial.println(pinState_2);
        }else{
          Serial.print("pinState2 == ");
          Serial.println(pinState_2);
        }

        // PINSTATE 3
        if (pinState_3 == 1){
          Serial.print("pinState3 == ");
          Serial.println(pinState_3);
        }else{
          Serial.print("pinState3 == ");
          Serial.println(pinState_3);
        }

        // PINSTATE 4
        if (pinState_4 == 1){
          Serial.print("pinState4 == ");
          Serial.println(pinState_4);
        }else{
          Serial.print("pinState4 == ");
          Serial.println(pinState_4);
        }

        if (lastColor == "DARK GREEN"){

            if (pinState_1 == 0 &&
                  pinState_2 == 1 &&
                  pinState_3 == 1 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, HIGH);
                digitalWrite(ledIndicator_wrong, LOW);
            }else if (pinState_1 == 1 &&
                  pinState_2 == 1 &&
                  pinState_3 == 1 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, LOW);
            }else{
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, HIGH);
            }
          
        }else if (lastColor == "LIGHT GREEN"){
          
            if (pinState_1 == 1 &&
                  pinState_2 == 0 &&
                  pinState_3 == 1 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, HIGH);
                digitalWrite(ledIndicator_wrong, LOW);
            }else if (pinState_1 == 1 &&
                  pinState_2 == 1 &&
                  pinState_3 == 1 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, LOW);
            }else{
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, HIGH);
            }
        }else if (lastColor == "RED"){
            if (pinState_1 == 1 &&
                  pinState_2 == 1 &&
                  pinState_3 == 0 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, HIGH);
                digitalWrite(ledIndicator_wrong, LOW);
            }else if (pinState_1 == 1 &&
                  pinState_2 == 1 &&
                  pinState_3 == 1 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, LOW);
            }else{
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, HIGH);
            }
        }else if (lastColor == "ORANGE"){
            if (pinState_1 == 1 &&
                  pinState_2 == 1 &&
                  pinState_3 == 1 &&
                  pinState_4 == 0){
                digitalWrite(ledIndicator_right, HIGH);
                digitalWrite(ledIndicator_wrong, LOW);
            }else if (pinState_1 == 1 &&
                  pinState_2 == 1 &&
                  pinState_3 == 1 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, LOW);
            }else{
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, HIGH);
            }
        }else if (lastColor == "YELLOW"){
            if (pinState_1 == 0 &&
                  pinState_2 == 1 &&
                  pinState_3 == 1 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, HIGH);
                digitalWrite(ledIndicator_wrong, LOW);
            }else if (pinState_1 == 1 &&
                  pinState_2 == 1 &&
                  pinState_3 == 1 &&
                  pinState_4 == 1){
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, LOW);
            }else{
                digitalWrite(ledIndicator_right, LOW);
                digitalWrite(ledIndicator_wrong, HIGH);
            }
        }else{
            digitalWrite(ledIndicator_right, LOW);
            digitalWrite(ledIndicator_wrong, LOW);
        }
        

        
    }else{
      Serial.print("LAST COLOR >> ");
      Serial.println("NULL");

      digitalWrite(ledIndicator_right, LOW);
      digitalWrite(ledIndicator_wrong, LOW);
    }
    
    
    delay(1);
  }
  
  }



  Serial.print("R: ");
  Serial.println(rColorStrength);
  Serial.print("G: ");
  Serial.println(gColorStrength);
  Serial.print("B: ");
  Serial.println(bColorStrength);
  Serial.println("");
/*
  analogWrite(redPin, rColorStrength);
  analogWrite(greenPin, gColorStrength);
  analogWrite(bluePin, bColorStrength);
*/
  
}

void LEDLDR(){

//LDR-LED Circuit1
  value_1 = analogRead(ldr_1);
  if (value_1 >= 300){
    digitalWrite(led_1, HIGH);
    pinState_1 = 1;
  }
  if (value_1 < 300){
    digitalWrite(led_1, LOW);
    pinState_1 = 0;
  }
  Serial.print("VALUE_1: ");
  Serial.println(value_1);

  //LDR-LED Circuit2
  value_2 = analogRead(ldr_2);
  if (value_2 >= 300){
    digitalWrite(led_2, HIGH);
    pinState_2 = 1;
  }
  if (value_2 < 300){
    digitalWrite(led_2, LOW);
    pinState_2 = 0;
  }
  Serial.print("VALUE_2: ");
  Serial.println(value_2);

  //LDR-LED Circuit3
  value_3 = analogRead(ldr_3);
  if (value_3 >= 300){
    digitalWrite(led_3, HIGH);
    pinState_3 = 1;
  }
  if (value_3 < 300){
    digitalWrite(led_3, LOW);
    pinState_3 = 0;
  }
  Serial.print("VALUE_3: ");
  Serial.println(value_3);

  //LDR-LED Circuit4
  value_4 = analogRead(ldr_4);
  if (value_4 >= 300){
    digitalWrite(led_4, HIGH);
    pinState_4 = 1;
  }
  if (value_4 < 300){
    digitalWrite(led_4, LOW);
    pinState_4 = 0;
  }
  Serial.print("VALUE_4: ");
  Serial.println(value_4);

  Serial.println("");
  
  delay(250);  

  
}


