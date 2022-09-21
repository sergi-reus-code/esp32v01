#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class ledsClass {
  public:
    //
    ledsClass(){
        printf("en constructor de clase \n");
    }

    void animalSound() {
         printf("en animal sound \n");
      //cout << "The animal makes a sound \n";
    };
};

// Derived class
class leds2 : public ledsClass {
  public:
  leds2(){printf("en animal sound \n");};
    void animalSound() {
      printf("en animal sound \n");
    }
};

