#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class sdClass {
  public:
    //
    sdClass(){
        printf("en constructor de clase \n");
    }

    void animalSound() {
         //printf("en animal sound \n");
      //cout << "The animal makes a sound \n";
    };
};

// Derived class
class sd2 : public sdClass {
  public:
  sd2(){//printf("en animal sound \n");
  };
    void animalSound() {
      //printf("en animal sound \n");
    }
};

