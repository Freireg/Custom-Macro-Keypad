#include <Arduino.h>
#include <BleKeyboard.h>


#define ENCONDER_A    12
#define ENCONDER_B    14
#define LED_BLUE      34
#define LED_RED       32
#define LED_GREEN     35

BleKeyboard bleKeyboard;
int aState, aLastState;
int counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  pinMode(4, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  
  pinMode(ENCONDER_A, INPUT_PULLUP);
  pinMode(ENCONDER_B, INPUT_PULLUP);
  bleKeyboard.begin();

  aLastState = digitalRead(ENCONDER_A);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_RED, HIGH);
}

void loop() {
  
  if(bleKeyboard.isConnected()) 
  {
    digitalWrite(LED_RED, LOW);
    if(digitalRead(4))
    {
      bleKeyboard.print("Key");
      delay(300);
    }
  
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
//    bleKeyboard.println(counter);
//    Serial.println(counter);
//    Serial.print("DEBUG")
    delay(100);
   }

   aLastState = aState;
  }
}
