/*
 * coord.c
 *
 *  Created on: Oct 1, 2018
 *  Author: Vivek Maran
 */
//System headers
#include <stdio.h>
#include <stdlib.h>
#include "coord.h"

/**
 * Convert virtual coordinates to native coordinates
 * @param virt_coord -[IN] Virtual coordinate
 * @return - Point representing native coordinates.
 */
point virtualToNativeCoord(point* virt_coord)
{
	point native_coord = {0};

	native_coord.x = virt_coord->x + (DISPLAY_WIDTH_PIXELS/2);
	native_coord.y = (DISPLAY_HEIGHT_PIXES/2) - virt_coord->y;
	return native_coord;
}

