#include <SPI.h>
#include <Ethernet.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main   
  
  
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
  } else{
    Serial.println("WHOOOOOOOOP");
  }
  delay(100);
}
