#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "class/commsClass.h"




void commsTask(void *params)
{
  //Creamos el objeto leds
  commsClass *commsObject = new commsClass();
 
  uint state;
  while (true)
  {

    
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver COMMS \n", state);
    //TaskHandle_t recordHand = xTaskGetHandle("recordTask");
    //xTaskNotify(recordHand, (1 << 0), eSetBits);
    if (state == 1) {
    
        commsObject->animalSound();
    
    }
  
  }
}