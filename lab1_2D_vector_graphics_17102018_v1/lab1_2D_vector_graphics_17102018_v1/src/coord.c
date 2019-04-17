/*
 * coord.c
 *
 *  Created on: Oct 1, 2018
 *      Author: vivek
 */
//System headers
#include <stdio.h>
#include <stdlib.h>
#include "coord.h"

/**
 * @brief: Converts virtual co-ordinates to native co-ordinates
 * @param a_virt_coord -[IN] Virtual co-ordinate
 * @return - Point representing native co-ordinates.
 */
point virtualToNativeCoord(point* a_virt_coord)
{
	point native_coord = {0};

	if(NULL == a_virt_coord)
	{
		printf("Invalid arguments\n");

	}
	native_coord.x = a_virt_coord->x + (DISPLAY_WIDTH_PIXELS/2);
	native_coord.y = (DISPLAY_HEIGHT_PIXES/2) - a_virt_coord->y;
	return native_coord;
}

