//=========================UTILITY=========================//
/*
 * utility function that pauses the program until a physical button is pressed on the circuit
 */
void waitForStart() {
  while (digitalRead(switchDetector) != HIGH) {}
}

/*
 * helper function that takes in 2 light measurements, containing 3 values each, and compares them
 * returns true if at least two of the three components of each measurement are 10% different or more
 */
bool detectTransition(float r, float g, float b, float _r, float _g, float _b, int numValues = 2) {
  //Serial.println();
  float diffR = abs(r-_r)/((r+_r)/2);
  float diffG = abs(g-_g)/((g+_g)/2);
  float diffB = abs(b-_b)/((b+_b)/2);
  int total = 0;
  if (diffR >= .1) {total++;}
  if (diffG >= .1) {total++;}
  if (diffB >= .1) {total++;}
  return total >= numValues;
}

/*
 * Small helper function that makes sure the measured values from the color sensor
 * are not NaN or inf
 */
double validateValue(double v) {
    if (v != v || v == INFINITY) {v = 0;}
    return v;
}

/*
 * this function prints out an error message based on an input string,
 * and sets the red error LED to light up
 * outputs the loop in which the error was detected
 */
void throwError(String message = "") {
  digitalWrite(errorLED, HIGH);
  digitalWrite(shinyLED, HIGH);
  if (DEBUG) {
    Serial.print("Error: "); Serial.println(message); Serial.print("Loop: "); Serial.println(numLoops); Serial.println();
  }
  while(1);
}

/*
 * helper function that takes measurements every 60 microseconds
 * stops once the new measurements go over a certain threshold from the original measurements
 * returns how long it took since the original measurement took place
 * 
 * can also be used to simply pause the program until a screen transition is detected
 * 
 * //NOTE: use of this function could potentially break the loop if it has even a slight chance of failure
 * seeing as the loop needs to be executed hundreds, if not thousands, of times with no outside intervention
 */
double getTransition(int maxDelay = -1, int numValues = 2, bool error = false) {
  float _r, _g, _b;
  bool first = true;
  unsigned long initialTime = micros();
  while (true) {
    uint16_t clr, red, green, blue;
    tcs.setInterrupt(false);      // turn on LED
    delay(60);  // takes 50ms to read
    if (maxDelay != -1) {
      maxDelay -= 60;
    }
    tcs.getRawData(&red, &green, &blue, &clr);
    tcs.setInterrupt(true);  // turn off LED
    float r, g, b;
    uint32_t sum = clr;
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;

    r = validateValue(r);
    g = validateValue(g);
    b = validateValue(b);
    
    if (!first) {
      //Serial.print("r:"); Serial.print(r); Serial.print(" g:"); Serial.print(g); Serial.print(" b:"); Serial.print(b);
      if (detectTransition(r, g, b, _r, _g, _b, numValues)) {
        break;
      }
    } else {
      _r = r, _g = g, _b = b;
      //Serial.print("Base r: "); Serial.print(_r); Serial.print(" Base g: "); Serial.print(_g); Serial.print(" Base b: "); Serial.print(_b);
      first = false;
    }
    if (maxDelay < -1) {
      if (error) {
        throwError("Maximum time exceeded");
      }
      break;
    }
    //Serial.println();
  }
  unsigned long finalTime = micros();
  return (double)(finalTime - initialTime)/1000000.0;
}

/*
 * helper function that takes measurements every 60 microseconds
 * stops once it detects a completely black screen
 * returns how long it took since the original measurement took place
 * 
 * can also be used to simply pause the program until a black screen is detected
 * 
 * //NOTE: use of this function could potentially break the loop if it has even a slight chance of failure
 * seeing as the loop needs to be executed hundreds, if not thousands, of times with no outside intervention
 */
double getBlackScreen(int maxDelay = -1, bool error = false) {
  float _r, _g, _b;
  bool first = true;
  unsigned long initialTime = micros();
  while (true) {
    uint16_t clr, red, green, blue;
    tcs.setInterrupt(false);      // turn on LED
    delay(60);  // takes 50ms to read
    if (maxDelay != -1) {
      maxDelay -= 60;
    }
    tcs.getRawData(&red, &green, &blue, &clr);
    tcs.setInterrupt(true);  // turn off LED
    float r, g, b;
    uint32_t sum = clr;
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;

    r = validateValue(r);
    g = validateValue(g);
    b = validateValue(b);
    
    if (!first) {
      //Serial.print("r:"); Serial.print(r); Serial.print(" g:"); Serial.print(g); Serial.print(" b:"); Serial.print(b);
      if (r == 0 && g == 0 && b == 0) {
        break;
      }
    } else {
      _r = r, _g = g, _b = b;
      //Serial.print("Base r: "); Serial.print(_r); Serial.print(" Base g: "); Serial.print(_g); Serial.print(" Base b: "); Serial.print(_b);
      first = false;
    }
    if (maxDelay < -1) {
      if (error) {
        throwError("Maximum time exceeded");
      }
      break;
    }
    //Serial.println();
  }
  unsigned long finalTime = micros();
  return (double)(finalTime - initialTime)/1000000.0;
}

/*
 * this function accepts pointers to three float values
 * the function takes 60 milliseconds to measure light from the color sensor,
 * and uses the three passed float values to record the average for the red, green, and blue components of the measurement
 */
void measureLight(float *totalR, float *totalG, float *totalB) {
  *totalR = 0;
  *totalG = 0;
  *totalB = 0;
  for (int i = 0; i < NUM_MEASUREMENTS; i++) {
    uint16_t clr, red, green, blue;
    tcs.setInterrupt(false);      // turn on LED
    delay(60);  // takes 50ms to read
    tcs.getRawData(&red, &green, &blue, &clr);
    tcs.setInterrupt(true);  // turn off LED
    float r, g, b;
    uint32_t sum = clr;
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;

    r = validateValue(r);
    g = validateValue(g);
    b = validateValue(b);
    
    *totalR += r;
    *totalG += g;
    *totalB += b;

    if (DEBUG) {
      Serial.print("R: "); Serial.print(r); Serial.print(" G: ");Serial.print(g); Serial.print(" B: "); Serial.print(b); Serial.println();
    }
  }
  *totalR /= NUM_MEASUREMENTS;
  *totalG /= NUM_MEASUREMENTS;
  *totalB /= NUM_MEASUREMENTS;

  if (DEBUG) {
      Serial.print("AvgR: "); Serial.print(*totalR); Serial.print(" AvgG: ");Serial.print(*totalG); Serial.print(" AvgB: "); Serial.print(*totalB); Serial.println();
  }
}

/*
 * this utility function simply sends a few pulses to all of the servos, putting them in their initial positions,
 * before detatching them and sending no more unneeded pulses
 */
void resetServos() {
  servoAX.attach(pinAX);
  servoBY.attach(pinBY);
  servoUL.attach(pinUL);
  servoDR.attach(pinDR);
  servoStart.attach(pinStart);

  servoAX.write(posAX[0]);
  servoBY.write(posBY[0]);
  servoUL.write(posUL[0]);
  servoDR.write(posDR[0]);
  servoStart.write(posStart[0]);

  delay(250);

  servoAX.detach();
  servoBY.detach();
  servoUL.detach();
  servoDR.detach();
  servoStart.detach();
}

/*
 * this function executes whenever the program thinks it has found a shiny pokemon
 * sets the blue shiny indicator LED to light up
 * outputs the loop in which the shiny was detected
 */
void onShinyFound() {
  digitalWrite(shinyLED, HIGH);
  if (DEBUG) {
    Serial.println("Shiny Found!"); Serial.print("Loop: "); Serial.println(numLoops);Serial.println();
  }
  while(1);
}

