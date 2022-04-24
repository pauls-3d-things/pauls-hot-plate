#include "ui.h"

void progressBar(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t percent) {
  // can't draw it smaller than 10x8
  height = height < 8 ? 8 : height;
  width = width < 10 ? 10 : width;

  // draw it
  u8g2.drawRFrame(x, y, width, height, 4);
  u8g2.drawBox(x + 2, y + 2, (width - 4) * (percent / 100.0), height - 4);
}

void button(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t width, String str, bool clicked) {
  if (clicked) {
    u8g2.setDrawColor(1);
    u8g2.drawRBox(x, y + 1, width, u8g2.getMaxCharHeight() + 4, 2);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x + (width / 2) - ((String(str).length() * (u8g2.getMaxCharWidth())) / 2),
                 y + u8g2.getMaxCharHeight() + 3, str.c_str());
  } else {
    u8g2.setDrawColor(1);
    u8g2.drawRFrame(x, y, width, u8g2.getMaxCharHeight() + 6, 4);
    u8g2.drawStr(x + (width / 2) - ((String(str).length() * (u8g2.getMaxCharWidth())) / 2),
                 y + u8g2.getMaxCharHeight() + 2, str.c_str());
  }
}

void gauge(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t r, uint8_t percent) {
  uint8_t rx = x + r;
  uint8_t ry = y;

  uint8_t px = rx + (r - 2) * cos(2 * PI * (percent / 2.0 + 50) / 100);
  uint8_t py = ry + (r - 2) * sin(2 * PI * (percent / 2.0 + 50) / 100);

  u8g2.drawLine(rx, ry, px, py);

  u8g2.drawCircle(rx, y, r, U8G2_DRAW_UPPER_LEFT);
  u8g2.drawCircle(rx, y, r, U8G2_DRAW_UPPER_RIGHT);
}

void dialog(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, String title) {
  u8g2.drawRFrame(x, y, width, height, 2);

  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.drawStr(x + (width / 2) - ((String(title).length() * (u8g2.getMaxCharWidth())) / 2), y + u8g2.getMaxCharHeight(),
               title.c_str());
  u8g2.drawHLine(x, y + u8g2.getMaxCharHeight() + 1, width);
}