#include <Wire.h>
#include "pitches.h"
#include "RTClib.h"  // Credit: Adafruit
// A lot of this is found at: https://www.instructables.com/id/Getting-started-with-Arduino-Y%C3%BAn-and-ChronoDot-v2/
RTC_DS1307 RTC;

// Setting up variables
const int inputPin = 7; //Button Pin
const int outputPin = 8; //Speaker Pin
int buttonState = 0; //Button State 

//Varaibel types found here: https://www.arduino.cc/reference/en/#functions
bool timerState;
bool buzzerState;


void setup() {
  // Begin the Serial connection 
  Serial.begin(9600);
 
  // Instantiate the RTC
  Wire.begin();
  RTC.begin();
 
  // Check if the RTC is running.
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running");
  }

  // This is optional: Force timeset.
  delay(5000);
  Serial.println("Forcing TIMESET");
  RTC.adjust(DateTime(2000, 1, 21, 0, 0, 0));

  // This section grabs the current datetime and compares it to
  // the compilation time.  If necessary, the RTC is updated.
  DateTime now = RTC.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime()) {
    Serial.println("RTC is older than compile time! Updating");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
   
  Serial.println("Setup complete.");
}

bool Timer() {
  Serial.println("Starting timer function"); 
  DateTime now = RTC.now();
  //Setting up variables
  int currentMinutes = 0; 
  int stopMinutes = 0;
  

// Not needed for demo
 // int stopHours = 0;
 //int currentHours = 0;  
  

  // Checking current time
  now = RTC.now();
  currentMinutes = now.minute();
  stopMinutes = currentMinutes + 1;
  

//Not needed for demo
//  currentHours = now.minute();
 // stopHours = currentHours + 1;


// Not needed for demo
  //if(stopHours > 24) {
   //  Serial.println("INSIDE IF");
    // stopHours = stopHours - 24;
 // }
  

  //Print statements
  Serial.print("currentMinutes "); Serial.println(currentMinutes);
  Serial.print("stopMinutes") ; Serial.println(stopMinutes);

 
  

// Not needed for demo
 // Serial.print("stopHours " ); Serial.println(stopHours);
 // Serial.print("stopMinutes") ; Serial.println(stopMinutes);

  // Creating loop
  if((stopMinutes != currentMinutes)) {
    
    Serial.println("Starting if");
    buttonState = digitalRead(inputPin);
    Serial.print("buttonState: "); Serial.println(buttonState);

      while(buttonState == LOW) {
          now = RTC.now();
          Serial.println("Starting while loop");
          buttonState = digitalRead(inputPin);
          currentMinutes = now.minute();
          int seconds = now.second();

          //Not needed for demo
          //currentHours = now.minute();

          //Adding print statements for testing
          Serial.print("Updated minutes"); Serial.println(currentMinutes);Serial.print(".");Serial.println(seconds); 
          //Serial.print("Updated hours"); Serial.println(currentHours);

          //Serial.print("stopHours");Serial.println(stopHours);
          Serial.print("stopMinutes");Serial.println(stopMinutes);
  
          //If statements
          if(currentMinutes == stopMinutes){
              Serial.println("START IF");
              return true;
              
              }
          if (stopMinutes < currentMinutes){
              Serial.println("MIDDLE IF");
              return true;
              }

          if(buttonState == HIGH) {
              Serial.println("END IF");
              return false; 
          }

        delay (1000);
      }


  }
}

bool Buzzer() {
   Serial.println("Welcome to the Buzzer Function.");
   buttonState = digitalRead(inputPin);
   Serial.print("This is the buttonState.");Serial.println(buttonState);
   while(buttonState == LOW) {
      Serial.println("In the while loop.");
      buttonState = digitalRead(inputPin);
      tone(8,NOTE_D1, 1000);
      if(buttonState == HIGH) {
        return true;
      }

      
   }
}

void loop() {
  // Get the current time
  buttonState = digitalRead(inputPin);
  if (buttonState == HIGH) {
    Serial.println("BUTTON PUSHED");
    timerState = Timer();
    Serial.print("timerState"); Serial.println(timerState);
    if(timerState == 1) {
      Serial.println("FUNCTION WORKED");
      buzzerState = Buzzer();
        if(buzzerState == true) {
          Serial.print("IT WORKED");
        }
    }
    if(timerState == 0) {
      Serial.println("BUTTON WAS PRESSED");
    }
    
  }
  
  
}

