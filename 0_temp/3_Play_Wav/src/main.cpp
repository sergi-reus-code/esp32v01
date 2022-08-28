#include "Arduino.h"
#include "Audio.h"
#include "SPI.h"

// Digital I/O used
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18

#define I2S_DOUT      14
#define I2S_BCLK      12
#define I2S_LRC       27

Audio audio;

String ssid =     "casa1";
String password = "nike2004";



void setup() {
    Serial.begin(115200);
    pinMode(SD_CS, OUTPUT);      
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    SPI.setFrequency(1000000);
    SD.begin(SD_CS);

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) delay(1500);






    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(12); // 0...21

    //audio.connecttoFS(SD, "/320k_test.mp3");  //-> OK
//    audio.connecttoFS(SD, "/Pink-Panther.wav");   //-> DON'T PLAY      

      //audio.connecttohost("http://www.wdr.de/wdrlive/media/einslive.m3u");  //-> OK
    //audio.connecttohost("http://macslons-shop.com/media.asx");
    //audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.aac"); //  -> OK
      //audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.mp3"); //  128k mp3
//    audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/sample1.m4a"); // m4a

   // audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/Pink-Panther.wav"); //-> DON'T PLAY
    //audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/320k_test.mp3"); // -> OK

    //audio.connecttospeech("Wenn die Hunde schlafen, kann der Wolf gut Schafe stehlen.", "de");
   // audio.connecttospeech("Hola, ¿como estas?", "es");

}

void loop()
{
    audio.loop();
}

// optional
void audio_info(const char *info) {
Serial.print("info "); Serial.println(info);
}

void audio_id3data(const char *info) { //id3 metadata
Serial.print("id3data "); Serial.println(info);
}

void audio_eof_mp3(const char *info) { //end of file
Serial.print("eof_mp3 "); Serial.println(info);
}

void audio_showstation(const char *info) {
Serial.print("station "); Serial.println(info);
}

void audio_showstreamtitle(const char *info) {
Serial.print("streamtitle "); Serial.println(info);
}

void audio_bitrate(const char *info) {
Serial.print("bitrate "); Serial.println(info);
}

void audio_commercial(const char *info) { //duration in sec
Serial.print("commercial "); Serial.println(info);
}

void audio_icyurl(const char *info) { //homepage
Serial.print("icyurl "); Serial.println(info);
}

void audio_lasthost(const char *info) { //stream URL played
Serial.print("lasthost "); Serial.println(info);
}

void audio_eof_speech(const char *info) {
Serial.print("eof_speech "); Serial.println(info);
}