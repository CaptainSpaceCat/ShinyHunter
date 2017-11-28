/*
 * helper function that accepts a Servo object, a pin connected to that servo,
 * a position to move to, and a time in microseconds to wait while the servo turns
 * 
 * the function attaches the Servo object to the specified pin, sets it to the specified position,
 * waits for the delay time, then detaches the pin from the Servo object so as to avoid
 * sending a constant stream of pulses to the somewhat delicate servos
 */
void writeServo(Servo servo, int pin, int pos, int dTime = 250) {
  servo.attach(pin);
  servo.write(pos);
  delay(dTime);
  servo.detach();
}

/*
 * the next 9 functions press the ds buttons as noted by the function names
 */
//=========================ABXY=========================//
void b() {
  writeServo(servoBY, pinBY, posBY[2]);
  writeServo(servoBY, pinBY, posBY[0]);
}

void y() {
  writeServo(servoBY, pinBY, posBY[1]);
  writeServo(servoBY, pinBY, posBY[0]);
}

void x() {
  writeServo(servoAX, pinAX, posAX[2]);
  writeServo(servoAX, pinAX, posAX[0]);
}

void a() {
  writeServo(servoAX, pinAX, posAX[1]);
  writeServo(servoAX, pinAX, posAX[0]);
}

//=========================D PAD=========================//
void left() {
  writeServo(servoUL, pinUL, posUL[2]);
  writeServo(servoUL, pinUL, posUL[0]);
}

void down() {
  writeServo(servoDR, pinDR, posDR[1]);
  writeServo(servoDR, pinDR, posDR[0]);
}

void right() {
  writeServo(servoDR, pinDR, posDR[2]);
  writeServo(servoDR, pinDR, posDR[0]);
}

void up() {
  writeServo(servoUL, pinUL, posUL[1]);
  writeServo(servoUL, pinUL, posUL[0]);
}

//=========================START MENU=========================//
/*
 * pushes the start button on the ds to soft reset 
 * assumes that the L and R buttons are being constantly held down
 */
void softReset() {
  writeServo(servoStart, pinStart, posStart[1]);
  writeServo(servoStart, pinStart, posStart[0]);
}
