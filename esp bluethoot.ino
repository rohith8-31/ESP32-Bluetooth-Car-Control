#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>

// Right Motor Pins (L298N ENA, IN1, IN2)
int enableRightMotor = 22;   // D22 -> ENA
int rightMotorPin1   = 26;   // D26 -> IN1
int rightMotorPin2   = 27;   // D27 -> IN2

// Left Motor Pins (L298N ENB, IN3, IN4)
int enableLeftMotor  = 23;   // D23 -> ENB
int leftMotorPin1    = 18;   // D18 -> IN3
int leftMotorPin2    = 19;   // D19 -> IN4

// Maximum Motor Speed
#define MAX_MOTOR_SPEED 255

// PWM Configuration
const int PWMFreq = 1000;       // 1 kHz
const int PWMResolution = 8;    // 8-bit (0-255)

// Motor Rotation Function
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  // Right Motor Direction
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }
  else
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Left Motor Direction
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }
  else
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  // PWM Speed Control (ESP32 Arduino Core 3.x)
  ledcWrite(enableRightMotor, abs(rightMotorSpeed));
  ledcWrite(enableLeftMotor, abs(leftMotorSpeed));
}

// Configure Pin Modes
void setUpPinModes()
{
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  // Attach PWM to the enable pins (this also sets them as outputs)
  ledcAttach(enableRightMotor, PWMFreq, PWMResolution);
  ledcAttach(enableLeftMotor, PWMFreq, PWMResolution);

  // Stop motors initially
  rotateMotor(0, 0);
}

void setup()
{
  setUpPinModes();

  // Initialize Bluetooth
  Dabble.begin("MyBluetoothCar");
}

void loop()
{
  int rightMotorSpeed = 0;
  int leftMotorSpeed = 0;

  // Read gamepad input
  Dabble.processInput();

  // Forward
  if (GamePad.isUpPressed())
  {
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }

  // Backward
  if (GamePad.isDownPressed())
  {
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }

  // Turn Left
  if (GamePad.isLeftPressed())
  {
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }

  // Turn Right
  if (GamePad.isRightPressed())
  {
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }

  // Apply motor speed and direction
  rotateMotor(rightMotorSpeed, leftMotorSpeed);
}
