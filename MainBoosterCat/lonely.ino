//alerts player that the cat is hungry.
void sad(){
  if (counter==0){
    OrbitOledClear();
    OrbitOledMoveTo(0,10);
    OrbitOledDrawString("Your BoosterCat"); 
    OrbitOledMoveTo(0,20);
    OrbitOledDrawString("is lonely.");
    OrbitOledUpdate();
    delay(1000);
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledDrawString("Go to Menu");
    OrbitOledMoveTo(0,10);
    OrbitOledDrawString("and pet it");
    OrbitOledUpdate();
    delay(1000);
  } 
  counter++;
}

//uses temperature sensor to check if the player is "petting" the sensor.
stats pet(stats cat){  
  int16_t temp=0;
  OrbitOledClear();
  OrbitOledMoveTo(0,0);
  OrbitOledDrawString("Put your finger");
  OrbitOledMoveTo(0,10);
  OrbitOledDrawString("on sensor.");
  OrbitOledUpdate();
  delay(3000);
  TWire.beginTransmission(0x4F);//address for temperature sensor 0x4F= 1001111
  TWire.write(0x0);
  TWire.endTransmission(false);  
  TWire.requestFrom(0x4F, 2);
  int buffer[2];
  for (int i=0; i<2; i++){
    while (!TWire.available());
    buffer[i]=TWire.read();
  }
  //the reading is formatted in 2's complement
  // bitwise or concatenates the two bytes
  //the left shift by 8 : *2^8 (since MSB comes first)
  //right shift by 4: *2^-4;
  temp=((buffer[0]<<8)|buffer[1])>>4;
  if (temp/16>27){ //takes a while for temperature of body to pass onto sensor. 30 degrees is the reasonable number 
    if (cat.happiness<70) {
      cat.happiness += 30;
      OrbitOledClear();
      OrbitOledMoveTo(0,0);
      OrbitOledDrawString("Your BoosterCat");
      OrbitOledMoveTo(0,10);
      OrbitOledDrawString("is less lonely.");
      OrbitOledUpdate();
    }else{
      cat.happiness=100;
      OrbitOledClear();
      OrbitOledMoveTo(0,0);
      OrbitOledDrawString("Your BoosterCat");
      OrbitOledMoveTo(0,10);
      OrbitOledDrawString("is happy.");
      OrbitOledUpdate();
    }  
  }else{
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledDrawString("Try again");
    OrbitOledUpdate();
  }
  turnOff();
  delay(500);
  counter=0;
  menu_init=0;
  return cat;
}
