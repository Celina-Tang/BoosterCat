# include <Wire.h>

static TwoWire orbitWire(0); //used for accelerometer
static TwoWire TWire(0); //used for temperature

void WireInit(){
  orbitWire.begin();
  TWire.begin();
}

void WireWriteByte(int address,uint8_t value){
  orbitWire.beginTransmission(address);
  orbitWire.write(value);
  orbitWire.endTransmission();
}

void WireWriteRegister(int address, uint8_t reg, uint8_t value){
  orbitWire.beginTransmission(address);
  orbitWire.write(reg);
  orbitWire.write(value);
  orbitWire.endTransmission();
}

void WireRequestArray(int address, uint8_t* buffer, uint8_t amount){
  orbitWire.requestFrom(address, amount);
  do {
    while(!orbitWire.available());
    *(buffer++) = orbitWire.read();
  }while(--amount >0);
}

