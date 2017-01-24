#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Orbit OLED library
#include <delay.h>
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>

typedef struct{
  int fullness, happiness, cleanliness;
  unsigned long total_time;
}stats;

//global variables
stats cat={100000,100000,100000};
bool hunger, lonely, dirty, alive;
int LButtonState=0, RButtonState=0, UButtonState=0, DButtonState=0, MButtonState=0; //tells whether the button has been pressed.
int counter=0;
int menu_init=0;
int UI_x = 5;

void setup() {
  WireInit();
  buttonsInit();  
  alive = false;
  OrbitOledInit();
}

void loop() {
  readButtons();
  if (!alive){
    // Ask player if they want to make a new game:
    OrbitOledMoveTo(30, 5);
    OrbitOledDrawString("New game?");
    OrbitOledMoveTo(0,20);
    OrbitOledDrawChar('Y');
    OrbitOledMoveTo(120,20);
    OrbitOledDrawChar('N'); 
    OrbitOledUpdate(); 
    if (LButtonState == LOW) cat = newGame();
    if (RButtonState == LOW){
      OrbitOledClear();
      OrbitOledMoveTo(0,0);
      OrbitOledDrawString("Are you paw-");
      OrbitOledMoveTo(0,10);
      OrbitOledDrawString("sitive?");
      OrbitOledUpdate();
      delay(2000);
      OrbitOledClear();  
    }
  }else {
    if (MButtonState == HIGH) { // while in menu, no other events are happening
      cat = menu(cat);           
    }
    else {
      moveCat(cat);
      cat = updateStatus(cat);
      menu_init = 0; 
    }
  } 
}

