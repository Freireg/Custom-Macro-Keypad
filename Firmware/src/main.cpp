/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <NanoKeyboard.hpp>

NanoKeyboard keyboard;

void setup(){
  keyboard.setup();
}

void loop(){
  keyboard.begin();
}