#include <Arduino.h>
#include <stdio.h>


#include "esp32-hal-log.h"


#include "config.h"

static const char *TAG = "DEEP SLEEP";



SemaphoreHandle_t xSemaphore = NULL;



// A task that creates a semaphore.
void vATask( void * pvParameters )
{
   // Create the semaphore to guard a shared resource.
   vSemaphoreCreateBinary( xSemaphore );
}



// A task that uses the semaphore.
void vAnotherTask( void * pvParameters )
{
   // ... Do other things.
   if( xSemaphore != NULL )
   {
       // See if we can obtain the semaphore.  If the semaphore is not available
       // wait 10 ticks to see if it becomes free.
       if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
       {
           // We were able to obtain the semaphore and can now access the
           // shared resource.
           // ...
           // We have finished accessing the shared resource.  Release the
           // semaphore.
           xSemaphoreGive( xSemaphore );
       }
       else
       {
           // We could not obtain the semaphore and can therefore not access
           // the shared resource safely.
       }
   }
}

void setup()
{
  Serial.begin(115200);
ESP_LOGI(TAG, "Init");
}

void loop()
{
}