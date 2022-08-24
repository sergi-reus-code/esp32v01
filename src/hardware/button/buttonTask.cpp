#include <Arduino.h>
#include "buttonTask.h"


Button* button1 = NULL;



void buttonTask( void * parameter ) {
 
   
   //pasar por serial para ver salida
   
   *button1 = {18, 0, false};
   
   
   
   //pinMode(button1.PIN, INPUT_PULLUP);
    
    while(1) {

        vTaskDelay(1000 / portTICK_RATE_MS);
    }

}


/*
struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
} ;
*/

/*



Button button1 = NULL;

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 


void IRAM_ATTR isr() {
    button_time = millis();
if (button_time - last_button_time > 250)
{
        button1.numberKeyPresses++;
        button1.pressed = true;
       last_button_time = button_time;
}
}





void buttonTask( void * parameter ) {
 
   button1 = {18, 0, false};
   pinMode(button1.PIN, INPUT_PULLUP);
    
    while(1) {

        vTaskDelay(1000 / portTICK_RATE_MS);
    }

}






void buttonTask( void * parameter ) {
 
   
    
    while(1) {
        
        digitalWrite(ONBOARD_LED, LOW);
        vTaskDelay(1000 / portTICK_RATE_MS);
        
        digitalWrite(ONBOARD_LED, HIGH);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

}

   */