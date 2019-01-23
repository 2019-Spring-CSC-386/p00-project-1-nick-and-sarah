//Project 1
// Created By: Sarah Watts and Nick Straub-Deck 
//Function: When you press the button a timer will start, 
//once that time reaches 5 hours it will emit a buzzing noise

#include <Wire.h> // Library for the clock
  long timer; //Variable for the time
  const int inputPin = 7; //Button pin
  const int outputPin = 8; // Speaker pin
  int buttonState = 0; //State of button

void setup() {
  // put your setup code here, to run once:
  //found at this link: http://docs.macetech.com/doku.php/chronodot_v2.0
  // Getting the clock to work
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(0x68); // address DS3231
  Wire.write(0x0E); // select register
  Wire.write(0b00011100); // write register bitmap, bit 7 is /EOSC
  Wire.endTransmission();

 //  Setting input put and output pin for the button and the buzzer
 pinMode(inputPin, INPUT);
 pinMode(outputPin, OUTPUT); 
 
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
//}
//Testing the clock
//Also found at the following link:  http://docs.macetech.com/doku.php/chronodot_v2.0
  Wire.beginTransmission(0x68); // 0x68 is DS3231 device address
  Wire.write((byte)0); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(0x68, 3); // request three bytes (seconds, minutes, hours)
 
  while(Wire.available())
  { 
    int seconds = Wire.read(); // get seconds
    int minutes = Wire.read(); // get minutes
    int hours = Wire.read();   // get hours
 
    seconds = (((seconds & 0b11110000)>>4)*10 + (seconds & 0b00001111)); // convert BCD to decimal
    minutes = (((minutes & 0b11110000)>>4)*10 + (minutes & 0b00001111)); // convert BCD to decimal
    hours = (((hours & 0b00100000)>>5)*20 + ((hours & 0b00010000)>>4)*10 + (hours & 0b00001111)); // convert BCD to decimal (assume 24 hour mode)
 
    Serial.print(hours); Serial.print(":"); Serial.print(minutes); Serial.print(":"); Serial.println(seconds);
  }
 
  delay(1000);
}
