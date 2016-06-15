#ifndef DELTATRON_H
#define DELTATRON_H
/*! \file deltatron.h
    \brief Definition file for the deltatron object.
    
    Definition file for the deltatron which contains several
    parts of the montecarlo method that implement the model.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utilities.h"
#include "ugm_macros.h"
#include "memory_obj.h"
#include "stats.h"
#include "color.h"
#include "transition.h"
#include "MathLib/RandomLEcuyerBD.h"


//! Deltatron monte-carlo growth class.
/*! Implements random generation and growth heursitics to 
    simulate urban growth.
*/
class Deltatron
{
public:
  
  //! Constructor.
  /*! Takes refrences to all the other data class's needed to
      perfrom growth simulation.
  */
  Deltatron(Proc & inruninfo, Scenario & inscene,    
         Landclass & inlclasses, Coeff &incoeffs,
         IGrid & iningrids,  ColorDirectory & incolortable,
         PGrid & inpgrids,  Transition & intrans,
         Stats & instats,   MathLib::RandomLEcuyerBD & inrandomgen);

  //! Main entry point for monte carlo methods.
  /*!
   */
  void delta (int *new_indices,                     /* IN     */
              Classes * landuse_classes,            /* IN     */
              Classes * class_indices,              /* IN     */
              GRID_P workspace1,                    /* MOD    */
              GRID_P deltatron,                     /* IN/OUT */
              GRID_P urban_land,                    /* IN     */
              GRID_P land_out,                      /* OUT    */
              GRID_P slp,                           /* IN     */
              int drive,                            /* IN     */
              CLASS_SLP_TYPE* class_slope,          /* IN     */
              FTRANS_TYPE* ftransition);            /* IN     */
  
  //! Performs deltatron phase 1 growth.
  /*!
   */
  void phase1 (int drive,                              /* IN     */
               GRID_P urban_land,                      /* IN     */
               GRID_P phase1_land,                     /* OUT    */
               GRID_P slope,                           /* IN     */
               GRID_P deltatron,                       /* IN/OUT */
               Classes * landuse_classes,              /* IN     */
               Classes * class_indices,                /* IN     */
               int *new_indices,                       /* IN     */
               CLASS_SLP_TYPE * class_slope,           /* IN     */
               FTRANS_TYPE * ftransition);             /* IN     */
  
  //! Determines new landuse to transition to over time.
  /*!
   */
  int get_new_landuse (Classes * class_indices,        /* IN     */
                       Classes * landuse_classes,      /* IN     */
                       PIXEL local_slope,              /* IN     */
                       CLASS_SLP_TYPE * class_slope);  /* IN     */

  //! Performs phase 2 deltatron growth
  /*!
   */
  void phase2 (GRID_P urban_land,                      /* IN     */
               GRID_P phase1_land,                     /* IN     */
               GRID_P deltatron,                       /* IN/OUT */
               GRID_P phase2_land,                     /* OUT    */
               Classes * landuse_classes,              /* IN     */
               int *new_indices,                       /* IN     */
               FTRANS_TYPE * ftransition);             /* IN     */



 private:

  //referneces to other sim objects.
  Proc & runinfo;
  Scenario & scene;    
  Landclass & lclasses;
  Coeff & coeffs;
  IGrid & ingrids;  
  ColorDirectory & colortable;
  PGrid & pgrids;  
  Transition & trans;
  Stats & stats;
  MathLib::RandomLEcuyerBD & randomgen;

};

#endif
