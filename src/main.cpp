#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "esp_sleep.h"
//#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
//#include "esp_log.h"
//#include "esp32-hal-log.h"
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
 
RTC_DATA_ATTR int bootCount = 0;
#define Threshold 40 /* Greater the value, more the sensitivity */

static const char *TAG = "app";


void callback(){
  //placeholder callback function
}


void mainTask(void *params)
{

  
  int tread1 = touchRead(T3);
  vTaskDelay(1000);
  int tread2 = touchRead(T3);

  if ((tread1 < Threshold) && (tread2 < Threshold) )
  {
    //printf("Start recording\n");

  // 1. Hacer round leds
  xTaskNotify(ledsHandler, (1 << 0), eSetValueWithOverwrite);
  


  // 2. Record sound & Store on SD
  xTaskNotify(recordHandler, (1 << 0), eSetValueWithOverwrite);
  xTaskNotify(sdHandler, (1 << 0), eSetValueWithOverwrite);  

  // 3. Send to server & Receive response & Store to SD
  xTaskNotify(commsHandler, (1 << 0), eSetValueWithOverwrite);
  xTaskNotify(sdHandler, (1 << 0), eSetValueWithOverwrite);  
  
  // 4. Play de response
    xTaskNotify(playerHandler, (1 << 0), eSetValueWithOverwrite);

  // 5. Check if interaction is done (Close/Repeat) 
   



    while (true) {




  //vTaskDelay(1000);

  //xTaskNotify(sdHandler, (1 << 0), eSetBits);  
  //vTaskDelay(1000);
  // 3. Send to server & Receive response & Store to SD
  //xTaskNotify(commsHandler, (1 << 0), eSetBits);
  //xTaskNotify(sdHandler, (1 << 0), eSetBits);  
  vTaskDelay(1000);
  // 4. Play de response
  //xTaskNotify(playerHandler, (1 << 0), eSetBits);
  vTaskDelay(1000);
  // 5. Check if interaction is done (Close/Repeat) 
  
  
  
  //break;
  }
  //printf("Bona nit.....\n");
  
  esp_deep_sleep_start();
  }
  else
  {
      
  
  //printf("Bona nit.....\n");
  
  esp_deep_sleep_start();
  }
  








  

  
  










  //Check all done



  

}












void setup(void)
{
 
  ++bootCount;



    //Setup interrupt on Touch Pad 3 (GPIO15)
  touchAttachInterrupt(T3, callback, Threshold);

  //Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();
  
  
  vTaskDelay(100); // only to take time to print on Serial
  //printf("Inicio programa iNote 2022  \n");

  ESP_LOGI(TAG, "Starting up");
  
  
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









   /*
  wifiMulti.addAP("casa1", "nike2004");  //Riu
  wifiMulti.addAP("MOVISTAR_4EB8", "87DC72A32E66337156AA");  //Puigcerdà
  wifiMulti.addAP("AndroidAP2C22", "nike2004");  //Mobil

  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }

  Serial.println(" Task0 running on core " + String(xPortGetCoreID()));

  while (1){
      vTaskDelay(10);
  }*/

