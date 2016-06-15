#ifndef PGRID_OBJ_C
#define PGRID_OBJ_C
/*! \file pgrid.h
    \brief Implementation file for the pgrid object.
    
    Implementation file for the pgrid object that represents
    temporary grids used in the sim.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "pgrid.h"
#include "memory_obj.h"


/*
  Global pgrid_count
 */
#define PGRID_COUNT 6


/*
   FUNCTION NAME: GetPGridCount
   PURPOSE:       return PGRID_COUNT
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int PGrid::GetPGridCount () const throw()
{
  return PGRID_COUNT;
}

/*
   FUNCTION NAME: Init
   PURPOSE:       initialize the p type grids
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void PGrid::Init () throw()
{
  char func[] = "Init";

  z.ptr = mem_GetPGridPtr (func);
  deltatron.ptr = mem_GetPGridPtr (func);
  delta.ptr = mem_GetPGridPtr (func);
  land1.ptr = mem_GetPGridPtr (func);
  land2.ptr = mem_GetPGridPtr (func);
  cumulate.ptr = mem_GetPGridPtr (func);
}

/*
   FUNCTION NAME: GetZPtr
   PURPOSE:       return pointer to z grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P PGrid::GetZPtr () throw()
{
  return z.ptr;
}

/*
   FUNCTION NAME: GetDeltatronPtr
   PURPOSE:       return pointer to deltatron grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P PGrid::GetDeltatronPtr () throw()
{
  return deltatron.ptr;
}

/*
   FUNCTION NAME: GetDeltaPtr
   PURPOSE:       return pointer to delta grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P PGrid::GetDeltaPtr () throw()
{
  return delta.ptr;
}

/*
   FUNCTION NAME: GetLand1Ptr
   PURPOSE:       return pointer to land1 grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P PGrid::GetLand1Ptr () throw()
{
  return land1.ptr;
}

/*
   FUNCTION NAME: GetLand2Ptr
   PURPOSE:       return pointer to land2 grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P PGrid::GetLand2Ptr () throw()
{
  return land2.ptr;
}

/*
   FUNCTION NAME: GetCumulatePtr
   PURPOSE:       return pointer to cumulate grid
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P PGrid::GetCumulatePtr () throw()
{
  return cumulate.ptr;
}


#endif
