#include <Arduino.h>


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
//#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include "soc/soc.h"            
#include "soc/rtc_cntl_reg.h"   
#include "FS.h"                 
#include "SD.h"             
#include "Base64.h"            



//https://github.com/zenmanenergy/ESP8266-Arduino-Examples/
String urlencode(String str)
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
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
















void setup() {
    
  Serial.begin(115200);
  delay(10);
  
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

  //read a image file from sd card and upload it to Google drive.
  sendSDImageToGoogleDrive("alba1.jpg");

  Serial.printf("Eso es todo");
  

}

void loop() {
  delay(100);
}

