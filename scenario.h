#ifndef SCENARIO_H
#define SCENARIO_H
/*! \file scenario.h
    \brief Definition file for the scenario object.
    
    Definition file for the scenario object which holds
    information about the simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include <stdio.h>
#include "ugm_defines.h"
#define SCEN_MAX_FILENAME_LEN 256
#define SCEN_MAX_URBAN_YEARS 20
#define SCEN_MAX_ROAD_YEARS 20
#define SCEN_MAX_LANDUSE_YEARS 2
#define SCEN_MAX_LANDUSE_CLASSES 256


#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#include "coeff.h"
#include "proc.h"
#include "ugm_macros.h"

enum ImageType{GIF_TYPE=1,TIFF_TYPE,GEOTIFF_TYPE,PNG_TYPE};

//! Structure to hold simulation window.
typedef struct
{
  int run1;
  int run2;
  int monte_carlo1;
  int monte_carlo2;
  int year1;
  int year2;
} print_window_t;

//! Structure to hold probility color info.
typedef struct
{
  int lower_bound;
  int upper_bound;
  int color;
} prob_color_info;

//! Structure to hold landclass info.
typedef struct
{
  char name[80];
  char type[80];
  int color;
  int grayscale;
} landuse_class_info;

//! The scenario object holds simulation data.
class Scenario
{
private:
  char log_filename[SCEN_MAX_FILENAME_LEN];
  FILE* log_fp;
  char filename[SCEN_MAX_FILENAME_LEN];
  char input_dir[SCEN_MAX_FILENAME_LEN];
  char output_dir[SCEN_MAX_FILENAME_LEN];
  char extension[SCEN_MAX_FILENAME_LEN];
  char whirlgif_binary[SCEN_MAX_FILENAME_LEN];
  char urban_data_file[SCEN_MAX_URBAN_YEARS][SCEN_MAX_FILENAME_LEN];
  int urban_data_file_count;
  char road_data_file[SCEN_MAX_ROAD_YEARS][SCEN_MAX_FILENAME_LEN];
  int road_data_file_count;
  char landuse_data_file[SCEN_MAX_LANDUSE_YEARS][SCEN_MAX_FILENAME_LEN];
  int landuse_data_file_count;
  char excluded_data_file[SCEN_MAX_FILENAME_LEN];
  char slope_data_file[SCEN_MAX_FILENAME_LEN];
  char background_data_file[SCEN_MAX_FILENAME_LEN];
  bool isechoing;
  bool logging;
  bool postprocessing;
  int random_seed;
  int num_working_grids;
  int monte_carlo_iterations;
  coeff_int_info start;
  coeff_int_info stop;
  coeff_int_info step;
  coeff_int_info best_fit;
  int prediction_start_date;
  int prediction_stop_date;
  int date_color;
  int seed_color;
  int water_color;
  prob_color_info probability_color[MAX_PROBABILITY_COLORS];
  int num_landuse_classes;
  landuse_class_info landuse_class[SCEN_MAX_LANDUSE_CLASSES];
  int probability_color_count;
  double rd_grav_sensitivity;
  double slope_sensitivity;
  double critical_low;
  double critical_high;
  double critical_slope;
  double boom;
  double bust;
  bool log_base_stats;
  bool log_debug;
  bool log_urbanization_attempts;
  bool log_coeff;
  int log_timings;
  bool write_coeff_file;
  bool write_avg_file;
  bool echo_image_files;
  bool write_color_keys;
  bool write_std_dev_file;
  bool log_memory_map;
  bool log_landclass_summary;
  bool log_slope_weights;
  bool log_reads;
  bool log_writes;
  bool log_colortables;
  bool log_processing_status;
  bool log_trans_matrix;
  bool view_growth_types;
  print_window_t growth_type_window;
  int phase0g_growth_color;
  int phase1g_growth_color;
  int phase2g_growth_color;
  int phase3g_growth_color;
  int phase4g_growth_color;
  int phase5g_growth_color;
  bool view_deltatron_aging;
  print_window_t deltatron_aging_window;
  int deltatron_color[256];
  int deltatron_color_count;
  ImageType input_type;
  ImageType output_type;
  
  //! Reads a given scenario file.
  /*!
   */
  void read_file(char * filename) throw();
  
  //! Converts a user string color to a color.
  /*!
   */
  int process_user_color(char *string2process) throw();
  
  //! Opens the simulation log.
  /*!
   */
  void open_log(bool restart) throw();
//scenario_info;
  int mpi_rank;

public:
  //! Constructor.
  /*! \param inmpi_rank the mpi rank of this process.
   */
  Scenario(int inmpi_rank) : mpi_rank(inmpi_rank)
    {}
  
  //! Logs the memory stuff to a file
  /*!
   */
  void MemoryLog(FILE* fp) throw();
  
  //! Initilizes the scenario file.
  /*! \param filename the name of the input scenario file.
   */
  void init(char* filename) throw();

  //! Echos the scenario info to a file.
  /*!
   */
  void echo(FILE* fp) throw();
  
  //! Returns the log file pointer.
  /*!
   */
  FILE* GetLogFP() throw();
  
  //! Returns the scenario filename.
  /*!
   */
  const char* GetScenarioFilename() const throw();
  
  //! Returns the output directory path.
  /*!
   */
  const char* GetOutputDir() const throw();
  
  //! Returns the path the whirlgif binary
  /*!
   */
  const char* GetWhirlgifBinary () const throw();
  
  //! Returns the path the input directory.
  /*!
   */
  const char* GetInputDir() const throw();
  
  //! Returns the number of urban data files.
  /*!
   */
  int   GetUrbanDataFileCount() const throw();
  
  //! Returns the number of road data files.
  /*!
   */
  int   GetRoadDataFileCount() const throw();
  
  //! Returns the number of landuse data files.
  /*!
   */
  int   GetLanduseDataFileCount() const throw();
  
  //! Returns whether the sim should track land use.
  /*!
   */
  int   GetDoingLanduseFlag() const throw();
  
  //! Returns a specific urban data filename.
  /*! \param i the index of the urban data file.
   */
  const char* GetUrbanDataFilename(int i) const throw();
  
  //! Returns a specific road data filename
  /*! \param i the index of the road data file.
   */
  const char* GetRoadDataFilename(int i) const throw();
  
  //! Returns a specific landuse data filename.
  /*! \param i is the index of the land use data file.
   */
  const char* GetLanduseDataFilename(int i) const throw();
  
  //! Returns the excluded data filename.
  /*!
   */
  const char* GetExcludedDataFilename() const throw();
  
  //! Retruns the slope data file name.
  /*!
   */
  const char* GetSlopeDataFilename() const throw();
  
  //! Returns the background data filename.
  /*!
   */
  const char* GetBackgroundDataFilename() const throw();
  
  //! Is echoing turned on.
  /*!
   */
  bool GetEchoFlag() const throw();
  
  //! Is logging turned on.
  /*!
   */
  bool GetLogFlag() const throw();
  
  //! Should the model do post processing.
  /*!
   */
  bool GetPostprocessingFlag() const throw();
  
  //! Returns the random seed.
  /*!
   */
  int   GetRandomSeed() const throw();
  
  //! Returns the number of Monte Carlo iterations.
  /*!
   */
  int   GetMonteCarloIterations() const throw();
  
  //! Returns the diffsion coeff start.
  /*!
   */
  int   GetCoeffDiffusionStart() const throw();
  
  //! Returns the breed coeff start.
  /*!
   */
  int   GetCoeffBreedStart() const throw();
  
  //! Returns the spread coeff start.
  /*!
   */
  int   GetCoeffSpreadStart() const throw();
  
  //! Returns the slope coeff start.
  /*!
   */
  int   GetCoeffSlopeResistStart() const throw();
  
  //! Returns the road gravity start.
  /*!
   */
  int   GetCoeffRoadGravityStart() const throw();
  
  //! Returns the diffsion coeff stop.
  /*!
   */
  int   GetCoeffDiffusionStop() const throw();
  
  //! Returns the breed coeff stop.
  /*!
   */
  int   GetCoeffBreedStop() const throw();
  
  //! Returns the spread coeff stop.
  /*!
   */
  int   GetCoeffSpreadStop() const throw();
  
  //! Returns the slope coeff stop.
  /*!
   */
  int   GetCoeffSlopeResistStop() const throw();
  
  //! Returns the road coeff stop.
  /*!
   */
  int   GetCoeffRoadGravityStop() const throw();
  
  //! Returns the diffsion coeff step.
  /*!
   */
  int   GetCoeffDiffusionStep() const throw();
  
  //! Returns the breed coeff step.
  /*!
   */
  int   GetCoeffBreedStep() const throw();
  
  //! Returns the spread coeff step.
  /*!
   */
  int   GetCoeffSpreadStep() const throw();
  
  //! Returns the slope coeff step.
  /*!
   */
  int   GetCoeffSlopeResistStep() const throw();
  
  //! Returns the road coeff step.
  /*!
   */
  int   GetCoeffRoadGravityStep() const throw();
  
  //! Returns the diffsion coeff best fit.
  /*!
   */
  int   GetCoeffDiffusionBestFit() const throw();
    
  //! Returns the breed coeff best fit.
  /*!
   */
  int   GetCoeffBreedBestFit() const throw();
  
  //! Returns the spread coeff best fit.
  /*!
   */
  int   GetCoeffSpreadBestFit() const throw();
  
  //! Returns the slope coeff best fit.
  /*!
   */
  int   GetCoeffSlopeResistBestFit() const throw();
  
  //! Returns the road coeff best fit.
  /*!
   */
  int   GetCoeffRoadGravityBestFit() const throw();
  
  //! Returns the prediction start date.
  /*!
   */
  int   GetPredictionStartDate() const throw();
  
  //! Returns the prediction stop date.
  /*!
   */
  int   GetPredictionStopDate() const throw();
  
  //! Get the date color.
  /*!
   */
  int   GetDateColor() const throw();
  
  //! Get the urban seed color.
  /*!
   */
  int   GetSeedColor() const throw();
  
  //! Returns the water color.
  /*!
   */
  int   GetWaterColor() const throw();
  
  //! Return the number of probablity colors.
  /*!
   */
  int   GetProbabilityColorCount() const throw();
  
  //! Get the lower bound number for a probablity color index.
  /*! \param i the color index.
   */
  int   GetProbabilityColorLowerBound(int i) const throw();
  
  //! Get the upper bound number of a probablity color index.
  /*! \param i the color index.
   */
  int   GetProbabilityColorUpperBound(int i) const throw();
  
  //! Get the color from a probablity color index.
  /*! \param i the color index.
   */
  int   GetProbabilityColor(int i) const throw();
  
  //! Is the memory map being logged.
  /*!
   */
  bool   GetLogMemoryMapFlag() const throw();
  
  //! Is the land summary being logged.
  /*!
   */
  bool   GetLogLandclassSummaryFlag() const throw();
  
  //! Is the slope weights being logged.
  /*!
   */
  bool   GetLogSlopeWeightsFlag() const throw();
  
  //! Is the reads being logged.
  /*!
   */
  bool   GetLogReadsFlag() const throw();
  
  //! Is the writes flag being logged.
  /*!
   */
  bool   GetLogWritesFlag() const throw();
  
  //! Is the colortables being logged.
  /*!
   */
  bool   GetLogColortablesFlag() const throw();
  
  //! Is the post processing being logged.
  /*!
   */
  bool   GetLogProcessingStatusFlag() const throw();
  
  //! Is the growth types going to be logged.
  /*!
   */
  bool   GetViewGrowthTypesFlag(const Proc & inproc) const throw();
  
  //! Is the aging going to being shown.
  /*!
   */
  bool   GetViewDeltatronAgingFlag(const Proc & inproc) const throw();
  
  //! Returns the phase 0 growth color.
  /*!
   */
  int   GetPhase0GrowthColor() const throw();
  
  //! Returns the phase 1 growth color.
  /*!
   */
  int   GetPhase1GrowthColor() const throw();
  
  //! Returns the phase 2 growth color.
  /*!
   */
  int   GetPhase2GrowthColor() const throw();
  
  //! Returns the phase 3 growth color.
  /*!
   */
  int   GetPhase3GrowthColor() const throw();
 
  //! Returns the phase 4 growth color.
  /*!
   */
  int   GetPhase4GrowthColor() const throw();
  
  //! Returns the phase 5 growth color.
  /*!
   */
  int   GetPhase5GrowthColor() const throw();
  
  //! Returns the deltatron color based on index.
  /*! \param index the index of the deletatron.
   */
  int GetDeltatronColor (int index) const throw();
  
  //! Returns the number of deltatron colors.
  /*!
   */
  int GetDeltatronColorCount () const throw();
  
  //! Closes the simulation log.
  /*!
   */
  void CloseLog () throw();
  
  //! Opens the simulation log for appending.
  /*!
   */
  void Append2Log () throw();
  
  //! Should the tranisition matrix be logged.
  /*!
   */
  bool GetLogTransitionMatrixFlag () const throw();
  
  //! Returns the road grav sensitivity
  /*!
   */
  double GetRdGrvtySensitivity () const throw();
  
  //! Returns the slope sensitivity.
  /*!
   */
  double GetSlopeSensitivity () const throw();
  
  //! Returns the high population threshold.
  /*!
   */
  double GetCriticalHigh () const throw();
  
  //! Returns the low val population threshold.
  /*!
   */
  double GetCriticalLow () const throw();
  
  //! Retruns the critcial slope threshold.
  /*!
   */
  double GetCriticalSlope () const throw();
  
  //! Returns the population boom threshold.
  /*!
   */
  double GetBoom () const throw();
  
  //! Returns the population bust threshold.
  /*!
   */
  double GetBust () const throw();
  
  //! Should timings be logged.
  /*! Deprecated.
   */
  int GetLogTimingsFlag() const throw();
  
  //! Should coeff be logged.
  /*! Deprecated.
   */
  bool GetLogCoeffFlag() const throw();
  
  //! Should urbanization attempts be logged.
  /*!
   */
  bool GetLogUrbanizationAttemptsFlag() const throw();
  
  //! Should the base stats be logged.
  /*! Deprecated.
   */
  bool GetLogBaseStatsFlag() const throw();
  
  //! Should the debug file be logged.
  /*! Deprecated.
   */
  bool GetLogDebugFlag() const throw();
  
  //! Should the coeff file be logged.
  /*! Depracted.
   */
  bool GetWriteCoeffFileFlag() const throw();
 
  //! Should the avg file be written.
  /*!
   */
  bool GetWriteAvgFileFlag() const throw();
  
  //! Should the std dev file be written.
  /*!
   */
  bool GetWriteStdDevFileFlag() const throw();
  
  //! Should the color key be written.
  /*! Deprecated.
   */
  bool GetWriteColorKeyFlag() const throw();
  
  //! Should the images be echoed.
  /*! Deprecated.
   */
  bool GetEchoImageFlag() const throw();
  
  //! Return the number of landuse classes.
  /*!
   */
  int GetNumLanduseClasses () const throw();
  
  //! Returns the land class name for a given index.
  /*! \param i the index of the land class.
   */
  const char* GetLanduseClassName (int) const throw();
  
  //! Returns the land class type for a given index.
  /*! \param i the index of the land class.
   */
  const char* GetLanduseClassType (int) const throw();
  
  //! Returns the color for a given land class.
  /*! \param i the index of the land class.
   */
  int GetLanduseClassColor (int) const throw();
  
  //! Returns the gray color for a given land class.
  /*! \param i the index of the land class.
   */
  int GetLanduseClassGrayscale (int i) const throw();
  
  //! Returns the number of working grids.
  /*!
   */
  int GetNumWorkingGrids() const throw();
  
  //! Returns the input image type.
  /*!
   */
  ImageType GetInputImageType() const throw();
  
  //! Returns the output image type.
  /*!
   */
  ImageType GetOutputImageType() const throw();
  
  //! Returns the output image extension.
  /*!
   */
  const char* GetOutputImageExtension() const throw();
};
#endif
  
