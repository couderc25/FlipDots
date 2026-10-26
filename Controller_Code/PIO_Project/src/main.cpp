#include <Arduino.h>

// put function declarations here:
void dotFlip(int row, int column, int flipDelay =100, int writeDelay = 15);
void buttonInterrupt();


const int r1hPin = 13;
const int r1lPin = 12;
const int r2hPin = 14;
const int r2lPin = 27;
const int c1hPin = 26;
const int c1lPin = 25;
const int c2hPin = 33;
const int c2lPin = 32;
const int buttonPin  = 23;
volatile bool buttonPressed = false;

int flipSpeed = 100;
int speedIndex = 0;

volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200; // Ignore presses within 200ms of each other


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(r1hPin, OUTPUT);
  pinMode(r1lPin, OUTPUT);
  pinMode(r2hPin, OUTPUT);
  pinMode(r2lPin, OUTPUT);
  pinMode(c1hPin, OUTPUT);
  pinMode(c1lPin, OUTPUT);
  pinMode(c2hPin, OUTPUT);
  pinMode(c2lPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on
  // delay(1000);                       // Wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // Turn the LED off
  // delay(1000);                       // Wait for a second
  if (buttonPressed){
    buttonPressed = false;

    speedIndex = (speedIndex + 1) % 3;

    if (speedIndex == 0){
    flipSpeed = 100;
    }else if(speedIndex == 1){
      flipSpeed = 500;
    }else if (speedIndex ==2) {
      flipSpeed = 25;
    }
  }
  // Row1 Col1 ON
  dotFlip(r1hPin,c1lPin, flipSpeed);
  // Row2 Col1 ON
  dotFlip(r2hPin,c1lPin, flipSpeed);
   // Row1 Col2 ON
  dotFlip(r1hPin,c2lPin, flipSpeed);
  // Row2 Col2 ON
  dotFlip(r2hPin,c2lPin, flipSpeed);
  // Row1 Col1 OFF
  dotFlip(r1lPin,c1hPin, flipSpeed);
  // Row2 Col1 OFF
  dotFlip(r2lPin,c1hPin, flipSpeed);
  // Row1 Col2 OFF
  dotFlip(r1lPin,c2hPin, flipSpeed);
  // Row2 Col2 OFF
  dotFlip(r2lPin,c2hPin, flipSpeed);
 
}

// put function definitions here:

void dotFlip(int row, int column, int flipDelay, int writeDelay){
  // Row1 Col1 ON
  digitalWrite(row, HIGH);
  digitalWrite(column, HIGH);
  delay(writeDelay);
  digitalWrite(row, LOW);
  digitalWrite(column, LOW);
  delay(flipDelay);
}

void IRAM_ATTR buttonInterrupt() {
  unsigned long currentTime = millis();
  
  // Only register the press if enough time has passed since the last one
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    buttonPressed = true;
    lastDebounceTime = currentTime;
  }
}