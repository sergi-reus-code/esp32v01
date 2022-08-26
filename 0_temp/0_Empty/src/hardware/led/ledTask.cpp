#include <Arduino.h>
#include "ledTask.h"





void ledTask( void * parameter ) {
 
   
    
    while(1) {
        /* Blink off (output low) */
        digitalWrite(ONBOARD_LED, LOW);
        vTaskDelay(1000 / portTICK_RATE_MS);
        /* Blink on (output high) */
        digitalWrite(ONBOARD_LED, HIGH);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

}

   