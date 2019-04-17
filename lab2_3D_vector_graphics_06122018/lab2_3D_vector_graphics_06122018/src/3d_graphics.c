/* 3d_utils.c
 *
 *  Created on: Oct 30, 2018
 *  Author: Vivek Maran
 */

#include <stddef.h>
#include <stdio.h>
#include "coord.h"
#include <math.h>
#include <stdlib.h>
#include "3d_utils.h"
#include "lcd_utils.h"
#include "3d_conv.h"
#include "2d_graphics.h"


#define display_scaling (2000000)
#define display_shifting (30)

point3D camera_position = { 300, 300, 300 };
point3D light_src = { 40, 40, 200 };
point light_src_2D = { 0, 0 };
point light_src_2Dnative = { 0, 0 };
float reflectivity[3] = {0.8,0,0};

//Variables for the Axes
point3D origin = { 0, 0, 0 };
point origin_2d = { 0, 0 };
point x_2d = { 0, 0 };
point y_2d = { 0, 0 };
point z_2d = { 0, 0 };

point native_origin = { 0, 0 };
point native_x2d = { 0, 0 };
point native_y2d = { 0, 0 };
point native_z2d = { 0, 0 };

/************************ CO-ORDINATES OF THE CUBE ****************************/
/* Coordinates of the first cube */
point3D cube_base_coord[] = {
		{ 0.0, 80.0, 0.0 }, { 0.0, 80.0, 80.0 }, { 80.0, 80.0, 80.0 },
		{ 80.0, 80.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 80.0 },
		{ 80.0, 0.0, 80.0 }, { 80.0, 0.0, 0.0 }};

/* Coordinates of the first cube, rotated from base co-ordinates */
point3D cube1[] = {
		{ 0.0, 80.0, 0.0 }, { 0.0, 80.0, 80.0 }, { 80.0, 80.0, 80.0 },
		{ 80.0, 80.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 80.0 },
		{ 80.0, 0.0, 80.0 }, { 80.0, 0.0, 0.0 }};

/* Coordinates of the second cube, rotated from base co-ordinates */
point3D cube2[] = {
		{ 0.0, 80.0, 0.0 }, { 0.0, 80.0, 80.0 }, { 80.0, 80.0, 80.0 },
		{ 80.0, 80.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 80.0 },
		{ 80.0, 0.0, 80.0 }, { 80.0, 0.0, 0.0 }};

/* Coordinates of the third cube, rotated from base co-ordinates */
point3D cube3[] = {
		{ 0.0, 80.0, 0.0 }, { 0.0, 80.0, 80.0 }, { 80.0, 80.0, 80.0 },
		{ 80.0, 80.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 80.0 },
		{ 80.0, 0.0, 80.0 }, { 80.0, 0.0, 0.0 }};

point3D rotated_cube1[] = { { 0.0, 80.0, 0.0 }, { 0.0, 80.0, 80.0 }, { 80.0,
		80.0, 80.0 }, { 80.0, 80.0, 0.0 }, { 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 80.0 }, { 80.0, 0.0, 80.0 }, { 80.0, 0.0, 0.0 }};


/* struct point to save 2D points of the cube */
point P_2D[] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, {
		0, 0 }, { 0, 0 } };

/* struct point to save native 2D points of the cube */
point P_2Dnative[] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
		{ 0, 0 }, { 0, 0 }, { 0, 0 } };

/* Points corresponding to XY, YZ and ZX plane*/
point3D g_xy_coord_1 = { 0.0, 0.0, 80.0 }, g_xy_coord_2 = { 0.0, 80.0, 80.0 },
		g_xy_coord3 = { 80.0, 0.0,80.0 }, g_xy_coord_4 = { 80.0, 80.0, 80.0 };
point3D g_yz_coord_1 = { 80.0, 0.0, 0.0 }, g_yz_coord_2 = { 80.0, 0.0, 80.0 },
		g_yz_coord3 = { 80.0, 80.0, 0.0 }, g_yz_coord4 = { 80.0, 80.0, 80.0 };
point3D g_zx_coord_1 = { 80.0, 80.0, 0.0 }, g_zx_coord_2 = { 80.0, 80.0, 80.0 },
		g_zx_coord3 = { 0.0, 80.0, 0.0 }, g_zx_coord4 = { 0.0, 80.0, 80.0 };


point3D initial[] = { { 10.0, 10.0, 80.0 }, { 10.0, 30.0, 80.0 }, { 10.0,
		60.0, 80.0 }, { 10.0, 70.0, 80.0 }, { 60, 45.0, 80.0 }, { 80.0, 45.0,
		80.0 }, { 28.0, 76.0, 80.0 }, { 4.0, 76.0, 80.0 } };

point3D initial_restore[] = { { 10.0, 10.0, 80.0 }, { 10.0, 30.0, 80.0 }, { 10.0,
		60.0, 80.0 }, { 10.0, 70.0, 80.0 }, { 60, 45.0, 80.0 }, { 80.0, 45.0,
		80.0 }, { 28.0, 76.0, 80.0 }, { 4.0, 76.0, 80.0 } };

/* struct point to save 2D points of the initial */
point I_2D[] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, {
		0, 0 }, { 0, 0 } };

/* struct point to save native 2D points of the initial */
point I_2Dnative[] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
		{ 0, 0 }, { 0, 0 }, { 0, 0 } };

point3D intersection1 = { 0, 0, 0 };
point intersection1_2D = { 0, 0 };
point intersection1_2Dnative = { 0, 0 };

point3D intersection2 = { 0, 0, 0 };
point intersection2_2D = { 0, 0 };
point intersection2_2Dnative = { 0, 0 };

point3D intersection3 = { 0, 0, 0 };
point intersection3_2D = { 0, 0 };
point intersection3_2Dnative = { 0, 0 };

point3D intersection4 = { 0, 0, 0 };
point intersection4_2D = { 0, 0 };
point intersection4_2Dnative = { 0, 0 };


/**
 * Convert 3D coordinates to 2D coordinates
 */
void all3Dto2D() {
	/* Convert 3D points to 2D */
	for (int i = 0; i <= 7; i++) {
		get_2d_from_3d(&cube_base_coord[i], &P_2D[i]);
		get_2d_from_3d(&initial[i], &I_2D[i]);
	}
	get_2d_from_3d(&light_src, &light_src_2D);
}

/**
 * Convert Virtual coordinates to native
 */
void allVirtualtoNative() {

	native_origin = virtualToNativeCoord(&origin_2d);
	light_src_2Dnative = virtualToNativeCoord(&light_src_2D);

	for (int i = 0; i <= 7; i++) {
		/* Cube's 2D coordinates virtual to native */
		P_2Dnative[i] = virtualToNativeCoord(&P_2D[i]);
		/* Initials' 2D coordinates virtual to native */
		I_2Dnative[i] = virtualToNativeCoord(&I_2D[i]);
	}
}

/**
 * Function to rotate and scale the cube.
 * @param theta -[IN] Angle at which the cube needs to be rotated
 * @param alpha -[IN]  scaling Factor
 */
void rotateAndScaleCube(float theta, float alpha) {

	static int cube_num = 0;
	float cos_theta = cos((theta * 3.1415926535859) / 180.0);
	float sin_theta = sin((theta * 3.1415926535859) / 180.0);

	/* Rotation is perfomed with a pre-multiplied matrix
	 * theta is the angle of rotation
	 * alpha is the scaling factor
	 * The constant in the equation controls the vector parellel to Z axis
	 * which needs rotation
	 */
	/* Rotation for first cube */
	if (cube_num == 0) {
		for (int i = 0; i < 8; i++) {
			cube_base_coord[i].x = alpha
					* ((cube_base_coord[i].x * cos_theta)
							- (cube_base_coord[i].y * sin_theta)
							- (400 * (cos_theta - sin_theta - 1)));
			cube_base_coord[i].y = alpha
					* ((cube_base_coord[i].x * sin_theta)
							+ (cube_base_coord[i].y * cos_theta)
							+ (400 * (sin_theta + cos_theta - 1)));
			cube_base_coord[i].z = alpha * cube_base_coord[i].z;
			initial[i].x = alpha
					* ((initial[i].x * cos_theta) - (initial[i].y * sin_theta)
							- (400 * (cos_theta - sin_theta - 1)));
			initial[i].y = alpha
					* ((initial[i].x * sin_theta) + (initial[i].y * cos_theta)
							+ (400 * (sin_theta + cos_theta - 1)));
			initial[i].z = alpha * initial[i].z;
		}
	} else if (cube_num == 1) {
		for (int i = 0; i < 8; i++) {

			cube_base_coord[i].x = alpha
					* ((cube_base_coord[i].x * cos_theta)
							- (cube_base_coord[i].y * sin_theta)
							+ (200 * (sin_theta))) + 10;
			cube_base_coord[i].y = alpha
					* ((cube_base_coord[i].x * sin_theta)
							+ (cube_base_coord[i].y * cos_theta)
							- (200 * (cos_theta - 1))) + 30;
			cube_base_coord[i].z = alpha * cube_base_coord[i].z;

			initial[i].x = alpha
					* ((initial[i].x * cos_theta) - (initial[i].y * sin_theta)
							+ (200 * (sin_theta))) + 10;
			initial[i].y = alpha
					* ((initial[i].x * sin_theta) + (initial[i].y * cos_theta)
							- (200 * (cos_theta - 1))) + 30;
			initial[i].z = alpha * initial[i].z;

		}
	}
	/* Rotation for second cube */
	else if (cube_num == 2) {
		for (int i = 0; i < 8; i++) {
			cube_base_coord[i].x = alpha
					* ((cube_base_coord[i].x * cos_theta)
							- (cube_base_coord[i].y * sin_theta)
							- (200 * (cos_theta - sin_theta - 1))) + 5;
			cube_base_coord[i].y = alpha
					* ((cube_base_coord[i].x * sin_theta)
							+ (cube_base_coord[i].y * cos_theta)
							- (200 * (sin_theta + cos_theta - 1))) + 5;
			cube_base_coord[i].z = alpha * cube_base_coord[i].z;
			initial[i].x = alpha
					* ((initial[i].x * cos_theta) - (initial[i].y * sin_theta)
							- (200 * (cos_theta - sin_theta - 1))) + 5;
			initial[i].y = alpha
					* ((initial[i].x * sin_theta) + (initial[i].y * cos_theta)
							- (200 * (sin_theta + cos_theta - 1))) + 5;
			initial[i].z = alpha * initial[i].z;
		}
	} else {
		/* Nothing to do */
	}
	g_xy_coord_1 = cube_base_coord[5];
	g_xy_coord_2 = cube_base_coord[1];
	g_xy_coord3 = cube_base_coord[6];
	g_xy_coord_4 = cube_base_coord[2];

	g_yz_coord_1 = cube_base_coord[7];
	g_yz_coord_2 = cube_base_coord[6];
	g_yz_coord3 = cube_base_coord[3];
	g_yz_coord4 = cube_base_coord[2];

	g_zx_coord_1 = cube_base_coord[3];
	g_zx_coord_2 = cube_base_coord[2];
	g_zx_coord3 = cube_base_coord[0];
	g_zx_coord4 = cube_base_coord[1];
	cube_num = cube_num + 1;
}

/**
 * Draw shadow.
 * @param p3 -[IN] Shadow point 1
 * @param p4 -[IN] Shadow point 2
 * @param p4 -[IN] Shadow point 3
 * @param p4 -[IN] Shadow point 4
 */
void drawShadow(point3D* p3, point3D* p4, point3D* p5, point3D* p6)
{
	point3D temp1, temp2;
	point a, b;

	/* SCAN-I */
	for (float i = p6->x, j = p5->x; i <= p3->x && j <= p4->x; i++, j++) {
		temp1.x = i;
		temp1.y = (((p3->y - p6->y) / (p3->x - p6->x)) * (temp1.x - p6->x))
				+ p6->y;
		temp2.x = j;
		temp2.y = (((p4->y - p5->y) / (p4->x - p5->x)) * (temp2.x - p5->x))
				+ p5->y;
		get_2d_from_3d(&temp1, &a);
		a = virtualToNativeCoord(&a);
		get_2d_from_3d(&temp2, &b);
		b = virtualToNativeCoord(&b);
		drawLineWithPoint(a, b, 0xD3D3D3);
	}

	/* SCAN-II */
	for (float i = p6->x, j = p3->x; i <= p5->x && j <= p4->x;
			i++, j++) {

		temp1.x = i;
		temp1.y = (((p5->y - p6->y) / (p5->x - p6->x))
				* (temp1.x - p6->x)) + p6->y;
		temp2.x = j;
		temp2.y = (((p4->y - p3->y) / (p4->x - p3->x))
				* (temp2.x - p3->x)) + p3->y;
		get_2d_from_3d(&temp1, &a);
		a = virtualToNativeCoord(&a);
		get_2d_from_3d(&temp2, &b);
		b = virtualToNativeCoord(&b);
		drawLineWithPoint(a, b, 0xD3D3D3);
	}
}

/**
 * Function to rotate the cube.
 * @param theta -[IN] Angle at which the cube needs to be rotated
 * @param alpha -[IN]  scaling Factor
 */
void drawCube(float angle) {

	/* Draw cube first */
	drawLineWithPoint(P_2Dnative[0], P_2Dnative[1], PINK);
	drawLineWithPoint(P_2Dnative[1], P_2Dnative[2], PINK);
	drawLineWithPoint(P_2Dnative[2], P_2Dnative[3], PINK);
	drawLineWithPoint(P_2Dnative[3], P_2Dnative[0], PINK);

	drawLineWithPoint(P_2Dnative[5], P_2Dnative[6], PINK);
	drawLineWithPoint(P_2Dnative[6], P_2Dnative[7], PINK);

	drawLineWithPoint(P_2Dnative[0], P_2Dnative[4], PINK);
	drawLineWithPoint(P_2Dnative[1], P_2Dnative[5], PINK);

	drawLineWithPoint(P_2Dnative[2], P_2Dnative[6], PINK);
	drawLineWithPoint(P_2Dnative[3], P_2Dnative[7], PINK);

	float lambda = (-1 * light_src.z) / (light_src.z - cube_base_coord[2].z);

	intersection1.x = light_src.x + lambda * (light_src.x - cube_base_coord[2].x);
	intersection1.y = light_src.y + lambda * (light_src.y - cube_base_coord[2].y);
	intersection1.z = light_src.z + lambda * (light_src.z - cube_base_coord[2].z);
	get_2d_from_3d(&intersection1, &intersection1_2D);
	intersection1_2Dnative = virtualToNativeCoord(&intersection1_2D);

	intersection2.x = light_src.x + lambda * (light_src.x - cube_base_coord[6].x);
	intersection2.y = light_src.y + lambda * (light_src.y - cube_base_coord[6].y);
	intersection2.z = light_src.z + lambda * (light_src.z - cube_base_coord[6].z);
	get_2d_from_3d(&intersection2, &intersection2_2D);
	intersection2_2Dnative = virtualToNativeCoord(&intersection2_2D);

	intersection3.x = light_src.x + lambda * (light_src.x - cube_base_coord[1].x);
	intersection3.y = light_src.y + lambda * (light_src.y - cube_base_coord[1].y);
	intersection3.z = light_src.z + lambda * (light_src.z - cube_base_coord[1].z);
	get_2d_from_3d(&intersection3, &intersection3_2D);
	intersection3_2Dnative = virtualToNativeCoord(&intersection3_2D);

	intersection4.x = light_src.x + lambda * (light_src.x - cube_base_coord[5].x);
	intersection4.y = light_src.y + lambda * (light_src.y - cube_base_coord[5].y);
	intersection4.z = light_src.z + lambda * (light_src.z - cube_base_coord[5].z);
	get_2d_from_3d(&intersection4, &intersection4_2D);
	intersection4_2Dnative = virtualToNativeCoord(&intersection4_2D);

    // Fill color for shadow
//	point3D p1 = cube_base_coord[7], p2 = cube_base_coord[3];
	point3D p3 = intersection2, p4 = intersection1, p5 =intersection3;
	point3D p6 = intersection4;
	drawShadow(&p3, &p4, &p5, &p6);

	point3D t1, t2;
	point w, x, y, z;
	int diff = 1;

	//Filling top surface
	for (float i = g_xy_coord_1.x, j = g_xy_coord_2.x;
			i <= g_xy_coord3.x && j <= g_xy_coord_4.x; i++, j++) {

		t1.x = i;
		t1.y = (((g_xy_coord3.y - g_xy_coord_1.y)
				/ (g_xy_coord3.x - g_xy_coord_1.x)) * (t1.x - g_xy_coord_1.x))
				+ g_xy_coord_1.y;
		if (angle != 0.0) {
			t1.z = g_xy_coord_1.z;
		}

		t2.x = j;
		t2.y = (((g_xy_coord_4.y - g_xy_coord_2.y)
				/ (g_xy_coord_4.x - g_xy_coord_2.x)) * (t2.x - g_xy_coord_2.x))
				+ g_xy_coord_2.y;
		if (angle != 0.0) {
			t2.z = g_xy_coord_2.z;
		}
		double dx = t2.x - t1.x;
		double dy = t2.y - t1.y;
		double dotProd = 0.0;
		double magdotProd = 0.0;
		double angle = 0.0;
		double diffuse = 0.0;

		int steps = 0;
		steps = (abs((int) dx)) > (abs((int) dy)) ?
				(abs((int) dx)) : (abs((int) dy));
		float xInc, yInc;
		xInc = dx / (float) steps;
		yInc = dy / (float) steps;

		point3D t1_temp = t1;

		for (int k = 0; k < steps; k++) {
			t1_temp.x += xInc;
			t1_temp.y += yInc;
			get_2d_from_3d(&t1_temp, &w);
			w = virtualToNativeCoord(&w);

			/* Compute diffuse reflection */
			dotProd = light_src.z - t1_temp.z;
			magdotProd = sqrt(
					pow((light_src.x - t1_temp.x), 2)
							+ pow((light_src.y - t1_temp.y), 2)
							+ pow((light_src.z - t1_temp.z), 2));
			angle = dotProd / magdotProd;
			diffuse = reflectivity[0] * angle / pow(magdotProd, 2);
			int color = display_scaling * diffuse + display_shifting;
			color = RED;
			drawPixel(w.x, w.y, color-(diff<<16));
		}
		diff+=3;
	}

	//Fill YZ  plane
	for (float i = g_yz_coord_1.y, j = g_yz_coord_2.y;
			i <= g_yz_coord3.y && j <= g_yz_coord4.y; i++, j++) {
		float m = (g_yz_coord3.y - g_yz_coord_1.y)
				/ (g_yz_coord3.x - g_yz_coord_1.x);

		t1.y = i;
		t1.z = (((g_yz_coord3.z - g_yz_coord_1.z)
				/ (g_yz_coord3.y - g_yz_coord_1.y)) * (t1.y - g_yz_coord_1.y))
				+ g_yz_coord_1.z;
		if (angle != 0.0) {
			t1.x = (t1.y - g_yz_coord_1.y + (m * g_yz_coord_1.x)) / m; //YZ1.x;
		}

		t2.y = j;
		t2.z = (((g_yz_coord4.z - g_yz_coord_2.z)
				/ (g_yz_coord4.y - g_yz_coord_2.y)) * (t2.y - g_yz_coord_2.y))
				+ g_yz_coord_2.z;
		if (angle != 0.0) {
			t2.x = t1.x; //YZ2.x;
		}

		get_2d_from_3d(&t1, &w);
		x = virtualToNativeCoord(&w);
		get_2d_from_3d(&t2, &y);
		z = virtualToNativeCoord(&y);
		drawLineWithPoint(x, z, LIGHT_PINK);
	}

	//Fill XZ  plane
	for (float i = g_zx_coord_1.x, j = g_zx_coord_2.x;
			i >= g_zx_coord3.x && j >= g_zx_coord4.x; i--, j--) {

//		float m = (g_zx_coord3.y - g_zx_coord_1.y)
//				/ (g_zx_coord3.x - g_zx_coord_1.x);
		t1.x = i;
		t1.z = (((g_zx_coord3.z - g_zx_coord_1.z)
				/ (g_zx_coord3.x - g_zx_coord_1.x)) * (t1.x - g_zx_coord_1.x))
				+ g_zx_coord_1.z;
		if (angle != 0.0) {
			t1.y = (((g_zx_coord3.y - g_zx_coord_1.y)
					/ (g_zx_coord3.x - g_zx_coord_1.x))
					* (t1.x - g_zx_coord_1.x)) + g_zx_coord_1.y; //(t1.y-ZX1.y + (m*ZX1.x))/m;//YZ1.x;
		}
		t2.x = j;
		t2.z = (((g_zx_coord4.z - g_zx_coord_2.z)
				/ (g_zx_coord4.y - g_zx_coord_2.y)) * (t2.y - g_zx_coord_2.y))
				+ g_zx_coord_2.z;
		if (angle != 0.0) {
			t2.y = t1.y; //YZ2.x;
		}
		get_2d_from_3d(&t1, &w);
		x = virtualToNativeCoord(&w);
		get_2d_from_3d(&t2, &y);
		z = virtualToNativeCoord(&y);
		drawLineWithPoint(x, z, ORANGE);
	}
}

/**
 * drawInitial
 * @param None
 * @Return None
 */
void drawInitial() {
	//	Drawline for initial
	drawLineWithPoint(I_2Dnative[0], I_2Dnative[1], WHITE);
	drawLineWithPoint(I_2Dnative[2], I_2Dnative[3], WHITE);
	drawLineWithPoint(I_2Dnative[1], I_2Dnative[4], WHITE);
	drawLineWithPoint(I_2Dnative[2], I_2Dnative[4], WHITE);
	drawLineWithPoint(I_2Dnative[0], I_2Dnative[5], WHITE);
	drawLineWithPoint(I_2Dnative[3], I_2Dnative[5], WHITE);
}


/**
 * Draw 3D cube with initial on top surface.
 * @param a_x -[IN] X axis
 * @param a_y -[IN] Y axis
 * @param a_z -[IN] Z axis
 */
void display3Dgraphics(point3D* a_x, point3D* a_y, point3D* a_z) {

	float angle = -10.0;		//0.5;
	initial[0].z = 80;

    /*******************************
     * CUBE-1 ROTATION
     *******************************/
	rotateAndScaleCube(angle, 1.0);
	for( int i = 0; i < 8; i++)
	{
		cube1[i] = cube_base_coord[i];
	}

    /*******************************
     * DRAW AXES
     *******************************/
	get_2d_from_3d(a_x, &x_2d);
	get_2d_from_3d(a_y, &y_2d);
	get_2d_from_3d(a_z, &z_2d);

	native_origin = virtualToNativeCoord(&origin_2d);
	native_x2d = virtualToNativeCoord(&x_2d);
	native_y2d = virtualToNativeCoord(&y_2d);
	native_z2d = virtualToNativeCoord(&z_2d);

	all3Dto2D();
	allVirtualtoNative();

	drawLineWithPoint(native_origin, native_x2d, RED);
	drawLineWithPoint(native_origin, native_y2d, GREEN);
	drawLineWithPoint(native_origin, native_z2d, BLUE);

    /*******************************
     * DRAW CUBE-1 AND INITIALS
     *******************************/
	drawCube(angle);
	drawInitial();

	for (int i = 0; i < 8; i++) {
		cube_base_coord[i] = rotated_cube1[i];
		initial[i] = initial_restore[i];
		initial[0].z = 80;
	}

    /*******************************
     * DRAW CUBE-2 AND INITIALS
     *******************************/
	angle = -25.0;
	rotateAndScaleCube(angle, 0.6);
	for (int i = 0; i < 8; i++) {
		cube2[i] = cube_base_coord[i];
	}

	get_2d_from_3d(a_x, &x_2d);
	get_2d_from_3d(a_y, &y_2d);
	get_2d_from_3d(a_z, &z_2d);

	native_origin = virtualToNativeCoord(&origin_2d);
	native_x2d = virtualToNativeCoord(&x_2d);
	native_y2d = virtualToNativeCoord(&y_2d);
	native_z2d = virtualToNativeCoord(&z_2d);

	all3Dto2D();
	allVirtualtoNative();
	drawCube(angle);
	drawInitial();

	/*******************************
	 * DRAW CUBE-2 AND INITIALS
    *******************************/
	for (int i = 0; i < 8; i++) {
		cube_base_coord[i] = rotated_cube1[i];
		initial[i] = initial_restore[i];
		initial[0].z = 80;
	}

	point3D trunk_start_3D;
	angle = 30.0;
	rotateAndScaleCube(angle, 0.6);

	for (int i = 0; i < 8; i++) {
		cube3[i] = cube_base_coord[i];
	}

	get_2d_from_3d(a_x, &x_2d);
	get_2d_from_3d(a_y, &y_2d);
	get_2d_from_3d(a_z, &z_2d);

	native_origin = virtualToNativeCoord(&origin_2d);
	native_x2d = virtualToNativeCoord(&x_2d);
	native_y2d = virtualToNativeCoord(&y_2d);
	native_z2d = virtualToNativeCoord(&z_2d);

	all3Dto2D();
	allVirtualtoNative();

	drawCube(angle);
	drawInitial();


	trunk_start_3D.x = (cube1[0].x + cube1[3].x)/2.0;
	trunk_start_3D.y = cube1[0].y;
	trunk_start_3D.z = cube1[0].z;
	draw_trees(trunk_start_3D, 1);

	trunk_start_3D.x = (cube2[0].x + cube2[3].x)/2.0;
	trunk_start_3D.y = cube2[0].y;
	trunk_start_3D.z = cube2[0].z;
	draw_trees(trunk_start_3D, 2);

	trunk_start_3D.x = (cube3[0].x + cube3[3].x)/2.0;
	trunk_start_3D.y = cube3[0].y;
	trunk_start_3D.z = cube3[0].z;
	draw_trees(trunk_start_3D, 3);

	FillshrinkingSquares(cube1[7],cube1[6],cube1[2],cube1[3]);
	FillshrinkingSquares(cube2[7],cube2[6],cube2[2],cube2[3]);
	FillshrinkingSquares(cube3[7],cube3[6],cube3[2],cube3[3]);
}

