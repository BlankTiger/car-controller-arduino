#include <RH_ASK.h>
#include <SPI.h>

RH_ASK radio;
char msgBuffer[13];

void setup() {
  Serial.begin(9600);
  while (!radio.init()) {
    Serial.println("Radio receiver initialization failed.");
  }
}

void loop() {
  uint8_t buf[13];
  uint8_t buflen = sizeof(buf);
  
  if (radio.recv(buf, &buflen)) {
    Serial.print("Received message: ");
    Serial.println((char*)buf);
  
    processMessage((char*)buf, buflen);
  }
}

void processMessage(char* message, uint8_t length) {
  int xValue, yValue, buttonClicked;
  if (sscanf(message, "$%d:%d:%d#", &xValue, &yValue, &buttonClicked) == 3) {
    Serial.print("X: ");
    Serial.print(xValue);
    Serial.print(" | Y: ");
    Serial.print(yValue);
    Serial.print(" | Button: ");
    Serial.println(buttonClicked);
  } else {
    Serial.println("Invalid message format");
  }
}
