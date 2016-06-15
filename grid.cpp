/*! \file grid.cpp
    \brief Implementation file for the grid object.
    
    Implementation file for the grid object which represents
    a data layer in the simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

/*
   FUNCTION NAME: grid_SetMinMax
   PURPOSE:       find the min and max for a given grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Grid::
SetMinMax ( void)
{
  
#ifdef PACKING
  int i;
  int total_pixels;
  int localmin;
  int localmax;
  GRID_P unpacked_ptr;

  total_pixels = ncols * nrows;
  unpacked_ptr = mem_GetWGridPtr (__FILE__, func, __LINE__);

  _unpack ((char *) ptr,
           unpacked_ptr,
           total_pixels,
           -1);

  localmin = unpacked_ptr[0];
  localmax = unpacked_ptr[0];
  for (i = 0; i < total_pixels; i++)
  {
    localmin = MIN (localmin, unpacked_ptr[i]);
    localmax = MAX (localmax, unpacked_ptr[i]);
  }
  mem_GetWGridFree (__FILE__, func, __LINE__, unpacked_ptr);
  min = localmin;
  max = localmax;
#else
  int i;
  int total_pixels;
  int localmin;
  int localmax;

  localmin = ptr[0];
  localmax = ptr[0];
  total_pixels = ncols * nrows;
  for (i = 0; i < total_pixels; i++)
  {
    localmin = MIN (localmin, ptr[i]);
    localmax = MAX (localmax, ptr[i]);
  }
  min = localmin;
  max = localmax;
#endif
}

/*
   FUNCTION NAME: histogram
   PURPOSE:       histogram the values in a grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Grid::
  Histogram ( void)
{
  int i;

  for (i = 0; i < 256; i++)
  {
    histogram[i] = 0;
  }
  for (i = 0; i < nrows * ncols; i++)
  {
    histogram[ptr[i]]++;
  }
}

/*
   FUNCTION NAME: dump
   PURPOSE:       dump some of the values pertaining to a given grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Grid::
  Dump (FILE * fp)
{
  int i;
  int total_pixels;

  total_pixels = nrows * ncols;
  fprintf (fp, "%s %u Index Count PercentOfImage\n", __FILE__, __LINE__);
  for (i = 0; i < 256; i++)
  {
    if (histogram[i] > 0)
    {
      fprintf (fp, "%s %u grid_ptr->histogram[%3u]=%5u %8.2f%%\n", __FILE__, __LINE__, i,
               histogram[i], 100.0 * histogram[i] / total_pixels);
    }
  }
}
