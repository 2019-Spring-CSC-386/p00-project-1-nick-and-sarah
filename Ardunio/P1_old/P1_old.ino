//Project 1
// Created By: Sarah Watts and Nick Straub-Deck 
//Function: When you press the button a timer will start, 
//once that time reaches 5 hours it will emit a buzzing noise

#include <Wire.h> // Library for the clock
#include "RTClib.h"
  long timer; //Variable for the time
  const int inputPin = 7; //Button pin
  const int outputPin = 8; // Speaker pin
  int buttonState = 0; //State of button

 //Variable types found here: https://www.arduino.cc/reference/en/#functions
  bool timerState; // State of the timer function
  bool buzzerState; // State of the buzzer function. 

void setup() {
  // put your setup code here, to run once:
  //found at this link: http://docs.macetech.com/doku.php/chronodot_v2.0
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(2019, 2, 7, 3, 0, 0));
  Serial.begin(9600);
  Wire.beginTransmission(0x68); // address DS3231
  Wire.write(0x0E); // select register
  Wire.write(0b00011100); // write register bitmap, bit 7 is /EOSC
  Wire.endTransmission();

 //  Setting input put and output pin for the button and the buzzer
 pinMode(inputPin, INPUT);
 pinMode(outputPin, OUTPUT); 
}

boolean Timer() {
  Serial.println("I'm in the timer function");
  ///Things go in here
  //Also found at the following link:  http://docs.macetech.com/doku.php/chronodot_v2.0
  Wire.beginTransmission(0x68); // 0x68 is DS3231 device address
  Wire.write((byte)0); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(0x68, 3); // request three bytes (seconds, minutes, hours)
  Serial.println("inital varaibles.");
  int currentMinutes = 0;
  int currentHours = 0;
  int stopHours;
  int stopMinutes;
  int minutes = 0;
  int hours = 0;
  
  minutes = Wire.read(); // get seconds
  hours = Wire.read();   // get hours
  currentMinutes =  (((minutes & 0b11110000)>>4)*10 + (minutes & 0b00001111)); // convert BCD to decimal // convert BCD to decimal
  currentHours = (((hours & 0b00100000)>>5)*20 + ((hours & 0b00010000)>>4)*10 + (hours & 0b00001111)); // convert BCD to decimal (assume 24 hour mode)
  stopHours = currentMinutes + 5;
  stopMinutes = currentMinutes;
  Serial.println("This is current Hours: "); Serial.println(currentHours); 
  Serial.println("This is current minutes: "); Serial.println(currentMinutes);
  Serial.println("This is stopHours: "); Serial.println(stopHours); 
  Serial.println("This is stopMinutes: ");Serial.println(stopMinutes);
    
  Serial.println("Before while loop");
  while (currentMinutes < stopHours){
    Serial.println("In while loop.");
    buttonState = digitalRead(inputPin);
    Serial.println(buttonState);
   while (buttonState == LOW) {
    Serial.println("In other while loop");
      buttonState = digitalRead(inputPin);
      minutes = Wire.read();
      hours = Wire.read();
      currentMinutes =  (((minutes & 0b11110000)>>4)*10 + (minutes & 0b00001111)); // convert BCD to decimal;
      currentHours = (((hours & 0b00100000)>>5)*20 + ((hours & 0b00010000)>>4)*10 + (hours & 0b00001111)); 
      Serial.println("This is currentHours on while loop: "); Serial.println(currentHours);
      Serial.println("This is current Minutes on while loop: "); Serial.println(currentMinutes);
      if(currentHours == stopHours && currentMinutes == stopMinutes);
           return true;
      if(currentHours == stopHours && currentMinutes > stopMinutes);
          return true;
      if (buttonState == HIGH);
         return false;
      
    }
 
  }
}


bool Buzzer() {
  ///Things go in here too 
}

void loop() {
 //Commented out to test the clock
 //Also edited from code at the following link: https://www.arduino.cc/en/tutorial/button
 //buttonState = digitalRead(inputPin); 
 //if(buttonState == HIGH) {
    // tone(8, 196, 8);
// }
// else if (buttonState == LOW){
    // noTone(8);
// }
///

    //Timer();
 
   
}

 
