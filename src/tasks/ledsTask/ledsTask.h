#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "class/ledsClass.h"

const char *TAGL = "LED TASK";



void ledsTask(void *params)
{
  //Creamos el objeto leds
  ledsClass *ledsObject = new ledsClass();

  vTaskDelay(1000);
  
  TaskHandle_t mainTaskHandle = xTaskGetHandle("mainTask");
  if(mainTaskHandle == NULL){ ESP_LOGE(TAGL, "Main Handler Null -----> ERROR MUST RESTART");}
 
  uint state;

  while (true)
  {
   
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);

    switch (state)
    {
    case 1:
        ESP_LOGI(TAGL, "Leds -----> 1");
      break;
    
    case 2:
        ESP_LOGI(TAGL, "Leds -----> 2");
      break;

    case 4:
        ESP_LOGI(TAGL, "Leds -----> 4");
      break;

    default:
      break;
    }
  
  }
}