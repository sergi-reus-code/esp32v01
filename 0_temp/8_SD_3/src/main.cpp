#include <Arduino.h>

#include <SD_MMC.h>

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

if(!SD_MMC.begin(5)) {
Serial.println("SD Card Mount Failure… Rebooting");
// ESP.restart();
} else {
fs::FS &tfs = SD_MMC;
uint8_t cardType = SD_MMC.cardType();
switch (cardType) {
case CARD_NONE : Serial.println("No SD Card type found");
break;
case CARD_MMC : Serial.println("MMC Card detected…");
break;
case CARD_SD : Serial.println("SD Card detected…");
break;
case CARD_SDHC : Serial.println("SDHC Card detected…");
break;
default : Serial.println("Default card detected ???");
break;
}
uint8_t bufr[5] = {'a','b', 'c', 'd', '\0'};
String tstpath = "/test1.txt";
File xfile=tfs.open(tstpath.c_str(), FILE_WRITE);
xfile.write(bufr, 5);
delay(100);
xfile.close();
delay(100);
File tfile=tfs.open(tstpath.c_str());
unsigned int tstsz = tfile.size();
Serial.println ("Test file saved as " + tstpath + " with size of " + String(tstsz) );
tfile.close();
}
SD_MMC.end();











  int touchValue = touchRead(T3);
  Serial.print(touchValue);

  if(touchValue < Threshold){
    inFunction=1;
    
    Serial.println(String(inFunction));
      xTaskCreatePinnedToCore(&mainFunction, "receiver", 2048, NULL, 2, NULL,1);
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
