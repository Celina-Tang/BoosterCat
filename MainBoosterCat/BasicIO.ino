// Basic I/O reading and writing 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LEFT_BUTTON  PF_4
#define RIGHT_BUTTON  PF_0
#define UP_BUTTON PE_0
#define DOWN_BUTTON PD_2
#define MENU 9

void buttonsInit(){
  pinMode(LEFT_BUTTON, INPUT_PULLUP); 
  pinMode(RIGHT_BUTTON, INPUT_PULLUP); 
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
  pinMode(MENU, INPUT);
  // define LED as an Output
  pinMode(RED_LED, OUTPUT); 
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
 }
void readButtons(){
  LButtonState = digitalRead(LEFT_BUTTON);
  RButtonState = digitalRead(RIGHT_BUTTON);
  UButtonState = digitalRead(UP_BUTTON);
  DButtonState = digitalRead(DOWN_BUTTON);
  MButtonState = digitalRead(MENU);
}
