/**
 * @file NanoKeyboard.cpp
 * @author Guilherme Freire (guilherme.freire@fbest.org.br)
 * @brief 
 * @version 0.1
 * @date 2022-08-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "NanoKeyboard.hpp"

uint8_t columnsPin[] = {4, 16, 17, 18}; //Columns 1, 2, 3 and 4 
uint8_t rowPin[] = {33, 32, 35};  //Rows 1, 2 and 3
//const char *button[3][4] = {{"B1", "B2", "B3", "B4"}, 
//                            {"B5", "B6", "B7", "B8"},
//                                  {"B9", "B10"}};
//
uint8_t button[3][4] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                          {9, 10}};

NanoKeyboard::NanoKeyboard()
{

}

NanoKeyboard::~NanoKeyboard(){}

void NanoKeyboard::setup(void)
{
  pinMode(ENCONDER_A, INPUT_PULLUP);
  pinMode(ENCONDER_B, INPUT_PULLUP);

  for(int i =0; i < outCount; i++)
  {
    pinMode(columnsPin[i], OUTPUT);
    digitalWrite(columnsPin[i], LOW);
  }

  for(int i = 0; i < inCount; i++)
  {
    pinMode(rowPin[i], INPUT_PULLDOWN);
  }

  bleKeyboard.begin();

  aLastState = digitalRead(ENCONDER_A);
}

void NanoKeyboard::begin(void)
{
  if(bleKeyboard.isConnected()) 
  {
    readFuncButton();
    readEncoder();
    readMatrix();
  }
}

void NanoKeyboard::readFuncButton(void)
{
  if(digitalRead(FUNC_BUTTON))
  {
    if(selectedSetup == 3)
    {
      selectedSetup = 1;
    }
    else
    {
    //  selectedSetup++;
    }
    delay(300);
  }
}

void NanoKeyboard::readEncoder(void)
{
  aState = digitalRead(ENCONDER_A);

  if(aState != aLastState)
  {
  if(digitalRead(ENCONDER_B) != aState)
  {
    counter++;
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_NUM_PLUS);
    bleKeyboard.releaseAll();
  }
  else
  {
    counter--;
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_NUM_MINUS);
    bleKeyboard.releaseAll();
  }

  delay(100);
  }

  aLastState = aState;
}

void NanoKeyboard::readMatrix(void)
{
  for(int i = 0; i < outCount; i++)
  {
    digitalWrite(columnsPin[i], HIGH);  //Setting one column HIGH      
    delayMicroseconds(5);

    for(int j = 0; j < inCount; j++)
    {
      if(digitalRead(rowPin[j]) == HIGH)
      {
        keyPressed(j,i);
      }
      else if(keyDown[j][i] != 0)
      {
        keyReset(j, i);
      }
    }
    digitalWrite(columnsPin[i], LOW);
    delayMicroseconds(500);
  }
}

void NanoKeyboard::keyPressed(uint8_t row, uint8_t col)
{
  if(keyDown[row][col] == 0) //If it's the first time the function has been called for this key
  {
    //bleKeyboard.print(button[row][col]);
    if(selectedSetup == 1)
    {
      runFirstSet(button[row][col]);
    }
    if(selectedSetup == 2)
    {
      runSecondSet(button[row][col]);
    }
    if(selectedSetup == 3)
    {
      runThirdSet(button[row][col]);
    }
  }
  else if(keyLong[row][col] && keyDown[row][col] > spamSpeed) //If the key has been held long enogh to warrant another keystroke set
  {
    if(selectedSetup == 1)
    {
      runFirstSet(button[row][col]);
    }
    if(selectedSetup == 2)
    {
      runSecondSet(button[row][col]);
    }
    if(selectedSetup == 3)
    {
      runThirdSet(button[row][col]);
    }
    keyDown[row][col] = 1;
  }
  else if(keyDown[row][col] > longPressDelay) //If the key has been held longer that longPressDelay, it switch into spam mode
  {
    keyLong[row][col] = true;
  }

  keyDown[row][col]++;
}

void NanoKeyboard::keyReset(uint8_t row, uint8_t col)
{
  keyDown[row][col] = 0;
  keyLong[row][col] = false;
}

void NanoKeyboard::runFirstSet(uint8_t button)
{
  //Do your verification routine
  switch (button)
  {
  case 1:
    for (size_t i = 0; i < sizeof(SET1_KEY_B1); i++)
    {
      bleKeyboard.press(SET1_KEY_B1[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 2:
    for (size_t i = 0; i < sizeof(SET1_KEY_B2); i++)
    {
      bleKeyboard.press(SET1_KEY_B2[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 3:
    for (size_t i = 0; i < sizeof(SET1_KEY_B3); i++)
    {
      bleKeyboard.press(SET1_KEY_B3[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 4:
    for (size_t i = 0; i < sizeof(SET1_KEY_B4); i++)
    {
      bleKeyboard.press(SET1_KEY_B4[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 5:
    for (size_t i = 0; i < sizeof(SET1_KEY_B5); i++)
    {
      bleKeyboard.press(SET1_KEY_B5[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 6:
    for (size_t i = 0; i < sizeof(SET1_KEY_B6); i++)
    {
      bleKeyboard.press(SET1_KEY_B6[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 7:
    for (size_t i = 0; i < sizeof(SET1_KEY_B7); i++)
    {
      bleKeyboard.press(SET1_KEY_B7[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 8:
    for (size_t i = 0; i < sizeof(SET1_KEY_B8); i++)
    {
      bleKeyboard.press(SET1_KEY_B8[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 9:
    for (size_t i = 0; i < sizeof(SET1_KEY_B9); i++)
    {
      bleKeyboard.press(SET1_KEY_B9[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 10:
    for (size_t i = 0; i < sizeof(SET1_KEY_B10); i++)
    {
      bleKeyboard.press(SET1_KEY_B10[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  default:
    break;
  }
}

void NanoKeyboard::runSecondSet(uint8_t button)
{
  //Do your verification routine
}

void NanoKeyboard::runThirdSet(uint8_t button)
{
  //Do your verification routine
}
