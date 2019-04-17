/*
 * 3d_conv.c
 *
 *  Created on: Dec 6, 2018
 *      Author: vivek
 */


#include <stddef.h>
#include <stdio.h>
#include "coord.h"
#include "math.h"
#include "3d_utils.h"
#include "lcd_utils.h"
#include "3d_conv.h"

/**
 * World to viewer coordinate system
 * @param world_coord -[IN] World coordinate
 * @param viewer_coord -[OUT]  Viewer coordinate
 */
void world_to_viewer_coord(point3D* world_coord, point3D* viewer_coord) {
	viewer_coord->x = ((-SIN_THETA) * world_coord->x)
			+ ((world_coord->y) * COS_THETA);
	viewer_coord->y = (-(world_coord->x) * COS_THETA * COS_PHI)
			+ (-(world_coord->y) * COS_PHI * SIN_THETA)
			+ ((world_coord->z) * SIN_PHI);
	viewer_coord->z = (-(world_coord->x) * SIN_PHI * COS_THETA)
			+ (-(world_coord->y) * SIN_PHI * COS_THETA)
			+ (-(world_coord->z) * COS_PHI) + DISTANCE_3D;

}

/**
 * 3D Viewer to 2D coordinate system
 * @param viewer_coord -[IN] 3D Viewer coordinate
 * @param a_2d -[OUT]  2D coordinate
 */
void viewer_to_2d_coord(point3D* viewer_coord, point* a_2d) {

	a_2d->x = (viewer_coord->x * D) / (viewer_coord->z);
	a_2d->y = (viewer_coord->y * D) / (viewer_coord->z);

}

/**
 * Convert 3D to 2D coordinate
 * @param a_3d_point -[IN] point in 3D co-ordinate system
 * @param a_2d_point -[OUT]  point in 2D co-ordinate system
 */
void get_2d_from_3d(point3D* a_3d_point, point* a_2d_point) {

	point3D viewer_cord = { 0 };
	world_to_viewer_coord(a_3d_point, &viewer_cord);
	viewer_to_2d_coord(&viewer_cord, a_2d_point);
}
