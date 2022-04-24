#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <U8g2lib.h>

void progressBar(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t percent);
void button(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t width, String str, bool clicked);
void gauge(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t r, uint8_t percent);
void dialog(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, String title);

#endif