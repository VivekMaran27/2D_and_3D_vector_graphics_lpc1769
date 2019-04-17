/*
 * 3d_utils.h
 *
 *  Created on: Oct 30, 2018
 *  Author: Vivek Maran
 */

#ifndef _3D_UTILS_H_
#define _3D_UTILS_H_


/**
 * Draw 3D cube with initial on top surface.
 * @param a_x -[IN] X axis
 * @param a_y -[IN] Y axis
 * @param a_z -[IN] Z axis
 */
void display3Dgraphics(point3D* a_x, point3D* a_y, point3D* a_z);

/**
 * World to viewer coordinate system
 * @param world_coord -[IN] World coordinate
 * @param viewer_coord -[OUT]  Viewer coordinate
 */
void world_to_viewer_coord(point3D* world_coord, point3D* viewer_coord);

/**
 * 3D Viewer to 2D coordinate system
 * @param viewer_coord -[IN] 3D Viewer coordinate
 * @param a_2d -[OUT]  2D coordinate
 */
void viewer_to_2d_coord(point3D* viewer_coord, point* a_2d);


#endif /* 3D_UTILS_H_ */
