#include <Arduino.h>
#include <BLEDevice.h>
#include <BleKeyboard.h>
#include "NanoKeyboard.hpp"


#define inCount   3
#define outCount  4
#define MAX_MACRO_SIZE 3


//Protoypes
void pressMacro(char *macro);
void readMatrix(void);

//----------------------------
typedef struct{
  char keyMacros[3][4][MAX_MACRO_SIZE];
  char encMacros[2][2][MAX_MACRO_SIZE];
  int setup;
} Layout;

Layout myLayout = {
  {
    {
    {KEY_F10, KEY_F11, KEY_F11}, //B1
    {KEY_F10},          //B2
    {KEY_F10},          //B3
    {KEY_F10}           //B4
    },
    {
    {KEY_F10, KEY_F11, KEY_F11}, //B5
    {KEY_F10},          //B6
    {KEY_F10},          //B7
    {KEY_F10}           //B8
    },
    {
    {KEY_F10, KEY_F11, KEY_F11}, //B9
    {KEY_F10}          //B10
    }
  },
  {
    { //Left encoder macros
      {KEY_F10, KEY_F11, KEY_F11}, //Turn left
      {KEY_F10, KEY_F11, KEY_F11}, //Turn right
    },
    { //Right encoder macros
      {KEY_F10, KEY_F11, KEY_F11}, //Turn left
      {KEY_F10, KEY_F11, KEY_F11}, //Turn right
    }
  },

  0
};

BleKeyboard NanoKeyboard("NanoKeyboard");

// Define the pins for the 12 keys arranged in a 3x4 matrix
const int rows = 3;
const int cols = 4;
uint8_t columnsPin[] = {4, 16, 17, 18}; //Columns 1, 2, 3 and 4 
uint8_t rowsPin[] = {33, 32, 34};  //Rows 1, 2 and 3
uint8_t left_encoder[] = {19, 21}; //Pin A and B
uint8_t right_enconder[] = {22, 23};
int aLastState, bLastState;
//-------------------------------------------------------------
// Define the key macros for each key
// char keyMacros[rows][cols][MAX_MACRO_SIZE] = 
// {
// {
//   {KEY_F10, KEY_F11, KEY_F11}, //B1
//   {KEY_F10},          //B2
//   {KEY_F10},          //B3
//   {KEY_F10}           //B4
// },
// {
//   {KEY_F10},          //B5
//   {KEY_F10},          //B6
//   {KEY_F10},          //B7
//   {KEY_F10}           //B8
// },
// {
//   {KEY_F10},          //B9
//   {KEY_F10},          //B10
// }
// };

// char encoderMacros[2][2][MAX_MACRO_SIZE] =
// {
//   { //Left encoder macros
//     {KEY_F10, KEY_F11, KEY_F11}, //Turn left
//     {KEY_F10, KEY_F11, KEY_F11}, //Turn right
//   },
//   { //Right encoder macros
//     {KEY_F10, KEY_F11, KEY_F11}, //Turn left
//     {KEY_F10, KEY_F11, KEY_F11}, //Turn right
//   }
// };
//-----------------------------------------------

void setup() 
{
  // Initialize the pins for the key matrix
  for(int i = 0; i < outCount; i++)
  {
    pinMode(columnsPin[i], OUTPUT);
    digitalWrite(columnsPin[i], LOW);
  }

  for(int i = 0; i < inCount; i++)
  {
    pinMode(rowsPin[i], INPUT_PULLDOWN);
  }
  // -----------------------------------------
  // Initialize both encoders
  pinMode(left_encoder[0], INPUT_PULLUP);
  pinMode(left_encoder[1], INPUT_PULLUP);

  pinMode(right_enconder[0], INPUT_PULLUP);
  pinMode(right_enconder[1], INPUT_PULLUP);

  aLastState = digitalRead(left_encoder[0]);
  bLastState = digitalRead(right_enconder[0]);

  //---------------------------------------------
  // Configure Led pins

  //--------------------------------------------
  // Start Blekeyboard
  NanoKeyboard.begin();
}

void loop()
{
  //Checks if keyboard is connected
  if(NanoKeyboard.isConnected())
  {
    //Function key pooling 
    //@todo
    //--------------------

    //Reading encoders
    //@todo
    //-------------------

    //Reading button matrix
    //@todo
    //-------------------


  }
}

void readEncoders()
{

}

void readMatrix(void)
{
  pressMacro(myLayout.keyMacros[0][0]);
}

void readFunction()
{

}

void pressMacro(char *macro)
{
  for (size_t i = 0; i < MAX_MACRO_SIZE; i++)
  {
    NanoKeyboard.press(macro[i]);
  }
  NanoKeyboard.releaseAll();

}



