#include <Arduino.h>

#include "hardware/led/ledTask.h"
#include "hardware/button/buttonTask.h"

#include "config.h"



static TaskHandle_t ledTask_handle;



void wait_for_button_push()
{
  while (gpio_get_level(GPIO_BUTTON) == 0)
  {
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}






void setup()
{

Serial.begin(112500);



xTaskCreatePinnedToCore(ledTask, "led Task2", 10000, NULL, 1, &ledTask_handle, 1); 






 
    
 //attachInterrupt(button1.PIN, isr, FALLING);

}
 
/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop()
{

/*
Serial.println("this is ESP32 Task");
    if (button1.pressed) {
        Serial.printf("Button has been pressed %u times\n", button1.numberKeyPresses);
        button1.pressed = false;
    }
*/

delay(1000);

}
 





