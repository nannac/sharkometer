#include <SPIMemory.h>

#define DEBUG true

SPIFlash flash;

long flashAddr = 0;

void setup() {
  
  Serial.begin(115200);
  while (!Serial);

  flash.begin();
  flash.eraseChip();
}

void loop() {
  
  struct dataStruct 
  {
    uint64_t timeElapsed = timeElapsed();
    uint8_t sensorValue; = readSensor();
  };

  flash.writeAnything(_addr, dataStruct))

  _addr = _addr + sizeof(dataStruct);
  
}

int timeElapsed()
{
  millis();
}

int readSensor()
{
  return rand()
}

void printAllPages()
{
  uint_8 data_buffer[256];
  uint32_t maxAddr = flash.getCapacity();
  for (int addr = 0; addr < maxAddr; addr++)
  {
    flash.readByteArray(addr, &data_buffer[0], 256);
    Serial.print(data_buffer);
    delay(100);
  }
}
