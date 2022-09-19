#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL;
static TaskHandle_t senderHandler = NULL;

static TaskHandle_t mainHandler = NULL;
static TaskHandle_t buttonHandler = NULL;
static TaskHandle_t ledsHandler = NULL;
static TaskHandle_t micHandler = NULL;
static TaskHandle_t sdHandler = NULL;
static TaskHandle_t speakerHandler = NULL;



void sender(void *params)
{
//  while (true)   {
    
    vTaskDelay(500/ portTICK_PERIOD_MS);
    //xTaskNotify(receiverHandler, (1 << 0), eSetBits);
    Serial.println(eTaskGetState(receiverHandler));
    xTaskNotify(receiverHandler, (1 << 1), eSetBits);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    //xTaskNotify(receiverHandler, (1 << 2), eSetBits);
    xTaskNotify(receiverHandler, (1 << 4), eSetBits);
    //vTaskDelay(500 / portTICK_PERIOD_MS);
   
 // }
}

void receiver(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    Serial.println(eTaskGetState(receiverHandler));
    printf("received state %d times\n", state);

  }
}

void mainTask(void *params)
{
  Serial.println("En main Task");
  delay(500);
  while (true) {
    Serial.println("Encendiendo microfono");
    delay(500);
    xTaskNotify(micHandler, (1 << 1), eSetBits);
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

void micTask(void *params)
{
  uint state;
  while (true) {
    printf("Waiting on mic \n");
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("Orden recivida: %d \n", state);
    delay(5000);
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


static TaskHandle_t mainHandler = NULL;
static TaskHandle_t buttonHandler = NULL;
static TaskHandle_t ledsHandler = NULL;
static TaskHandle_t micHandler = NULL;
static TaskHandle_t sdHandler = NULL;
static TaskHandle_t speakerHandler = NULL;



  //xTaskCreate(&receiver, "receiver", 2048, NULL, 2, &receiverHandler);
  //xTaskCreate(&sender, "sender", 2048, NULL, 2, &senderHandler);

xTaskCreate(&mainTask, "sender", 2048, NULL, 2, &mainHandler);
xTaskCreate(&buttonTask, "sender", 2048, NULL, 2, &buttonHandler);
xTaskCreate(&ledsTask, "sender", 2048, NULL, 2, &ledsHandler);
xTaskCreate(&micTask, "sender", 2048, NULL, 2, &micHandler);
xTaskCreate(&sdTask, "sender", 2048, NULL, 2, &sdHandler);
xTaskCreate(&speakerTask, "sender", 2048, NULL, 2, &speakerHandler);

//Check todas las tareas estan en bloqued






//delay(10000);
  //while conversa not finiquitada ir haciendo while
  //Serial.println("----------------------------");
//Serial.println(eTaskGetState(receiverHandler));

  //si consversa finiquitada porner en deep sleeep






}

void loop(){

    vTaskDelete(NULL);

}