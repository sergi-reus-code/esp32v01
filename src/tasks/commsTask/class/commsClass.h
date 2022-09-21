#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class commsClass {
  public:
    //
    commsClass(){
        printf("en constructor de clase \n");
    }

    void animalSound() {
         printf("en animal sound \n");
      //cout << "The animal makes a sound \n";
    };
};

// Derived class
class comms2 : public commsClass {
  public:
  comms2(){printf("en animal sound \n");};
    void animalSound() {
      printf("en animal sound \n");
    }
};

