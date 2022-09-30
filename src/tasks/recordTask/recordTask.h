#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"

#include "config.h"

#include "class/recordClass.h"

const char *TAGR = "RECORD TASK";



void recordTask(void *params)
{
  //Creamos el objeto leds
  recordClass *recordObject = new recordClass();
 
  vTaskDelay(1000);
  
  TaskHandle_t mainTaskHandle = xTaskGetHandle("mainTask");
  if(mainTaskHandle == NULL){ ESP_LOGE(TAGR, "Main Handler Null -----> ERROR MUST RESTART");}

  uint state;




  uint16_t touch_value2 = touchRead(14);

    while (touch_value2 < Threshold)
    {

      touch_value2 = touchRead(14);
      ESP_LOGI(TAGR, "gravando");



      // 2. Record sound & Store on SD
      
      

      vTaskDelay(500);
    }




  while (true)
  {

    
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);

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
        
       
    
    }



  
  }
}