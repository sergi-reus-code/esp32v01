#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "class/ledsClass.h"




void ledsTask(void *params)
{
  //Creamos el objeto leds
  ledsClass *ledsObject = new ledsClass();
 
  uint state;
  while (true)
  {

    
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    //printf("received state %d times in receiver LEDS \n", state);
    //TaskHandle_t recordHand = xTaskGetHandle("recordTask");
    //xTaskNotify(recordHand, (1 << 0), eSetBits);
    if (state == 1) {
    
        ledsObject->animalSound();
    
    }
  
  }
}