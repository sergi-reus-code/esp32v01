#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class playerClass 

{
  private:  
    int m_file_size;
  
  
  public:
    playerClass();
    void begin();
    void play(const char *fname);

};



