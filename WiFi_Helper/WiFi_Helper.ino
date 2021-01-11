#include "wifi_helper_main.h"


void setup()
{
  Serial.begin(115200);
  mainSetup();
}

void loop()
{
  mainLoop();
}
