#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "class/playerClass.h"

static const char *TAG1 = "PLAYER TASK";


void playerTask(void *params)
{
  //Creamos el objeto leds
  playerClass *playerObject = new playerClass();
 
  uint state;
  TaskHandle_t mainTaskHandele = xTaskGetHandle("main");
  TaskHandle_t recordHand = xTaskGetHandle("recordTask");



  ESP_LOGI(TAG1, "111111111 --> %d",state );
  xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
  ESP_LOGI(TAG1, "2222222222 --> %d",state );
  ESP_LOGI(TAG1, "2222222222 --> %d",mainTaskHandele );

  if (state == 1) {
        playerObject->play("/sdcard/test.wav");
        if(mainTaskHandele != NULL){
          xTaskNotify(mainTaskHandele, 0xFF, eSetValueWithOverwrite);
        }else{
          printf("NULL pointer\n");

        }
  }  
/*
  while (true)
  {
    
  }*/
}