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
const uint8_t SET1_KEY_B1[] = {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_DELETE}; 
const uint8_t SET1_KEY_B2[] = {'O'};
const uint8_t SET1_KEY_B3[] = {};
const uint8_t SET1_KEY_B4[] = {};
const uint8_t SET1_KEY_B5[] = {KEY_LEFT_CTRL, 'c'};
const uint8_t SET1_KEY_B6[] = {};
const uint8_t SET1_KEY_B7[] = {};
const uint8_t SET1_KEY_B8[] = {};
const uint8_t SET1_KEY_B9[] = {};
const uint8_t SET1_KEY_B10[] = {};

const uint8_t SET1_ENCODER1_RIGHT[] = {KEY_LEFT_CTRL, KEY_NUM_PLUS};
const uint8_t SET1_ENCODER1_LEFT[] = {KEY_LEFT_CTRL, KEY_NUM_MINUS};

const uint8_t SET1_ENCODER2_RIGHT[] = {};
const uint8_t SET1_ENCODER2_LEFT[] = {};

//Second Keyboard commands set
const uint8_t SET2_KEY_B1[] = {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_DELETE}; 
const uint8_t SET2_KEY_B2[] = {'k'};
const uint8_t SET2_KEY_B3[] = {};
const uint8_t SET2_KEY_B4[] = {};
const uint8_t SET2_KEY_B5[] = {KEY_LEFT_CTRL, 'v'};
const uint8_t SET2_KEY_B6[] = {};
const uint8_t SET2_KEY_B7[] = {};
const uint8_t SET2_KEY_B8[] = {};
const uint8_t SET2_KEY_B9[] = {};
const uint8_t SET2_KEY_B10[] = {};

const uint8_t SET2_ENCODER1_RIGHT[] = {};
const uint8_t SET2_ENCODER1_LEFT[] = {};

const uint8_t SET2_ENCODER2_RIGHT[] = {};
const uint8_t SET2_ENCODER2_LEFT[] = {};

//Third Keyboard commands set
const uint8_t SET3_KEY_B1[] = {KEY_LEFT_ALT, KEY_F8}; 
const uint8_t SET3_KEY_B2[] = {'k'};
const uint8_t SET3_KEY_B3[] = {};
const uint8_t SET3_KEY_B4[] = {};
const uint8_t SET3_KEY_B5[] = {KEY_LEFT_CTRL, KEY_F8};
const uint8_t SET3_KEY_B6[] = {};
const uint8_t SET3_KEY_B7[] = {};
const uint8_t SET3_KEY_B8[] = {};
const uint8_t SET3_KEY_B9[] = {};
const uint8_t SET3_KEY_B10[] = {};

const uint8_t SET3_ENCODER1_RIGHT[] = {};
const uint8_t SET3_ENCODER1_LEFT[] = {};

const uint8_t SET3_ENCODER2_RIGHT[] = {};
const uint8_t SET3_ENCODER2_LEFT[] = {};

#endif