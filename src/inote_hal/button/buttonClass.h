#pragma once

#include <Arduino.h>

class buttonClass {
  public:
    //
    buttonClass(){Serial.println("En constructor de base");};
    
    void animalSound() {
        Serial.println("Sound of base");
      //cout << "The animal makes a sound \n";
    }
};

// Derived class
class Pig : public buttonClass {
  public:
  Pig(){Serial.println("En constructor de Pig");};
    void animalSound() {
      Serial.println("Sound of Pig");
    }
};

// Derived class
class Dog : public buttonClass {
  public:
    void animalSound() {
      //cout << "The dog says: bow wow \n";
    }
}; 