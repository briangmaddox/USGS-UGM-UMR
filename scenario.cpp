/*! \file scenario.cpp
    \brief Implementation file for the scenario object.
    
    Implementation file for the scenario object which holds
    information about the simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "scenario.h"
#include "utilities.h"


#define SCEN_LINE_BUF_LEN 256




/*
   FUNCTION NAME: GetScenarioFilename
   PURPOSE:       return scenario filename
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetScenarioFilename () const throw()
{
  return filename;
}

/*
   FUNCTION NAME: GetLogFP
   PURPOSE:       return log file pointer
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
FILE * Scenario::GetLogFP () throw()
{
  return log_fp;
}

/*
   FUNCTION NAME: Append2Log
   PURPOSE:       open log for appending
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Scenario::Append2Log () throw()
{
  char msg_buf[MAX_FILENAME_LEN]; 
 if (log_fp == NULL)
  {
    FILE_OPEN (log_fp, log_filename, "a");
  }
  else
  {
    sprintf (msg_buf, "%s is already open", log_filename);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  
}

/*
   FUNCTION NAME: GetOutputDir
   PURPOSE:       return output directory
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetOutputDir () const throw()
{
  return output_dir;
}

/*
   FUNCTION NAME: GetWhirlgifBinary
   PURPOSE:       return whirlgif_binary
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetWhirlgifBinary () const throw()
{
  return whirlgif_binary;
}

/*
   FUNCTION NAME: GetInputDir
   PURPOSE:       return input directory
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetInputDir () const throw()
{
  return input_dir;
}

/*
   FUNCTION NAME: GetUrbanDataFileCount
   PURPOSE:       return # of urban input files
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetUrbanDataFileCount () const throw()
{
  return urban_data_file_count;
}

/*
   FUNCTION NAME: GetRoadDataFileCount
   PURPOSE:       return # road data files
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetRoadDataFileCount () const throw()
{
  return road_data_file_count;
}

/*
   FUNCTION NAME: GetLanduseDataFileCount
   PURPOSE:       return # landuse data files
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetLanduseDataFileCount () const throw()
{
  return landuse_data_file_count;
}

/*
   FUNCTION NAME: GetDoingLanduseFlag
   PURPOSE:       return doing landuse flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if doing landuse, then landuse_data_file_count is = 2
  
  
*/
int Scenario::GetDoingLanduseFlag () const throw()
{
  return landuse_data_file_count;
}

/*
   FUNCTION NAME: GetUrbanDataFilename
   PURPOSE:       return urban data filename by index, i
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetUrbanDataFilename (int i) const throw()
{
  return urban_data_file[i];
}

/*
   FUNCTION NAME: GetRoadDataFilename
   PURPOSE:       return road data filename by index, i
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetRoadDataFilename (int i) const throw()
{
  return road_data_file[i];
}

/*
   FUNCTION NAME: GetLanduseDataFilename
   PURPOSE:       return landuse data filename by index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetLanduseDataFilename (int i) const throw()
{
  return landuse_data_file[i];
}

/*
   FUNCTION NAME: GetExcludedDataFilename
   PURPOSE:       return excluded data filename by index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetExcludedDataFilename () const throw()
{
  return excluded_data_file;
}

/*
   FUNCTION NAME: GetSlopeDataFilename
   PURPOSE:       return slope data filename
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetSlopeDataFilename () const throw()
{
  return slope_data_file;
}

/*
   FUNCTION NAME: GetBackgroundDataFilename
   PURPOSE:       return background data filename
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * Scenario::GetBackgroundDataFilename () const throw()
{
  return background_data_file;
}

/*
   FUNCTION NAME: GetEchoImageFlag
   PURPOSE:       return echo_image_files flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetEchoImageFlag () const throw()
{
  return echo_image_files;
}

/*
   FUNCTION NAME: GetWriteColorKeyFlag
   PURPOSE:       return write_color_keys flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetWriteColorKeyFlag () const throw()
{
  return write_color_keys;
}

/*
   FUNCTION NAME: GetPostprocessingFlag
   PURPOSE:       return Postprocessing flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetPostprocessingFlag () const throw()
{
  return postprocessing;
}

/*
   FUNCTION NAME: GetLogFlag
   PURPOSE:       return Log flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogFlag () const throw()
{
  return logging;
}

/*
   FUNCTION NAME: GetEchoFlag
   PURPOSE:       return echo flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetEchoFlag () const throw()
{
  return isechoing;
}

/*
   FUNCTION NAME: GetRandomSeed
   PURPOSE:       return random seed value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetRandomSeed () const throw()
{
  return random_seed;
}

/*
   FUNCTION NAME: GetMonteCarloIterations
   PURPOSE:       return # monte carlo iterations
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetMonteCarloIterations () const throw()
{
  return monte_carlo_iterations;
}

/*
   FUNCTION NAME: GetCoeffDiffusionStart
   PURPOSE:       return diffusion start value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffDiffusionStart () const throw()
{
  return start.diffusion;
}

/*
   FUNCTION NAME: GetCoeffBreedStart
   PURPOSE:       return breed start value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffBreedStart () const throw()
{
  return start.breed;
}

/*
   
   FUNCTION NAME: GetCoeffSpreadStart
   PURPOSE:       return spread start value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffSpreadStart () const throw()
{
  return start.spread;
}

/*
   FUNCTION NAME: GetCoeffSlopeResistStart
   PURPOSE:       return slope resistance start value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffSlopeResistStart () const throw()
{
  return start.slope_resistance;
}

/*
   FUNCTION NAME: GetCoeffRoadGravityStart
   PURPOSE:       return road gravity start value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffRoadGravityStart () const throw()
{
  return start.road_gravity;
}

/*
   FUNCTION NAME: GetCoeffDiffusionStop
   PURPOSE:       return diffusion stop value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffDiffusionStop () const throw()
{
  return stop.diffusion;
}

/*
   FUNCTION NAME: GetCoeffBreedStop
   PURPOSE:       return breed stop value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffBreedStop () const throw()
{
  return stop.breed;
}

/*
   FUNCTION NAME: GetCoeffSpreadStop
   PURPOSE:       return spread stop value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffSpreadStop () const throw()
{
  return stop.spread;
}

/*
   FUNCTION NAME: GetCoeffSlopeResistStop
   PURPOSE:       return slope resistance stop value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffSlopeResistStop () const throw()
{
  return stop.slope_resistance;
}

/*
   FUNCTION NAME: GetCoeffRoadGravityStop
   PURPOSE:       return road gravity stop value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffRoadGravityStop () const throw()
{
  return stop.road_gravity;
}

/*
   FUNCTION NAME: GetCoeffDiffusionStep
   PURPOSE:       return diffustion step value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffDiffusionStep () const throw()
{
  return step.diffusion;
}

/*
   FUNCTION NAME: GetCoeffBreedStep
   PURPOSE:       return breed step value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffBreedStep () const throw()
{
  return step.breed;
}

/*
   FUNCTION NAME: GetCoeffSpreadStep
   PURPOSE:       return spread step value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffSpreadStep () const throw()
{
  return step.spread;
}

/*
   FUNCTION NAME: GetCoeffSlopeResistStep
   PURPOSE:       return slope resistance step value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffSlopeResistStep () const throw()
{
  return step.slope_resistance;
}

/*
   FUNCTION NAME: GetCoeffRoadGravityStep
   PURPOSE:       return road gravity step value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffRoadGravityStep () const throw()
{
  return step.road_gravity;
}

/*
   FUNCTION NAME: GetCoeffDiffusionBestFit
   PURPOSE:       return diffusion best fit value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffDiffusionBestFit () const throw()
{
  return best_fit.diffusion;
}

/*
   FUNCTION NAME: GetCoeffBreedBestFit
   PURPOSE:       return breed best fit value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffBreedBestFit () const throw()
{
  return best_fit.breed;
}

/*
   FUNCTION NAME: GetCoeffSpreadBestFit
   PURPOSE:       return spread best fit value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffSpreadBestFit () const throw()
{
  return best_fit.spread;
}

/*
   FUNCTION NAME: GetCoeffSlopeResistBestFit
   PURPOSE:       return slope resistance best fit value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffSlopeResistBestFit () const throw()
{
  return best_fit.slope_resistance;
}

/*
   FUNCTION NAME: GetCoeffRoadGravityBestFit
   PURPOSE:       return road gravity best fit value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetCoeffRoadGravityBestFit () const throw()
{
  return best_fit.road_gravity;
}

/*
   FUNCTION NAME: GetPredictionStartDate
   PURPOSE:       return prediction start date
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetPredictionStartDate () const throw()
{
  return prediction_start_date;
}

/*
   FUNCTION NAME: GetPredictionStopDate
   PURPOSE:       return prediction stop date
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetPredictionStopDate () const throw()
{
  return prediction_stop_date;
}

/*
   FUNCTION NAME: GetDateColor
   PURPOSE:       return date color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetDateColor () const throw()
{
  return date_color;
}

/*
   FUNCTION NAME: GetSeedColor
   PURPOSE:       return seed color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetSeedColor () const throw()
{
  return seed_color;
}

/*
   FUNCTION NAME: GetWaterColor
   PURPOSE:       return water color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetWaterColor () const throw()
{
  return water_color;
}

/*
   FUNCTION NAME: GetProbabilityColorCount
   PURPOSE:       return # probability color count
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetProbabilityColorCount () const throw()
{
  return probability_color_count;
}

/*
   FUNCTION NAME: GetProbabilityColorLowerBound
   PURPOSE:       return lower bound for probability color index, i
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetProbabilityColorLowerBound (int i) const throw()
{
  return probability_color[i].lower_bound;
}

/*
   FUNCTION NAME: GetProbabilityColorUpperBound
   PURPOSE:       return upper bound for probability color index, i
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetProbabilityColorUpperBound (int i) const throw()
{
  return probability_color[i].upper_bound;
}

/*
   FUNCTION NAME: GetProbabilityColor
   PURPOSE:       return probability color by index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetProbabilityColor (int i) const throw()
{
  return probability_color[i].color;
}

/*
   FUNCTION NAME: GetLogMemoryMapFlag
   PURPOSE:       return log memory map flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogMemoryMapFlag () const throw()
{
  return log_memory_map;
}

/*
   FUNCTION NAME: GetLogSlopeWeightsFlag
   PURPOSE:       return log slope weights flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogSlopeWeightsFlag () const throw()
{
  return log_slope_weights;
}

/*
   FUNCTION NAME: GetLogLandclassSummaryFlag
   PURPOSE:       return log landclass summary flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogLandclassSummaryFlag () const throw()
{
  return log_landclass_summary;
}

/*
   FUNCTION NAME: GetLogReadsFlag
   PURPOSE:       return log reads flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogReadsFlag () const throw()
{
  return log_reads;
}

/*
   FUNCTION NAME: GetLogWritesFlag
   PURPOSE:       return log writes flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogWritesFlag () const throw()
{
  return log_writes;
}

/*
   FUNCTION NAME: GetNumLanduseClasses
   PURPOSE:       return num_landuse_classes
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
int Scenario::GetNumLanduseClasses () const throw()
{
  return num_landuse_classes;
}

/*
   FUNCTION NAME: GetLanduseClassType
   PURPOSE:       return ptr to landuse_class Type
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
const char * Scenario::GetLanduseClassType (int i) const throw()
{
  return landuse_class[i].type;
}

/*
   FUNCTION NAME: GetLanduseClassColor
   PURPOSE:       return landuse_class color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
int Scenario::GetLanduseClassColor (int i) const throw()
{
  return landuse_class[i].color;
}

/*
   FUNCTION NAME: GetLanduseClassGrayscale
   PURPOSE:       return landuse_class Grayscale
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
int Scenario::GetLanduseClassGrayscale (int i) const throw()
{
  return landuse_class[i].grayscale;
}

/*
   FUNCTION NAME: GetLanduseClassName
   PURPOSE:       return ptr to landuse_class name
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
const char * Scenario::GetLanduseClassName (int i) const throw()
{
  return landuse_class[i].name;
}


/*
   FUNCTION NAME: GetLogColortablesFlag
   PURPOSE:       return log colortables flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogColortablesFlag () const throw()
{
  return log_colortables;
}

/*
   FUNCTION NAME: GetRdGrvtySensitivity
   PURPOSE:       return road gravity sensitivity
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Scenario::GetRdGrvtySensitivity () const throw()
{
  return rd_grav_sensitivity;
}

/*
   FUNCTION NAME: GetSlopeSensitivity
   PURPOSE:       return slope sensitivity
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Scenario::GetSlopeSensitivity () const throw()
{
  return slope_sensitivity;
}

/*
   FUNCTION NAME: GetCriticalLow
   PURPOSE:       return critical low
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Scenario::GetCriticalLow () const throw()
{
  return critical_low;
}

/*
   FUNCTION NAME: GetCriticalHigh
   PURPOSE:       return critical high
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Scenario::GetCriticalHigh () const throw()
{
  return critical_high;
}

/*
   FUNCTION NAME: GetCriticalSlope
   PURPOSE:       return log processing status flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Scenario::GetCriticalSlope () const throw()
{
  return critical_slope;
}

/*
   FUNCTION NAME: GetBoom
   PURPOSE:       return boom value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Scenario::GetBoom () const throw()
{
  return boom;
}

/*
   FUNCTION NAME: GetBust
   PURPOSE:       return bust value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
double Scenario::GetBust () const throw()
{
  return bust;
}

/*
   FUNCTION NAME: GetWriteCoeffFileFlag
   PURPOSE:       return coeff log flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetWriteCoeffFileFlag () const throw()
{
  return write_coeff_file;
}

/*
   FUNCTION NAME: GetWriteAvgFileFlag
   PURPOSE:       return log processing status flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetWriteAvgFileFlag () const throw()
{
  return write_avg_file;
}

/*
   FUNCTION NAME: GetLogBaseStatsFlag
   PURPOSE:       return log base statistics flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogBaseStatsFlag () const throw()
{
  return log_base_stats;
}

/*
   FUNCTION NAME: GetLogDebugFlag
   PURPOSE:       return log base statistics flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogDebugFlag () const throw()
{
  return log_debug;
}
/*
   FUNCTION NAME: GetLogUrbanizationAttemptsFlag
   PURPOSE:       return log urbanization attempts flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogUrbanizationAttemptsFlag () const throw()
{
  return log_urbanization_attempts;
}

/*
   FUNCTION NAME: GetLogCoeffFlag
   PURPOSE:       return log coeff flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogCoeffFlag () const throw()
{
  return log_coeff;
}

/*
   FUNCTION NAME: GetLogTimingsFlag
   PURPOSE:       return log timings flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetLogTimingsFlag () const throw()
{
  return log_timings;
}

/*
   FUNCTION NAME: GetWriteStdDevFileFlag
   PURPOSE:       return log processing status flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetWriteStdDevFileFlag () const throw()
{
  return write_std_dev_file;
}

/*
   FUNCTION NAME: GetLogTransitionMatrixFlag
   PURPOSE:       return log processing status flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogTransitionMatrixFlag () const throw()
{
  return log_trans_matrix;
}

/*
   FUNCTION NAME: GetLogProcessingStatusFlag
   PURPOSE:       return log processing status flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetLogProcessingStatusFlag () const throw()
{
  return log_processing_status;
}

/*
   FUNCTION NAME: GetViewGrowthTypesFlag
   PURPOSE:       return view growth types flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetViewGrowthTypesFlag (const Proc & inproc) const throw()
{
  if (view_growth_types)
  {
    if ((inproc.GetCurrentRun () >= growth_type_window.run1) &&
        (inproc.GetCurrentRun () <= growth_type_window.run2) &&
        (inproc.GetCurrentMonteCarlo () >=
         growth_type_window.monte_carlo1) &&
        (inproc.GetCurrentMonteCarlo () <=
         growth_type_window.monte_carlo2) &&
        (inproc.GetCurrentYear () >= growth_type_window.year1) &&
        (inproc.GetCurrentYear () <= growth_type_window.year2))
    {
      return view_growth_types;
    }
  }
  return false;
}

/*
   FUNCTION NAME: GetViewDeltatronAgingFlag
   PURPOSE:       return view deltatron aging flag
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Scenario::GetViewDeltatronAgingFlag (const Proc & inproc) const throw()
{
  if (view_deltatron_aging)
  {
    if ((inproc.GetCurrentRun () >= deltatron_aging_window.run1) &&
        (inproc.GetCurrentRun () <= deltatron_aging_window.run2) &&
        (inproc.GetCurrentMonteCarlo () >=
         deltatron_aging_window.monte_carlo1) &&
        (inproc.GetCurrentMonteCarlo () <=
         deltatron_aging_window.monte_carlo2) &&
     (inproc.GetCurrentYear () >= deltatron_aging_window.year1) &&
        (inproc.GetCurrentYear () <= deltatron_aging_window.year2))
    {
      return view_deltatron_aging;
    }
  }
  return false;
}

/*
   FUNCTION NAME: GetDeltatronColorCount
   PURPOSE:       return deltatron color count
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetDeltatronColorCount () const throw()
{
  return deltatron_color_count;
}

/*
   FUNCTION NAME: GetDeltatronColor
   PURPOSE:       return deltatron color by index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetDeltatronColor (int index) const throw()
{
  assert (index < deltatron_color_count);

  return deltatron_color[index];
}

/*
   FUNCTION NAME: GetPhase0GrowthColor
   PURPOSE:       return phase0g_growth_color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetPhase0GrowthColor () const throw()
{
  return phase0g_growth_color;
}

/*
   FUNCTION NAME: GetPhase1GrowthColor
   PURPOSE:       phase1g_growth_color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetPhase1GrowthColor () const throw()
{
  return phase1g_growth_color;
}

/*
   FUNCTION NAME: GetPhase2GrowthColor
   PURPOSE:       return phase2g_growth_color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetPhase2GrowthColor () const throw()
{
  return phase2g_growth_color;
}

/*
   FUNCTION NAME: GetPhase3GrowthColor
   PURPOSE:       return phase3g_growth_color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetPhase3GrowthColor () const throw()
{
  return phase3g_growth_color;
}

/*
   FUNCTION NAME: GetPhase4GrowthColor
   PURPOSE:       return phase4g_growth_color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetPhase4GrowthColor () const throw()
{
  return phase4g_growth_color;
}

/*
   FUNCTION NAME: GetPhase5GrowthColor
   PURPOSE:       return phase5g_growth_color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Scenario::GetPhase5GrowthColor () const throw()
{
  return phase5g_growth_color;
}

/*
   FUNCTION NAME: init
   PURPOSE:       initialize scenario object
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Scenario::init (char *filename) throw()
{

  deltatron_color_count = 0;
  read_file (filename);
  open_log (false);

}

//Added to separate the wgrids and scenerio stuff
int Scenario::GetNumWorkingGrids() const throw()
{
  return num_working_grids;
}


/*
   FUNCTION NAME: read_file
   PURPOSE:       read the scenario file
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Scenario::read_file (char *filename) throw()
{
  FILE *fp;
  char line[MAX_FILENAME_LEN];
  char orig_line[MAX_FILENAME_LEN];
  char *keyword;
  char *object_ptr;
  int index;
  char msg_buf[MAX_FILENAME_LEN]; 

  assert (filename != NULL);

  strcpy (filename, filename);

  FILE_OPEN (fp, filename, "r");

  num_landuse_classes = 0;
  urban_data_file_count = 0;
  road_data_file_count = 0;
  landuse_data_file_count = 0;
  probability_color_count = 0;
  strcpy (whirlgif_binary, "");

  while (fgets (line, MAX_FILENAME_LEN, fp) != NULL)
  {
    strncpy (orig_line, line, strlen (line));
    /*
     
      IGNORE LINES BEGINNING WITH #
     
     */
    if (strncmp (line, "#", 1))
    {
      /*
       
        IGNORE TEXT TO RIGHT OF # AND BLANK LINES
       
       */
      strtok (line, "#");
      util_trim (line);
      if (strlen (line) > 0)
      {
        keyword = strtok (line, "=");
        if (!strcmp (keyword, "INPUT_DIR"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          strcpy (input_dir, object_ptr);
        }
	else if(!strcmp (keyword, "INPUT_TYPE"))
	{
	  object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          input_type = (ImageType)(object_ptr[0]-'0');
	}
	else if(!strcmp (keyword, "OUTPUT_TYPE"))
	{
	  object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          output_type = (ImageType)(object_ptr[0]-'0');

          switch(output_type)
          {
	     case TIFF_TYPE:
	        strcpy(extension,".tif");
		break;
             case GEOTIFF_TYPE:
		strcpy(extension,".tif");
		break;
             case GIF_TYPE:
             default:
      		strcpy(extension,".gif");
          }
	  
	}
        else if (!strcmp (keyword, "OUTPUT_DIR"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          strcpy (output_dir, object_ptr);
        }
        else if (!strcmp (keyword, "WHIRLGIF_BINARY"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          strcpy (whirlgif_binary, object_ptr);
        }
        else if (!strcmp (keyword, "URBAN_DATA"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          index = urban_data_file_count;
          strcpy (urban_data_file[index], object_ptr);
          urban_data_file_count++;
        }
        else if (!strcmp (keyword, "ROAD_DATA"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          index = road_data_file_count;
          strcpy (road_data_file[index], object_ptr);
          road_data_file_count++;
        }
        else if (!strcmp (keyword, "URBAN_DATA"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          index = urban_data_file_count;
          strcpy (urban_data_file[index], object_ptr);
          urban_data_file_count++;
        }
        else if (!strcmp (keyword, "LANDUSE_DATA"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          index = landuse_data_file_count;
          strcpy (landuse_data_file[index], object_ptr);
          landuse_data_file_count++;
        }
        else if (!strcmp (keyword, "EXCLUDED_DATA"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          strcpy (excluded_data_file, object_ptr);
        }
        else if (!strcmp (keyword, "SLOPE_DATA"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          strcpy (slope_data_file, object_ptr);
        }
        else if (!strcmp (keyword, "BACKGROUND_DATA"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          strcpy (background_data_file, object_ptr);
        }
        else if (!strcmp (keyword, "ROAD_GRAV_SENSITIVITY"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          rd_grav_sensitivity = atof (object_ptr);
        }
        else if (!strcmp (keyword, "SLOPE_SENSITIVITY"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          slope_sensitivity = atof (object_ptr);
        }
        else if (!strcmp (keyword, "CRITICAL_LOW"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          critical_low = atof (object_ptr);
        }
        else if (!strcmp (keyword, "CRITICAL_HIGH"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          critical_high = atof (object_ptr);
        }
        else if (!strcmp (keyword, "CRITICAL_SLOPE"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          critical_slope = atof (object_ptr);
        }
        else if (!strcmp (keyword, "BOOM"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          boom = atof (object_ptr);
        }
        else if (!strcmp (keyword, "BUST"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          bust = atof (object_ptr);
        }
        else if (!strcmp (keyword, "ECHO_IMAGE_FILES(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          echo_image_files = 1;
          if (!strcmp (object_ptr, "NO"))
          {
            echo_image_files = 0;
          }
        }
        else if (!strcmp (keyword, "WRITE_COLOR_KEY_IMAGES(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          write_color_keys = 1;
          if (!strcmp (object_ptr, "NO"))
          {
            write_color_keys = 0;
          }
        }
        else if (!strcmp (keyword, "WRITE_COEFF_FILE(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          write_coeff_file = 1;
          if (!strcmp (object_ptr, "NO"))
          {
            write_coeff_file = 0;
          }
        }
        else if (!strcmp (keyword, "WRITE_AVG_FILE(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          write_avg_file = 1;
          if (!strcmp (object_ptr, "NO"))
          {
            write_avg_file = 0;
          }
        }
        else if (!strcmp (keyword, "WRITE_STD_DEV_FILE(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          write_std_dev_file = 1;
          if (!strcmp (object_ptr, "NO"))
          {
            write_std_dev_file = 0;
          }
        }
        else if (!strcmp (keyword, "LOG_TRANSITION_MATRIX(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_trans_matrix = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_trans_matrix = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_URBANIZATION_ATTEMPTS(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_urbanization_attempts = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_urbanization_attempts = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_BASE_STATISTICS(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_base_stats = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_base_stats = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_DEBUG(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_debug = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_debug = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_INITIAL_COEFFICIENTS(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_coeff = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_coeff = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_TIMINGS(0:off/1:low verbosity/2:high verbosity)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          log_timings = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "RANDOM_SEED"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          random_seed = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "NUM_WORKING_GRIDS"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          num_working_grids = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "MONTE_CARLO_ITERATIONS"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          monte_carlo_iterations = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "ANIMATION(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          postprocessing = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            postprocessing = 1;
          }
        }
        else if (!strcmp (keyword, "ECHO(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          isechoing = false;
          if (!strcmp (object_ptr, "YES"))
          {
            isechoing = true;
          }
        }
        else if (!strcmp (keyword, "LOGGING(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          logging = FALSE;
          if (!strcmp (object_ptr, "YES"))
          {
            logging = TRUE;
          }
        }
        else if (!strcmp (keyword, "WRITE_MEMORY_MAP(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_memory_map = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_memory_map = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_LANDCLASS_SUMMARY(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_landclass_summary = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_landclass_summary = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_SLOPE_WEIGHTS(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_slope_weights = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_slope_weights = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_READS(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_reads = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_reads = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_WRITES(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_writes = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_writes = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_COLORTABLES(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          log_colortables = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            log_colortables = 1;
          }
        }
        else if (!strcmp (keyword, "LOG_PROCESSING_STATUS(0:off/1:low verbosity/2:high verbosity)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          log_processing_status = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "VIEW_GROWTH_TYPES(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          view_growth_types = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            view_growth_types = 1;
          }
        }
        else if (!strcmp (keyword, "GROWTH_TYPE_PRINT_WINDOW"))
        {
          object_ptr = strtok (NULL, "\n");
          util_trim (object_ptr);
          growth_type_window.run1 = atoi (strtok (object_ptr, ","));
          growth_type_window.run2 = atoi (strtok (NULL, ","));
          growth_type_window.monte_carlo1 = atoi (strtok (NULL, ","));
          growth_type_window.monte_carlo2 = atoi (strtok (NULL, ","));
          growth_type_window.year1 = atoi (strtok (NULL, ","));
          growth_type_window.year2 = atoi (strtok (NULL, ","));
        }
        else if (!strcmp (keyword, "CALIBRATION_DIFFUSION_START"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          start.diffusion = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_DIFFUSION_STOP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          stop.diffusion = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_DIFFUSION_STEP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          step.diffusion = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "PREDICTION_DIFFUSION_BEST_FIT"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          best_fit.diffusion = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_BREED_START"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          start.breed = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_BREED_STOP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          stop.breed = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_BREED_STEP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          step.breed = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "PREDICTION_BREED_BEST_FIT"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          best_fit.breed = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_SPREAD_START"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          start.spread = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_SPREAD_STOP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          stop.spread = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_SPREAD_STEP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          step.spread = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "PREDICTION_SPREAD_BEST_FIT"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          best_fit.spread = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_SLOPE_START"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          start.slope_resistance = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_SLOPE_STOP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          stop.slope_resistance = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_SLOPE_STEP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          step.slope_resistance = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "PREDICTION_SLOPE_BEST_FIT"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          best_fit.slope_resistance = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_ROAD_START"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          start.road_gravity = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_ROAD_STOP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          stop.road_gravity = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "CALIBRATION_ROAD_STEP"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          step.road_gravity = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "PREDICTION_ROAD_BEST_FIT"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          best_fit.road_gravity = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "PREDICTION_START_DATE"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          prediction_start_date = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "PREDICTION_STOP_DATE"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          prediction_stop_date = atoi (object_ptr);
        }
        else if (!strcmp (keyword, "DATE_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          date_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "SEED_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          seed_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "WATER_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          water_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "PROBABILITY_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          index = probability_color_count;
          probability_color[index].lower_bound =
            atoi (strtok (object_ptr, ","));
          probability_color[index].upper_bound =
            atoi (strtok (NULL, ","));
          probability_color[index].color =
            process_user_color (strtok (NULL, ","));


          probability_color_count++;
        }
        else if (!strcmp (keyword, "PHASE0G_GROWTH_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          phase0g_growth_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "PHASE1G_GROWTH_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          phase1g_growth_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "PHASE2G_GROWTH_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          phase2g_growth_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "PHASE3G_GROWTH_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          phase3g_growth_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "PHASE4G_GROWTH_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          phase4g_growth_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "PHASE5G_GROWTH_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          phase5g_growth_color = process_user_color (object_ptr);
        }
        else if (!strcmp (keyword, "LANDUSE_CLASS"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          landuse_class[num_landuse_classes].grayscale =
            atoi (strtok (object_ptr, ","));
          object_ptr = strtok (NULL, ",");
          util_trim (object_ptr);
          strcpy (landuse_class[num_landuse_classes].name,
                  object_ptr);
          object_ptr = strtok (NULL, ",");
          util_trim (object_ptr);
          strcpy (landuse_class[num_landuse_classes].type,
                  object_ptr);
          landuse_class[num_landuse_classes].color =
            process_user_color (strtok (NULL, "\n"));

          num_landuse_classes++;
        }
        else if (!strcmp (keyword, "VIEW_DELTATRON_AGING(YES/NO)"))
        {
          object_ptr = strtok (NULL, " \n");
          util_trim (object_ptr);
          util_AllCAPS (object_ptr);
          view_deltatron_aging = 0;
          if (!strcmp (object_ptr, "YES"))
          {
            view_deltatron_aging = 1;
          }
        }
        else if (!strcmp (keyword, "DELTATRON_PRINT_WINDOW"))
        {
          object_ptr = strtok (NULL, "\n");
          util_trim (object_ptr);
          deltatron_aging_window.run1 =
            atoi (strtok (object_ptr, ","));
          deltatron_aging_window.run2 = atoi (strtok (NULL, ","));
          deltatron_aging_window.monte_carlo1 =
            atoi (strtok (NULL, ","));
          deltatron_aging_window.monte_carlo2 =
            atoi (strtok (NULL, ","));
          deltatron_aging_window.year1 = atoi (strtok (NULL, ","));
          deltatron_aging_window.year2 = atoi (strtok (NULL, ","));
        }
        else if (!strcmp (keyword, "DELTATRON_COLOR"))
        {
          object_ptr = strtok (NULL, "\0");
          util_trim (object_ptr);
          deltatron_color[deltatron_color_count++] =
            process_user_color (object_ptr);
        }
      }
    }
  }
  fclose (fp);

}

/*
   FUNCTION NAME: process_user_color
   PURPOSE:       parse the user color input string
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/

int Scenario::process_user_color (char *string2process) throw()
{
  int color_val;

 
  assert (string2process != NULL);

  util_trim (string2process);
  if (strlen (string2process) == 0)
  {
    color_val = 0;
  }
  else
  {
    if ((!strncmp (string2process, "0x", 2)) ||
        (!strncmp (string2process, "0X", 2)))
    {
      sscanf (string2process, "%x", &(color_val));
    }
    else
    {
      color_val = atoi (strtok (string2process, ",")) * 256 * 256;
      color_val += atoi (strtok (NULL, ",")) * 256;
      color_val += atoi (strtok (NULL, "\0"));
    }
  }

  return (color_val);
}

/*
   FUNCTION NAME: echo
   PURPOSE:       echo scenario struct to FILE * fp
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/

void Scenario::echo (FILE * fp) throw()
{
  int index;

 
  assert (fp != NULL);

  fprintf (fp, "filename = %s\n", filename);
  fprintf (fp, "input_dir = %s\n", input_dir);
  fprintf (fp, "output_dir = %s\n", output_dir);
  fprintf (fp, "whirlgif_binary = %s\n", whirlgif_binary);
  for (index = 0; index < urban_data_file_count; index++)
  {
    fprintf (fp, "urban_data_file[%u] = %s\n",
             index, urban_data_file[index]);
  }
  for (index = 0; index < road_data_file_count; index++)
  {
    fprintf (fp, "road_data_file[%u] = %s\n",
             index, road_data_file[index]);
  }
  for (index = 0; index < landuse_data_file_count; index++)
  {
    fprintf (fp, "landuse_data_file[%u] = %s\n",
             index, landuse_data_file[index]);
  }
  fprintf (fp, "excluded_data_file = %s\n",
           excluded_data_file);
  fprintf (fp, "slope_data_file = %s\n", slope_data_file);
  fprintf (fp, "background_data_file = %s\n",
           background_data_file);
  fprintf (fp, "echo = %u\n", isechoing);
  fprintf (fp, "logging = %u\n", logging);
  fprintf (fp, "log_processing_status = %u\n",
           log_processing_status);
  fprintf (fp, "random_seed = %u\n", random_seed);
  fprintf (fp, "num_working_grids = %d\n", num_working_grids);
  fprintf (fp, "monte_carlo_iterations = %u\n",
           monte_carlo_iterations);
  fprintf (fp, "start.diffusion = %u\n", start.diffusion);
  fprintf (fp, "stop.diffusion = %u\n", stop.diffusion);
  fprintf (fp, "step.diffusion = %u\n", step.diffusion);
  fprintf (fp, "best_fit.diffusion = %u\n",
           best_fit.diffusion);
  fprintf (fp, "start.breed = %u\n", start.breed);
  fprintf (fp, "stop.breed = %u\n", stop.breed);
  fprintf (fp, "step.breed = %u\n", step.breed);
  fprintf (fp, "best_fit.breed = %u\n", best_fit.breed);
  fprintf (fp, "start.spread = %u\n", start.spread);
  fprintf (fp, "stop.spread = %u\n", stop.spread);
  fprintf (fp, "step.spread = %u\n", step.spread);
  fprintf (fp, "best_fit.spread = %u\n", best_fit.spread);
  fprintf (fp, "start.slope_resistance = %u\n",
           start.slope_resistance);
  fprintf (fp, "stop.slope_resistance = %u\n",
           stop.slope_resistance);
  fprintf (fp, "step.slope_resistance = %u\n",
           step.slope_resistance);
  fprintf (fp, "best_fit.slope_resistance = %u\n",
           best_fit.slope_resistance);
  fprintf (fp, "start.road_gravity = %u\n",
           start.road_gravity);
  fprintf (fp, "stop.road_gravity = %u\n",
           stop.road_gravity);
  fprintf (fp, "step.road_gravity = %u\n",
           step.road_gravity);
  fprintf (fp, "best_fit.road_gravity = %u\n",
           best_fit.road_gravity);
  fprintf (fp, "prediction_start_date = %u\n",
           prediction_start_date);
  fprintf (fp, "prediction_stop_date = %u\n",
           prediction_stop_date);
  fprintf (fp, "date_color = %x\n", date_color);
  fprintf (fp, "seed_color = %x\n", seed_color);
  fprintf (fp, "water_color = %x\n", water_color);
  fprintf (fp, "probability_color[%u].lower_bound = %u\n", index,
           probability_color[index].lower_bound);
  fprintf (fp, "probability_color[%u].upper_bound = %u\n", index,
           probability_color[index].upper_bound);
  fprintf (fp, "probability_color[%u].color = %X\n", index,
           probability_color[index].color);
  fprintf (fp, "rd_grav_sensitivity = %f\n",
           rd_grav_sensitivity);
  fprintf (fp, "slope_sensitivity = %f\n", slope_sensitivity);
  fprintf (fp, "critical_low = %f\n", critical_low);
  fprintf (fp, "critical_high = %f\n", critical_high);
  fprintf (fp, "critical_slope = %f\n", critical_slope);
  fprintf (fp, "boom = %f\n", boom);
  fprintf (fp, "bust = %f\n", bust);
  fprintf (fp, "log_base_stats = %u\n", log_base_stats);
  fprintf (fp, "log_debug = %u\n", log_debug);
  fprintf (fp, "log_urbanization_attempts = %u\n",
           log_urbanization_attempts);
  fprintf (fp, "log_coeff = %u\n", log_coeff);
  fprintf (fp, "log_timings = %u\n", log_timings);
  fprintf (fp, "write_avg_file = %u\n", write_avg_file);
  fprintf (fp, "write_std_dev_file = %u\n",
           write_std_dev_file);
  fprintf (fp, "log_memory_map = %u\n", log_memory_map);
  fprintf (fp, "log_landclass_summary = %u\n",
           log_landclass_summary);
  fprintf (fp, "log_slope_weights = %u\n", log_slope_weights);
  fprintf (fp, "log_reads = %u\n", log_reads);
  fprintf (fp, "log_writes = %u\n", log_writes);
  fprintf (fp, "log_colortables = %u\n", log_colortables);
  fprintf (fp, "log_processing_status = %u\n",
           log_processing_status);
  fprintf (fp, "log_trans_matrix = %u\n", log_trans_matrix);
  fprintf (fp, "view_growth_types = %u\n", view_growth_types);
  fprintf (fp, "growth_type_window.run1 = %d\n",
           growth_type_window.run1);
  fprintf (fp, "growth_type_window.run2 = %d\n",
           growth_type_window.run2);
  fprintf (fp, "growth_type_window.monte_carlo1 = %d\n",
           growth_type_window.monte_carlo1);
  fprintf (fp, "growth_type_window.monte_carlo2 = %d\n",
           growth_type_window.monte_carlo2);
  fprintf (fp, "growth_type_window.year1 = %d\n",
           growth_type_window.year1);
  fprintf (fp, "growth_type_window.year2 = %d\n",
           growth_type_window.year2);
  fprintf (fp, "phase0g_growth_color = %x\n",
           phase0g_growth_color);
  fprintf (fp, "phase1g_growth_color = %x\n",
           phase1g_growth_color);
  fprintf (fp, "phase2g_growth_color = %x\n",
           phase2g_growth_color);
  fprintf (fp, "phase3g_growth_color = %x\n",
           phase3g_growth_color);
  fprintf (fp, "phase4g_growth_color = %x\n",
           phase4g_growth_color);
  fprintf (fp, "phase5g_growth_color = %x\n",
           phase5g_growth_color);
  fprintf (fp, "view_deltatron_aging = %u\n",
           view_deltatron_aging);
  fprintf (fp, "deltatron_aging_window.run1 = %d\n",
           deltatron_aging_window.run1);
  fprintf (fp, "deltatron_aging_window.run2 = %d\n",
           deltatron_aging_window.run2);
  fprintf (fp, "deltatron_aging_window.monte_carlo1 = %d\n",
           deltatron_aging_window.monte_carlo1);
  fprintf (fp, "deltatron_aging_window.monte_carlo2 = %d\n",
           deltatron_aging_window.monte_carlo2);
  fprintf (fp, "deltatron_aging_window.year1 = %d\n",
           deltatron_aging_window.year1);
  fprintf (fp, "deltatron_aging_window.year2 = %d\n",
           deltatron_aging_window.year2);
  for (index = 0; index < deltatron_color_count; index++)
  {
    fprintf (fp, "deltatron_color[%u] = %u\n",
             index, deltatron_color[index]);
  }

}

/*
   FUNCTION NAME: open_log
   PURPOSE:       open the log file
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Scenario::CloseLog () throw()
{
  char msg_buf[MAX_FILENAME_LEN]; 
  if (log_fp)
  {
    fclose (log_fp);
    log_fp = NULL;
  }
  else
  {
    sprintf (msg_buf, "Log file is not open");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  
}

/*
   FUNCTION NAME: open_log
   PURPOSE:       open the log file
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Scenario::open_log (bool restart) throw()
{
  
  static int opened = 0;
  char msg_buf[MAX_FILENAME_LEN]; 
  
  if (logging == TRUE)
  {
    if (opened > 0)
    {
      sprintf (msg_buf, "log file already open");
      LOG_ERROR (msg_buf);
      EXIT (1);
    }
    sprintf (log_filename, "%sLOG_%u", output_dir, mpi_rank);

    if (!restart);
    {
      FILE_OPEN (log_fp, log_filename, "w");
      CloseLog ();
    }

    opened = 1;
  }
  else
  {
    log_fp = NULL;
  }
  
}
/*
 Returns the input image type.
*/
ImageType Scenario::GetInputImageType() const throw()
{
   return input_type;
}

/*
 Returns the output image type.
*/
ImageType Scenario::GetOutputImageType() const throw()
{
   return output_type;
}

/*
 Returns the output image extension
*/
const char* Scenario::GetOutputImageExtension() const throw()
{
   return extension;
}
