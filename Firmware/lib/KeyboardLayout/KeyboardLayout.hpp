/**
 * @file KeyboardLayout.hpp
 * @author Guilherme Freire (guilherme.freire@fbest.org.br)
 * @brief 
 * @version 0.1
 * @date 2022-08-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef KEYBOARDLAYOUT_H_
#define KEYBOARDLAYOUT_H_
#include <BleKeyboard.h>



//First Keyboard commands set
const uint8_t SET1_KEY_B1[] = {KEY_F1}; 
const uint8_t SET1_KEY_B2[] = {KEY_F2};
const uint8_t SET1_KEY_B3[] = {KEY_F3};
const uint8_t SET1_KEY_B4[] = {KEY_F4};
const uint8_t SET1_KEY_B5[] = {KEY_F5};
const uint8_t SET1_KEY_B6[] = {KEY_F6};
const uint8_t SET1_KEY_B7[] = {KEY_F7};
const uint8_t SET1_KEY_B8[] = {KEY_F8};
const uint8_t SET1_KEY_B9[] = {KEY_F9};
const uint8_t SET1_KEY_B10[] = {KEY_F10};

const uint8_t SET1_ENCODER1_RIGHT[] = {KEY_LEFT_CTRL, KEY_NUM_PLUS};
const uint8_t SET1_ENCODER1_LEFT[] = {KEY_LEFT_CTRL, KEY_NUM_MINUS};

const uint8_t SET1_ENCODER2_RIGHT[] = {KEY_UP_ARROW};
const uint8_t SET1_ENCODER2_LEFT[] = {KEY_DOWN_ARROW};

//Second Keyboard commands set
const uint8_t SET2_KEY_B1[] = {KEY_F8}; 
const uint8_t SET2_KEY_B2[] = {KEY_F5};
const uint8_t SET2_KEY_B3[] = {KEY_F6};
const uint8_t SET2_KEY_B4[] = {KEY_F7};
const uint8_t SET2_KEY_B5[] = {KEY_LEFT_CTRL, 'b'};
const uint8_t SET2_KEY_B6[] = {KEY_F11};
const uint8_t SET2_KEY_B7[] = {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'b'};
const uint8_t SET2_KEY_B8[] = {KEY_LEFT_CTRL, KEY_F2};
const uint8_t SET2_KEY_B9[] = {};
const uint8_t SET2_KEY_B10[] = {};

const uint8_t SET2_ENCODER1_RIGHT[] = {KEY_F5};
const uint8_t SET2_ENCODER1_LEFT[] = {KEY_F7};

const uint8_t SET2_ENCODER2_RIGHT[] = {};
const uint8_t SET2_ENCODER2_LEFT[] = {};

//Third Keyboard commands set
const uint8_t SET3_KEY_B1[] = {KEY_LEFT_CTRL, 'd'}; 
const uint8_t SET3_KEY_B2[] = {KEY_LEFT_CTRL, 'f'};
const uint8_t SET3_KEY_B3[] = {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'f'};
const uint8_t SET3_KEY_B4[] = {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'n'};
const uint8_t SET3_KEY_B5[] = {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'b'};
const uint8_t SET3_KEY_B6[] = {KEY_LEFT_CTRL, KEY_LEFT_ALT, 'u'};
const uint8_t SET3_KEY_B7[] = {KEY_LEFT_CTRL, KEY_LEFT_SHIFT};
const uint8_t SET3_KEY_B8[] = {};
const uint8_t SET3_KEY_B9[] = {};
const uint8_t SET3_KEY_B10[] = {};

const uint8_t SET3_ENCODER1_RIGHT[] = {};
const uint8_t SET3_ENCODER1_LEFT[] = {};

const uint8_t SET3_ENCODER2_RIGHT[] = {};
const uint8_t SET3_ENCODER2_LEFT[] = {};

#endif