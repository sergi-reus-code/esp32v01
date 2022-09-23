#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "class/recordClass.h"




void recordTask(void *params)
{
  //Creamos el objeto leds
  recordClass *recordObject = new recordClass();
 
  uint state;
  while (true)
  {

    
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    //printf("received state %d times in receiver RECORD \n", state);
    //TaskHandle_t recordHand = xTaskGetHandle("recordTask");
    //xTaskNotify(recordHand, (1 << 0), eSetBits);
    if (state == 1) {
      
      while (true) {

           int tread1 = touchRead(T3);
          if (tread1 < 40)
          {
             printf("Sdfasdfasd\n");
             
             printf("This is my_int: %d\n", tread1); // long long decimal

             vTaskDelay(500);
          }
          else
          {
            break;
          }
          



            
      
      }
        
        recordObject->animalSound();
    
    }

    if (state == 2) {
      
      

             printf("Estado 2");
      
    
        
       
    
    }




  
  }
}