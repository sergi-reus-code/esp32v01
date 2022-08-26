#include <Arduino.h>
#include <stdio.h>


#include "esp32-hal-log.h"


#include "config.h"

static const char *TAG = "DEEP SLEEP";





void setup()
{
  Serial.begin(115200);
ESP_LOGI(TAG, "Init");
}

void loop()
{
}