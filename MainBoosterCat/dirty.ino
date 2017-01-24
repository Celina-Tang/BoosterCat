// BoosterCat Dirty Status Occurance 

// setups for communicating with I2C accelerometer 
void WireRequestArray(int address, uint8_t* buffer, uint8_t amount);
void WireWriteRegister(int address, uint8_t reg, uint8_t value);
void WireWriteByte(int address, uint8_t value);

// Needed Register Maps
static uint8_t const acc = 0x1D;
static uint8_t const Power_Ctl = 0x2d;
static uint8_t const Data_Format = 0x31; //set range for data; D1 = 1, D0 = 0 to be 8g/ D1 =0, D0 = 1 to be 4g
static uint8_t const Read = 0x32; // x-Axis Data 0
static uint8_t const Thresh_Act = 0x24; // Threshold for detecting activity
static uint8_t const Thresh_Inact = 0x25; // Threshold for detecting inactivity
static uint8_t const Act_Inact = 0x27; //Activity/Inactivity Control
static uint8_t const Event_Set = 0x2E; // Enable interruption
static uint8_t const Event_Read = 0x30; // read if interrupted


// prompt the player that the Booster Cat is unclean; displaying on the LCD screen
void unclean(){
  if (counter==0){
    OrbitOledClear();
    OrbitOledMoveTo(0,10);
    OrbitOledDrawString("Your BoosterCat"); 
    OrbitOledMoveTo(0,20);
    OrbitOledDrawString("is dirty.");
    OrbitOledUpdate();
    delay(2000);
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledDrawString("Go to Menu");
    OrbitOledMoveTo(0,10);
    OrbitOledDrawString("and clean it");
    OrbitOledUpdate();
    delay(2000);
  } 
  counter++; // counter implemented so that there is no continuous prompt about the same occurance 
}


// The player select the clean function; increase cleanliness of the Booster Cat
stats clean(stats cat){
  unsigned long time_before = millis();
  unsigned long time_after = millis();

  int before = cat.cleanliness;

  // Give instruction to the player
  OrbitOledClear();
  OrbitOledMoveTo(0,10);
  OrbitOledDrawString("Shake screen"); 
  OrbitOledMoveTo(0,20);
  OrbitOledDrawString("to clean");
  OrbitOledUpdate();
  
  // setup accelecerometer settings
  // set range of data 
  WireWriteRegister(acc, Data_Format, 1); //set the range of measured acc to +/-4g
  WireWriteRegister(acc, Act_Inact, 0x70); // set to dc-coupled operation
  WireWriteRegister(acc, Thresh_Act, 65); //if the measured value is greater than the theshold value, then it is active
  WireWriteRegister(acc, Event_Set, 0x10);


  size_t const num_bytes = 5;
  uint8_t shake[num_bytes]={0};

  // wake up the accelerometer, then start measuring
  WireWriteRegister(acc, Power_Ctl, 1 << 3); 
  delay(300);

  // Accelerometer aquires data while no interrupt signal (for activation) is sent and while three seconds have not passed
  while(shake[3] == 0 && (time_after-time_before) <= 3000){
    time_after = millis();

    // Obtain interrupt signal for activation
    WireWriteByte(acc, 0x30);
    WireRequestArray(acc, shake, num_bytes);
    delay(100);
  }

  // if an interrupt signal for activation detected, then increase cleanliness
  if (shake[3]){
    if (cat.cleanliness > 70){
      cat.cleanliness=100;
      OrbitOledClear();
      OrbitOledMoveTo(0,0);
      OrbitOledDrawString("Your cat is");
      OrbitOledMoveTo(0,10);
      OrbitOledDrawString("clean.");
      OrbitOledUpdate();
      delay(2000);
    }else {
      cat.cleanliness += 30;
      OrbitOledClear();
      OrbitOledMoveTo(0,0);
      OrbitOledDrawString("Your BoosterCat");
      OrbitOledMoveTo(0,10);
      OrbitOledDrawString("is a bit cleaner.");
      OrbitOledUpdate();
      delay(2000);
    }    
  }else { // If nothing happened, info user
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledDrawString("Try Again");
    OrbitOledUpdate();
    delay(2000);
  }
  turnOff();
  counter = 0; // set counter 0 for new prompts
  menu_init = 0; // return to menu
  return cat;
}

  

