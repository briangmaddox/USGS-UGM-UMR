#ifndef SPREAD_H
#define SPREAD_H



#define SWGHT_TYPE float
#define SLOPE_WEIGHT_ARRAY_SZ 256


#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "utilities.h"
#include "memory_obj.h"
#include "ugm_macros.h"
#include "stats.h"
#include "transition.h"
#include "color.h"
#include "MathLib/RandomLEcuyerBD.h"


/* #defines visable to any module including this header file*/
class Spread
{

 public:
  
  Spread(Proc & inruninfo, Scenario & inscene,    
         Landclass & inlclasses, Coeff &incoeffs,
         IGrid & iningrids,  ColorDirectory & incolortable,
         PGrid & inpgrids,  Transition & intrans,
         Stats & instats, MathLib::RandomLEcuyerBD & inrandomgen);



  void spread  (
                    float *average_slope,                          /* OUT    */
                    int *num_growth_pix,                           /* OUT    */
                    int* sng,
                    int* sdc,
                    int* og,
                    int* rt,
                    int* pop,
                    GRID_P z                                     /* IN/OUT */
                    );                       /* MOD    */


 private:

  void LogSlopeWeights (FILE * fp, int array_size, SWGHT_TYPE * lut);
  void spiral (int index,                                   /* IN     */
               int *i_out,                                  /* OUT    */
               int *j_out);                               /* OUT    */
  void phase1n3 (COEFF_TYPE diffusion_coefficient,          /* IN     */
                 COEFF_TYPE breed_coefficient,              /* IN     */
                 GRID_P z,                                  /* IN     */
                 GRID_P delta,                              /* IN/OUT */
                 GRID_P slp,                                /* IN     */
                 GRID_P excld,                              /* IN     */
                 SWGHT_TYPE * swght,                        /* IN     */
                 int *sng,                                  /* IN/OUT */
                 int *sdc);                               /* IN/OUT */

  void phase4 (COEFF_TYPE spread_coefficient,               /* IN     */
               GRID_P z,                                    /* IN     */
               GRID_P excld,                                /* IN     */
               GRID_P delta,                                /* IN/OUT */
               GRID_P slp,                                  /* IN     */
               SWGHT_TYPE * swght,                          /* IN     */
               int *og);                                  /* IN/OUT */
  

  void phase5 (COEFF_TYPE road_gravity,                     /* IN     */
               COEFF_TYPE diffusion_coefficient,            /* IN     */
               COEFF_TYPE breed_coefficient,                /* IN     */
               GRID_P z,                                    /* IN     */
               GRID_P delta,                                /* IN/OUT */
               GRID_P slp,                                  /* IN     */
               GRID_P excld,                                /* IN     */
               GRID_P roads,                                /* IN     */
               SWGHT_TYPE * swght,                          /* IN     */
               int *rt,                                     /* IN/OUT */
               GRID_P workspace);                         /* MOD    */
  
  void get_slp_weights (int array_size,                     /* IN     */
                         SWGHT_TYPE * lut);                /* OUT    */
  bool road_search (int i_grwth_center,          /* IN     */
                    int j_grwth_center,          /* IN     */
                    int *i_road,                 /* OUT    */
                    int *j_road,                 /* OUT    */
                    int max_search_index,        /* IN     */
                    GRID_P roads);             /* IN     */
  bool road_walk (int i_road_start,                   /* IN     */
                  int j_road_start,                   /* IN     */
                  int *i_road_end,                    /* OUT    */
                  int *j_road_end,                    /* OUT    */
                  GRID_P roads,                       /* IN     */
                  double diffusion_coefficient);    /* IN     */
  bool urbanize_nghbr (int i,                         /* IN     */
                       int j,                         /* IN     */
                       int *i_nghbr,                  /* OUT    */
                       int *j_nghbr,                  /* OUT    */
                       GRID_P z,                      /* IN     */
                       GRID_P delta,                  /* IN     */
                       GRID_P slp,                    /* IN     */
                       GRID_P excld,                  /* IN     */
                       SWGHT_TYPE * swght,            /* IN     */
                       PIXEL pixel_value,             /* IN     */
                       int *stat);                  /* OUT    */
 
  void get_neighbor (int i_in,                           /* IN     */
                     int j_in,                           /* IN     */
                     int *i_out,                         /* OUT    */
                     int *j_out);                      /* OUT    */

  bool urbanize (int row,                                   /* IN     */
                 int col,                                   /* IN     */
                 GRID_P z,                                  /* IN     */
                 GRID_P delta,                              /* IN     */
                 GRID_P slp,                                /* IN     */
                 GRID_P excld,                              /* IN     */
                 SWGHT_TYPE * swght,                        /* IN     */
                 PIXEL pixel_value,                         /* IN     */
                 int *stat);                              /* OUT    */

  COEFF_TYPE GetDiffusionValue (COEFF_TYPE diffusion_coeff);    /* IN    */
  COEFF_TYPE GetRoadGravValue (COEFF_TYPE rg_coeff);            /* IN    */

  
  Proc & runinfo; 
  Scenario & scene;    
  Landclass & lclasses; 
  Coeff &coeffs;
  IGrid & ingrids;  
  ColorDirectory & colortable;
  PGrid & pgrids;  
  Transition & trans;
  Stats & stats;
  MathLib::RandomLEcuyerBD & randomgen;

};

#endif


