#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "I2SSampler.h"
#include "I2SMEMSSampler.h"

#include "WAVFileWriter.h"

#include "SDCard.h"

#include "config.h"

#include "class/recordClass.h"

const char *TAGR = "RECORD TASK";



void recordTask(void *params)
{
  //Creamos el objeto leds
  recordClass *recordObject = new recordClass();
 
  vTaskDelay(1000);
  
  TaskHandle_t mainTaskHandle = xTaskGetHandle("mainTask");
  if(mainTaskHandle == NULL){ ESP_LOGE(TAGR, "Main Handler Null -----> ERROR MUST RESTART");}

  uint state;


  ESP_LOGI(TAGR, "Mounting SDCard on /sdcard");

  //new SDCard("/sdcard", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);
  
  vTaskDelay(1000);
  ESP_LOGI(TAGR, "Creating microphone");

  I2SSampler *input = new I2SMEMSSampler(I2S_NUM_0, i2s_mic_pins, i2s_mic_Config);













  uint16_t touch_value2 = touchRead(14);

  const char *fname = "tett.wav";

    while (touch_value2 < Threshold)
    {

      touch_value2 = touchRead(14);
      ESP_LOGI(TAGR, "gravando");

/*
                                int16_t *samples = (int16_t *)malloc(sizeof(int16_t) * 1024);
                                ESP_LOGI(TAGR, "Start recording");
                                input->start();
                                // open the file on the sdcard
                                FILE *fp = fopen(fname, "wb");
                                // create a new wave file writer
                                WAVFileWriter *writer = new WAVFileWriter(fp, input->sample_rate());
                                // keep writing until the user releases the button
                                while (touch_value2 < Threshold)
                                {
                                  int samples_read = input->read(samples, 1024);
                                  int64_t start = esp_timer_get_time();
                                  writer->write(samples, samples_read);
                                  int64_t end = esp_timer_get_time();
                                  ESP_LOGI(TAGR, "Wrote %d samples in %lld microseconds", samples_read, end - start);
                                }
                                // stop the input
                                input->stop();
                                // and finish the writing
                                writer->finish();
                                fclose(fp);
                                delete writer;
                                free(samples);
                                ESP_LOGI(TAGR, "Finished recording");

*/











      
      
      

      
    }


  xTaskNotify(mainTaskHandle, (1 << 0), eSetValueWithOverwrite);
  vTaskDelay(500);  
  vTaskDelete(NULL);



}