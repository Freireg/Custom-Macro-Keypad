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
uint8_t rowPin[] = {33, 32, 34};  //Rows 1, 2 and 3
uint8_t left_encoder[] = {19, 21}; //Pin A and B
uint8_t right_enconder[] = {22, 23};
uint8_t button[3][4] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                          {9, 10}};

AiEsp32RotaryEncoder LeftEncoder= AiEsp32RotaryEncoder(ROTARY_ENCODER2_A_PIN, ROTARY_ENCODER2_B_PIN, -1, ROTARY_ENCODER_STEPS);
AiEsp32RotaryEncoder RightEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER1_A_PIN, ROTARY_ENCODER1_B_PIN, -1, ROTARY_ENCODER_STEPS);

NanoKeyboard::NanoKeyboard()
{

}

NanoKeyboard::~NanoKeyboard(){}

void IRAM_ATTR readEncoder1ISR()
{
  RightEncoder.readEncoder_ISR();
}

void IRAM_ATTR readEncoder2ISR()
{
  LeftEncoder.readEncoder_ISR();
}


void NanoKeyboard::setup(void)
{
  pinMode(ROTARY_ENCODER2_A_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER2_B_PIN, INPUT_PULLUP);

  pinMode(ROTARY_ENCODER1_A_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER1_B_PIN, INPUT_PULLUP);

  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);

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
  

  LeftEncoder.begin();
  LeftEncoder.setup(readEncoder2ISR);
  LeftEncoder.setBoundaries(0, 1000, false);
  LeftEncoder.setAcceleration(250);

  RightEncoder.begin();
  RightEncoder.setup(readEncoder1ISR);
  RightEncoder.setBoundaries(0, 1000, false);
  RightEncoder.setAcceleration(250);

}

uint8_t NanoKeyboard::begin(void)
{
  if(bleKeyboard.isConnected()) 
  {
    return 1;
  }
  else
  {
    if(digitalRead(BLED))
    {
      digitalWrite(BLED, LOW);
    }
    else 
    {
      digitalWrite(BLED, HIGH);
    }
    delay(150);
    return 0;
  }
  
}

void NanoKeyboard::run(void)
{
  readFuncButton();
  readLeftEncoder(left_encoder);
  readRightEncoder(right_enconder);
  readMatrix();
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
      selectedSetup++;
    }
    ledMode();
    delay(300);
  }
  else{ ledMode(); }
  
}

void NanoKeyboard::readLeftEncoder(uint8_t *encoder)
{
  aState = LeftEncoder.readEncoder();
  if(LeftEncoder.encoderChanged())
  {
    if(aState != aLastState)
    {
      switch (selectedSetup)
      {
      case 1:
        for(uint8_t i = 0; i < sizeof(SET1_ENCODER1_RIGHT); i++)
        {
          bleKeyboard.press(SET1_ENCODER1_RIGHT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      case 2:
        for(uint8_t i = 0; i < sizeof(SET2_ENCODER1_RIGHT); i++)
        {
          bleKeyboard.press(SET2_ENCODER1_RIGHT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      case 3:
        for(uint8_t i = 0; i < sizeof(SET3_ENCODER1_RIGHT); i++)
        {
          bleKeyboard.press(SET3_ENCODER1_RIGHT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      default:
        break;
      }

    }
    else
    {
      switch (selectedSetup)
      {
      case 1:
        for(uint8_t i = 0; i < sizeof(SET1_ENCODER1_LEFT); i++)
        {
          bleKeyboard.press(SET1_ENCODER1_LEFT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      case 2:
        for(uint8_t i = 0; i < sizeof(SET2_ENCODER1_LEFT); i++)
        {
          bleKeyboard.press(SET2_ENCODER1_LEFT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      case 3:
        for(uint8_t i = 0; i < sizeof(SET3_ENCODER1_LEFT); i++)
        {
          bleKeyboard.press(SET3_ENCODER1_LEFT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      default:
        break;
    }

  delayMicroseconds(600);
  }

  aLastState = aState;
  }
}


void NanoKeyboard::readRightEncoder(uint8_t *encoder)
{
  bState = RightEncoder.readEncoder();

  if(bState != bLastState)
  {
    if(RightEncoder.readEncoder() != bState)
    {
      switch (selectedSetup)
      {
      case 1:
        for(uint8_t i = 0; i < sizeof(SET1_ENCODER2_RIGHT); i++)
        {
          bleKeyboard.press(SET1_ENCODER2_RIGHT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      case 2:
        for(uint8_t i = 0; i < sizeof(SET2_ENCODER2_RIGHT); i++)
        {
          bleKeyboard.press(SET2_ENCODER2_RIGHT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      case 3:
        for(uint8_t i = 0; i < sizeof(SET3_ENCODER2_RIGHT); i++)
        {
          bleKeyboard.press(SET3_ENCODER2_RIGHT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      default:
        break;
      }

    }
    else
    {
      switch (selectedSetup)
      {
      case 1:
        for(uint8_t i = 0; i < sizeof(SET1_ENCODER2_LEFT); i++)
        {
          bleKeyboard.press(SET1_ENCODER2_LEFT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      case 2:
        for(uint8_t i = 0; i < sizeof(SET2_ENCODER2_LEFT); i++)
        {
          bleKeyboard.press(SET2_ENCODER2_LEFT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      case 3:
        for(uint8_t i = 0; i < sizeof(SET3_ENCODER2_LEFT); i++)
        {
          bleKeyboard.press(SET3_ENCODER2_LEFT[i]);
        }
        bleKeyboard.releaseAll();
        break;
      default:
        break;
    }

  delayMicroseconds(600);
  }

  bLastState = bState;
  }
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
  switch (button)
  {
  case 1:
    for (size_t i = 0; i < sizeof(SET2_KEY_B1); i++)
    {
      bleKeyboard.press(SET2_KEY_B1[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 2:
    for (size_t i = 0; i < sizeof(SET2_KEY_B2); i++)
    {
      bleKeyboard.press(SET2_KEY_B2[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 3:
    for (size_t i = 0; i < sizeof(SET2_KEY_B3); i++)
    {
      bleKeyboard.press(SET2_KEY_B3[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 4:
    for (size_t i = 0; i < sizeof(SET2_KEY_B4); i++)
    {
      bleKeyboard.press(SET2_KEY_B4[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 5:
    for (size_t i = 0; i < sizeof(SET2_KEY_B5); i++)
    {
      bleKeyboard.press(SET2_KEY_B5[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 6:
    for (size_t i = 0; i < sizeof(SET2_KEY_B6); i++)
    {
      bleKeyboard.press(SET2_KEY_B6[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 7:
    for (size_t i = 0; i < sizeof(SET2_KEY_B7); i++)
    {
      bleKeyboard.press(SET2_KEY_B7[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 8:
    for (size_t i = 0; i < sizeof(SET2_KEY_B8); i++)
    {
      bleKeyboard.press(SET2_KEY_B8[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 9:
    for (size_t i = 0; i < sizeof(SET2_KEY_B9); i++)
    {
      bleKeyboard.press(SET2_KEY_B9[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 10:
    for (size_t i = 0; i < sizeof(SET2_KEY_B10); i++)
    {
      bleKeyboard.press(SET2_KEY_B10[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  default:
    break;
  }
}

void NanoKeyboard::runThirdSet(uint8_t button)
{
  //Do your verification routine
  switch (button)
  {
  case 1:
    for (size_t i = 0; i < sizeof(SET3_KEY_B1); i++)
    {
      bleKeyboard.press(SET3_KEY_B1[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 2:
    for (size_t i = 0; i < sizeof(SET3_KEY_B2); i++)
    {
      bleKeyboard.press(SET3_KEY_B2[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 3:
    for (size_t i = 0; i < sizeof(SET3_KEY_B3); i++)
    {
      bleKeyboard.press(SET3_KEY_B3[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 4:
    for (size_t i = 0; i < sizeof(SET3_KEY_B4); i++)
    {
      bleKeyboard.press(SET3_KEY_B4[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 5:
    for (size_t i = 0; i < sizeof(SET3_KEY_B5); i++)
    {
      bleKeyboard.press(SET3_KEY_B5[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 6:
    for (size_t i = 0; i < sizeof(SET3_KEY_B6); i++)
    {
      bleKeyboard.press(SET3_KEY_B6[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 7:
    for (size_t i = 0; i < sizeof(SET3_KEY_B7); i++)
    {
      bleKeyboard.press(SET3_KEY_B7[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 8:
    for (size_t i = 0; i < sizeof(SET3_KEY_B8); i++)
    {
      bleKeyboard.press(SET3_KEY_B8[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 9:
    for (size_t i = 0; i < sizeof(SET3_KEY_B9); i++)
    {
      bleKeyboard.press(SET3_KEY_B9[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  case 10:
    for (size_t i = 0; i < sizeof(SET3_KEY_B10); i++)
    {
      bleKeyboard.press(SET3_KEY_B10[i]);
    }
    bleKeyboard.releaseAll();    
    break;
  default:
    break;
  }
}

void NanoKeyboard::ledMode(void)
{
  switch (selectedSetup)
  {
  case 1:
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    delayMicroseconds(10);
    digitalWrite(RLED,HIGH);
    break;
  case 2:
    digitalWrite(BLED, LOW);
    digitalWrite(RLED, LOW);
    delayMicroseconds(10);
    digitalWrite(GLED,HIGH);
    break;
  case 3:
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    delayMicroseconds(10);
    digitalWrite(BLED,HIGH);
    break;  
  default:
    break;
  }
}