#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/touch_sensor.h"

#include "tasks/ledsTask/ledsTask.h"
#include "tasks/recordTask/recordTask.h"
#include "tasks/sdTask/sdTask.h"
#include "tasks/commsTask/commsTask.h"
#include "tasks/playerTask/playerTask.h"

#include "SDCard.h"

#include "config.h"


static TaskHandle_t ledsHandler = NULL; //Leds
static TaskHandle_t recordHandler = NULL; //Record
static TaskHandle_t sdHandler = NULL; //SD 
static TaskHandle_t commsHandler = NULL; //Comms Send&Receiver 
static TaskHandle_t playerHandler = NULL; //Player
static TaskHandle_t mainHandler = NULL; // Main program
 
#define Threshold 15 /* Greater the value, more the sensitivity */

static const char *TAG = "MAIN APP";






void mainTask(void *params){

  uint16_t touch_value1 = touchRead(14);
  vTaskDelay(500);
  uint16_t touch_value2 = touchRead(14);
  
 
  if ((touch_value1 < Threshold) && (touch_value2 < Threshold) )
  {


    // 3. Send to server & Receive response & Store to SD
    //xTaskNotify(commsHandler, (1 << 0), eSetValueWithOverwrite);
    //xTaskNotify(sdHandler, (1 << 0), eSetValueWithOverwrite);  
                      
    // 4. Play de response
    //xTaskNotify(playerHandler, (1 << 0), eSetValueWithOverwrite);

    // 5. Check if interaction is done (Close/Repeat) 
              


              while (touch_value2 < Threshold) {

                  touch_value2 = touchRead(14);
                  ESP_LOGI(TAG, "gravando");
                  
                  
                  // 1. Hacer round leds
                  //xTaskNotify(ledsHandler, (1 << 0), eSetValueWithOverwrite);
                  
                  // 2. Record sound & Store on SD
                  //xTaskNotify(recordHandler, (1 << 0), eSetValueWithOverwrite);
                  //xTaskNotify(sdHandler, (1 << 0), eSetValueWithOverwrite);  


                  vTaskDelay(500);





                       
                  }
                  uint state;
                  //xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
                  ESP_LOGI(TAG, "enviando");
                  xTaskNotify(playerHandler, (1 << 0), eSetValueWithOverwrite);
                  xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);


ESP_LOGI(TAG, "bona nit TUTTO BENNE");



vTaskDelay(1000);

esp_deep_sleep_start();
                  
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

  Serial.begin(115200);
  vTaskDelay(100); // only to take time to print on Serial
  ESP_LOGI(TAG, "Starting up");

  ESP_LOGI(TAG, "Mounting SDCard on /sdcard");
  new SDCard("/sdcard", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);
  
  Serial.println(touchRead(14));
  ESP_LOGI(TAG, "Lectura del touchPAD14 --> %d",touchRead(14) );



  //Setup interrupt on Touch Pad 6 (GPIO14)
  touchAttachInterrupt(T6, callback, Threshold);

  //Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();

  xTaskCreatePinnedToCore(&ledsTask,"ledsTask",2048,NULL,1,&ledsHandler,1);
  xTaskCreatePinnedToCore(&recordTask, "recordTask", 2048, NULL, 2, &recordHandler,1);
  xTaskCreatePinnedToCore(&sdTask, "sdTask", 2048, NULL, 2, &sdHandler,1);
  xTaskCreatePinnedToCore(&commsTask, "commsTask", 2048, NULL, 2, &commsHandler,0);
  xTaskCreatePinnedToCore(&playerTask, "playerTask", 4096, NULL, 2, &playerHandler,1);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  xTaskCreatePinnedToCore(&mainTask, "mainTask", 2048, NULL, 2, &mainHandler,1);
  
}


void loop(){

  vTaskDelete(NULL);

}