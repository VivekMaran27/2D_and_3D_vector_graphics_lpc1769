/*
 ===============================================================================
 Name        : DrawLine.c
 Author      : Vivek Maran
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "LPC17xx.h"                        /* LPC17xx definitions */
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "coord.h"
#include "lcd_utils.h"

/* Be careful with the port number and location number, because

 some of the location may not exist in that port. */

#define PORT_NUM            0

uint8_t src_addr[SSP_BUFSIZE];
uint8_t dest_addr[SSP_BUFSIZE];

int _height = ST7735_TFTHEIGHT;
int _width = ST7735_TFTWIDTH;

void spiwrite(uint8_t c)

{

	int pnum = 0;

	src_addr[0] = c;

	SSP_SSELToggle(pnum, 0);

	SSPSend(pnum, (uint8_t *) src_addr, 1);

	SSP_SSELToggle(pnum, 1);

}

void writecommand(uint8_t c)

{

	LPC_GPIO0->FIOCLR |= (0x1 << 21);

	spiwrite(c);

}

void writedata(uint8_t c)

{

	LPC_GPIO0->FIOSET |= (0x1 << 21);

	spiwrite(c);

}

void writeword(uint16_t c)

{

	uint8_t d;

	d = c >> 8;

	writedata(d);

	d = c & 0xFF;

	writedata(d);

}

void write888(uint32_t color, uint32_t repeat)

{

	uint8_t red, green, blue;

	int i;

	red = (color >> 16);

	green = (color >> 8) & 0xFF;

	blue = color & 0xFF;

	for (i = 0; i < repeat; i++) {

		writedata(red);

		writedata(green);

		writedata(blue);

	}

}

void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)

{

	writecommand(ST7735_CASET);

	writeword(x0);

	writeword(x1);

	writecommand(ST7735_RASET);

	writeword(y0);

	writeword(y1);

}

void fillrect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)

{


	int16_t width, height;

	width = x1 - x0 + 1;

	height = y1 - y0 + 1;

	setAddrWindow(x0, y0, x1, y1);

	writecommand(ST7735_RAMWR);

	write888(color, width * height);

}

void lcddelay(int ms)

{

	int count = 24000;

	int i;

	for (i = count * ms; i--; i > 0)
		;

}

void lcd_init()

{

	int i;
	printf("LCD Demo Begins!!!\n");
	// Set pins P0.16, P0.21, P0.22 as output
	LPC_GPIO0->FIODIR |= (0x1 << 16);

	LPC_GPIO0->FIODIR |= (0x1 << 21);

	LPC_GPIO0->FIODIR |= (0x1 << 22);

	// Hardware Reset Sequence
	LPC_GPIO0->FIOSET |= (0x1 << 22);
	lcddelay(500);

	LPC_GPIO0->FIOCLR |= (0x1 << 22);
	lcddelay(500);

	LPC_GPIO0->FIOSET |= (0x1 << 22);
	lcddelay(500);

	// initialize buffers
	for (i = 0; i < SSP_BUFSIZE; i++) {

		src_addr[i] = 0;
		dest_addr[i] = 0;
	}

	// Take LCD display out of sleep mode
	writecommand(ST7735_SLPOUT);
	lcddelay(200);

	// Turn LCD display on
	writecommand(ST7735_DISPON);
	lcddelay(200);

	// Invert colours
	//writecommand(INV);
	lcddelay(500);
}

void drawPixel(int16_t x, int16_t y, uint32_t color)

{

	if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))

		return;

	setAddrWindow(x, y, x + 1, y + 1);

	writecommand(ST7735_RAMWR);

	write888(color, 1);

}

/**
 * Draw a line segment joining the two given points with the given colour.
 * @param p0    -[IN] First point of the line
 * @param p1    -[IN] Second point of the line
 * @param color -[IN] Colour of the line
 */
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)

{
	int16_t slope = abs(y1 - y0) > abs(x1 - x0);
	if (slope) {
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	}

	else {
		ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (slope) {
			drawPixel(y0, x0, color);
		} else {
			drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}

}

/**
 * Draw a line segment joining the two given points with the given colour.
 * @param p0    -[IN] First point of the line
 * @param p1    -[IN] Second point of the line
 * @param color -[IN] Colour of the line
 */
void drawLineWithPoint(point p0, point p1, uint32_t color)
{
	int16_t slope = abs(p1.y - p0.y) > abs(p1.x - p0.x);
	if (slope) {
		swap(p0.x, p0.y);
		swap(p1.x, p1.y);
	}

	if (p0.x > p1.x) {
		swap(p0.x, p1.x);
		swap(p0.y, p1.y);
	}

	int16_t dx, dy;
	dx = p1.x - p0.x;
	dy = abs(p1.y - p0.y);

	int16_t err = dx / 2;
	int16_t ystep;

	if (p0.y < p1.y) {
		ystep = 1;
	}

	else {
		ystep = -1;
	}

	for (; p0.x <= p1.x; p0.x++) {
		if (slope) {
			drawPixel(p0.y, p0.x, color);
		} else {
			drawPixel(p0.x, p0.y, color);
		}
		err -= dy;
		if (err < 0) {
			p0.y += ystep;
			err += dx;
		}
	}
}
