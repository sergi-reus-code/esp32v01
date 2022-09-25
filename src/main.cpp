#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "tasks/ledsTask/ledsTask.h"
#include "tasks/recordTask/recordTask.h"
#include "tasks/sdTask/sdTask.h"
#include "tasks/commsTask/commsTask.h"
#include "tasks/playerTask/playerTask.h"

static TaskHandle_t ledsHandler = NULL; //Leds
static TaskHandle_t recordHandler = NULL; //Record
static TaskHandle_t sdHandler = NULL; //SD 
static TaskHandle_t commsHandler = NULL; //Comms Send&Receiver 
static TaskHandle_t playerHandler = NULL; //Player
static TaskHandle_t mainHandler = NULL; // Main program
 
#define Threshold 40 /* Greater the value, more the sensitivity */

static const char *TAG = "MAIN APP";




void mainTask(void *params){

  int tread1 = touchRead(T3);
  ESP_LOGI(TAG, "Touch read -> %d",tread1);
  vTaskDelay(500);
  int tread2 = touchRead(T3);

  if ((tread1 < Threshold) && (tread2 < Threshold) )
  {
    printf("Start recording\n");

                        // 1. Hacer round leds
                        //xTaskNotify(ledsHandler, (1 << 0), eSetValueWithOverwrite);
                      
                        // 2. Record sound & Store on SD
                        //xTaskNotify(recordHandler, (1 << 0), eSetValueWithOverwrite);
                        //xTaskNotify(sdHandler, (1 << 0), eSetValueWithOverwrite);  

                        // 3. Send to server & Receive response & Store to SD
                        //xTaskNotify(commsHandler, (1 << 0), eSetValueWithOverwrite);
                        //xTaskNotify(sdHandler, (1 << 0), eSetValueWithOverwrite);  
                      
                        // 4. Play de response
                        //xTaskNotify(playerHandler, (1 << 0), eSetValueWithOverwrite);

                        // 5. Check if interaction is done (Close/Repeat) 
              
    while (true) {

                          //vTaskDelay(1000);

                          //xTaskNotify(sdHandler, (1 << 0), eSetBits);  
                          //vTaskDelay(1000);
                          // 3. Send to server & Receive response & Store to SD
                          //xTaskNotify(commsHandler, (1 << 0), eSetBits);
                          //xTaskNotify(sdHandler, (1 << 0), eSetBits);  
                          //vTaskDelay(1000);
                          // 4. Play de response
                          //xTaskNotify(playerHandler, (1 << 0), eSetBits);
                          //vTaskDelay(1000);
                          // 5. Check if interaction is done (Close/Repeat) 
  
            int tread3 = touchRead(T3);
            ESP_LOGI(TAG, "Touch read3 -> %d",tread3);
            vTaskDelay(500);

            if(tread3 < Threshold){

              return;
            }
    
       }
      
  }
  else
  {
    ESP_LOGI(TAG, "bona nit else");
    vTaskDelay(1000);
    esp_deep_sleep_start();
  }
  
}

void IRAM_ATTR callback(){
  
}



void setup(void)
{

  vTaskDelay(100); // only to take time to print on Serial
  ESP_LOGI(TAG, "Starting up");
  
  //Setup interrupt on Touch Pad 3 (GPIO15)
  touchAttachInterrupt(T3, callback, Threshold);
  //Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();

  xTaskCreatePinnedToCore(&ledsTask,"asdasd",2048,NULL,1,&ledsHandler,1);
  xTaskCreatePinnedToCore(&recordTask, "recordTask", 2048, NULL, 2, &recordHandler,1);
  xTaskCreatePinnedToCore(&sdTask, "sdTask", 2048, NULL, 2, &sdHandler,1);
  xTaskCreatePinnedToCore(&commsTask, "commsTask", 2048, NULL, 2, &commsHandler,0);
  xTaskCreatePinnedToCore(&playerTask, "playerTask", 2048, NULL, 2, &playerHandler,1);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  xTaskCreatePinnedToCore(&mainTask, "main", 2048, NULL, 2, &mainHandler,1);

}


void loop(){
  vTaskDelete(NULL);
}