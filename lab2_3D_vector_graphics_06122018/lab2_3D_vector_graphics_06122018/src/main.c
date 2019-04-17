/*
 ===============================================================================
 Name        : main.c
 Author      : Vivek Maran
 Version     : 1
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
#include <signal.h>
#include "lcd_utils.h"

/* Be careful with the port number and location number, because

 some of the location may not exist in that port. */
#define M_PI 3.14159265358979323846
#define PORT_NUM            0

#define ST7735_TFTWIDTH 127
#define ST7735_TFTHEIGHT 159

#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_SLPOUT 0x11
#define ST7735_DISPON 0x29

#define swap(x, y) {x = x + y; y = x - y; x = x - y ;}

int generate_random_in_range(int min_num, int max_num) {
	return (min_num + (rand() % (max_num - min_num + 1)));
}

/*
 Main Function main()
 */
int main(void)

{
	uint32_t pnum = PORT_NUM;
	pnum = 0;

	/* Axes */
	point3D x = { 250, 0, 0 };
	point3D y = { 0, 250, 0 };
	point3D z = { 0, 0, 250 };

	if (pnum == 0)
		SSP0Init();

	else
		puts("Port number is not correct");

	lcd_init();
	fillrect(0, 0, ST7735_TFTWIDTH, ST7735_TFTHEIGHT, BLACK);	//light blue 0xFFCD9B   0x696969
	display3Dgraphics(&x, &y, &z);
	lcddelay(100);
	return 0;

}

