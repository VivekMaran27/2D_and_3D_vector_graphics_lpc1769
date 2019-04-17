/*
 * coord.h
 *
 *  Created on: Oct 1, 2018
 *      Author: vivek
 */
#include <stdint.h>
#ifndef SRC_COORD_H_
#define SRC_COORD_H_


#define DISPLAY_WIDTH_PIXELS (128)
#define DISPLAY_HEIGHT_PIXES (160)

/**
 * Structure encapsulating a point
 */
typedef struct point{
	int16_t x;
	int16_t y;
}point;

/**
 * @brief: Converts virtual co-ordinates to native co-ordinates
 * @param a_virt_coord -[IN] Virtual co-ordinate
 * @return - Point representing native co-ordinates.
 */
point virtualToNativeCoord(point* a_virt_coord);


/**
 * Print outgoing pointers /\ from each non-null parent node->
 * @param level the current level
 * @param offset the current offset
 * @param level_nodes the current level of nodes
 */

#endif /* SRC_COORD_H_ */

