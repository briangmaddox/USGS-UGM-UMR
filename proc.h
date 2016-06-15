#ifndef PROC_H
#define PROC_H
/*! \file proc.h
    \brief Definition file for the proc object.
    
    Definition file for the proc object which handles
    simulation run info.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include <stdlib.h>
#include <stdio.h>
#include "ugm_defines.h"
#include "coeff.h"

//! Proc simulation run tracking class.
/*!
 */
class Proc
{
public:
  //! Main constructor for the class.
  /*!
   */
  Proc();
  
  //! Main destructor for the class.
  /*!
   */
  virtual ~Proc();

  //! Sets the proccessing type.
  /*! \param i the processing type (Calibrate or predict)
   */
  void SetProcessingType(int i) throw();
 
  //! Counts the total number of runs that the master does.
  /*! 
   */
  void SetTotalRuns(const Coeff &) throw();

  //! Sets the current run.
  /*! \param i the new current run.
   */
  void SetCurrentRun(int i) throw();
  
  //! Set the current monte carlo variable.
  /*! \param i the new current monte carlo variable.
   */
  void SetCurrentMonteCarlo(int i) throw();
  
  //! Sets the current simulation year.
  /*!
   */
  void SetCurrentYear(int i) throw();
  
  //! Sets the year where the simulation stops
  /*!
   */
  void SetStopYear(int i) throw();

  //! Returns the proccessing type.
  /*!
   */
  int GetProcessingType() const throw();
  
  //! Returns the total number of runs the master does.
  /*!
   */
  int GetTotalRuns() const throw();
  
  //! Returns the current run.
  /*!
   */
  int GetCurrentRun() const throw();
  
  //! Returns the current monte carlo variable.
  /*!
   */
  int GetCurrentMonteCarlo() const throw();
  
  //! Return the current year
  /*!
   */
  int GetCurrentYear() const throw();
  
  //! Returns the stop year.
  /*!
   */
  int GetStopYear() const throw();
  
  //! Returns the last year.
  /*!
   */
  int GetLastRun() const throw();

  //! Return the last run flag.
  /*!
   */
  bool GetLastRunFlag() const throw();
  
  //! Returns the last monte carlo flag.
  /*!
   */
  bool GetLastMonteCarloFlag () const throw();
 
  //! Set the last monte carlo variable.
  /*! \param val for the last monte carlo method.
   */
  void SetLastMonteCarlo(int val) throw();
  
  //! Increments the current run.
  /*!
   */
  int IncrementCurrentRun() throw();
  
  //! Sets the last monte carlo flag
  /*!
   */
  int SetLastMonteCarloFlag() throw();
  
  //! Increments the current year.
  /*!
   */
  int IncrementCurrentYear() throw();
  
  //! Set the number of runs executed
  /*! \param val the number runs executed.
   */
  void SetNumRunsExecThisCPU (int val) throw();
  
  //! Get the number of runs.
  /*! 
   */
  int GetNumRunsExecThisCPU () const throw();
  
  //! Increments the number of run
  /*!
   */
  void IncrementNumRunsExecThisCPU () throw();
  
  //! Returns the restart flag.
  /*! Restart is not available in this version of the UGM.
   */
  bool GetRestartFlag () const throw();
  
  //! Set the restart flag.
  /*! Restart is not available in this version of the UGM.
   */
  void SetRestartFlag (bool i) throw();
  
private:
  int type_of_processing;
  int total_runs;
  int total_runs_exec_this_cpu;
  int last_run;
  int last_mc;
  int current_run;
  int current_monte_carlo;
  int current_year;
  int stop_year;
  bool restart_flag;
  bool last_run_flag;
  bool last_mc_flag;

};

#endif
