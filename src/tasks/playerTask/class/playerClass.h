#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "I2SOutput.h"

#include "config.h"

class playerClass 

{
  private:  
    int m_file_size;
  
  
  public:
    playerClass(){
      I2SOutput *output = new I2SOutput(I2S_NUM_0, i2s_speaker_pins);
      play(output, "/sdcard/test.wav");
    };

    
    void play(Output *output, const char *fname);


};



