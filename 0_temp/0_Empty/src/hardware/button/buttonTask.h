#pragma once

#include <Arduino.h>

struct Button {
    uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
};


void buttonTask( void * parameter );