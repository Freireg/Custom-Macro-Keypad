#include "NanoKeyboard.hpp"
//----------------------------
Layout_t myLayout[MAX_LAYOUT_SETUP];// = {0};
BleKeyboard NanoKeyboard("NanoKeyboard", "Espressif", 100);

// Define the pins for the 12 keys arranged in a 3x4 matrix
const int rows = inCount;
const int cols = outCount;
int aLastState, bLastState, aState, bState;
uint8_t layoutID = 0;

uint8_t columnsPin[] = {4, 16, 17, 18};   //Columns 1, 2, 3 and 4 
uint8_t rowsPin[] = {33, 32, 34};         //Rows 1, 2 and 3
uint8_t left_encoder[] = {19, 21};        //Pin A and B
uint8_t right_encoder[] = {22, 23};      //Pin A and B


uint8_t keyDown[inCount][outCount];
bool keyLong[inCount][outCount];

uint8_t encoDown[inCount][outCount];
bool encoLong[inCount][outCount];

unsigned long prevMillis = 0;
const unsigned long blinkInterval = 500;
//-------------------------------------------------------------
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

  pinMode(right_encoder[0], INPUT_PULLUP);
  pinMode(right_encoder[1], INPUT_PULLUP);

  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(BLED, OUTPUT);

  aLastState = digitalRead(left_encoder[0]);
  bLastState = digitalRead(right_encoder[0]);

  //---------------------------------------------
  // Configure Led pins

  //--------------------------------------------
  // Start Blekeyboard
  NanoKeyboard.begin();
}


void loop()
{
  unsigned long currentMillis = millis();
  myLayout[0] = {
  {
    {
    {KEY_LEFT_CTRL, 'C'},          //B1
    {KEY_LEFT_CTRL, 'V'},          //B2
    {KEY_LEFT_CTRL, 'Z'},          //B3
    {KEY_LEFT_CTRL, 'X'}           //B4
    },
    {
    {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'N'}, //B5
    {KEY_LEFT_CTRL, 'O'},          //B6
    {KEY_LEFT_CTRL, 'K', 'O'},          //B7
    {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'P'}           //B8
    },
    {
    {KEY_F9, '9'},          //B9
    {KEY_F10, '0'}          //B10
    }
  },
  {
    { //Left encoder macros
      {KEY_LEFT_SHIFT, KEY_RIGHT_ARROW}, //Turn RIGHT
      {KEY_LEFT_SHIFT, KEY_LEFT_ARROW}, //Turn LEFT
    },
    { //Right encoder macros
      {KEY_LEFT_CTRL, KEY_PAGE_UP}, //Turn left
      {KEY_LEFT_CTRL, KEY_PAGE_DOWN}, //Turn right
    }
  },

  0
};
  myLayout[1] = {
  {
    {
    {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'T'}, //B1
    {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'C'},          //B2
    {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'V'},          //B3
    {KEY_F4, '4'}           //B4
    },
    {
    {KEY_F5, '5'}, //B5
    {KEY_F6, '6'},          //B6
    {KEY_F7, '7'},          //B7
    {KEY_F8, '8'}           //B8
    },
    {
    {KEY_F9, '9'}, //B9
    {KEY_F10, '0'}          //B10
    }
  },
  {
    { //Left encoder macros
      {KEY_LEFT_CTRL, KEY_NUM_PLUS}, //Turn right
      {KEY_LEFT_CTRL, KEY_NUM_MINUS}, //Turn left 
    },
    { //Right encoder macros
      {KEY_LEFT_CTRL, KEY_PAGE_UP}, //Turn left
      {KEY_LEFT_CTRL, KEY_PAGE_DOWN}, //Turn right
    }
  },

  1
};
  //Checks if keyboard is connected
  if(NanoKeyboard.isConnected())
  {
    //Function key pooling 
    readFunction();
    //--------------------

    //Reading encoders
    readEncoders();
    //-------------------

    //Reading button matrix
    readMatrix();
    //-------------------

    //Waits for any external Bluetooth request
    //@todo
    //-------------------
  }
  else
  {
    digitalWrite(GLED, LOW);    
    digitalWrite(RLED, LOW);
    //If not connected, run led blink pattern
    if(currentMillis - prevMillis >= blinkInterval)
    {
      prevMillis = currentMillis;
      digitalWrite(BLED, !digitalRead(BLED));
      
    }
  }
}

/**
 * @brief 
 * 
 */
void readEncoders(void)
{
  aState = digitalRead(left_encoder[0]);
  bState = digitalRead(right_encoder[0]);

  if(aState != aLastState)
  {
    if(digitalRead(left_encoder[1]) != aState)
    {
      pressMacro(myLayout[layoutID].encMacros[0][0]);
    }
    else
    {
      pressMacro(myLayout[layoutID].encMacros[0][1]);
    }
  }

  if(bState != bLastState)
  {
    if(digitalRead(right_encoder[1]) != bState)
    {
      pressMacro(myLayout[layoutID].encMacros[1][0]);
    }
    else
    {
      pressMacro(myLayout[layoutID].encMacros[1][1]);
    }
  }
  
  delayMicroseconds(600);
  
  bLastState = bState;  
  aLastState = aState;
}

/**
 * @brief Read the 10 buttons matrix by triggering each column one by one and reading each row
 * 
 */
void readMatrix(void)
{
  for(int i = 0; i < outCount; i++)
  {
    digitalWrite(columnsPin[i], HIGH);  //Setting one column HIGH      
    delayMicroseconds(5);

    for(int j = 0; j < inCount; j++)
    {
      if(digitalRead(rowsPin[j]) == HIGH)
      {
        if(keyDown[j][i] == 0) //If it's the first time the function has been called for this key
        {
          pressMacro(myLayout[layoutID].keyMacros[j][i]);

        }
        else if(keyLong[j][i] && keyDown[j][i] > spamSpeed)
        {
          pressMacro(myLayout[layoutID].keyMacros[j][i]);
        }
        else if(keyDown[j][i] > longPressDelay) //If the key has been held longer that longPressDelay, it switch into spam mode
        {
          keyLong[j][i] = true;
        }
        keyDown[j][i]++;
      }
      else if(keyDown[j][i] != 0)
      {
        // keyReset(j, i);
        keyDown[j][i] = 0;
        keyLong[j][i] = false;
      }
    }
    digitalWrite(columnsPin[i], LOW);
    delayMicroseconds(500);
  }
}

/**
 * @brief 
 * 
 */
void readFunction(void)
{
  if(digitalRead(FUNC_BUTTON))
  {
    if(layoutID == MAX_LAYOUT_SETUP)
    {
      layoutID = 0;
    }
    else
    {
      layoutID++;
    }
    ledMode(layoutID);
    delay(300);
  }
  else{ ledMode(layoutID); }
}
/**
 * @brief Uses the Blekeyboard to emulate pressing the macro buttons
 * 
 * @param macro 
 */
void pressMacro(uint8_t *macro)
{
  for (size_t i = 0; i < MAX_MACRO_SIZE; i++)
  {
    NanoKeyboard.press(macro[i]);
  }
  NanoKeyboard.releaseAll();

}

/**
 * @todo Remove
*/
void keyReset(uint8_t row, uint8_t col)
{
  keyDown[row][col] = 0;
  keyLong[row][col] = false;
}

/**
 * @brief @todo
 * 
 * @param i 
 * @param setup 
 */
void configLayout(uint8_t *string, uint8_t setup)
{
  for (uint8_t row = 0; row < 3; row++)
  {
    for(uint8_t col = 0;col < 4; col++)
    {
      for (uint8_t i = 0;i < MAX_MACRO_SIZE; i++)
      {
        myLayout[setup].keyMacros[row][col][i] = string[i];//Remove the i on string
      }
    }
  }
  // myLayout[setup].encMacros = {
  //   { //Left encoder macros
  //     {0xCB, 0xCC, 0xCC}, //Turn left
  //     {0xCB, 0xCC, 0xCC}, //Turn right
  //   },
  //   { //Right encoder macros
  //     {0xCB, 0xCC, 0xCC}, //Turn left
  //     {0xCB, 0xCC, 0xCC}, //Turn right
  //   }
  // };
  
  myLayout[setup].setup = setup;
};

/**
 * @brief Turn on the led on the respective layout color
 * 
 * @param selectedSetup 
 */
void ledMode(uint8_t selectedSetup)
{
  switch (selectedSetup)
  {
  case 0:
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    delayMicroseconds(10);
    digitalWrite(RLED,HIGH);
    break;
  case 1:
    digitalWrite(BLED, LOW);
    digitalWrite(RLED, LOW);
    delayMicroseconds(10);
    digitalWrite(GLED,HIGH);
    break;
  case 2:
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    delayMicroseconds(10);
    digitalWrite(BLED,HIGH);
    break;  
  default:
    break;
  }
}

