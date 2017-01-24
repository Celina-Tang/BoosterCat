unsigned long time1;
unsigned long time2;

stats newGame(){
  OrbitOledClear();
  OrbitOledMoveTo(0, 10);
  OrbitOledDrawString("Keep your"); 
  OrbitOledMoveTo(0, 20);
  OrbitOledDrawString("Boostercat alive!");
  OrbitOledUpdate();
  delay(1000);
  OrbitOledClear();
  OrbitOledMoveTo(0,10);
  OrbitOledDrawString("Feed, Clean"); 
  OrbitOledMoveTo(0, 20);
  OrbitOledDrawString("and Pet it");
  OrbitOledUpdate();
  delay(1000);
  hunger=false, lonely=false, dirty=false, alive = true;
  stats cat{80,80,80,.total_time = 0};
  return cat;
}

void death(stats cat){
  digitalWrite(RED_LED,LOW);
  digitalWrite(BLUE_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
  // conversion from total_time (measured in millisec) to hour, minute, and second 
  int hour = cat.total_time/3600000;
  int minute = (cat.total_time - hour *(3600000))/60000;
  int second = (cat.total_time - hour*3600000 - minute*60000)/1000;

  // conversion of int's to char for printing later
  char lifespan[12];
  snprintf(lifespan, 12, "%dh %dm %ds", hour, minute, second);

  // Set BoosterCat to be dead
  alive = false;
  OrbitOledClear();
  OrbitOledMoveTo(0,0);
  OrbitOledDrawString("Your cat died of ");
  OrbitOledMoveTo(0,10);
  if (cat.fullness<=0) OrbitOledDrawString("hunger.");
  else if (cat.happiness<=0) OrbitOledDrawString("loneliness.");
  else OrbitOledDrawString("dirtiness.");
  OrbitOledDrawString("(X.X)");
  OrbitOledUpdate();
  delay(3000);

  // print how long the Booster Cat has survived for
  OrbitOledClear();
  OrbitOledMoveTo(0,0);
  OrbitOledDrawString("Your cat");
  OrbitOledMoveTo(0,10);
  OrbitOledDrawString("survived for");
  OrbitOledMoveTo(0,20);
  OrbitOledDrawString(lifespan);
  OrbitOledUpdate();
  delay(3000);
  OrbitOledClear();
}

stats updateStatus(stats cat){
  time2= millis();// check how long it has passed since the last update status
  if ((time2- time1)>= 2000){ // update status once every two sec 
    cat.fullness-=5;
    cat.happiness-=2;
    cat.cleanliness-=7; 
    cat.total_time += time2-time1; // increment total time
    time1 = millis();  
  }
  
  //else if chosen over if statements allows "prioritization of needs"
  //the status that will cause a prompt to notify player about the Booster Cat
  if (cat.fullness<=30){
    hunger = true;
    digitalWrite(RED_LED, HIGH);
    hungry();    
  }else if (cat.happiness<=40){
    lonely = true;
    digitalWrite(BLUE_LED,HIGH);
    sad();
  }else if(cat.cleanliness<=50){
    dirty = true;
    digitalWrite(GREEN_LED,HIGH);
    unclean();
  }
  turnOff();
  // death condition
  if (cat.fullness<=0||cat.happiness<=0||cat.cleanliness<=0) death(cat);
  return cat;
}
//turns off led once the cat is healthy again
void turnOff(){
  if (cat.fullness>30){
    hunger = false;
    digitalWrite(RED_LED,LOW);
  }
  if (cat.happiness>40){
    lonely = false;
    digitalWrite(BLUE_LED,LOW);
  }
  if (cat.cleanliness>50){
    digitalWrite(GREEN_LED,LOW);
    dirty = false;
  }
}

