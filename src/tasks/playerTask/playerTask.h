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
 vTaskDelay(1000);
  uint state;
  TaskHandle_t mainTaskHa = xTaskGetHandle("mainTask");
  TaskHandle_t recordHand = xTaskGetHandle("recordTask");



        if(mainTaskHa != NULL){
          ESP_LOGI(TAG1, "main no null");
        }else{
          ESP_LOGI(TAG1, "main null");

        }


                if(recordHand != NULL){
          ESP_LOGI(TAG1, "record no null");
        }else{
          ESP_LOGI(TAG1, "record null");

        }





  ESP_LOGI(TAG1, "111111111 --> %d",state );
  xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
  ESP_LOGI(TAG1, "2222222222 --> %d",state );
  ESP_LOGI(TAG1, "2222222222 --> %d",mainTaskHa );

  if (state == 1) {
        playerObject->play("/sdcard/test.wav");
        //playerObject->play();
        ESP_LOGI(TAG1, "titititit");
        //xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
        if(mainTaskHa != NULL){
          ESP_LOGI(TAG1, "tatatatatatat");
          xTaskNotify(mainTaskHa, (1 << 0), eSetValueWithOverwrite);
          ESP_LOGI(TAG1, "tutututututut");
        }else{
          printf("NULL pointer\n");

        }
  }  

  while (true)
  {
    
  }
}