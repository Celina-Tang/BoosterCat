// BoosterCat Hungry Status Occurance 

// prompt the player that the Booster Cat is hungry; displaying on the LCD screen
void hungry(){
  if (counter==0){
    OrbitOledClear();
    OrbitOledMoveTo(0,10);
    OrbitOledDrawString("Your BoosterCat"); 
    OrbitOledMoveTo(0,20);
    OrbitOledDrawString("is hungry.");
    OrbitOledUpdate();
    delay(1000);
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledDrawString("Go to Menu");
    OrbitOledMoveTo(0,10);
    OrbitOledDrawString("and feed it");
    OrbitOledUpdate();
    delay(1000);
  } 
  counter++;
}


// The player select the feed function; increase fullness of the Booster Cat
stats feed(stats cat){
  if (cat.fullness>=70){
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledDrawString("Your Boostercat"); 
    OrbitOledMoveTo(0,10);
    OrbitOledDrawString("is full.");
    OrbitOledUpdate();    
    cat.fullness=100;
  }else{
    cat.fullness += 30;  
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledDrawString("Your BoosterCat");
    OrbitOledMoveTo(0,10);
    OrbitOledDrawString("ate some food.");
    OrbitOledUpdate();
  }    
  turnOff();
  delay(500);
  counter = 0; 
  menu_init=0; // return to menu
  return cat;
}

