#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class recordClass {
  public:
    //
    recordClass(){
        printf("en constructor de clase \n");
    }

    void animalSound() {
         printf("en animal sound \n");
      //cout << "The animal makes a sound \n";
    };
};

// Derived class
class record2 : public recordClass {
  public:
  record2(){printf("en animal sound \n");};
    void animalSound() {
      printf("en animal sound \n");
    }
};

