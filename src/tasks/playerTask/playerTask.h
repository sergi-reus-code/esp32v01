#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "class/playerClass.h"

static const char *TAGP = "PLAYER TASK";



void playerTask(void *params)
{
  //Creamos el objeto leds
  playerClass *playerObject = new playerClass();

  vTaskDelay(100);
  
  TaskHandle_t mainTaskHandle = xTaskGetHandle("mainTask");
  if(mainTaskHandle == NULL){ ESP_LOGE(TAGP, "Main Handler Null -----> ERROR MUST RESTART");}

  uint state; 


  ESP_LOGI(TAGP, "111111111 --> %d",state );
  xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
  ESP_LOGI(TAGP, "2222222222 --> %d",state );
  ESP_LOGI(TAGP, "2222222222 --> %d",mainTaskHandle );

  if (state == 1) {
        playerObject->play("/sdcard/test.wav");
        //playerObject->play();
        ESP_LOGI(TAGP, "titititit");
        //xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
        if(mainTaskHandle != NULL){
          ESP_LOGI(TAGP, "tatatatatatat");
          xTaskNotify(mainTaskHandle, (1 << 0), eSetValueWithOverwrite);
          ESP_LOGI(TAGP, "tutututututut");
        }else{
          printf("NULL pointer\n");

        }
  }  

  while (true)
  {
    
  }
}