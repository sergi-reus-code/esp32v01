#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "tasks/ledsTask/ledsTask.h"
#include "tasks/recordTask/recordTask.h"
#include "tasks/sdTask/sdTask.h"
#include "tasks/commsTask/commsTask.h"
#include "tasks/playerTask/playerTask.h"


static TaskHandle_t ledsHandler = NULL; //Leds
static TaskHandle_t recordHandler = NULL; //Record
static TaskHandle_t sdHandler = NULL; //SD 
static TaskHandle_t commsHandler = NULL; //Comms Send&Receiver 
static TaskHandle_t playerHandler = NULL; //Player
static TaskHandle_t mainHandler = NULL; // Main program
 
RTC_DATA_ATTR int bootCount = 0;
#define Threshold 40 /* Greater the value, more the sensitivity */

void callback(){
  //placeholder callback function
}


void mainTask(void *params)
{

  // 1. Hacer round leds
  xTaskNotify(ledsHandler, (1 << 0), eSetBits);
  
  // 2. Record sound & Store on SD
  xTaskNotify(recordHandler, (1 << 0), eSetBits);
  xTaskNotify(sdHandler, (1 << 0), eSetBits);  

  // 3. Send to server & Receive response & Store to SD
  xTaskNotify(commsHandler, (1 << 0), eSetBits);
  xTaskNotify(sdHandler, (1 << 0), eSetBits);  
  
  // 4. Play de response
    xTaskNotify(playerHandler, (1 << 0), eSetBits);

  // 5. Check if interaction is done (Close/Repeat) 
   








  

  
  










  //Check all done



  
  printf("Bona nit.....\n");
  
  printf("Bona nit.....\n");
  vTaskDelay(2000);
  esp_deep_sleep_start();
  
  //xTaskCreate(&sender, "sender", 2048, NULL, 2, NULL);
  //return;

  






}












void setup(void)
{
 
  ++bootCount;



    //Setup interrupt on Touch Pad 3 (GPIO15)
  touchAttachInterrupt(T3, callback, Threshold);

  //Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();
  
  
  vTaskDelay(100); // only to take time to print on Serial
  printf("Inicio programa iNote 2022  \n");
  
  
  xTaskCreatePinnedToCore(&ledsTask,"asdasd",2048,NULL,1,&ledsHandler,1);
  xTaskCreatePinnedToCore(&recordTask, "recordTask", 2048, NULL, 2, &recordHandler,1);
  xTaskCreatePinnedToCore(&sdTask, "sdTask", 2048, NULL, 2, &sdHandler,1);
  xTaskCreatePinnedToCore(&commsTask, "commsTask", 2048, NULL, 2, &commsHandler,0);
  xTaskCreatePinnedToCore(&playerTask, "playerTask", 2048, NULL, 2, &playerHandler,1);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  xTaskCreatePinnedToCore(&mainTask, "main", 2048, NULL, 2, &mainHandler,1);



  
}

void loop(){
    
vTaskDelete(NULL);

}




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