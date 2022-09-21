#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp32-hal-log.h"
static const char *TAG = "MAIN PROGRAM";

static TaskHandle_t ledsHandler = NULL; //Leds
static TaskHandle_t recordHandler = NULL; //Record
static TaskHandle_t sdHandler = NULL; //SD 
static TaskHandle_t commsHandler = NULL; //Comms Send&Receiver 
static TaskHandle_t playerHandler = NULL; //Player


void ledsTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver LEDS \n", state);
  }
}

void recordTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver RECORD \n", state);
  }
}

void sdTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver SD \n", state);
  }
}

void commsTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver SEND&RECEIVER \n", state);
  }
}

void playerTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver PLAYER \n", state);
  }
}


/*

void sender(void *params)
{
  while (true)
  {
    xTaskNotify(receiverHandler1, (1 << 0), eSetBits);
    xTaskNotify(receiverHandler1, (1 << 1), eSetBits);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    xTaskNotify(receiverHandler1, (1 << 2), eSetBits);
    xTaskNotify(receiverHandler1, (1 << 3), eSetBits);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    xTaskNotify(receiverHandler2, (1 << 0), eSetBits);
    xTaskNotify(receiverHandler2, (1 << 1), eSetBits);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    xTaskNotify(receiverHandler2, (1 << 2), eSetBits);
    xTaskNotify(receiverHandler2, (1 << 3), eSetBits);
    vTaskDelay(100 / portTICK_PERIOD_MS);


  }
}

*/










void setup(void)
{
  xTaskCreate(&ledsTask, "receiver1", 2048, NULL, 2, &ledsHandler);
  xTaskCreate(&recordTask, "receiver2", 2048, NULL, 2, &recordHandler);
  xTaskCreate(&sdTask, "receiver3", 2048, NULL, 2, &sdHandler);
  xTaskCreate(&commsTask, "receiver4", 2048, NULL, 2, &commsHandler);
  xTaskCreate(&playerTask, "receiver5", 2048, NULL, 2, &playerHandler);
  

  printf("Inicio programa iNote 2022  \n");

  //check if record task is ready

  xTaskNotify(ledsHandler, (1 << 0), eSetBits);
  xTaskNotify(ledsHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(ledsHandler, (1 << 2), eSetBits);
  xTaskNotify(ledsHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(recordHandler, (1 << 0), eSetBits);
  xTaskNotify(recordHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(recordHandler, (1 << 2), eSetBits);
  xTaskNotify(recordHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(sdHandler, (1 << 0), eSetBits);
  xTaskNotify(sdHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(sdHandler, (1 << 2), eSetBits);
  xTaskNotify(sdHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(commsHandler, (1 << 0), eSetBits);
  xTaskNotify(commsHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(commsHandler, (1 << 2), eSetBits);
  xTaskNotify(commsHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(playerHandler, (1 << 0), eSetBits);
  xTaskNotify(playerHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(playerHandler, (1 << 2), eSetBits);
  xTaskNotify(playerHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);



  //xTaskCreate(&sender, "sender", 2048, NULL, 2, NULL);
}

void loop(){
    /*
  //Inicio programa 
  printf("Inicio programa iNote 2022  \n");

  //check if record task is ready

  xTaskNotify(receiverHandler1, (1 << 0), eSetBits);
  xTaskNotify(receiverHandler1, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(receiverHandler1, (1 << 2), eSetBits);
  xTaskNotify(receiverHandler1, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(receiverHandler2, (1 << 0), eSetBits);
  xTaskNotify(receiverHandler2, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(receiverHandler2, (1 << 2), eSetBits);
  xTaskNotify(receiverHandler2, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(receiverHandler3, (1 << 0), eSetBits);
  xTaskNotify(receiverHandler3, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(receiverHandler3, (1 << 2), eSetBits);
  xTaskNotify(receiverHandler3, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(receiverHandler4, (1 << 0), eSetBits);
  xTaskNotify(receiverHandler4, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(receiverHandler4, (1 << 2), eSetBits);
  xTaskNotify(receiverHandler4, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(receiverHandler5, (1 << 0), eSetBits);
  xTaskNotify(receiverHandler5, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(receiverHandler5, (1 << 2), eSetBits);
  xTaskNotify(receiverHandler5, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

*/
vTaskDelete(NULL);

}