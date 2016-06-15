#ifndef INPUT_H
#define INPUT_H
/*! \file input.h
    \brief Definition file for the input utility functions
    
    Definition file for the input utility functions.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include <stdio.h>
#include "ugm_typedefs.h"
#include "scenario.h"



//!Consume input from a specified file.
/*!
 */
void inp_slurp(char* filename,
               void* ptr,
               int count);

//! Reads the restart file.
/*! Note: this option is disabled in our UMR-USGS version.
 */
void
  inp_read_restart_file (Scenario & scene, int* diffusion,
                         int* breed,
                         int* spread,
                         int* slope_resistance,
                         int* road_gravity,
                         long *random_seed,
                         int *counter, int mpi_rank);

#endif
