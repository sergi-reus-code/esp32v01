/* 1º Ejemplo colas.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esp_system.h"
#include "nvs_flash.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/heap_regions.h"

#define TAM_COLA 20 /*20 mensajes*/
#define TAM_MSG 7 /*Cada Mensaje 7 caracteres*/

xQueueHandle cola_Mensaje;

void escribe1(void *pvParameter)
{
    char cadena[7];
    while(1) {
    strcpy (cadena, "Tarea1\n");
      if (xQueueSendToBack(cola_Mensaje, &cadena,2000/portTICK_RATE_MS)!=pdTRUE){//2seg--> Tiempo max. que la tarea está bloqueada si la cola está llena
         printf("error escribe1\n");

    }
      vTaskDelay(2000 / portTICK_RATE_MS);
 }
}
void escribe2(void *pvParameter)
{
    char cadena[7];
    while(1) {

       strcpy (cadena, "Tarea2\n");
       if (xQueueSendToBack(cola_Mensaje, &cadena,2000/portTICK_RATE_MS)!=pdTRUE){
          printf("error escribe2\n");
    }
       vTaskDelay(2000 / portTICK_RATE_MS);
 }

}

void escribe3(void *pvParameter)
{
    char cadena[7];
    while(1) {
       strcpy (cadena, "Tarea3\n");
       if (xQueueSendToBack(cola_Mensaje, &cadena,2000/portTICK_RATE_MS)!=pdTRUE){
          printf("error escribe3\n");
          }
       vTaskDelay(2000 / portTICK_RATE_MS);
       }
    }

void lee1(void *pvParameter)
{
   int i;
   char Rx[7];
   while(1) {

    if(xQueueReceive(cola_Mensaje,&Rx,10000/portTICK_RATE_MS)==pdTRUE) {//10s --> Tiempo max. que la tarea está bloqueada si la cola está vacía

         for(i=0; i<strlen(Rx); i++)
           {
             printf("%c",Rx[i]);
           }

          } else{
             printf("Fallo al leer la cola");

     }

   }
}


void app_main() {

    nvs_flash_init();

    cola_Mensaje= xQueueCreate(TAM_COLA, TAM_MSG);

    xTaskCreate(&lee1,     "lee1",     1024, NULL, 5, NULL);
    xTaskCreate(&escribe1, "escribe1", 1024, NULL, 1, NULL);
    xTaskCreate(&escribe2, "escribe2", 1024, NULL, 1, NULL);
    xTaskCreate(&escribe3, "escribe3", 1024, NULL, 1, NULL);


}