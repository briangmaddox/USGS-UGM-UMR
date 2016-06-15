#ifndef TRANSITION_OBJ
#define TRANSITION_OBJ
/*! \file transition.h
    \brief Definition file for the Transition object.
    
    Definition file for the Transition object which 
    computes and handles the transition and slope matrix.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "ugm_defines.h"
#include "ugm_macros.h"
#include "landclass.h"
#include "memory.h"
#include "igrid.h"

//! Transition class manages the transition and slope matrixes
/*!
*/
class Transition
{
   private:
      double class_slope[MAX_NUM_CLASSES];
      double ftransition[MAX_NUM_CLASSES * MAX_NUM_CLASSES];
      double pct;
      int ltransition[MAX_NUM_CLASSES * MAX_NUM_CLASSES];
      int class_count[MAX_NUM_CLASSES][2];
      int trans_count;
      int class_count_sum0;
      int class_count_sum1;
      int num_classes;
   public:
      //! Constructor 
      /*!
       */
      Transition() {};

      //! Destructor
      /*!
      */
      ~Transition() {};
      
      //! Routine to compute the transition and slope matrixes
      /*!
      */
      void transition (const IGrid & ingrids,
                       Landclass & lclass,
                       GRID_P land1,                          /* IN  */
                      GRID_P land2,                          /* IN  */
                      GRID_P slope,                          /* IN  */
                      int *new_indices,                      /* IN  */
                      Classes * landuse_classes,             /* IN  */
                      double *ftransition,                   /* OUT */
                      double *class_slope);                /* OUT */

      //! Returns a pointer to the slope matrix
      /*!
      */
      double * GetClassSlope ();

      //! Returns a pointer to the transition matrix
      /*!
      */
      double * GetFTransition ();

      //! Initializes the transition object
      /*!
      */
      void Init (IGrid & ingrids, Landclass & lclass);

};

#endif
