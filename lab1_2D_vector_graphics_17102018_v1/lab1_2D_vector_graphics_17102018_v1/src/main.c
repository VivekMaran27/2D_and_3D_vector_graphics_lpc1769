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
#include "queue.h"
#include <time.h>
#include <signal.h>
#include "lcd_utils.h"
#include "shrinking_squares.h"
#include "trees.h"

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

#define INV 0x21

int generate_random_in_range (int min_num, int max_num)
{
	return (min_num + (rand() % (max_num - min_num + 1)));
}

/*
 Main Function main()
 */
int main(void)

{
	uint32_t pnum = PORT_NUM;
	pnum = 0;

	if (pnum == 0)
		SSP0Init();

	else
		puts("Port number is not correct");

	lcd_init();
	//writecommand(INV);

	while (1) {
		fillrect(0, 0, ST7735_TFTWIDTH, ST7735_TFTHEIGHT, BLACK);
		shrinkingSquaresScreenSaver();
		fillrect(0, 0, ST7735_TFTWIDTH, ST7735_TFTHEIGHT, BLACK);
		lcddelay(3000);
		draw_trees();
	}
	lcddelay(3000);
	return 0;

}


