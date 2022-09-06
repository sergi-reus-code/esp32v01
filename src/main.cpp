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
/*
const char* myDomain = "script.google.com";
String myScript = "/";    
String myFoldername = "&myFoldername=ESP32-CAM";    
String myFilename = "&myFilename=ESP32-CAM.jpg";    
String myImage = "&myFile=";  //Imagen que cargo en el esp32
*/
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include "soc/soc.h"            
#include "soc/rtc_cntl_reg.h"   
#include "FS.h"                 
#include "SD.h"             
#include "Base64.h"    

//Arduino LOGI , don't delete never
#include <esp32-hal-log.h>

static const char* TAG = "MyModule";
touch_pad_t touchPin;
RTC_DATA_ATTR int bootCount = 0;
// EZBUTTON!!!!!!!!!!!!!!!






TaskHandle_t Task0;
TaskHandle_t Task1;

WiFiMulti wifiMulti;


void wait_for_button_push()
{
  while (gpio_get_level(GPIO_BUTTON) == 0)
  {
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void record(I2SSampler *input, const char *fname)
{
  int16_t *samples = (int16_t *)malloc(sizeof(int16_t) * 1024);
  ESP_LOGI(TAG, "Start recording");
  input->start();
  
  // open the file on the sdcard
  FILE *fp = fopen(fname, "wb");
  
  // create a new wave file writer
  WAVFileWriter *writer = new WAVFileWriter(fp, input->sample_rate());
  
  // keep writing until the user releases the button
  while (gpio_get_level(GPIO_BUTTON) == 1)
  {
    
    int samples_read = input->read(samples, 1024);
    int64_t start = esp_timer_get_time();
    writer->write(samples, samples_read);
    int64_t end = esp_timer_get_time();
    ESP_LOGI(TAG, "Wrote %d samples in %lld microseconds", samples_read, end - start);
  }
  // stop the input
  input->stop();
  // and finish the writing
  writer->finish();
  fclose(fp);
  delete writer;
  free(samples);
  ESP_LOGI(TAG, "Finished recording");
}

void play(Output *output, const char *fname)
{
  int16_t *samples = (int16_t *)malloc(sizeof(int16_t) * 1024);
  // open the file on the sdcard
  FILE *fp = fopen(fname, "rb");
  // create a new wave file writer
  WAVFileReader *reader = new WAVFileReader(fp);
  ESP_LOGI(TAG, "Start playing");
  output->start(reader->sample_rate());
  ESP_LOGI(TAG, "Opened wav file");
  // read until theres no more samples
  while (true)
  {
    int samples_read = reader->read(samples, 1024);
    if (samples_read == 0)
    {
      break;
    }
    ESP_LOGI(TAG, "Read %d samples", samples_read);
    output->write(samples, samples_read);
    ESP_LOGI(TAG, "Played samples");
  }
  // stop the input
  output->stop();
  fclose(fp);
  delete reader;
  free(samples);
  ESP_LOGI(TAG, "Finished playing");
}


/*

void main_task_1(void *param)
{
  ESP_LOGI(TAG, "Starting up CORE 1");

#ifdef USE_SPIFFS
  //ESP_LOGI(TAG, "Mounting SPIFFS on /sdcard");
  //SPIFFS.begin(true, "/sdcard");
#else
  ESP_LOGI(TAG, "Mounting SDCard on /sdcard");
  //new SDCard("/sdcard", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);
#endif

  ESP_LOGI(TAG, "Creating microphone");


  I2SSampler *input = new I2SMEMSSampler(I2S_NUM_0, i2s_mic_pins, i2s_mic_Config);



  Output *output = new I2SOutput(I2S_NUM_0, i2s_speaker_pins);


  gpio_set_direction(GPIO_BUTTON, GPIO_MODE_INPUT);
  gpio_set_pull_mode(GPIO_BUTTON, GPIO_PULLDOWN_ONLY);

  while (true)
  {

    

    // wait for the user to push and hold the button
    wait_for_button_push();
    record(input, "/sdcard/test.wav");
    // wait for the user to push the button again
    wait_for_button_push();
    play(output, "/sdcard/test.wav");
    
    ESP_LOGI(TAG, "Doing up CORE 1");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
*/

void main_task_1(void *param){

/*

  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }

  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD_MMC card attached");
    SD.end();
    return;
  }
  Serial.println("");
  Serial.print("SD_MMC Card Type: ");
  if(cardType == CARD_MMC){
      Serial.println("MMC");
  } else if(cardType == CARD_SD){
      Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }  
  Serial.printf("SD Card Size: %lluMB\n", SD.cardSize() / (1024 * 1024));
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
  Serial.println();
  
  SD.end();   

*/


  //ESP_LOGI(TAG, "Starting up CORE 1");

  //vTaskDelay(500);
  //ESP_LOGI(TAG, "Mounting SDCard on /sdcard");
  //vTaskDelay(500);
  //new SDCard("/sdcard", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);
  //vTaskDelay(500);    

  ESP_LOGI(TAG, "Creating microphone");


  //I2SSampler *input = new I2SMEMSSampler(I2S_NUM_0, i2s_mic_pins, i2s_mic_Config);



  //Output *output = new I2SOutput(I2S_NUM_0, i2s_speaker_pins);


  gpio_set_direction(GPIO_BUTTON, GPIO_MODE_INPUT);
  gpio_set_pull_mode(GPIO_BUTTON, GPIO_PULLDOWN_ONLY);

  while (true)
  {

    Serial.println("Estoy en el bucle 0");
  

    // wait for the user to push and hold the button
    wait_for_button_push();

     Serial.println("Estoy en el bucle 1");
    //record(input, "/sdcard/test.wav");
    // wait for the user to push the button again
    wait_for_button_push();
    //play(output, "/sdcard/test.wav");
    
    ESP_LOGI(TAG, "Doing up CORE 1");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }




}

void main_task_0(void *param){

    while (true)
  {
  //WiFi.mode(WIFI_STA);

  //Serial.println("");
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  //WiFi.begin(ssid, password);  
  
    //wifiMulti.addAP("ssid_from_AP_1", "your_password_for_AP_1");
    //wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
    //wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3")



  long int StartTime=millis();
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    if ((StartTime+10000) < millis()) break;  //2 segundos
  } 

  Serial.println("");
  Serial.println("STAIP address: ");
  Serial.println(WiFi.localIP());
    
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reset");
    delay(25);
    ESP.restart();   
  }
   Serial.println(" Task0 running on core " + String(xPortGetCoreID()));
   vTaskDelay(pdMS_TO_TICKS(1245));
  }

}

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


void callback(){

  if (bootCount == 0)
  {
    ++bootCount;
  
  } else {
    
    //dar de alta semaphoro
    ++bootCount;
  
  }

}









void setup()
{

Serial.begin(115200);
delay(100);
Serial.println("Estoy en el inicio  " + String(bootCount));



  /*
  WiFi.mode(WIFI_STA);

  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);  
  
  long int StartTime=millis();
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    if ((StartTime+10000) < millis()) break;
  } 

  Serial.println("");
  Serial.println("STAIP address: ");
  Serial.println(WiFi.localIP());
    
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reset");
    delay(25);
    ESP.restart();   
  }
*/

  


  //read a image file from sd card and upload it to Google drive.
  //sendSDImageToGoogleDrive("alba1.jpg");


  //ESP_LOGI(TAG, "Creating main task on CPU0 -> WIFI @ Comms");
  //xTaskCreatePinnedToCore(main_task_0, "Main0", 4096, NULL, 1, &Task0,0);

  //ESP_LOGI(TAG, "Creating main task on CPU1 -> I2S Manager (Microphone @ Speaker");
  //xTaskCreatePinnedToCore(main_task_1, "Main1", 4096, NULL, 1, &Task1,1);

  touchAttachInterrupt(T9, callback, Threshold);

  esp_sleep_enable_touchpad_wakeup();
  
  esp_deep_sleep_start();

}

void loop() // Run on core 1
{


vTaskDelete(NULL);


}