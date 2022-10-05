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
#include "tasks/commsTask/commsTask.h"
#include "tasks/playerTask/playerTask.h"

#include "config.h"

#define SCK  18
#define MISO  19
#define MOSI  23
#define CS  5




static TaskHandle_t ledsHandler = NULL;   // Leds
static TaskHandle_t recordHandler = NULL; // Record
static TaskHandle_t commsHandler = NULL;  // Comms Send&Receiver
static TaskHandle_t playerHandler = NULL; // Player
static TaskHandle_t mainHandler = NULL;   // Main program

static bool finished = false;

const char *TAG = "MAIN APP";


void IRAM_ATTR callback()
{
  ESP_LOGI(TAG, "Ta aqui lu problema.......");
}

void goToSleep(){

  touchAttachInterrupt(14, callback, 40);
 //touchAttachInterrupt(T6, callback, 20);                // Setup interrupt on Touch Pad 6 (GPIO14) ..... Threshold
  
  esp_err_t ret = esp_sleep_enable_touchpad_wakeup();      
 if (ret != ESP_OK){
ESP_LOGI(TAG, "jodida carallu" );

 }  

 ESP_LOGI(TAG, "Bona nit final...... A TOMA PEL CUL");
esp_deep_sleep_start();

}



void mainTask(void *params)
{
  vTaskDelay(100); // only to take time
  ESP_LOGI(TAG, "Starting up..... iNote2022");

  //new SDCard("/sdcard", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);


  

  uint state;
  uint16_t touch_value1 = touchRead(14);
  vTaskDelay(500);
  uint16_t touch_value2 = touchRead(14);
  ESP_LOGI(TAG, "Touch value --> %d", touch_value2);

  if ((touch_value1 < Threshold) && (touch_value2 < Threshold))
  {

        while(!finished){

        // 1. Hacer round leds i gravar audio
          ESP_LOGI(TAG, "Leds y gravando");
          //xTaskNotify(ledsHandler, (1 << 0), eSetValueWithOverwrite);
          xTaskNotify(recordHandler, (1 << 0), eSetValueWithOverwrite);
          xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
        
                  if (state==1){
                    ESP_LOGI(TAG, "Let's continue to comms");
                    vTaskDelay(1000);
                  } else {
                    ESP_LOGI(TAG, "ERRORRRRRRRRRRRRR ----> MUST BREAK");
                  } 

        // 2. Enviar archivo i recivir respuesta
          ESP_LOGI(TAG, "Leds y comms");
          //xTaskNotify(ledsHandler, (1 << 1), eSetValueWithOverwrite);
          //xTaskNotify(commsHandler, (1 << 0), eSetValueWithOverwrite);
          //xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
                
                  if (state==1){
                    ESP_LOGI(TAG, "Let's continue to player");
                    vTaskDelay(1000);
                  } else {
                    ESP_LOGI(TAG, "ERRORRRRRRRRRRRRR ----> MUST BREAK");
                  } 

        // 3. Reproducir respuesta
          ESP_LOGI(TAG, "Leds y reproduciendo");
          //xTaskNotify(ledsHandler, (1 << 2), eSetValueWithOverwrite);
          //xTaskNotify(playerHandler, (1 << 0), eSetValueWithOverwrite);
          //xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
        
                  if (state==1){
                    ESP_LOGI(TAG, "Let's continue to sleep");
                    vTaskDelay(1000);
                    goToSleep();       //este no va aqui
                  } else {
                    ESP_LOGI(TAG, "ERRORRRRRRRRRRRRR ----> MUST BREAK");
                  }
                  
            finished = false;
            goToSleep();
          }
        }


  
  else
  {
    ESP_LOGI(TAG, "bona nit FALSA ALARMA");
    //vTaskDelay(5000);
    goToSleep();
    
  }
}



void setup(void)
{

     Serial.begin(115200);



















  vTaskDelay(1000); // only to take time
  ESP_LOGI(TAG, "Starting up..... iNote2022");

  //new SDCard("/sdcard", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);

//SPIClass spi = SPIClass(VSPI);

  //spi.begin(SCK, MISO, MOSI, CS);

  if (!SD.begin(CS)){
    Serial.println("Card Mount Failed");
    return;
  }
  

  //xTaskCreatePinnedToCore(&ledsTask, "ledsTask", 2048, NULL, 1, &ledsHandler, 1);
  xTaskCreatePinnedToCore(&recordTask, "recordTask", 4096, NULL, 2, &recordHandler, 1);
  //xTaskCreatePinnedToCore(&commsTask, "commsTask", 2048, NULL, 2, &commsHandler, 0);
  //xTaskCreatePinnedToCore(&playerTask, "playerTask", 4096, NULL, 2, &playerHandler, 1);
  
  xTaskCreatePinnedToCore(&mainTask, "mainTask", 2048, NULL, 2, &mainHandler, 1);

}

void loop()
{
  // Deleting loop Task
  vTaskDelete(NULL);                                            
}