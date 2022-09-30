#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "class/commsClass.h"

const char *TAGC = "COMMS TASK";



void commsTask(void *params)
{
  //Creamos el objeto leds
  commsClass *commsObject = new commsClass();

  vTaskDelay(1000);
  
  TaskHandle_t mainTaskHandle = xTaskGetHandle("mainTask");
  if(mainTaskHandle == NULL){ ESP_LOGE(TAGC, "Main Handler Null -----> ERROR MUST RESTART");}
 
  uint state;

  while (true)
  {
    
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);

    if (state == 1) {
    
        
    
    } else {


    }
  
  }
}