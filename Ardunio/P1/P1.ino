
#include <Wire.h>
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
  RTC.adjust(DateTime(2000, 1, 21, 3, 0, 0));

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
  int currentHours = 0; 
  int stopHours = 0;
  int stopMinutes = 0;
  

  // Checking current time
  currentMinutes = now.minute();
  currentHours = now.hour();
  stopHours = currentHours + 5;
  stopMinutes = now.minute();
  if(stopHours > 24) {
     Serial.println("INSIDE IF");
     stopHours = stopHours - 24;
  }
  

  //Print statements
  Serial.print("currentMinutes "); Serial.println(currentMinutes);
  Serial.print("currentHours "); Serial.println(currentHours);
  Serial.print("stopHours" ); Serial.println(stopHours);
  Serial.print("stopMinutes") ; Serial.println(stopMinutes);

  // Creating loop
  if((stopHours != currentHours)) {
    
    Serial.println("Starting if");
    buttonState = digitalRead(inputPin);
    Serial.print("buttonState: "); Serial.println(buttonState);

      while(buttonState == LOW) {
          now = RTC.now();
          Serial.println("Starting while loop");
          buttonState = digitalRead(inputPin);
          currentMinutes = now.minute();
          int seconds = now.second();
          currentHours = now.hour();

          //Adding print statements for testing
          Serial.print("Updated minutes"); Serial.print(currentMinutes);Serial.print(".");Serial.println(seconds); 
          Serial.print("Updated hours"); Serial.println(currentHours);

  
          //If statements
          if(currentHours == stopHours && currentMinutes == stopMinutes){
              return true;
              }
          if (currentHours == stopHours && stopMinutes > currentMinutes){
              return true;
              }

          if(buttonState == HIGH) {
            return false; 
          }

        delay (1000);
      }


  }
}

void loop() {
  // Get the current time
  Timer();
  
}
