#ifndef GRID_H
#define GRID_H
/*! \file grid.h
    \brief Definition file for the grid object.
    
    Definition file for the grid object which represents
    a layer of data to be used in the simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include "ugm_defines.h"
#include "ugm_macros.h"
#include <stdio.h>

//! Grid class represents a layer of data and its associated metrics.
/*!
 */
class Grid
{
   private:
       //! Simple structure for holding year information.
       typedef struct
       {
          int   digit;
         char  string[DIGITS_IN_YEAR + 1];
       } year_info;
   public:
      //! Finds the minimum and maximum value in the data layer.
      /*!
       */
      void SetMinMax ( void);
      
      //! Computes the histrogram (per pixel) of the grid.
      /*!
       */
      void Histogram ( void);
      
      //! Dumps the grid file to a output file.
      /*!
       */
      void Dump (FILE * fp);
      
      GRID_P   ptr;
      bool packed;
      int  color_bits;
      int  bits_per_pixel;
      int size_words;
      int size_bytes;
      int  nrows;
      int  ncols;
      int  max;
      int  min;
      int  histogram[256];
      char filename[MAX_FILENAME_LEN];
      year_info year;
   
};

#endif
