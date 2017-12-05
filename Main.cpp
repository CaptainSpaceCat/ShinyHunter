#include <Servo.h>
#include "Adafruit_TCS34725.h"
#include "BucketList.h"

int numLoops = 0;

//1 - GND
//2 - Color Sensor SDA
//3 - Color Sensor SCL
//4 - 
#define pinAX 5
#define pinBY 6
#define pinUL 7
#define pinDR 8
#define pinStart 9
//10 - 
#define errorLED 11
#define shinyLED 12
#define switchDetector 13

Servo servoAX, servoBY, servoUL, servoDR, servoStart;

BucketList timeBuckets(5, 1.4);

int posAX[] = {105, 36, 178}; //A <-> X
int posBY[] = {90, 30, 155};
int posUL[] = {90, 70, 115};
int posDR[] = {90, 65, 105};
int posStart[] = {90, 55};

const int NUM_MEASUREMENTS = 6;
const bool DEBUG = true;

const int delayDefault = 250;
const int delayScreenTransition = 2500;

#define commonAnode true
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#include "DSButtons.h"
#include "Utility.h"
#include "HuntingLoops.h"

/*
 * Initial setup function run before the main program loop
 * starts the serial monitor, sets up the indicator LEDs, and starts the color sensor
 */
void setup() {
  if (DEBUG) {
    Serial.begin(9600);
  }
  
  
  pinMode(switchDetector, INPUT);
  pinMode(shinyLED, OUTPUT);
  digitalWrite(shinyLED, LOW);
  pinMode(errorLED, OUTPUT);
  digitalWrite(errorLED, LOW);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  resetServos();

/* optional |
            V */
  //switchToTester();
  delay(200);
  

  waitForStart();
  Serial.println("Starting hunt!");
}

/*
 * main program loop, repeatedly executes whatever shiny hunting loop is placed inside
 * additinally, can be configured to output serial data about how many times it has looped
 */
void loop() {
  numLoops++;
  if (DEBUG) {
    Serial.print("Starting Loop: "); Serial.println(numLoops);Serial.println();
  }
  horde_new();
}
