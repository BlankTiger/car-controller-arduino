#include <RH_ASK.h>
#include <SPI.h>

RH_ASK radio;
char msgBuffer[50];

int sensorX = A0;
int xValue = 0;
char xBuffer[4];

int sensorY = A1;
int yValue = 0;
char yBuffer[4];

int button = 7;
int buttonClicked = 0;

void setup() {
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  Serial.begin(9600);
  while (!radio.init()) {
    Serial.println("Radio transmitter initialization failed.");
  }
}

void loop() {
  // X: middle around 511 or 512
  xValue = analogRead(sensorX);
  // Y: middle around 513 or 514
  yValue = analogRead(sensorY);
  // Button: 0 if clicked, 1 if not clicked
  buttonClicked = digitalRead(button);

  // printJoystickInfo();
  sendInstructions();
}

void printJoystickInfo() {
  sprintf(msgBuffer, "X: %d | Y: %d | Button: %d", xValue, yValue, buttonClicked);
  Serial.println(msgBuffer);
}

void sendInstructions() {
  formatValue(xValue, xBuffer);
  formatValue(yValue, yBuffer);

  sprintf(msgBuffer, "$%s:%s:%d#", xBuffer, yBuffer, buttonClicked);
  Serial.print("Sending msg: ");
  Serial.println(msgBuffer);

  radio.send((uint8_t*)msgBuffer, strlen(msgBuffer));
  radio.waitPacketSent();
}

void formatValue(int value, char* buffer) {
  if (value > 999) {
    sprintf(buffer, "%d", value);
  } else if (value > 99) {
    sprintf(buffer, "0%d", value);
  } else if (value > 9) {
    sprintf(buffer, "00%d", value);
  } else {
    sprintf(buffer, "000%d", value);
  }
}
