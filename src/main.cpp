#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "classes/led/ledsClass.h"

#include "esp32-hal-log.h"
static const char *TAG = "MAIN PROGRAM";

static TaskHandle_t ledsHandler = NULL; //Leds
static TaskHandle_t recordHandler = NULL; //Record
static TaskHandle_t sdHandler = NULL; //SD 
static TaskHandle_t commsHandler = NULL; //Comms Send&Receiver 
static TaskHandle_t playerHandler = NULL; //Player
static ledsClass ledsObject;

void ledsTask(void *params)
{
  //Creamos el objeto leds
  ledsObject.animalSound();

  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver LEDS \n", state);
  }
}

void recordTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver RECORD \n", state);
  }
}

void sdTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver SD \n", state);
  }
}

void commsTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver SEND&RECEIVER \n", state);
  }
}

void playerTask(void *params)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
    printf("received state %d times in receiver PLAYER \n", state);
  }
}


/*

void sender(void *params)
{
  while (true)
  {
    xTaskNotify(receiverHandler1, (1 << 0), eSetBits);
    xTaskNotify(receiverHandler1, (1 << 1), eSetBits);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    xTaskNotify(receiverHandler1, (1 << 2), eSetBits);
    xTaskNotify(receiverHandler1, (1 << 3), eSetBits);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    xTaskNotify(receiverHandler2, (1 << 0), eSetBits);
    xTaskNotify(receiverHandler2, (1 << 1), eSetBits);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    xTaskNotify(receiverHandler2, (1 << 2), eSetBits);
    xTaskNotify(receiverHandler2, (1 << 3), eSetBits);
    vTaskDelay(100 / portTICK_PERIOD_MS);


  }
}

*/










void setup(void)
{

  xTaskCreate(&ledsTask, "receiver1", 2048, NULL, 2, &ledsHandler);
  xTaskCreate(&recordTask, "receiver2", 2048, NULL, 2, &recordHandler);
  xTaskCreate(&sdTask, "receiver3", 2048, NULL, 2, &sdHandler);
  xTaskCreate(&commsTask, "receiver4", 2048, NULL, 2, &commsHandler);
  xTaskCreate(&playerTask, "receiver5", 2048, NULL, 2, &playerHandler);
  

  printf("Inicio programa iNote 2022  \n");

  //check if record task is ready
  vTaskDelay(100);

  xTaskNotify(ledsHandler, (1 << 0), eSetBits);
  xTaskNotify(ledsHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(ledsHandler, (1 << 2), eSetBits);
  xTaskNotify(ledsHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(recordHandler, (1 << 0), eSetBits);
  xTaskNotify(recordHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(recordHandler, (1 << 2), eSetBits);
  xTaskNotify(recordHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(sdHandler, (1 << 0), eSetBits);
  xTaskNotify(sdHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(sdHandler, (1 << 2), eSetBits);
  xTaskNotify(sdHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(commsHandler, (1 << 0), eSetBits);
  xTaskNotify(commsHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(commsHandler, (1 << 2), eSetBits);
  xTaskNotify(commsHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskNotify(playerHandler, (1 << 0), eSetBits);
  xTaskNotify(playerHandler, (1 << 1), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskNotify(playerHandler, (1 << 2), eSetBits);
  xTaskNotify(playerHandler, (1 << 3), eSetBits);
  vTaskDelay(1000 / portTICK_PERIOD_MS);



  //xTaskCreate(&sender, "sender", 2048, NULL, 2, NULL);
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