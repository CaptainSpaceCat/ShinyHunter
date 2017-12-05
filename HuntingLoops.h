//=========================HUNTING LOOPS=========================//
/*
 * repeatedly runs horde encounters
 * assumes you have a pokemon with sweet scent in the third slot in your party
 * your first slot pokemon has no critical ability
 * the target pokemon has no critical ability
 */
void horde_default() {
  x();
  a();
  delay(1600);
  down();
  a();
  down();
  a();
  a();
  delay(8000);
  float startR, startG, startB;
  measureLight(&startR, &startG, &startB);
  delay(10500); //8500 for less laggy, bit of an issue, 9100 for laggier like vulpix
  //10200 for oras
  float endR, endG, endB;
  measureLight(&endR, &endG, &endB);
  if (!detectTransition(startR, startG, startB, endR, endG, endB)) {
    onShinyFound();
  }
  left();
  right();
  a();
  delay(8000); //6500 for lower levels, implement run away pokemon, 8500 for laaag
}

void horde_new() {
  double loopTime = 0;
  double timeTaken;
  x();
  a();
  delay(200);
  //Serial.print("Entering X menu: ");
  timeTaken = getTransition(3000);
  loopTime += timeTaken;
  //Serial.println(timeTaken); //1.15
  down();
  a();
  down();
  a();
  a();
  delay(200);
  //Serial.print("Sweet scent: ");
  timeTaken = getTransition(3000);
  loopTime += timeTaken;
  //Serial.println(timeTaken);
  delay(200);
  //Serial.print("SS animation: ");
  timeTaken = getBlackScreen(8000);
  loopTime += timeTaken;
  //Serial.println(timeTaken);
  delay(200);
  //Serial.print("Shiny measurement: ");
  timeTaken = getTransition(30000, 2, true);
  loopTime += timeTaken;
  Serial.println(timeTaken);
  if (timeBuckets.add(timeTaken)) {
    onShinyFound();
  }
  left();
  right();
  a();
  delay(400);
  //Serial.print("Run fuzzy screen: ");
  timeTaken = getBlackScreen(8000);
  loopTime += timeTaken;
  //Serial.println(timeTaken);
  delay(200);
  //Serial.print("Run black screen: ");
  timeTaken = getTransition(4000);
  loopTime += timeTaken;
  //Serial.println(timeTaken);
  delay(200);
  //Serial.print("Main menu fuzzy: ");
  timeTaken = getTransition(2000, 1);
  loopTime += timeTaken;
  //Serial.println(timeTaken);
  //Serial.print("> Total Loop Time: "); Serial.println(loopTime);
}

/*
 * repeatedly interacts with whatever is in front of it, then runs from the encounter if no shiny is detected
 * assumes you are standing in front of a stationary pookemon who will still be there if you run from the encounter
 * your first slot pokemon has no critical ability
 * the target pokemon has no critical ability
 */
void roam_default() {
  a();
  delay(1500);
  a();
  delay(500);
  float startR, startG, startB;
  measureLight(&startR, &startG, &startB);
  delay(8500); //9000 for latios
  float endR, endG, endB;
  measureLight(&endR, &endG, &endB);
  if (!detectTransition(startR, startG, startB, endR, endG, endB)) {
    onShinyFound();
  }
  left();
  right();
  a();
  delay(6500); // 7000 for latios
  a();
}

/* //IN DEVELOPMENT//
 * repeatedly moves player back and forth until an encounter is detected, will run away from encounter if no shiny detected
 * assumes that the player is in a large enough patch of grass or other pokemon generating area
 * your first slot pokemon has no critical ability
 * the target pokemon has no critical ability
 */
void grass_default() {
  float startR, startG, startB;
  measureLight(&startR, &startG, &startB);
  while(true) {
    left();
    right();
    float endR, endG, endB;
    measureLight(&endR, &endG, &endB);
    if (detectTransition(startR, startG, startB, endR, endG, endB)) {
      break;
    }
  }
  delay(500);
  startR, startG, startB;
  measureLight(&startR, &startG, &startB);
  delay(8500); //9000 for latios
  float endR, endG, endB;
  measureLight(&endR, &endG, &endB);
  if (!detectTransition(startR, startG, startB, endR, endG, endB)) {
    onShinyFound();
  }
  left();
  right();
  a();
  delay(6500); // 7000 for latios
  a();
}

/*
 * repeatedly interacts with whatever is in front of it, then soft resets if no shiny is detected
 * assumes you are standing in front of a hyperspace hole or other pokemon which will not be there if you run from it
 * your first slot pokemon has no critical ability
 * the target pokemon has no critical ability
 * approx 13.84 hrs per shiny
 */
void hyperspace_default() {
  
  a();
  delay(1000);
  a();
  delay(100);
  a();
  delay(100);
  a();
  delay(2000);
  float startR, startG, startB;
  measureLight(&startR, &startG, &startB);
  delay(9750); //8500 for faster
  float endR, endG, endB;
  measureLight(&endR, &endG, &endB);
  if (!detectTransition(startR, startG, startB, endR, endG, endB)) {
    onShinyFound();
  }
  softReset();
  delay(12500);
  a();
  delay(2250);
  a();
  delay(4250);
  a();
  delay(5500);
}

/*
 * repeatedly interacts with whatever is in front of it, then soft resets if no shiny is detected
 * assumes you are standing in front of a hyperspace hole or other pokemon which will not be there if you run from it
 * your first slot pokemon has no critical ability
 * the target pokemon does have a critical ability
 * approx 13.84 hrs per shiny
 */
void hyperspace_ability() {
  a();
  delay(2250);
  a();
  delay(4250);
  a();
  delay(5500);
  a();
  delay(800);
  a();
  delay(75);
  a();
  delay(75);
  a();
  delay(2000);
  float startR, startG, startB;
  measureLight(&startR, &startG, &startB);
  delay(12500);
  float endR, endG, endB;
  measureLight(&endR, &endG, &endB);
  if (!detectTransition(startR, startG, startB, endR, endG, endB)) {
    onShinyFound();
  }
  softReset();
  delay(12500);
}

/*optional helper function that switches the pokemon in slot 1 with the pokemon in slot 2 of your party
 *assumes you have a shiny in slot 2 with the same ability time as your slot 1
 */
void switchToTester() {
  waitForStart();
  a();
  delay(2250);
  a();
  delay(4250);
  a();
  delay(4750);
  x();
  delay(1500);
  a();
  delay(1500);
  a();
  up();
  up();
  a();
  right();
  a();
  b();
  delay(2500);
//  up();
//  a();
//  delay(2000);
//  a();
//  delay(8000);
//  softReset();
  b();
  delay(1500);
}
