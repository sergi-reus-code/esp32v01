#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "esp32-hal-log.h"


static const char *TAG = "DEEP SLEEP";


static TaskHandle_t receiverHandler = NULL;
static TaskHandle_t senderHandler = NULL;

static TaskHandle_t mainHandler = NULL;
static TaskHandle_t buttonHandler = NULL;
static TaskHandle_t ledsHandler = NULL;
static TaskHandle_t recordHandler = NULL;
static TaskHandle_t sdHandler = NULL;
static TaskHandle_t speakerHandler = NULL;



void sender(void *params)
{
  while (true)   {
    Serial.print("antes -> ");
    xTaskNotify(receiverHandler, (1 << 0), eSetBits);
    Serial.print("despues -> ");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    //xTaskNotify(receiverHandler, (1 << 1), eSetBits);
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
    //xTaskNotify(receiverHandler, (1 << 2), eSetBits);
    //xTaskNotify(receiverHandler, (1 << 3), eSetBits);
    
   
  }
}

void mainTask(void *params)
{
  Serial.println("En main Task");
  while (true) {
    Serial.println("EEEEEstado de la tarea ");
    xTaskNotify(&recordHandler, (1 << 0), eSetBits);
    Serial.println("AAAAAEstado de la tarea ");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}










void receiver(void *params)
{
  uint state;
  while (true)
  {
    
    xTaskNotifyWait(0, 0, &state, portMAX_DELAY);
    
    printf("received state %d times\n", state);

  }
}

void recordTask(void *params)
{
  uint state;
  while (true) {
   
    
    xTaskNotifyWait(0, 0, &state, portMAX_DELAY);
    printf("received state %d times\n", state);
    
    
  }
}















void buttonTask(void *params)
{
  uint state;
  while (true) {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("Orden recivida: %d \n", state);
  }
}

void ledsTask(void *params)
{
  uint state;
  while (true) {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("Orden recivida: %d \n", state);
  }
}


void sdTask(void *params)
{
  uint state;
  while (true) {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("Orden recivida: %d \n", state);
  }
}

void speakerTask(void *params)
{
  uint state;
  while (true) {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("Orden recivida: %d \n", state);
    
  }
}










void setup(void)
{
  Serial.begin(115200);
  //Crear todas las tareas -> Dentro de las tareas crear los objetos -> Ponerlos en wait



//xTaskCreate(&receiver, "receiver", 2048, NULL, 2, &receiverHandler);
//xTaskCreate(&sender, "sender", 2048, NULL, 2, NULL);

xTaskCreate(&mainTask, "mainTask", 2048, NULL, 2, &mainHandler);
xTaskCreate(&recordTask, "recordTask", 2048, NULL, 2, &recordHandler);


//xTaskCreate(&buttonTask, "sender", 2048, NULL, 2, &buttonHandler);
//xTaskCreate(&ledsTask, "sender", 2048, NULL, 2, &ledsHandler);

//xTaskCreate(&sdTask, "sender", 2048, NULL, 2, &sdHandler);
//xTaskCreate(&speakerTask, "sender", 2048, NULL, 2, &speakerHandler);

//Check todas las tareas estan en bloqued






//delay(10000);
  //while conversa not finiquitada ir haciendo while
  //Serial.println("----------------------------");
//Serial.println(eTaskGetState(receiverHandler));

  //si consversa finiquitada porner en deep sleeep






}

void loop(){

    //vTaskDelete(NULL);

}