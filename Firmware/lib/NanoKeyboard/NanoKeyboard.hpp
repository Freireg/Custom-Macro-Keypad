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
#include <BleKeyboard.h>
#include "KeyboardLayout.hpp"


#define FUNC_BUTTON   2

#define ENCONDER_A    21
#define ENCONDER_B    19
#define inCount   3
#define outCount  4
#define longPressDelay  350
#define spamSpeed 15

class NanoKeyboard
{
  public:
    NanoKeyboard(void);
    ~NanoKeyboard(void);
    void begin(void);
    void setup(void);
    
  private:
    BleKeyboard bleKeyboard;
    int aState, aLastState;
    int counter = 0;
    uint8_t keyDown[inCount][outCount];
    bool keyLong[inCount][outCount];
    uint8_t selectedSetup = 1;
    void readEncoder(void);
    void readFuncButton(void);
    void readMatrix(void);
    void keyPressed(uint8_t row, uint8_t col);
    void keyReset(uint8_t row, uint8_t col);
    void runFirstSet(uint8_t button);
    void runSecondSet(uint8_t button);
    void runThirdSet(uint8_t button);

};

#endif