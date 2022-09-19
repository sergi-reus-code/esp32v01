#include <Arduino.h>

static TaskHandle_t receiverHandler = NULL;


#define Threshold 40 /* Greater the value, more the sensitivity */


RTC_DATA_ATTR int inFunction = 0;
touch_pad_t touchPin;

void callback(){
  //placeholder callback function
}


void goToSleep(){
  touchAttachInterrupt(T3, callback, Threshold);
  esp_sleep_enable_touchpad_wakeup();
  esp_deep_sleep_start();
}



void sender(void *params)
{
  while (true)
  {
vTaskDelay(1000/ portTICK_PERIOD_MS);

    
    Serial.println(eTaskGetState(receiverHandler));
    xTaskNotify(receiverHandler, (1 << 1), eSetBits);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    xTaskNotify(receiverHandler, (1 << 4), eSetBits);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    goToSleep();
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



void mainFunction(void *params)
{
  
  while (touchRead(T3) < Threshold)
  {
    printf("pepepepe");

  }
  


  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    Serial.println(eTaskGetState(receiverHandler));
    printf("received state %d times\n", state);

  }
}


















void setup(){

  Serial.begin(115200);
  delay(250); //Take some time to open up the Serial Monitor

  int touchValue = touchRead(T3);
  Serial.print(touchValue);

  if(touchValue < Threshold){
    inFunction=1;
    
    Serial.println(String(inFunction));
      xTaskCreatePinnedToCore(&mainFunction, "receiver", 2048, NULL, 2, NULL,0);
      xTaskCreate(&receiver, "receiver", 2048, NULL, 2, &receiverHandler);
      xTaskCreate(&sender, "sender", 2048, NULL, 2, NULL);

  }
  else{
    inFunction=0;   
    Serial.println(String(inFunction)); 
    //Serial.println(" Do nothing");
    goToSleep();
  }


  
}

void loop(){
  //This will never be reached
}
