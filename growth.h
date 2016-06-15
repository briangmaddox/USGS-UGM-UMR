#ifndef GROWTH_H
#define GROWTH_H
/*! \file growth.h
    \brief Definition file for the growth object.
    
    Definition file for the growth object which runs the
    deltatron and spread portions of the simultion.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "stats.h"
#include "transition.h"
#include "landclass.h"
#include "color.h"
#include "MathLib/RandomLEcuyerBD.h"

//! Growth class runs the deltatron and spread parts of the sim.
class Growth
{
public:

  //! Constructor.
  /*! Accepts all simultation state objects so that it can
      have access to simulation data.
  */
  Growth( Proc & inruninfo, Scenario & inscene,
              Landclass & inlclasses, Coeff &incoeffs,
              IGrid & iningrids,  ColorDirectory & incolortable,
              PGrid & inpgrids,  Transition & intrans,
              Stats & instats,
              MathLib::RandomLEcuyerBD & inrandomgen);

  //! Loop over simulated years performing grow operations.
  /*!
   */
  void grow(GRID_P z_ptr, GRID_P land1_ptr);

 private:

  //! routine for handling non landuse processing
  /*!
   */
  void non_landuse (GRID_P z_ptr);
 
  //! Initialize variables for doing landuse.
  /*!
   */
  void landuse_init (GRID_P deltatron_ptr,
                         GRID_P land1_ptr);
  //! Routine for handling landuse type of processing.
  /*!
   */
  void landuse (GRID_P land1_ptr,
                     int num_growth_pix);

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



