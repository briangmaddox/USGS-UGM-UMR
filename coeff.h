#ifndef COEFF_H
#define COEFF_H
/*! \file coeff.h
    \brief Definition file for the coeff object.
    
    Definition file for the coeff object which keeps track
    of the coeffs throughout the model simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/


#include "ugm_macros.h"
#include "ugm_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


//! A structure for holding real value coeffs.
/*! Holds all real value coeffs during the 
    the simulation.
    \sa coeff_int
*/
typedef struct coeff_val
{
   double    diffusion;
   double    spread;
   double    breed;
   double    slope_resistance;
   double    road_gravity;
} coeff_val_info;

//! A structure for holding integer value coeffs.
/*! Holds integer value coeff through out calibration.
    \sa coeff_val
*/
typedef struct coeff_int
{
   int diffusion;
   int spread;
   int breed;
   int slope_resistance;
   int road_gravity;
} coeff_int_info;


//! Coeff storage class.
/*! Holds all the coeffs during the model simulation.
 */
class Coeff
{
private:
  coeff_val_info saved_coefficient;
  coeff_val_info current_coefficient;
  coeff_int_info step_coeff;
  coeff_int_info start_coeff;
  coeff_int_info stop_coeff;
  coeff_int_info best_fit_coeff;
  char coeff_filename[MAX_FILENAME_LEN];
  int glb_npes; // # nodes in cluster
  int glb_mype; // # rank in the cluster
	
public:
  //! Main constructor.
  /*! Sets up the mpi variable and intilizes class members.
   */
  Coeff(int arg_size,int arg_rank);
  
  //! Writes coeffs to a file.
  /*! Writes out the current coeffs to the coeff file.
   */
  void WriteCurrentCoeff() throw();
 
  //! Merges all the coeff files into one file.
  /*! Takes all the coeff files from the slaves and
      merges them into one file.
  */
  void ConcatenateFiles(bool writeit, const char * outputdir) throw();

  //! Creates the coeff file.
  /*! Creates the coeff file for this mpi process.
      \param outputdir the output directory where the file is stored.
   */
  void CreateCoeffFile(const char * outputdir) throw();
  
  //! Saves a given diffusion coeff.
  /*! \param val the value to store
   */
  void SetSavedDiffusion(double val) throw();
  
  //! Saves a given spread coeff.
  /*! \param val the value to store
   */
  void SetSavedSpread(double val) throw();
  
  //! Saves a given breed coeff.
  /*! \param val the value to store
   */
  void SetSavedBreed(double val) throw();
  
  //! Saves a given slope resist coeff.
  /*! \param val the value to store
   */
  void SetSavedSlopeResist(double val) throw();
  
  //! Saves a given road grav coeff.
  /*! \param val the value to store
   */
  void SetSavedRoadGravity(double val) throw();
  
  //! Sets the current diffusion coeff.
  /*! \param val the new current diffusion coeff.
   */
  void SetCurrentDiffusion(double val) throw();
  
  //! Sets the current spread coeff.
  /*! \param val the new current spread coeff.
   */
  void SetCurrentSpread(double val) throw();
  
  //! Sets the current breed coeff.
  /*! \param val the new current breed coeff.
   */
  void SetCurrentBreed(double val) throw();
  
  //! Sets the current slope resist coeff.
  /*! \param val the new current slope resist coeff.
   */
  void SetCurrentSlopeResist(double val) throw();
  
  //! Sets the current road grav coeff.
  /*! \param val the new current road grav coeff.
   */
  void SetCurrentRoadGravity(double val) throw();
  
  //! Sets the diffusion coeff increment.
  /*! \param val the new diffusion coeff increment.
   */
  void SetStepDiffusion(int val) throw();

  //! Sets the spread coeff increment.
  /*! \param val the new spread coeff increment.
   */
  void SetStepSpread(int val) throw();

  //! Sets the breed coeff increment.
  /*! \param val the new breed coeff increment.
   */
  void SetStepBreed(int val) throw();
  
  //! Sets the slope resist coeff increment.
  /*! \param val the new slope resist coeff increment.
   */
  void SetStepSlopeResist(int val) throw();
  
  //! Sets the road grav coeff increment.
  /*! \param val the new road grav coeff increment.
   */
  void SetStepRoadGravity(int val) throw();
  
  //! Sets the diffusion coeff starting point.
  /*! \param val the new diffusion coeff start point.
   */
  void SetStartDiffusion(int val) throw();

  //! Sets the spread coeff starting point.
  /*! \param val the new spread coeff start point.
   */
  void SetStartSpread(int val) throw();
  
  //! Sets the breed coeff starting point.
  /*! \param val the new breed coeff start point.
   */
  void SetStartBreed(int val) throw();
  
  //! Sets the slope resist coeff starting point.
  /*! \param val the new slope resist coeff start point.
   */
  void SetStartSlopeResist(int val) throw();
  
  //! Sets the road grav coeff starting point.
  /*! \param val the new diffusion road grav start point.
   */
  void SetStartRoadGravity(int val) throw();
  
  //! Sets the diffusion coeff stopping point.
  /*! \param val the new diffusion coeff stop point.
   */
  void SetStopDiffusion(int val) throw();
  
  //! Sets the spread coeff stopping point.
  /*! \param val the new spread coeff stop point.
   */
  void SetStopSpread(int val) throw();
  
  //! Sets the breed coeff stopping point.
  /*! \param val the new breed coeff stop point.
   */
  void SetStopBreed(int val) throw();

  //! Sets the slope resist coeff stopping point.
  /*! \param val the new slope resist coeff stop point.
   */
  void SetStopSlopeResist(int val) throw();
  
  //! Sets the road grav coeff stopping point.
  /*! \param val the new road grav coeff stop point.
   */
  void SetStopRoadGravity(int val) throw();
  
  //! Sets the diffusion coeff best fit value.
  /*! \param val the new diffusion coeff best fit value.
   */
  void SetBestFitDiffusion(int val) throw();
  
  //! Sets the spread coeff best fit value.
  /*! \param val the new spread coeff best fit value.
   */
  void SetBestFitSpread(int val) throw();
  
  //! Sets the breed coeff best fit value.
  /*! \param val the new breed coeff best fit value.
   */
  void SetBestFitBreed(int val) throw();
  
  //! Sets the slope resist coeff best fit value.
  /*! \param val the new slope resist coeff best fit value.
   */
  void SetBestFitSlopeResist(int val) throw();

  //! Sets the road grav coeff best fit value.
  /*! \param val the new road grav coeff best fit value.
   */
  void SetBestFitRoadGravity(int val) throw();
  
  //! Returns the saved diffusion coeff.
  /*!
   */
  double GetSavedDiffusion() const throw();
  
  //! Returns the saved spread coeff.
  /*!
   */
  double GetSavedSpread() const throw();
  
  //! Returns the breed coeff.
  /*!
   */
  double GetSavedBreed() const throw();
  
  //! Returns the saved slope coeff.
  /*!
   */
  double GetSavedSlopeResist() const throw();
  
  //! Returns the saved road grav coeff.
  /*!
   */
  double GetSavedRoadGravity() const throw();
  
  //! Returns the current diffusion coeff.
  /*!
   */
  double GetCurrentDiffusion() const throw();
  
  //! Returns the current spread coeff.
  /*!
   */
  double GetCurrentSpread() const throw();
  
  //! Returns the current breed coeff.
  /*!
   */
  double GetCurrentBreed() const throw();
 
  //! Returns the current slope resist coeff.
  /*!
   */
  double GetCurrentSlopeResist() const throw();

  //! Returns the current road grav coeff
  /*!
   */
  double GetCurrentRoadGravity() const throw();
  
  //! Returns the current diffusion coeff step.
  /*!
   */  
  int GetStepDiffusion() const throw();

  //! Returns the current spread coeff step.
  /*!
   */
  int GetStepSpread() const throw();

  //! Returns the current breed coeff step.
  /*!
   */
  int GetStepBreed() const throw();
  
  //! Returns the current slope coeff step.
  /*!
   */
  int GetStepSlopeResist() const throw();
  
  //! Returns the current road grav coeff step.
  /*!
   */
  int GetStepRoadGravity() const throw();

  //! Returns the diffusion coeff start.
  /*!
   */
  int GetStartDiffusion() const throw();

  //! Returns the spread coeff start.
  /*!
   */
  int GetStartSpread() const throw();
  
  //! Returns the breed coeff start.
  /*!
   */
  int GetStartBreed() const throw();
  
  //! Returns the slope coeff start.
  /*!
   */
  int GetStartSlopeResist() const throw();
  
  //! Returns the road grav coeff start.
  /*!
   */
  int GetStartRoadGravity() const throw();
  
  //! Returns the diffusion coeff stop.
  /*!
   */
  int GetStopDiffusion() const throw();
  
  //! Returns the spread coeff stop.
  /*!
   */
  int GetStopSpread() const throw();

  //! Returns the breed coeff stop.
  /*!
   */
  int GetStopBreed() const throw();
  
  //! Returns the slope coeff stop.
  /*!
   */
  int GetStopSlopeResist() const throw();
  
  //! Returns the road grav coeff stop.
  /*!
   */
  int GetStopRoadGravity() const throw();
  
  //! Returns the Diffusion coeff best fit.
  /*!
   */  
  int GetBestFitDiffusion() const throw();

  //! Returns the spread coeff best fit.
  /*!
   */  
  int GetBestFitSpread() const throw();
  
  //! Returns the breed coeff best fit.
  /*!
   */  
  int GetBestFitBreed() const throw();
  
  //! Returns the slope coeff best fit.
  /*!
   */  
  int GetBestFitSlopeResist() const throw();
  
  //! Returns the road grav coeff best fit.
  /*!
   */  
  int GetBestFitRoadGravity() const throw();
  

  //! Modifies the coeffs based on the current population.
  /*! Changes the coeffs based on whether the population
      is in decline, growing and other factors.
   */  
  void SelfModication(double crit_high,
                      double crit_low,
                      double slope_sense,
                      double road_sense,
                      double boom, 
                      double bust,
                      double growth_rate, double percent_urban) throw();
  
};

#endif
