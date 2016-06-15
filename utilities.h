#ifndef UTILITIES_H
#define UTILITIES_H
#include "ugm_defines.h"
#include "grid.h"
#include "scenario.h"
#include "imageio.h"
#include "igrid.h"
#include "color.h"
#include "MathLib/RandomLEcuyerBD.h"
 
/*! \file utilities.h
    \brief Definition file for model utility functions.

    Definition file for common utility functions.
    For credits see CREDITS.TXT in this directory.
    \sa CREDITS.TXT

*/

//! Converts a string to all caps.
/*!
 */
void util_AllCAPS(char* str_ptr);

//! Merges two grids together.
/*!
 */
void util_merge_background (GRID_P foreground_gif,    /* IN     */
                            GRID_P background_gif,    /* IN     */
                            GRID_P merged_gif);       /* OUT    */

//! Copys one grid to another.
/*!
 */
void util_copy_grid (GRID_P source,  /* IN     */
		     GRID_P target); /* OUT    */

//! Set the pixels in target based on values in source grid
/*!
 */
void util_condition_gif (int num_pixels, /* IN     */
                         GRID_P source,  /* IN     */
                         int option,     /* IN     */
                         int cmp_value,  /* IN     */
                         GRID_P target,  /* OUT    */
                         int set_value); /* IN     */

//! Count pixels meeting option & value conditionals
/*!
 */
int util_count_pixels (int num_pixels, /* IN     */
                       GRID_P pixels,  /* IN     */
                       int option,     /* IN     */
                       int value);     /* IN     */

//! Returns a randomly selected neighbor.
/*!
 */
void util_get_neighbor(int i_in,      /* IN     */
                       int j_in,      /* IN     */
                       int* i_out,    /* OUT    */
                       int* j_out,    /* OUT    */
                       MathLib::RandomLEcuyerBD & randomgen);   /* OUT    */

//! Trims a string from left and right.
/*!
 */
int util_trim (char s[]);   /* IN/OUT */


//! Count the neighbors meeting certain criteria.
/*!
 */
int util_count_neighbors(GRID_P grid,    /* IN     */
                         int igridnumcols,
                         int i,          /* IN     */
                         int j,          /* IN     */
                         int option,     /* IN     */
                         PIXEL value);   /* IN     */

//! Return next neighbor in a sequence
/*!
 */
void util_get_next_neighbor(const IGrid & ingrids,
                            int i_in,      /* IN     */
                            int j_in,      /* IN     */
                            int* i_out,    /* OUT    */
                            int* j_out,    /* OUT    */
                            int index);    /* IN     */
 
//! Count the # of similar pixels in two given grids
/*! \param num_pixels the number of pixels.
    \param ptr1 the first grid.
    \param ptr2 the second grid.
 */
int util_img_intersection (int num_pixels,     /* IN     */
                           GRID_P ptr1,        /* IN     */
                           GRID_P ptr2);       /* IN     */


//!  Map selected pixels into a new index.
/*! 
 */
void util_map_gridpts_2_index(GRID_P in,          /* IN     */
                              GRID_P out,         /* OUT    */
                              int* lower_bound,   /* IN     */
                              int* upper_bound,   /* IN     */
                              int* index,         /* IN     */
                              int count);         /* IN     */

//! Overlay one image onto another
/*!
 */
void util_overlay(GRID_P layer0,  /* IN     */
                  GRID_P layer1,  /* IN     */
                  GRID_P out );   /* OUT    */

//! Write probability grids
/*!
 */
void util_WriteZProbGrid (Proc & runinfo,             /* IN     */          
			  Scenario & scene,           /* IN     */
			  IGrid & ingrids,            /* IN     */
			  ColorDirectory &colortable, /* IN     */
			  GRID_P z_ptr,               /* IN     */
			  char name[]);               /* IN     */

//! Overlay the seed onto a probability image
/*!
 */
void util_overlay_seed (IGrid & ingrids,      /* IN     */
			GRID_P z_prob_ptr);   /* IN/OUT */

//! Initialize a grid with value
/*! /param gif is the grid to intialize.
    /param value is the the value to intialize the grid too.
*/
void util_init_grid (GRID_P gif,      /* OUT    */
                     PIXEL value);    /* IN     */
#endif
