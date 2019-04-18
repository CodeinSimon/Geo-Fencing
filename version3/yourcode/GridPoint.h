//
// Created by Simon Nie on 2019/1/4.
// @Copyright (c) 2019 Simon Nie. All rights reserved.
//

#ifndef INC_16307130133_3_GRIDPOINT_H
#define INC_16307130133_3_GRIDPOINT_H

#include <stdio.h>
#include <vector>

/* this grid-method function can be download in https://erich.realtimerendering.com/ptinpoly/
 * */
/* ptinpoly.h - point in polygon inside/outside algorithms header file.
 *
 * by Eric Haines, 3D/Eye Inc, erich@eye.com
 */

/* Define CONVEX to compile for testing only convex polygons (when possible,
 * this is faster) */
/* #define CONVEX */

/* Define HYBRID to compile triangle fan test for CONVEX with exterior edges
 * meaning an early exit (faster - recommended).
 */
/* #define HYBRID */

/* Define DISPLAY to display test triangle and test points on screen */
/* #define DISPLAY */

/* Define RANDOM to randomize order of edges for exterior test (faster -
 * recommended). */
/* #define RANDOM */

/* Define SORT to sort triangle edges and areas for half-plane and Spackman
 * tests (faster - recommended).
 * The bad news with SORT for non-convex testing is that this usually messes
 * up any coherence for the triangle fan tests, meaning that points on an
 * interior edge can be mis-classified (very rare, except when -c is used).
 * In other words, if a point lands on an edge between two test triangles,
 * normally it will be inside only one - sorting messes up the test order and
 * makes it so that the point can be inside two.
 */
/* #define SORT */

/* Define WINDING if a non-zero winding number should be used as the criterion
 * for being inside the polygon.  Only used by the general crossings test and
 * Weiler test.	 The winding number computed for each is the number of
 * counter-clockwise loops the polygon makes around the point.
 */
/* #define WINDING */

/* =========================== System Related ============================= */

#define EPSILON		0.00001
/* =========== Grid stuff ================================================= */

#define GR_FULL_VERT	0x01	/* line crosses vertically */
#define GR_FULL_HORZ	0x02	/* line crosses horizontally */

typedef struct {
    double	xa,ya ;
    double	minx, maxx, miny, maxy ;
    double	ax, ay ;
    double	slope, inv_slope ;
} GridRec, *pGridRec;

#define GC_BL_IN	0x0001	/* bottom left corner is in (else out) */
#define GC_BR_IN	0x0002	/* bottom right corner is in (else out) */
#define GC_TL_IN	0x0004	/* top left corner is in (else out) */
#define GC_TR_IN	0x0008	/* top right corner is in (else out) */
#define GC_L_EDGE_HIT	0x0010	/* left edge is crossed */
#define GC_R_EDGE_HIT	0x0020	/* right edge is crossed */
#define GC_B_EDGE_HIT	0x0040	/* bottom edge is crossed */
#define GC_T_EDGE_HIT	0x0080	/* top edge is crossed */
#define GC_B_EDGE_PARITY	0x0100	/* bottom edge parity */
#define GC_T_EDGE_PARITY	0x0200	/* top edge parity */
#define GC_AIM_L	(0<<10) /* aim towards left edge */
#define GC_AIM_B	(1<<10) /* aim towards bottom edge */
#define GC_AIM_R	(2<<10) /* aim towards right edge */
#define GC_AIM_T	(3<<10) /* aim towards top edge */
#define GC_AIM_C	(4<<10) /* aim towards a corner */
#define GC_AIM		0x1c00

#define GC_L_EDGE_CLEAR GC_L_EDGE_HIT
#define GC_R_EDGE_CLEAR GC_R_EDGE_HIT
#define GC_B_EDGE_CLEAR GC_B_EDGE_HIT
#define GC_T_EDGE_CLEAR GC_T_EDGE_HIT

#define GC_ALL_EDGE_CLEAR	(GC_L_EDGE_HIT | \
				 GC_R_EDGE_HIT | \
				 GC_B_EDGE_HIT | \
				 GC_T_EDGE_HIT )

typedef struct {
    short		tot_edges ;
    unsigned short	gc_flags ;
    GridRec		*gr ;
} GridCell, *pGridCell;

typedef struct {
    int		xres, yres ;	/* grid size */
    int		tot_cells ;	/* xres * yres */
    double	minx, maxx, miny, maxy ;	/* bounding box */
    double	xdelta, ydelta ;
    double	inv_xdelta, inv_ydelta ;
    double	*glx, *gly ;
    GridCell	*gc ;
} GridSet, *pGridSet;

void GridSetup(std::vector<std::pair<double, double> >& pgon, int numverts, int resolution, pGridSet p_gs);
//void GridSetup(double pgon[][2], int numverts, int resolution, pGridSet p_gs);
int AddGridRecAlloc(pGridCell p_gc, double xa, double ya, double xb, double yb, double eps);
int GridTest(pGridSet p_gs, double& x, double& y);

void GridCleanup(pGridSet p_gs);

//bool pointInPolygon(double px, double py, std::vector<std::pair<double, double>> &polygon);

#endif //INC_16307130133_3_GRIDPOINT_H


