#include <Arduino.h>

#include "SDCard.h"















void setup(){

  Serial.begin(115200);

new SDCard("/fs", GPIO_NUM_19, GPIO_NUM_23, GPIO_NUM_18, GPIO_NUM_5);

  
}

void loop(){
  //This will never be reached
}
