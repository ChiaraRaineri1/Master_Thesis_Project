// Pin definitions
const int upPin = 5;    // button to move motor forward (white)
const int downPin = 6;  // button to move motor backward (green)
const int stopPin = 7;  // emergency stop button (red)
const int stepPin = 2;  // step pin for the motor
const int dirPin = 3;   // direction pin for the motor

void setup() {
  pinMode(upPin, INPUT_PULLUP);    // set buttons as inputs with pullup resistors
  pinMode(downPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(stepPin, OUTPUT);        // motor control pins as outputs
  pinMode(dirPin, OUTPUT);
}

void loop() {
  if((digitalRead(upPin)==HIGH && digitalRead(downPin)==HIGH && digitalRead(stopPin)==HIGH)) {
    Serial.println("press a button to operate");
  }

  // forward (white) button pressed? --> clip has to reach the needle
  else if(digitalRead(upPin)==LOW && digitalRead(downPin)==HIGH) {        
    digitalWrite(dirPin, LOW);          // enables motor to move in forward direction
    for (int x = 0; x < 3000; x++) {    // moves 3000 steps == 30 mm == 3 cm
      // emergency stop --> has highest priority
      if(digitalRead(stopPin)==LOW) {
        digitalWrite(stepPin, LOW);     // no motions
        return;                         // exits the loop to prevent any other motor commands
      }
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(5000);          // for 5 ms
      digitalWrite(stepPin, LOW);      
      delayMicroseconds(5000);          // for 5 ms --> total velocity = 1 mm/s
    }
  }

// backward (green) button pressed? --> needle extraction
  else if(digitalRead(downPin)==LOW && digitalRead(upPin)==HIGH) { 
    digitalWrite(dirPin, HIGH);         // enables motor to move in backward direction
    for (int x = 0; x < 3000; x++) {    // moves 3000 steps == 30 mm == 3 cm
      // emergency stop --> has highest priority
      if(digitalRead(stopPin)==LOW) {
        digitalWrite(stepPin, LOW);     // no motions
        return;                         // exits the loop to prevent any other motor commands
      }
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(10000);          // for 10 ms
      digitalWrite(stepPin, LOW);      
      delayMicroseconds(10000);          // for 10 ms --> total velocity = 0.5 mm/s
    }
  }
} 

