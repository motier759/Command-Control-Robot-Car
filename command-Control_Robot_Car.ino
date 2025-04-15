// Pin definitions for motor control and lights
#define in1 5          // Motor 1 forward
#define in2 6          // Motor 1 backward
#define in3 10         // Motor 2 forward
#define in4 11         // Motor 2 backward
#define frontLight 12  // Front light
#define backLight 13   // Back light

// Variables for controlling the robot
int command;           // Holds the serial command received
int Speed = 204;       // Default motor speed (PWM value)
int Speedsec;          // Secondary speed for turning
int buttonState = 0;   // Current state of the button
int lastButtonState = 0; // Previous state of the button
int Turnradius = 0;    // Turning radius (secondary speed)
int brakeTime = 45;    // Time for the brake to stay active (in milliseconds)
int brkonoff = 1;      // Brake on/off flag (1 for ON, 0 for OFF)

void setup() {
  // Set motor pins and light pins as OUTPUT
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(frontLight, OUTPUT); 
  pinMode(backLight, OUTPUT); 

  // Start serial communication for receiving commands
  Serial.begin(9600); 
}

void loop() {
  // Check if a command has been received via serial
  if (Serial.available() > 0) {
    command = Serial.read();  // Read the incoming command
    Stop();  // Stop motors before executing any new command

    // Process the received command using a switch statement
    switch (command) {
      case 'F': forward(); break;       // Move forward
      case 'B': back(); break;          // Move backward
      case 'L': left(); break;          // Turn left
      case 'R': right(); break;         // Turn right
      case 'G': forwardleft(); break;   // Move forward left
      case 'I': forwardright(); break;  // Move forward right
      case 'H': backleft(); break;      // Move backward left
      case 'J': backright(); break;     // Move backward right
      case '0': Speed = 100; break;     // Set speed level 0
      case '1': Speed = 140; break;     // Set speed level 1
      case '2': Speed = 153; break;     // Set speed level 2
      case '3': Speed = 165; break;     // Set speed level 3
      case '4': Speed = 178; break;     // Set speed level 4
      case '5': Speed = 191; break;     // Set speed level 5
      case '6': Speed = 204; break;     // Set speed level 6
      case '7': Speed = 216; break;     // Set speed level 7
      case '8': Speed = 229; break;     // Set speed level 8
      case '9': Speed = 242; break;     // Set speed level 9
      case 'q': Speed = 255; break;     // Maximum speed
    }

    Speedsec = Turnradius;  // Set secondary speed for turning

    // Handle braking system
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }
}

// Function to move forward
void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
  digitalWrite(frontLight, HIGH);  // Turn on the front light
  digitalWrite(backLight, LOW);   // Turn off the back light
}

// Function to move backward
void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
  digitalWrite(frontLight, LOW);  // Turn off the front light
  digitalWrite(backLight, HIGH); // Turn on the back light
}

// Function to turn left
void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
  digitalWrite(frontLight, HIGH);  // Turn on the front light
  digitalWrite(backLight, LOW);   // Turn off the back light
}

// Function to turn right
void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
  digitalWrite(frontLight, HIGH);  // Turn on the front light
  digitalWrite(backLight, LOW);   // Turn off the back light
}

// Function to move forward left
void forwardleft() {
  analogWrite(in1, Speedsec);
  analogWrite(in3, Speed);
  digitalWrite(frontLight, HIGH);  // Turn on the front light
  digitalWrite(backLight, LOW);   // Turn off the back light
}

// Function to move forward right
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speedsec);
  digitalWrite(frontLight, HIGH);  // Turn on the front light
  digitalWrite(backLight, LOW);   // Turn off the back light
}

// Function to move backward right
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speedsec);
  digitalWrite(frontLight, LOW);  // Turn off the front light
  digitalWrite(backLight, HIGH); // Turn on the back light
}

// Function to move backward left
void backleft() {
  analogWrite(in2, Speedsec);
  analogWrite(in4, Speed);
  digitalWrite(frontLight, LOW);  // Turn off the front light
  digitalWrite(backLight, HIGH); // Turn on the back light
}

// Function to stop all motors
void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
  digitalWrite(frontLight, LOW);  // Turn off the front light
  digitalWrite(backLight, LOW);  // Turn off the back light
}

// Function to activate the brake
void brakeOn() {
  buttonState = command;  // Update the button state
  if (buttonState != lastButtonState) { // Check if the button state has changed
    if (buttonState == 'S') { // Brake command received
      if (lastButtonState != buttonState) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime); // Wait for brake time duration
        Stop(); // Stop the motors
      }
    }
    lastButtonState = buttonState; // Update last button state
  }
}

// Function to deactivate the brake
void brakeOff() {
  // Placeholder for brake off functionality (currently empty)
}