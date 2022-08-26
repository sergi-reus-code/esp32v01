#include <Arduino.h>
#include <stdio.h>
//#include <FreeRTOS.h>
#include <I2SMEMSSampler.h>
#include <I2SOutput.h>
#include <SDCard.h>
#include "SPIFFS.h"
#include <WAVFileReader.h>
#include <WAVFileWriter.h>
#include "esp32-hal-log.h"

#include "hardware/led/ledTask.h"
#include "hardware/button/buttonTask.h"

#include "config.h"

static const char *TAG = "AW";

static TaskHandle_t ledTask_handle;


void wait_for_button_push()
{
  while (gpio_get_level(GPIO_BUTTON) == 0)
  {
    ESP_LOGI(TAG, "Button pressed");
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

void main_task(void *param)
{
  ESP_LOGI(TAG, "Starting up");

#ifdef USE_SPIFFS
  ESP_LOGI(TAG, "Mounting SPIFFS on /sdcard");

  //SPIFFS.begin(false,"/sdcard");

  SPIFFS.totalBytes();
  SPIFFS.begin(true, "/sdcard");
  bool resp = SPIFFS.exists("/Hello.mp3");
  Serial.println(resp);

  
#else
  ESP_LOGI(TAG, "Mounting SDCard on /sdcard");
  new SDCard("/sdcard", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);
#endif

  //ESP_LOGI(TAG, "Creating microphone");
#ifdef USE_I2S_MIC_INPUT
  //I2SSampler *input = new I2SMEMSSampler(I2S_NUM_0, i2s_mic_pins, i2s_mic_Config);
#else
  I2SSampler *input = new ADCSampler(ADC_UNIT_1, ADC1_CHANNEL_7, i2s_adc_config);
#endif

#ifdef USE_I2S_SPEAKER_OUTPUT
  //Output *output = new I2SOutput(I2S_NUM_0, i2s_speaker_pins);
#else
  Output *output = new DACOutput(I2S_NUM_0);
#endif



  while (true)
  {
    ESP_LOGI(TAG, "Waitting");

    // wait for the user to push and hold the button
    wait_for_button_push();
    ESP_LOGI(TAG, "Recording");
    //record(input, "/sdcard/test.wav");
    // wait for the user to push the button again
    wait_for_button_push();
    ESP_LOGI(TAG, "Playing");
    //play(output, "/sdcard/test.wav");
    
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup()
{
  Serial.begin(115200);
  vTaskDelay(pdMS_TO_TICKS(1000));

    gpio_set_direction(GPIO_BUTTON, GPIO_MODE_INPUT);
  gpio_set_pull_mode(GPIO_BUTTON, GPIO_PULLDOWN_ONLY);
  
  xTaskCreate(main_task, "Main", 4096, NULL, 0, NULL);
}

void loop()
{
}