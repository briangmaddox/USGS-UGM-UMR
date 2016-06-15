#ifndef DRIVER_H
#define DRIVER_H
/*! \file driver.h
    \brief Definition file for the driver object.
    
    Definition file for the driver which will actually
    run the overal simulation given a set of coeffs.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "igrid.h"
#include "pgrid.h"
#include "landclass.h"
#include "color.h"
#include "coeff.h"
#include "utilities.h"
#include "memory_obj.h"
#include "scenario.h"
#include "transition.h"
#include "ugm_macros.h"
#include "ugm_defines.h"
#include "proc.h"
#include "imageio.h"
#include "stats.h"
#include "color.h"
#include "MathLib/RandomLEcuyerBD.h"


//simple typedef
typedef double fmatch_t;


//! Driving simulation class.
/*! Class is responsible for driving the overal simultation.
 */
class Driver
{
public:
  
  //! Constructor.
  /*! Accepts all model data objects neccesary for running the
      simulation.
  */
  Driver( Proc & inruninfo, Scenario & inscene,
          Landclass & inlclasses, Coeff &incoeffs,
          IGrid & iningrids,  ColorDirectory & incolortable,
          PGrid & inpgrids,  Transition & intrans,
          Stats & instats,
          MathLib::RandomLEcuyerBD & inrandomgen);
  
  //! Main function for driving the simulation.
  /*!
   */
  void drv_driver ();

 private:
  
  //! Monte Carlo loop that calls grow to move the simulation forward.
  /*!
   */
  void drv_monte_carlo (GRID_P z_cumulate_ptr, GRID_P sim_landuse_ptr);
                     
  //!  Calculates the matching value of the landuse transition.
  /*!
   */
  fmatch_t drv_fmatch (GRID_P cum_probability_ptr,
                       GRID_P landuse1_ptr);


  //model data and utility classes.
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
