/*
 * 3d_conv.h
 *
 *  Created on: Dec 6, 2018
 *      Author: vivek
 */

#ifndef CONV_3D_H_
#define CONV_3D_H_

#define SIN_THETA ((sqrt(2.0))/(2.0))
#define COS_THETA ((sqrt(2.0))/(2.0))
#define SIN_PHI ((sqrt(6.0))/(3.0))
#define COS_PHI ((sqrt(3.0))/(3.0))
#define DISTANCE_3D ((300)*(sqrt(3.0)))
#define D (300) //250

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

/**
 * Convert 3D to 2D coordinate
 * @param a_3d_point -[IN] point in 3D co-ordinate system
 * @param a_2d_point -[OUT]  point in 2D co-ordinate system
 */
void get_2d_from_3d(point3D* a_3d_point, point* a_2d_point);

#endif /* 3D_CONV_H_ */
