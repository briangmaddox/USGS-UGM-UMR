/*! \file proc.cpp
    \brief Implementation file for the proc object.
    
    Implementation file for the proc object which handles
    simulation run info.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "proc.h"
#include "ugm_macros.h"

/*
 Main constructor for the class
*/
Proc::Proc() :  type_of_processing(0), total_runs(0),
  total_runs_exec_this_cpu(0), last_run(0),
  last_mc(0), current_run(0),
  current_monte_carlo(0),
  current_year(0), stop_year(0),
  restart_flag(false),
  last_run_flag(false), last_mc_flag(false)
{}
  
/*
 Main destructor for the class
*/
Proc::~Proc()
{}


/*
   FUNCTION NAME: SetRestartFlag
   PURPOSE:       set the restart flag variable
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetRestartFlag (bool i) throw()
{
  restart_flag = i;
}

/*
   FUNCTION NAME: GetRestartFlag
   PURPOSE:       return the restart flag variable
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Proc::GetRestartFlag() const throw()
{
  return restart_flag;
}

/*
   FUNCTION NAME: SetProcessingType
   PURPOSE:       set the processing type variable
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetProcessingType (int i) throw()
{
  type_of_processing = i;
}

/*
   FUNCTION NAME: SetTotalRuns
   PURPOSE:       count the total # of runs
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetTotalRuns (const Coeff & incoeffs) throw()
{
  int i;
  int j;
  int k;
  int l;
  int m;
  int x1 = 0;
  int x2 = 0;
  int x3 = 0;
  int x4 = 0;
  int x5 = 0;
  for (i = incoeffs.GetStartDiffusion ();
       i <= incoeffs.GetStopDiffusion ();
       i += incoeffs.GetStepDiffusion ())
  {
    x1++;
  }
  for (j = incoeffs.GetStartBreed ();
       j <= incoeffs.GetStopBreed ();
       j += incoeffs.GetStepBreed ())
  {
    x2++;
  }
  for (k = incoeffs.GetStartSpread ();
       k <= incoeffs.GetStopSpread ();
       k += incoeffs.GetStepSpread ())
  {
    x3++;
  }
  for (l = incoeffs.GetStartSlopeResist ();
       l <= incoeffs.GetStopSlopeResist ();
       l += incoeffs.GetStepSlopeResist ())
  {
    x4++;
  }
  for (m = incoeffs.GetStartRoadGravity ();
       m <= incoeffs.GetStopRoadGravity ();
       m += incoeffs.GetStepRoadGravity ())
  {
    x5++;
  }
  
 
  x1 = MAX (x1, 1);
  x2 = MAX (x2, 1);
  x3 = MAX (x3, 1);
  x4 = MAX (x4, 1);
  x5 = MAX (x5, 1);
  total_runs = x1 * x2 * x3 * x4 * x5;
  last_run_flag = FALSE;
  last_mc_flag = FALSE;
  last_run = total_runs - 1;
}

/*
   FUNCTION NAME: SetCurrentRun
   PURPOSE:       set the current run variable, current_run
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetCurrentRun (int i) throw()
{
  current_run = i;
}

/*
   FUNCTION NAME: SetCurrentMonteCarlo
   PURPOSE:       set current monte carlo variable
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetCurrentMonteCarlo (int i) throw()
{
  current_monte_carlo = i;
  SetLastMonteCarloFlag ();
}

/*
   FUNCTION NAME: SetCurrentYear
   PURPOSE:       set current year
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetCurrentYear (int i) throw()
{
  current_year = i;
}

/*
   FUNCTION NAME: SetStopYear
   PURPOSE:       set the stop year
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetStopYear (int i) throw()
{
  stop_year = i;
}

/*
   FUNCTION NAME: GetProcessingType
   PURPOSE:       return the processing type
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::GetProcessingType () const throw()
{
  return type_of_processing;
}

/*
   FUNCTION NAME: GetTotalRuns
   PURPOSE:       return total run count
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::GetTotalRuns () const throw()
{
  return total_runs;
}

/*
   FUNCTION NAME: GetCurrentRun
   PURPOSE:       return the current run
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::GetCurrentRun () const throw()
{
  return current_run;
}

/*
   FUNCTION NAME: GetCurrentMonteCarlo
   PURPOSE:       return the current monte carlo
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::GetCurrentMonteCarlo () const throw()
{
  return current_monte_carlo;
}

/*
   FUNCTION NAME: GetCurrentYear
   PURPOSE:       return the current year
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::GetCurrentYear () const throw()
{
  return current_year;
}

/*
   FUNCTION NAME: GetStopYear
   PURPOSE:       return the stop year
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::GetStopYear () const throw()
{
  return stop_year;
}

/*
   FUNCTION NAME: GetLastRun
   PURPOSE:       return last run count
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::GetLastRun () const throw()
{
  return last_run;
}

/*
   FUNCTION NAME: GetLastRunFlag
   PURPOSE:       return last run flag; TRUE if this is the last run
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Proc::GetLastRunFlag () const throw()
{
  return last_run_flag;
}

/*
   FUNCTION NAME: SetLastMonteCarlo
   PURPOSE:       set last monte carlo run
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetLastMonteCarlo (int val) throw()
{
  last_mc = val;
}

/*
   FUNCTION NAME: GetLastMonteCarloFlag
   PURPOSE:       return last monte carlo flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Proc::GetLastMonteCarloFlag () const throw()
{
  return last_mc_flag;
}

/*
   FUNCTION NAME: SetNumRunsExecThisCPU
   PURPOSE:       set the num runs executed by this cpu
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::SetNumRunsExecThisCPU (int val) throw()
{
  total_runs_exec_this_cpu = val;
}

/*
   FUNCTION NAME: GetNumRunsExecThisCPU
   PURPOSE:       return the num runs executed by this cpu
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::GetNumRunsExecThisCPU () const throw()
{
  return total_runs_exec_this_cpu;
}

/*
   FUNCTION NAME: IncrementNumRunsExecThisCPU
   PURPOSE:       increment the num runs executed by this cpu
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Proc::IncrementNumRunsExecThisCPU () throw()
{
  total_runs_exec_this_cpu++;
}

/*
   FUNCTION NAME: IncrementCurrentRun
   PURPOSE:       increment current run variable
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::IncrementCurrentRun () throw()
{
  if ((++current_run) == last_run)
  {
    last_run_flag = TRUE;
  }
  return (current_run);
}

/*
   FUNCTION NAME: SetLastMonteCarloFlag
   PURPOSE:       increment current monte carlo variable
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::SetLastMonteCarloFlag () throw()
{
  if ((current_monte_carlo) == last_mc)
  {
    last_mc_flag = TRUE;
  }
  return (current_monte_carlo);
}

/*
   FUNCTION NAME: IncrementCurrentYear
   PURPOSE:       increment current year variable
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Proc::IncrementCurrentYear () throw()
{
  return (++current_year);
}
