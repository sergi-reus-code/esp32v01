#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL;

void sender(void *params)
{
  while (true)
  {
vTaskDelay(10000/ portTICK_PERIOD_MS);

    //xTaskNotify(receiverHandler, (1 << 0), eSetBits);
    Serial.println(eTaskGetState(receiverHandler));
    xTaskNotify(receiverHandler, (1 << 1), eSetBits);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    //xTaskNotify(receiverHandler, (1 << 2), eSetBits);
    xTaskNotify(receiverHandler, (1 << 4), eSetBits);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
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

void ledsTask(void *params)
{
  uint state;
  while (true)
  {

    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    //Serial.println(eTaskGetState(receiverHandler));
    //printf("received state %d times\n", state);

  }
}








void setup(void)
{
  Serial.begin(115200);
  //Crear todas las tareas -> Dentro de las tareas crear los objetos -> Ponerlos en wait

  //Check todas las tareas estan en bloqued 

  xTaskCreate(&receiver, "receiver", 2048, NULL, 2, &receiverHandler);
  xTaskCreate(&sender, "sender", 2048, NULL, 2, NULL);
delay(3000);
  //while conversa not finiquitada ir haciendo while
  Serial.println("----------------------------");
Serial.println(eTaskGetState(receiverHandler));

  //si consversa finiquitada porner en deep sleeep






}

void loop(){

    vTaskDelete(NULL);

}