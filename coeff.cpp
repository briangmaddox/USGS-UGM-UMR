/*! \file coeff.cpp
    \brief Implementation file for the coeff object.
    
    Implementation file for the coeff object which keeps track
    of the coeffs throughout the model simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/


#include "coeff.h"


/*
  Class Constructor
*/
Coeff::Coeff(int arg_size, int arg_rank )
{
  glb_npes = arg_size;
  glb_mype = arg_rank;
  saved_coefficient.diffusion = 0;
  saved_coefficient.spread = 0;
  saved_coefficient.breed = 0;
  saved_coefficient.slope_resistance = 0;
  saved_coefficient.road_gravity = 0;
  
  current_coefficient.diffusion = 0;
  current_coefficient.spread = 0;
  current_coefficient.breed = 0;
  current_coefficient.slope_resistance = 0;
  current_coefficient.road_gravity = 0;

  step_coeff.diffusion = 0;
  step_coeff.spread = 0;
  step_coeff.breed = 0;
  step_coeff.slope_resistance = 0;
  step_coeff.road_gravity = 0;

  start_coeff.diffusion = 0;
  start_coeff.spread = 0;
  start_coeff.breed = 0;
  start_coeff.slope_resistance = 0;
  start_coeff.road_gravity = 0;

  stop_coeff.diffusion = 0;
  stop_coeff.spread = 0;
  stop_coeff.breed = 0;
  stop_coeff.slope_resistance = 0;
  stop_coeff.road_gravity = 0;

  best_fit_coeff.diffusion = 0;
  best_fit_coeff.spread = 0;
  best_fit_coeff.breed = 0;
  best_fit_coeff.slope_resistance = 0;
  best_fit_coeff.road_gravity = 0;


}

/*
   FUNCTION NAME: coeff_SetCurrentDiffusion
   PURPOSE:       set the diffusion field
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetCurrentDiffusion (double val) throw()
{
  if (val == 0)
  {
    current_coefficient.diffusion = 1;
    saved_coefficient.diffusion = 1;
  }
  else
  {
    current_coefficient.diffusion = val;
    saved_coefficient.diffusion = val;
  }
}

/*
   FUNCTION NAME: SetCurrentSpread
   PURPOSE:       set the spread field of current_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
*/
void Coeff::SetCurrentSpread (double val) throw()
{
  if (val == 0)
  {
    current_coefficient.spread = 1;
    saved_coefficient.spread = 1;
  }
  else
  {
    current_coefficient.spread = val;
    saved_coefficient.spread = val;
  }
}
/*
 FUNCTION NAME: SetCurrentBreed
 PURPOSE:       set breed field of current_coefficient struct
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Coeff::SetCurrentBreed (double val) throw()
{
  if (val == 0)
  {
    current_coefficient.breed = 1;
    saved_coefficient.breed = 1;
  }
  else
  {
    current_coefficient.breed = val;
    saved_coefficient.breed = val;
  }
}

/*
 FUNCTION NAME: SetCurrentSlopeResist
 PURPOSE:       set slope_resistance field of current_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetCurrentSlopeResist (double val) throw()
{
  if (val == 0)
  {
    current_coefficient.slope_resistance = 1;
    saved_coefficient.slope_resistance = 1;
  }
  else
  {
    current_coefficient.slope_resistance = val;
    saved_coefficient.slope_resistance = val;
  }
}

/*
   FUNCTION NAME: SetCurrentRoadGravity
   PURPOSE:       set road_gravity field of current_coefficient
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetCurrentRoadGravity (double val) throw()
{
  if (val == 0)
  {
    current_coefficient.road_gravity = 1;
    saved_coefficient.road_gravity = 1;
  }
  else
  {
    current_coefficient.road_gravity = val;
    saved_coefficient.road_gravity = val;
  }
}

/*
   FUNCTION NAME: SetStepDiffusion
   PURPOSE:       set diffusion field of step_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStepDiffusion (int val) throw()
{
  step_coeff.diffusion = val;
}

/*
   FUNCTION NAME: SetStepSpread
   PURPOSE:       set spread of step_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStepSpread (int val) throw()
{
  step_coeff.spread = val;
}

/*
   FUNCTION NAME: SetStepBreed
   PURPOSE:       set breed field of step_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStepBreed (int val) throw()
{
  step_coeff.breed = val;
}

/*
   FUNCTION NAME: SetStepSlopeResist
   PURPOSE:       set slope_resistance field of step_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStepSlopeResist (int val) throw()
{
  step_coeff.slope_resistance = val;
}

/*
   FUNCTION NAME: SetStepRoadGravity
   PURPOSE:       set road_gravity field of step_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStepRoadGravity (int val) throw()
{
  step_coeff.road_gravity = val;
}

/*
   FUNCTION NAME: diffusion
   PURPOSE:       set diffusion field of start_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStartDiffusion (int val) throw()
{
  start_coeff.diffusion = val;
}

/*
   FUNCTION NAME: SetStartSpread
   PURPOSE:       set spread field of start_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/

void Coeff::SetStartSpread (int val) throw()
{
  start_coeff.spread = val;
}

/*
   FUNCTION NAME: SetStartBreed
   PURPOSE:       set breed field of start_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStartBreed (int val) throw()
{
  start_coeff.breed = val;
}

/*
   FUNCTION NAME: SetStartSlopeResist
   PURPOSE:       set slope_resistance field of start_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStartSlopeResist (int val) throw()
{
  start_coeff.slope_resistance = val;
}

/*
   FUNCTION NAME: SetStartRoadGravity
   PURPOSE:       set road_gravity field of start_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStartRoadGravity (int val) throw()
{
  start_coeff.road_gravity = val;
}

/*
   FUNCTION NAME: SetStopDiffusion
   PURPOSE:       set diffusion field of stop_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStopDiffusion (int val) throw()
{
  stop_coeff.diffusion = val;
}

/*
   FUNCTION NAME: SetStopSpread
   PURPOSE:       set spread field of stop_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStopSpread (int val) throw()
{
  stop_coeff.spread = val;
}

/*
   FUNCTION NAME: SetStopBreed
   PURPOSE:       set breed field of stop_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStopBreed (int val) throw()
{
  stop_coeff.breed = val;
}

/*
   FUNCTION NAME: SetStopSlopeResist
   PURPOSE:       set slope_resistance field of stop_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStopSlopeResist (int val) throw()
{
  stop_coeff.slope_resistance = val;
}

/*
   FUNCTION NAME: SetStopRoadGravity
   PURPOSE:       set road_gravity field of stop_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetStopRoadGravity (int val) throw()
{
  stop_coeff.road_gravity = val;
}

/*
   FUNCTION NAME: SetBestFitDiffusion
   PURPOSE:       set diffusion field of best_fit_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetBestFitDiffusion (int val) throw()
{
  best_fit_coeff.diffusion = val;
}

/*
   FUNCTION NAME: SetBestFitSpread
   PURPOSE:       set spread field of best_fit_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetBestFitSpread (int val) throw()
{
  best_fit_coeff.spread = val;
}

/*
   FUNCTION NAME: SetBestFitBreed
   PURPOSE:       set breed field of best_fit_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetBestFitBreed (int val) throw()
{
  best_fit_coeff.breed = val;
}

/*
   FUNCTION NAME: SetBestFitSlopeResist
   PURPOSE:       set slope_resistance field of best_fit_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetBestFitSlopeResist (int val) throw()
{
  best_fit_coeff.slope_resistance = val;
}

/*
   FUNCTION NAME: SetBestFitRoadGravity
   PURPOSE:       set road_gravity field of best_fit_coeff
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetBestFitRoadGravity (int val) throw()
{
  best_fit_coeff.road_gravity = val;
}

/*
   FUNCTION NAME: SetSavedDiffusion
   PURPOSE:       set diffusion field of saved_coefficient
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetSavedDiffusion (double val) throw()
{
  saved_coefficient.diffusion = val;
}

/*
   FUNCTION NAME: SetSavedSpread
   PURPOSE:       set spread field of saved_coefficient
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetSavedSpread (double val) throw()
{
  saved_coefficient.spread = val;
}

/*
   FUNCTION NAME: SetSavedBreed
   PURPOSE:       set breed field of saved_coefficient
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetSavedBreed (double val) throw()
{
  saved_coefficient.breed = val;
}

/*
   FUNCTION NAME: SetSavedSlopeResist
   PURPOSE:       set slope_resistance field of saved_coefficient
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetSavedSlopeResist (double val) throw()
{
  saved_coefficient.slope_resistance = val;
}

/*
   FUNCTION NAME: SetSavedRoadGravity
   PURPOSE:       set road_gravity field of saved_coefficient
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::SetSavedRoadGravity (double val) throw()
{
  saved_coefficient.road_gravity = val;
}


/*
   FUNCTION NAME: GetSavedDiffusion
   PURPOSE:       return diffusion from saved_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetSavedDiffusion () const throw()
{
  return saved_coefficient.diffusion;
}

/*
   FUNCTION NAME: GetSavedSpread
   PURPOSE:       return spread from saved_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetSavedSpread () const throw()
{
  return saved_coefficient.spread;
}

/*

   FUNCTION NAME: GetSavedBreed
   PURPOSE:       return breed from saved_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetSavedBreed () const throw()
{
  return saved_coefficient.breed;
}

/*
   FUNCTION NAME: GetSavedSlopeResist
   PURPOSE:       return slope_resistance from saved_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetSavedSlopeResist () const throw()
{
  return saved_coefficient.slope_resistance;
}

/*
   FUNCTION NAME: GetSavedRoadGravity
   PURPOSE:       return road_gravity from saved_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetSavedRoadGravity () const throw()
{
  return saved_coefficient.road_gravity;
}

/*
   FUNCTION NAME: GetCurrentDiffusion
   PURPOSE:       return diffusion from current_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetCurrentDiffusion () const throw()
{
  return current_coefficient.diffusion;
}

/*
   FUNCTION NAME: GetCurrentSpread
   PURPOSE:       return spread from current_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetCurrentSpread () const throw()
{
  return current_coefficient.spread;
}

/*
   FUNCTION NAME: GetCurrentBreed
   PURPOSE:       return breed from current_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetCurrentBreed () const throw()
{
  return current_coefficient.breed;
}

/*
   FUNCTION NAME: GetCurrentSlopeResist
   PURPOSE:       return slope_resistance from current_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetCurrentSlopeResist () const throw()
{
  return current_coefficient.slope_resistance;
}

/*
   FUNCTION NAME: GetCurrentRoadGravity
   PURPOSE:       return road_gravity from current_coefficient struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Coeff::GetCurrentRoadGravity () const throw()
{
  return current_coefficient.road_gravity;
}

/*
   FUNCTION NAME: GetStepDiffusion
   PURPOSE:       return diffusion from step_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStepDiffusion () const throw()
{
  return step_coeff.diffusion;
}

/*
   FUNCTION NAME: GetStepSpread
   PURPOSE:       return spread from step_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStepSpread () const throw()
{
  return step_coeff.spread;
}

/*
   FUNCTION NAME: GetStepBreed
   PURPOSE:       return breed from step_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStepBreed () const throw()
{
  return step_coeff.breed;
}

/*
   FUNCTION NAME: GetStepSlopeResist
   PURPOSE:       return slope_resistance from step_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStepSlopeResist () const throw()
{
  return step_coeff.slope_resistance;
}

/*
   FUNCTION NAME: GetStepRoadGravity
   PURPOSE:       return road_gravity from step_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStepRoadGravity () const throw()
{
  return step_coeff.road_gravity;
}

/*
   FUNCTION NAME: GetStartDiffusion
   PURPOSE:       return diffusion from start_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStartDiffusion () const throw()
{
  return start_coeff.diffusion;
}

/*
   FUNCTION NAME: GetStartSpread
   PURPOSE:       return spread from start_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStartSpread () const throw()
{
  return start_coeff.spread;
}

/*
   FUNCTION NAME: GetStartBreed
   PURPOSE:       return breed from start_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStartBreed () const throw()
{
  return start_coeff.breed;
}

/*
   FUNCTION NAME: GetStartSlopeResist
   PURPOSE:       return slope_resistance from start_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStartSlopeResist () const throw()
{
  return start_coeff.slope_resistance;
}

/*
   FUNCTION NAME: GetStartRoadGravity
   PURPOSE:       return road_gravity from start_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStartRoadGravity () const throw()
{
  return start_coeff.road_gravity;
}

/*
   FUNCTION NAME: GetStopDiffusion
   PURPOSE:       return diffusion from stop_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStopDiffusion () const throw()
{
  return stop_coeff.diffusion;
}

/*
   FUNCTION NAME: GetStopSpread
   PURPOSE:       return spread from stop_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStopSpread () const throw()
{
  return stop_coeff.spread;
}

/*
   FUNCTION NAME: GetStopBreed
   PURPOSE:       return breed from stop_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStopBreed () const throw()
{
  return stop_coeff.breed;
}

/*
   FUNCTION NAME: GetStopSlopeResist
   PURPOSE:       return slope_resistance from stop_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStopSlopeResist () const throw()
{
  return stop_coeff.slope_resistance;
}

/*
   FUNCTION NAME: GetStopRoadGravity
   PURPOSE:       return road_gravity from stop_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetStopRoadGravity () const throw()
{
  return stop_coeff.road_gravity;
}

/*
   FUNCTION NAME: GetBestFitDiffusion
   PURPOSE:       return diffusion from best_fit_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetBestFitDiffusion () const throw()
{
  return best_fit_coeff.diffusion;
}

/*
   FUNCTION NAME: GetBestFitSpread
   PURPOSE:       return spread from best_fit_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetBestFitSpread () const throw()
{
  return best_fit_coeff.spread;
}

/*
   FUNCTION NAME: GetBestFitBreed
   PURPOSE:       return breed from best_fit_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetBestFitBreed () const throw()
{
  return best_fit_coeff.breed;
}

/*
   FUNCTION NAME: GetBestFitSlopeResist
   PURPOSE:       return slope_resistance from best_fit_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetBestFitSlopeResist () const throw()
{
  return best_fit_coeff.slope_resistance;
}

/*
   FUNCTION NAME: GetBestFitRoadGravity
   PURPOSE:       return road_gravity from best_fit_coeff struct
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Coeff::GetBestFitRoadGravity () const throw()
{
  return best_fit_coeff.road_gravity;
}


/*
   FUNCTION NAME: ConcatenateFiles
   PURPOSE:       concatenate coefficient files for a given run
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Coeff::ConcatenateFiles (bool writeit, const char * outputdir) throw()
{
#if 1
#define MAX_LINE_LEN 256
  char msg_buf[MAX_FILENAME_LEN];         
  char source_file[MAX_FILENAME_LEN];
  char destination_file[MAX_FILENAME_LEN];
  char command[2 * MAX_FILENAME_LEN + 20];
  int i;
  FILE *fp;
  FILE *source_fp;
  int line_count;
  char line[MAX_LINE_LEN];
  
  
  /*
   
    create the destination coeff.log file by copying the zeroth
    file onto log
   
   */
  sprintf (destination_file, "%scoeff.log", outputdir);
  sprintf (source_file, "%srun%u", outputdir, 0);
  sprintf (command, "mv %s %s", source_file, destination_file);
  system (command);
  
  
  /*
   
    loop over all the files appending each to the destination file
   
   */
  for (i = 1; i < glb_npes; i++)
  {
    FILE_OPEN (fp, destination_file, "a");
    
    sprintf (source_file, "%srun%u", outputdir, i);
    
    FILE_OPEN (source_fp, source_file, "r");
    
    line_count = 0;
    while (fgets (line, MAX_LINE_LEN, source_fp) != NULL)
    {
      line_count++;
      if (line_count <= 1)
        continue;
      fputs (line, fp);
    }
    fclose (source_fp);
    fclose (fp);
    
    sprintf (command, "rm %s", source_file);
    system (command);
  }
  
  //sort the file
  sprintf(source_file, "%stest.temp", outputdir);
  sprintf(command, "sort -g %s -o %s", destination_file, source_file);
  system(command);
  sprintf(command, "mv %s %s", source_file, destination_file);
  system(command);
  


  
#else
#define MAX_LINE_LEN 256
 
  char line[MAX_LINE_LEN];
  char source_file[MAX_FILENAME_LEN];
  char destination_file[MAX_FILENAME_LEN];
  char command[2 * MAX_FILENAME_LEN + 20];
  FILE *fp;
  FILE *source_fp;
  int line_count;
  

  
  sprintf (destination_file, "%scoeff.log", outputdir);
  if (current_run == 0)
  {
    /*
     
      CURRENT_RUN == 0 SO THERE IS ONLY 1 FILE SO WE JUST MOVE IT TO 
      THE RIGHT LOCATION
     
     */
    sprintf (source_file, "%srun%u", outputdir, 0);
    sprintf (command, "mv %s %s", source_file, destination_file);
    system (command);
  }
  else
  {
    /*
     
      CURRENT_RUN != 0 SO WE MUST OPEN THE DESTINATION FILE IN APPEND MODE
      APPEND EACH LINE OF THE SOURCE FILE TO IT
     
     */
    FILE_OPEN (fp, destination_file, "a");
    
    sprintf (source_file, "%srun%u", outputdir, current_run);
    
    FILE_OPEN (source_fp, source_file, "r");
    
    line_count = 0;
    while (fgets (line, MAX_LINE_LEN, source_fp) != NULL)
    {
      line_count++;
      if (line_count <= 1)
        continue;
      fputs (line, fp);
    }
    fclose (source_fp);
    fclose (fp);
    /*
     
      REMOVE THE NO LONGER NEEDED SOURCE FILE
     
     */
    sprintf (command, "rm %s", source_file);
    system (command);
  }
  
#endif
}

/*
   FUNCTION NAME: WriteCurrentCoeff
   PURPOSE:       write current coefficients to a coefficient file
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:   the coefficient file is initially created by
                  CreateCoeffFile () which initializes
                  the filename variable.
  
  
*/
void Coeff::WriteCurrentCoeff () throw()
{
  FILE *fp;
  char msg_buf[MAX_FILENAME_LEN]; 
  FILE_OPEN (fp, coeff_filename, "a");
  
  fprintf (fp, "%8.2f %8.2f %8.2f %8.2f %8.2f\n",
           current_coefficient.diffusion,
           current_coefficient.breed,
           current_coefficient.spread,
           current_coefficient.slope_resistance,
           current_coefficient.road_gravity);
  fclose (fp);

}
/*
   FUNCTION NAME: CreateCoeffFile
   PURPOSE:       creates a coefficient file for the current run
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/

void Coeff::CreateCoeffFile (const char * outputdir) throw()
{
  FILE *fp;
  sprintf (coeff_filename, "%srun%u",
           outputdir, glb_mype);
  char msg_buf[MAX_FILENAME_LEN]; 
  FILE_OPEN (fp, coeff_filename, "w");

  fprintf (fp,
         "  Run    MC Year Diffusion   Breed   Spread SlopeResist RoadGrav\n");
  fclose (fp);
  
}

/*
   FUNCTION NAME: SelfModication
   PURPOSE:       performs self modification of parameters
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
 
*/

void Coeff::SelfModication (double crit_high,
                            double crit_low,
                            double slope_sense,
                            double road_sense,
                            double boom, 
                            double bust,
                            double growth_rate, double percent_urban) throw()
{
 

  /*
   
    boom year
   
   */
  if (growth_rate > crit_high)
  {
    current_coefficient.slope_resistance -=
      (double) (percent_urban * slope_sense);
    if (current_coefficient.slope_resistance <= MIN_SLOPE_RESISTANCE_VALUE)
    {
      current_coefficient.slope_resistance = 1.0;
    }

    current_coefficient.road_gravity +=
      (double) (percent_urban * road_sense);
    if (current_coefficient.road_gravity > MAX_ROAD_GRAVITY_VALUE)
    {
      current_coefficient.road_gravity = MAX_ROAD_GRAVITY_VALUE;
    }

    if (current_coefficient.diffusion < MAX_DIFFUSION_VALUE)
    {
      current_coefficient.diffusion *= boom;

      if (current_coefficient.diffusion > MAX_DIFFUSION_VALUE)
      {
        current_coefficient.diffusion = MAX_DIFFUSION_VALUE;
      }

      current_coefficient.breed *= boom;
      if (current_coefficient.breed > MAX_BREED_VALUE)
      {
        current_coefficient.breed = MAX_BREED_VALUE;
      }

      current_coefficient.spread *= boom;
      if (current_coefficient.spread > MAX_SPREAD_VALUE)
      {
        current_coefficient.spread = MAX_SPREAD_VALUE;
      }
    }
  }

  /*
   
    bust year
   
   */
  if (growth_rate < crit_low)
  {
    current_coefficient.slope_resistance +=
      (double) (percent_urban * slope_sense);
    if (current_coefficient.slope_resistance > MAX_SLOPE_RESISTANCE_VALUE)
    {
      current_coefficient.slope_resistance = MAX_SLOPE_RESISTANCE_VALUE;
    }

    current_coefficient.road_gravity -=
      (double) (percent_urban * road_sense);
    if (current_coefficient.road_gravity <= MIN_ROAD_GRAVITY_VALUE)
    {
      current_coefficient.road_gravity = 1.0;
    }

    if ((growth_rate < crit_low) &&
        (current_coefficient.diffusion > 0))
    {
      current_coefficient.diffusion *= bust;
      if (current_coefficient.diffusion <= MIN_DIFFUSION_VALUE)
      {
        current_coefficient.diffusion = 1.0;
      }

      current_coefficient.spread *= bust;
      if (current_coefficient.spread <= MIN_SPREAD_VALUE)
      {
        current_coefficient.spread = 1.0;
      }

      current_coefficient.breed *= bust;

      if (current_coefficient.breed <= MIN_BREED_VALUE)
      {
        current_coefficient.breed = 1.0;
      }
    }
  }
}
