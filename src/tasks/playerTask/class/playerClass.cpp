#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Arduino.h>

#include "playerClass.h"
#include "WAVFileReader.h"

static const char *TAG = "MAIN APP";

void playerClass::play()
{

I2SOutput *output = new I2SOutput(I2S_NUM_0, i2s_speaker_pins);

const char *fname ="/sdcard/test.wav";



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

void playerClass::play(const char *fname)
{
  ESP_LOGI(TAG, "Played samples");

  I2SOutput *output = new I2SOutput(I2S_NUM_0, i2s_speaker_pins);
  /*
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

  */
}