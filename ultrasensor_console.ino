   /* William Clemons
    * Nathan Nhek
    * 
    * Proximity Alarm
    * Detect nearby objects and set off a buzzing noise when under a certain distance. 
    * Set to display the distance to a LCD screen.
    */
    // include the library that contains the #defines for all passive buzzer pitches
    #include "pitches.h"
    // include the library for the LCD screen
    #include <LiquidCrystal.h>

    // define where the lcd connects to the arduino pins
    const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
    // init the display
    LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
    
    // defines pins numbers
    // trig pin generates the ultrasonic burst
    // echo pin recieves waves after bouncing back
    const int trigPin = 4;
    const int echoPin = 3;

    // defines variables
    long duration;
    int distance;

    //array to hold all the needed notes to make the alarm noise
    int alarm[] = {
      // note scheme = 1, 2, 2, 3, 2, -, 4, 1
       NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
    };

    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int noteDurations[] = {
      4, 8, 8, 4, 4, 4, 4, 4
    };
    
    void setup() {
      //set the columns, rows to display on
      lcd.begin(16,1);
      pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
      pinMode(echoPin, INPUT); // Sets the echoPin as an Input
      Serial.begin(9600); // Starts the serial communication
    }

    
    void loop() {
      //by default, have no tone emitting
      noTone(2);
      
      // Clears the trigPin by setting it to 0
      digitalWrite(trigPin, LOW);
      // set a delay of 2 ms
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds (v = 340 m/s -> .034cm/s)
      duration = pulseIn(echoPin, HIGH);

      // Calculating the distance (time = distance / speed = [d/.034cm/s])
      // solve for distance; distance = time*.034/2 (divide by 2 because the echo pin doubles the sound wave 
      // the echo pin doubles the sound wave because it travels out from the arduino, and then back to the arduino)
      // distance here is in inches (1 cm = 0.393701 inches)
      distance = duration*0.034/2*0.393701;
      // Prints the distance on the Serial Monitor
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" inches");
      Serial.println();

      // print to the LCD screen and add a delay after so it's not overwhelmed
      lcd.clear();
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print("in");
      delay(100);
      
      // If something is detected within 12 inches, start the alarm
      if (distance < 12) {
        // iterate over the notes of the alarm:
        for (int thisNote = 0; thisNote < 8; thisNote++) {

          // to calculate the note duration, take one second
          // divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / noteDurations[thisNote];
          // tone takes in pin #, alarm noise pitch, and duration of note
          tone(2, alarm[thisNote], noteDuration);

          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing:
          noTone(2);
        }
      
      }
    }
