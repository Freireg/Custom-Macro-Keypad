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

struct NanoKeyboardLayout_t
{
  char keyMacros[3][4][3];
  char encMacros[2][2][3];
  int setup;

};


#endif