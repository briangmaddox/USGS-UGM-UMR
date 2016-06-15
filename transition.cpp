/*! \file transition.h
    \brief Definition file for the Transition object.
    
    Definition file for the Transition object which 
    computes and handles the transition and slope matrix.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "transition.h"


/*

 FUNCTION NAME: GetClassSlope
 PURPOSE:       return class slope
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double *Transition::
  GetClassSlope ()
{
  return class_slope;
}

/*

 FUNCTION NAME: GetFTransition
 PURPOSE:       return ftransition
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double *Transition::
  GetFTransition ()
{
  return ftransition;
}

/*
 FUNCTION NAME: Init
 PURPOSE:       driver to initialize transition matrix
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Transition::
  Init (IGrid & ingrids, Landclass & lclass)
{
  char func[] = "Init";
  GRID_P landuse0_ptr;
  GRID_P landuse1_ptr;
  GRID_P slope_ptr;

  // FUNC_INIT;
  num_classes = lclass.GetNumLandclasses ();

  landuse0_ptr = ingrids.GetLanduseGridPtr (__FILE__, func, __LINE__, 0);
  landuse1_ptr = ingrids.GetLanduseGridPtr (__FILE__, func, __LINE__, 1);
  slope_ptr = ingrids.GetSlopeGridPtr (__FILE__, func, __LINE__);
  transition (ingrids,
              lclass,
              landuse0_ptr,                            /* IN  */
              landuse1_ptr,                            /* IN  */
              slope_ptr,                               /* IN  */
              lclass.GetNewIndicesPtr (),           /* IN  */
              lclass.GetClassesPtr (),              /* IN  */
              ftransition,                             /* OUT */
              class_slope);                          /* OUT */
  landuse0_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, landuse0_ptr);
  landuse1_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, landuse1_ptr);
  slope_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, slope_ptr);
  //FUNC_END;
}

/*
 FUNCTION NAME: transition
 PURPOSE:       initialize the transition matrix
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:

*/
void Transition::transition (const IGrid & ingrids,
                             Landclass & lclass,
                             GRID_P land1,                            /* IN  */
                    GRID_P land2,                            /* IN  */
                    GRID_P slope,                            /* IN  */
                    int *new_indices,                        /* IN  */
                    Classes * landuse_classes,               /* IN  */
                    double *ftransition,                     /* OUT */
                    double *class_slope)                   /* OUT */
{

  //char func[] = "transition";
  int i;
  int j;
  int k;
  int l;
  int lsum;
  PIXEL land1_val;
  PIXEL land2_val;
  int land1_idx;
  int land2_idx;


  
  assert (land1 != NULL);
  assert (land2 != NULL);
  assert (slope != NULL);
  assert ((num_classes > 0) && (num_classes <= MAX_NUM_CLASSES));
  assert (new_indices != NULL);
  assert (landuse_classes != NULL);
  assert (ltransition != NULL);
  assert (ftransition != NULL);
  assert (class_slope != NULL);

  trans_count = 0;
  class_count_sum0 = 0;
  class_count_sum1 = 0;

  /*
   
    ZERO OUT MEMORY
   
   */
  memset ((void *) ltransition, 0,
          num_classes * sizeof (ltransition[0]) * num_classes);
  memset ((void *) ftransition, 0,
          num_classes * sizeof (ftransition[0]) * num_classes);
  for (k = 0; k < num_classes; k++)
  {
    class_count[k][0] = 0;
    class_count[k][1] = 0;
    class_slope[k] = 0.0;
  }

  for (i = 0; i < ingrids.GetNumRows (); i++)
  {
    for (j = 0; j < ingrids.GetNumCols (); j++)
    {
      land1_val = land1[ingrids.GetNumCols()*i +j];
      land2_val = land2[ingrids.GetNumCols()*i + j];

      land1_idx = new_indices[land1_val];
      land2_idx = new_indices[land2_val];

      class_count[land1_idx][0]++;
      class_count[land2_idx][1]++;

      class_slope[land2_idx] +=
        (double) slope[ingrids.GetNumCols()*i+ j];


      ltransition[lclass.GetNumLandclasses()*land1_idx + land2_idx]++;

      if (land1_val != land2_val)
      {
        trans_count++;
      }
    }
  }

  for (k = 0; k < num_classes; k++)
  {
    lsum = 0;
    class_count_sum0 += class_count[k][0];
    class_count_sum1 += class_count[k][1];

    for (l = 0; l < num_classes; l++)
    {
      ftransition[lclass.GetNumLandclasses()*k + l] =
        (double) ltransition[lclass.GetNumLandclasses()*k + l];
      lsum += ltransition[lclass.GetNumLandclasses()*k + l];
    }

    for (l = 0; l < num_classes; l++)
    {
      ftransition[lclass.GetNumLandclasses()*k + l] = (lsum == 0) ?
        0.0 : ftransition[lclass.GetNumLandclasses()*k + l] / (double) lsum;
    }
  }

  //FUNC_END;
  return;
}
