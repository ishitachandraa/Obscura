#define TOUCH_SENSOR_PIN 2
#define ENABLE1 5  // PWM-enabled pin for Motor 1
#define ENABLE2 10 // PWM-enabled pin for Motor 2
#define IN1 6
#define IN2 9
#define IN3 7
#define IN4 8
#include <Servo.h>

Servo cardServo;  // Create a Servo object
#define SERVO_PIN 3  // Connect the servo signal pin to Arduino pin 9

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud
  cardServo.attach(SERVO_PIN);  // Attach the servo
  cardServo.write(40);  // Set the servo to its initial position
  pinMode(TOUCH_SENSOR_PIN, INPUT);
  pinMode(ENABLE1, OUTPUT);
  pinMode(ENABLE2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initially, motors are off
  digitalWrite(ENABLE1, LOW);
  digitalWrite(ENABLE2, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();  // Read the incoming serial signal
    if (command == '1') {  // If the signal is '1'
      cardServo.write(160);
      delay(20000) ; // Move the servo to reveal the card
     ;  // Return the servo to the initial position
    }
  }
  if (digitalRead(TOUCH_SENSOR_PIN) == HIGH) {
    // Enable Motor 1 at one-fourth speed (64 out of 255 PWM duty cycle)
    analogWrite(ENABLE1, 100);

    // Enable Motor 2 at full speed
    analogWrite(ENABLE2, 100); // Set Motor 2 to full speed
    // Set motor directions (arbitrary for running the motors)
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    // Keep motors running for 5 seconds
    delay(15000);

    // Turn motors off
    digitalWrite(ENABLE1, LOW);
    digitalWrite(ENABLE2, LOW);
  }
}
