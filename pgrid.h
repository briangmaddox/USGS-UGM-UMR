#ifndef PGRID_H
#define PGRID_H
/*! \file pgrid.h
    \brief Definition file for the pgrid object.
    
    Definition file for the pgrid object that represents
    temporary grids used in the sim.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "ugm_defines.h"
#include "grid.h"

//! PGrid class.
/*! Contains tempoary grids for simulation.
 */
class PGrid
{
public:
  //! Returns the number of pgrids.
  /*!
   */
  int GetPGridCount() const throw();
  
  //! Initlizes the pgrids.
  /*!
   */
  void Init() throw();
  
  //! Returns a pointer to the Z grid.
  /*!
   */
  GRID_P GetZPtr() throw();
  
  //! Returns a pointer to the deltatron grid.
  /*!
   */
  GRID_P GetDeltatronPtr() throw();
  
  //! Returns a pointer to the delta grid.
  /*!
   */
  GRID_P GetDeltaPtr() throw();
  
  //! Returns a pointer to the first landclass grid.
  /*!
   */
  GRID_P GetLand1Ptr() throw();
  
  //! Returns a pointer to the second landlcass grid.
  /*!
   */
  GRID_P GetLand2Ptr() throw();
  
  //! Returns a pointer to the cumulate grid.
  /*!
   */
  GRID_P GetCumulatePtr() throw();

private:
  Grid z;
  Grid deltatron;
  Grid delta;
  Grid land1;
  Grid land2;
  Grid cumulate;
};


#endif
