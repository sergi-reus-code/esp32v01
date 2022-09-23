#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class playerClass {
  public:
    //
    playerClass(){
        printf("en constructor de clase \n");
    }

    void animalSound() {
         //printf("en animal sound \n");
      //cout << "The animal makes a sound \n";
    };
};

// Derived class
class player2 : public playerClass {
  public:
  player2(){//printf("en animal sound \n");
  };
    void animalSound() {
      //printf("en animal sound \n");
    }
};

