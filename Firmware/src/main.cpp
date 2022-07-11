#include <Arduino.h>
#include <BleKeyboard.h>


uint8_t readMatrix(void);
void matrixOutput(uint8_t keyPressed);
uint8_t rows[] = {16, 23, 24};
const int rowCount = sizeof(rows)/sizeof(rows[0]);

uint8_t cols[] = {27, 28, 29, 30};
const int colCount = sizeof(cols)/sizeof(cols[0]);

uint8_t key[colCount][rowCount];

BleKeyboard bleKeyboard;



void setup() {
  Serial.begin(9600);
  bleKeyboard.begin();

  /* Set every pin as input */
  for(uint8_t i = 0; i <rowCount; i++)
  {
    pinMode(rows[i], INPUT);
  }
  for(uint8_t i = 0; i <colCount; i++)
  {
    pinMode(cols[i], INPUT); //Do I need a pull-up?
  }

  /************************/
}

void loop() {
  uint8_t keyPressed;
  keyPressed = readMatrix();
  matrixOutput(keyPressed);
}

uint8_t readMatrix(void)
{
  uint8_t currentCol, currentRow;
  char pressedKey[3];
  for (uint8_t colIndex=0; colIndex < colCount; colIndex++)
  {
    currentCol = cols[colIndex];
    pinMode(currentCol, OUTPUT);
    digitalWrite(currentCol, HIGH); //If I use a pull-up, set as LOW

    for(uint8_t rowIndex=0; rowIndex < rowCount; rowIndex++)
    {
      currentRow = rows[rowIndex];
      pinMode(currentRow, INPUT); //Might change as well
      key[colIndex][rowIndex] = digitalRead(currentRow);
      if(key[colIndex][rowIndex]) //Might be low
      {
        return((rowIndex*10) + colIndex);
      }
    }
  pinMode(currentCol, INPUT);
  }
  
}

void matrixOutput(uint8_t keyPressed)
{
  switch (keyPressed)
  {
  case 0:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_1);
    bleKeyboard.releaseAll();
    break;
  case 1:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_2);
    bleKeyboard.releaseAll();
    break;
  case 2:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_3);
    bleKeyboard.releaseAll();
    break;
  case 3:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_4);
    bleKeyboard.releaseAll();
    break;
  case 10:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_5);
    bleKeyboard.releaseAll();
    break;
  case 11:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_6);
    bleKeyboard.releaseAll();
    break;
  case 12:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_7);
    bleKeyboard.releaseAll();
    break;
  case 13:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_8);
    bleKeyboard.releaseAll();
    break;
  case 20:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_NUM_9);
    bleKeyboard.releaseAll();
    break;
  case 21:
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.print("y");
    bleKeyboard.releaseAll();
    break;
  default:
    break;
  }
}