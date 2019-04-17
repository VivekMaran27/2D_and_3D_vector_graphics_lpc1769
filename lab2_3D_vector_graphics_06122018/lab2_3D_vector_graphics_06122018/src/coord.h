/*
 * coord.h
 *
 *  Created on: Oct 1, 2018
 *  Author: Vivek Maran
 */
#include <stdint.h>
#ifndef SRC_COORD_H_
#define SRC_COORD_H_


#define DISPLAY_WIDTH_PIXELS (128)
#define DISPLAY_HEIGHT_PIXES (160)

/* Structure for 2D coordinate */
typedef struct point{
	int16_t x;
	int16_t y;
}point;

/* Structure for 3D coordinate */
typedef struct point3D{
	float x;
	float y;
	float z;
}point3D;

/**
 * Convert virtual coordinates to native coordinates
 * @param virt_coord -[IN] Virtual coordinate
 * @return - Point representing native co-ordinates.
 */
point virtualToNativeCoord(point* virt_coord);

/**
 * Draw a line segment joining the two given points with the given colour.
 * @param p0    -[IN] First point of the line
 * @param p1    -[IN] Second point of the line
 * @param color -[IN] Colour of the line
 */
void drawLineWithPoint(point p0, point p1, uint32_t color);


#endif /* SRC_COORD_H_ */

