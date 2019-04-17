/*
 * lcd_utils.h
 *
 *  Created on: Oct 5, 2018
 *  Author: Vivek Maran
 */

#ifndef SRC_LCD_UTILS_H_
#define SRC_LCD_UTILS_H_

#include "coord.h"

#define ST7735_TFTWIDTH 127
#define ST7735_TFTHEIGHT 159

#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_SLPOUT 0x11
#define ST7735_DISPON 0x29
#define INV 0x21

#define swap(x, y) {x = x + y; y = x - y; x = x - y ;}

// defining color values
#if 0
#define LIGHTBLUE 0x00FFE0
#define GREEN 0x00FF00
#define DARKBLUE 0x000033
#define BLACK 0x000000
#define BLUE 0x0007FF
#define RED 0xFF0000
#define MAGENTA 0x00F81F
#define WHITE 0xFFFFFF
#define PURPLE 0xCC33FF
#define ORANGE 0x0045FF
#define GREEN4 0x00FC7C
#define GREEN3 0x32CD32
#define GREEN2 0x228B22
#define GREEN1 0x006400
#define BROWN 0x663300
#endif

#define LIGHTBLUE 0x00FFE0
#define GREEN 0x00FF00
#define DARKBLUE 0x000033
#define BLACK 0x000000
#define BLUE 0x0007FF
#define RED 0xFF0000
#define MAGENTA 0x00F81F
#define WHITE 0xFFFFFF
#define PURPLE 0xCC33FF
#define ORANGE 0xFF9933
#define GREEN4 0x00FC7C
#define GREEN3 0x32CD32
#define GREEN2 0x228B22
#define GREEN1 0x006400
#define BROWN 0x663300
#define BROWN_1 0x331900
#define PINK 0xe00ba0
#define PINK_1 0xf441cd
#define ORANGE_1 0xf48342
#define LIGHT_PINK 0xFFCCFF
#define YELLOW 0xFFFF00
#define PINK_2 0xFF6666

#define DISPLAY_WIDTH_PIXELS (128)
#define DISPLAY_HEIGHT_PIXELS (160)

/**
 * Given four coordinates, draw a square.
 * @param p0    -[IN] First point of the square
 * @param p1    -[IN] Second point of the square
 * @param p2    -[IN] Third point of the square
 * @param p3    -[IN] Four point of the square
 */
void drawSquare(point p0, point p1, point p2, point p3, uint32_t color);

/**
 * Draw a line segment joining the two given points with the given colour.
 * @param p0    -[IN] First point of the line
 * @param p1    -[IN] Second point of the line
 * @param color -[IN] Colour of the line
 */
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);

void drawPixel(int16_t x, int16_t y, uint32_t color);

void fillrect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);

void lcd_init();

void lcddelay(int ms);

void writecommand(uint8_t c);

#endif /* SRC_LCD_UTILS_H_ */
