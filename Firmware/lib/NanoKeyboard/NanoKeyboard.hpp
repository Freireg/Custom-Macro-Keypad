/**
 * @file NanoKeyboard.hpp
 * @author Guilherme Freire (guilherme.freire@fbest.org.br)
 * @brief 
 * @version 0.1
 * @date 2022-08-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef NANOKEYBOARD_H_
#define NANOKEYBOARD_H_

#include <Arduino.h>
#include <BLEDevice.h>
#include <BleKeyboard.h>

#define inCount           3
#define outCount          4
#define MAX_MACRO_SIZE    3
#define MAX_LAYOUT_SETUP  3


#define longPressDelay  350
#define spamSpeed 15


typedef struct{
  const char keyMacros[3][4][MAX_MACRO_SIZE];
  char encMacros[2][2][MAX_MACRO_SIZE];
  uint8_t setup;
} Layout_t;


//Protoypes
void readMatrix(void);
void readEncoders(void);
void readFunction(void);
void pressMacro(char *macro);

#endif