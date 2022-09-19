#include <Arduino.h>

#include <stdio.h>
//#include <FreeRTOS.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <I2SMEMSSampler.h>

#include <I2SOutput.h>

#include <SDCard.h>
#include "SPIFFS.h"
#include <WAVFileReader.h>
#include <WAVFileWriter.h>
#include "config.h"


const char* ssid     = "casa1";   
const char* password = "nike2004";   

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include "soc/soc.h"            
#include "soc/rtc_cntl_reg.h"   
#include "FS.h"                 
#include "SD.h"             
#include "Base64.h"    


touch_pad_t touchPin;
RTC_DATA_ATTR int bootCount = 0;
// EZBUTTON!!!!!!!!!!!!!!!


#include "inote_hal/button/buttonClass.h"

buttonClass myButton;

buttonClass *myButton2 = NULL;

TaskHandle_t Task0_0;
TaskHandle_t Task1_0;
TaskHandle_t Task2_0;

TaskHandle_t Task0_1;
TaskHandle_t Task1_1;
TaskHandle_t Task2_1;


SemaphoreHandle_t xSemaphoreGoSleep = NULL;


WiFiMulti wifiMulti;


void wait_for_button_push()
{
  while (gpio_get_level(GPIO_BUTTON) == 0)
  {
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}











void main_task_0_0(void *param){
Serial.println("Starting up 0 in CORE 0");
  //vTaskDelay(2000);  
  //myButton.animalSound();
  //buttonClass *myButton2 = new Pig();
  //myButton2->animalSound();
  vTaskDelay(100);
  while (1){
      vTaskDelay(100);
  }
}


void main_task_0_1(void *param)
{
  Serial.println("Starting up 1 in CORE 0");
  while (1){
      vTaskDelay(100);
  }
}


void main_task_0_2(void *param){

  Serial.println("Starting up 2 in CORE 0");
  while (1){
      vTaskDelay(100);
  }

}

void main_task_1_0(void *param){
Serial.println("Starting up 0 in CORE 1");
  //vTaskDelay(2000);  
  //myButton.animalSound();
  //buttonClass *myButton2 = new Pig();
  //myButton2->animalSound();
  vTaskDelay(100);
  while (1){
      vTaskDelay(100);
  }
}


void main_task_1_1(void *param)
{
  Serial.println("Starting up 1 in CORE 1");
  while (1){
      vTaskDelay(100);
  }
}


void main_task_1_2(void *param){

  Serial.println("Starting up 2 in CORE 1");
  while (1){
      vTaskDelay(100);
  }

}


void setup() {

  Serial.begin(115200);
  delay(100);

  //ESP_LOGI(TAG, "Creating main task on CPU0 -> WIFI @ Comms");
    xTaskCreatePinnedToCore(main_task_0_0, "Main0", 1024, NULL, 1, &Task0_0,0);
    xTaskCreatePinnedToCore(main_task_0_1, "Main1", 1024, NULL, 1, &Task1_0,0);
    xTaskCreatePinnedToCore(main_task_0_2, "Main2", 1024, NULL, 1, &Task2_0,0);

  //ESP_LOGI(TAG, "Creating main task on CPU1 -> I2S Manager (Microphone @ Speaker");
    xTaskCreatePinnedToCore(main_task_1_0, "Main0", 1024, NULL, 1, &Task0_1,1);
    xTaskCreatePinnedToCore(main_task_1_1, "Main1", 1024, NULL, 1, &Task1_1,1);
    xTaskCreatePinnedToCore(main_task_1_2, "Main2", 1024, NULL, 1, &Task2_1,1);






//buttonClass *myButton2 = new Pig();

//myButton2->animalSound();

//Pig myButton3;
//myButton3.animalSound();

//xSemaphoreGoSleep = xSemaphoreCreateBinary();

//touchAttachInterrupt(T9, inicio_cb, Threshold);

//esp_sleep_enable_touchpad_wakeup();

//goSleep();


    //read a image file from sd card and upload it to Google drive.
//sendSDImageToGoogleDrive("alba1.jpg");




}

void loop() // Run on core 1
{ vTaskDelete(NULL); }




/*
void goSleep () {

esp_deep_sleep_start();

}
*/



/*

String sendSDImageToGoogleDrive(String filepath) 
{
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return "";
  }  
  
  fs::FS &fs = SD;
  File file = fs.open("/" + filepath);
  if(!file){
    Serial.println("Failed to open file for reading");
    SD.end();  
    return "";  
  }
  Serial.println("Read from file: "+filepath);
  Serial.println("file size: "+String(file.size()));
  Serial.println("");
  
  const char* myDomain = "http://192.168.18.5:3001/upload/";
  String getAll="", getBody = "";

  Serial.println("Connect to " + String(myDomain));
  WiFiClient client_tcp;
  
  if (client_tcp.connect("192.168.18.5", 3001)) {  
  
    client_tcp.println("POST /upload HTTP/1.1");
    client_tcp.println("Host: " + String(myDomain));
    client_tcp.println("Content-Length: " + String(file.size()));
    client_tcp.println("Content-Type: application/octet-stream");
    client_tcp.println("File: " + filepath);
    client_tcp.println("Connection: keep-alive");
    client_tcp.println();

        int len = 0;
        int total = 0;
        uint8_t buf[1025] = {};
        size_t _len = 256;
        do {
            len = file.read(buf, _len);
            client_tcp.write(buf, len);
            total += len;
        } while (len > 0);


        client_tcp.println();

  File filew = fs.open("/resp.jpg",FILE_WRITE);
  if(!filew){
    Serial.println("Failed to open file for reading");
    SD.end();  
    
  }

   //Wait for response
    
    int waitTime = 10000;   // timeout 10 seconds
    long startTime = millis();
    boolean state = false;
    
    while ((startTime + waitTime) > millis())
    {
      Serial.print(".");
      delay(100); 

        
      while (client_tcp.available()) 
      {
          char c = client_tcp.read();
          
          if (state==true) {
              filew.print(c);
              getBody += String(c);}        
          if (c == '\n') 
          {
            if (getAll.length()==0) state=true; 
            getAll = "";
          } 
          else if (c != '\r')
            getAll += String(c);
          startTime = millis();
       }
       if (getBody.length()>0) break;
    }
    client_tcp.stop();
    //Serial.println(getBody);
    filew.close();


   Serial.println("Guardar en archivo Wav");


  }
  else {
    getBody="Connected to " + String(myDomain) + " failed.";
    Serial.println("Connected to " + String(myDomain) + " failed.");
  }
  
  return getBody;

}


*/


   /*
  wifiMulti.addAP("casa1", "nike2004");  //Riu
  wifiMulti.addAP("MOVISTAR_4EB8", "87DC72A32E66337156AA");  //Puigcerdà
  wifiMulti.addAP("AndroidAP2C22", "nike2004");  //Mobil

  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }

  Serial.println(" Task0 running on core " + String(xPortGetCoreID()));

  while (1){
      vTaskDelay(10);
  }*/


  /*

  void inicio_cb(){

  if (bootCount == 0)     //primer inicio
  {
    ++bootCount;
    vTaskDelay(500);
  
  } else {
    
    //dar de alta semaphoro
    ++bootCount;




  }


Serial.println("estoy en boot" + String(bootCount) );

}

*/