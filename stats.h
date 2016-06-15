#ifndef STATS_H
#define STATS_H
/*! \file stats.h
    \brief Definition file for Statistics compilation functions.

    Definition file for the statistics functions.
    For credits see CREDITS.TXT in this directory.
    \sa CREDITS.TXT

*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "ugm_defines.h" 
#include "pgrid.h"
#include "proc.h"
#include "igrid.h"
#include "memory.h"
#include "scenario.h"
#include "ugm_macros.h"
#include "coeff.h"
#include "utilities.h"

#define MAX_LINE_LEN 256
#define SIZE_CIR_Q 100000

#define Q_STORE(R,C)                                                     \
  if((sidx+1==ridx)||((sidx+1==SIZE_CIR_Q)&&!ridx)){                     \
    printf("Error Circular Queue Full\n");                               \
    printf("Increase SIZE_CIR_Q and recompile\n");                       \
    printf("sidx=%d ridx=%d SIZE_CIR_Q=%d\n",sidx,ridx,SIZE_CIR_Q);      \
    EXIT(1);}                                                            \
  cir_q[sidx].row = R;                                                   \
  cir_q[sidx].col = C;                                                   \
  sidx++;                                                                \
  depth++;                                                               \
  sidx %= SIZE_CIR_Q
#define Q_RETREIVE(R,C)                                                  \
  ridx = ridx%SIZE_CIR_Q;                                                \
  R = cir_q[ridx].row;                                                   \
  C = cir_q[ridx].col;                                                   \
  ridx++;                                                                \
  depth--


typedef struct
{
   int  sng;
   int  sdg;
   int  sdc;
   int  og;
   int  rt;
   int  pop;
}  Gstats;

typedef struct
{
   double area;
   double edges;
   double clusters;
   double pop;
   double xmean;
   double ymean;
   double rad;
   double average_slope;
   double mean_cluster_size;
   double percent_urban;
}  stats_info;

typedef struct
{
  double sng;
  double sdg;
  double sdc;
  double og;
  double rt;
  double pop;
  double area;
  double edges;
  double clusters;
  double xmean;
  double ymean;
  double rad;
  double slope;
  double mean_cluster_size;
  double diffusion;
  double spread;
  double breed;
  double slope_resistance;
  double road_gravity;
  double percent_urban;
  double percent_road;
  double growth_rate;
  double leesalee;
  double num_growth_pix;
} stats_val_t; 
 
//! The stats object. 
class Stats
{

 public:

  //! Initializes stats object
  /*!
  */
  Stats(int inmpi_rank, int inmpi_size);

  //! Updates Running total for each statistic
  /*!
  */
  void UpdateRunningTotal (int index);  

  //! Returns the Number of This Years Growth Pixels.
  /*!
  */
  int GetNumGrowthPixels ();

  //! Records this years percentage urban.
  /*!
  */
  void SetPercentUrban (int val); 

  //! Logs Average values.
  /*!
  */
  void LogAverages (int index,   
		    FILE * fp);  

  //! Logs the Record File.
  /*!
  */
  void LogRecord (FILE * fp); 

  //! Concatenates the Scenario control files.
  /*!
  */   
  void ConcatenateControlFiles(const Scenario & scene);  /* IN    */

  //! Concatenates the Standard Deviation Scenario files
  /*!
  */
  void ConcatenateStdDevFiles(const Scenario & scene);  

  //! Concatenates the Average files from Scenario.
  /*!
  */
  void ConcatenateAvgFiles(const Scenario & scene);      

  //! Initializes the statistics value arrays with base numbers.
  /*!
  */ 
  void Init(const Proc & runinfo,   
	    IGrid & ingrids);      

  //! Performs the Analysis on values.
  /*!
  */
  void Analysis(const Coeff & coeffs, 
		IGrid & ingrids,
		Proc & runinfo, 
		Scenario & scene,
		double fmatch);

  //! Updates the prediction and other status
  /*!
  */
  void Update(const Coeff & coeffs,
	      IGrid & ingrids, 
	      const Scenario & scene, 
	      const Proc & runinfo,
	      PGrid & pgrids,
              int num_growth_pix);

  //! Sets the SNG value.
  /*!
  */
  void SetSNG(int val) ;

  //! Sets the SDG value.
  /*!
  */
  void SetSDG(int val) ;

  //! Sets the OG value.
  /*!
  */
  void SetOG(int val) ;

  //! Sets the RT value.
  /*!
  */
  void SetRT(int val) ;

  //! Sets the POP value.
  /*!
  */
  void SetPOP(int val) ;

  //!  Logs the Base Statistics.
  /*!
  */  
  void LogBaseStats (IGrid & ingrids, /* IN    */
		     FILE* fp);       /* IN    */

  //! Returns this year's urban percentage.
  /*!
  */  
  double GetPercentUrban() ;  

  //! Returns this years Growth Rate.
  /*!
  */
  double GetGrowthRate() ;  

  //! Returns this years leesalee value
  /*!
  */
  double GetLeesalee() ;

  //! Returns the SNG value.
  /*!
  */    
  int GetSNG() ;

  //! Returns the SDG value.
  /*!
  */
  int GetSDG() ;

  //! Returns the OG value.
  /*!
  */
  int GetOG() ;

  //! Returns the RT value.
  /*!
  */
  int GetRT() ;

  //! Returns the POP value.
  /*!
  */
  int GetPOP() ;

  //! Sets the area value.
  /*!
  */  
  void SetArea(int val) ;

  //! Sets the edge values.
  /*!
  */
  void SetEdges(int val) ;

  //! Sets the cluster values.
  /*!
  */
  void SetClusters(int val) ;

  //! Sets the Pop value.
  /*!
  */
  void SetPop(int val) ;

  //! Records the value for Xmean.
  /*!
  */
  void SetXmean(double val) ;

  //! Records the value for Ymean.
  /*!
  */
  void SetYmean(double val) ;

  //! Records the value for Rad.
  /*!
  */
  void SetRad(double val) ;

  //! Records the Average Slope value.
  /*!
  */
  void SetAvgSlope(double val) ;

  //! Records the Mean Cluster Size.
  /*!
  */
  void SetMeanClusterSize(double val) ;

  //! Returns the Area value.
  /*!
  */  
  int GetArea() ;

  //! Returns the Edges value.
  /*!
  */
  int GetEdges() ;

  //! Returns the Clusters value.
  /*!
  */
  int GetClusters() ;

  //! Returns the Pop value.
  /*!
  */
  int GetPop() ;

  //! Returns the Xmean value.
  /*!
  */
  double GetXmean() ;

  //! Returns the Ymean value.
  /*!
  */
  double GetYmean() ;

  //! Returns the Rad value.
  /*!
  */
  double GetRad() ;

  //! Returns the Average Slope value.
  /*!
  */
  double GetAvgSlope() ;

  //! Returns the Mean Cluster Size
  /*!
  */
  double GetMeanClusterSize() ;

  //! Initializes The Urbanization Attempts.
  /*!
  */
  void InitUrbanizationAttempts();

  //! Logs to file.
  /*!
  */
  void LogUrbanizationAttempts(FILE* fp);

  //! Increments the Successes.
  /*!
  */
  void IncrementUrbanSuccess();

  //! Increments ZFailure.
  /*!
  */
  void IncrementZFailure();

  //! Increments the Delta Failure Value.
  /*!
  */
  void IncrementDeltaFailure();

  //! Increments the Slope Failure Value.
  /*!
  */
  void IncrementSlopeFailure();

  //! Instantiates the Control File.
  /*!
  */
  void CreateControlFile (char *filename);

  //! Increments Excluded Failure Value.
  /*!
  */
  void IncrementEcludedFailure();

  //! Instantiates the Stats Value File.
  /*!
  */
  void CreateStatsValFile (char *filename);
  
 private:
  
  int mpi_rank;
  int mpi_size;
  stats_info actual[MAX_URBAN_YEARS];
  stats_info regression;
  stats_val_t average[MAX_URBAN_YEARS];
  stats_val_t std_dev[MAX_URBAN_YEARS];
  stats_val_t running_total[MAX_URBAN_YEARS];
  
  struct
  {
    int run;
    int monte_carlo;
    int year;
    stats_val_t this_year;
  }
  record;
  
  struct
  {
    double fmatch;
    double actual;
    double simulated;
    double compare;
    double leesalee;
    double product;
  }
  aggregate;
  
  struct
  {
    long successes;
    long z_failure;
    long delta_failure;
    long slope_failure;
    long excluded_failure;
  }
  urbanization_attempt;
  
  int sidx;
  int ridx;
  
  /* link element for Cluster routine */
  typedef struct ugm_link
  {
    int row;
    int col;
  }
  ugm_link;
  
  struct ugm_link cir_q[SIZE_CIR_Q];
  
  //! Records the stat values.
  /*!
  */
  void Save (const Scenario & scene,
	     IGrid & ingrids,
	     const Proc & runinfo,
	     char *filename);

  //! Logs this Years Stats.
  /*!
  */
  void LogThisYearStats (FILE * fp);

  //! Calculates this year's Growth Rate.
  /*!
  */
  void CalGrowthRate ();

  //! Calculates the urban percentage for this year.
  /*!
  */
  void CalPercentUrban (int,
			int, 
			int);

  //! Calculates averages for each statistic.
  /*!
  */
  void CalAverages (const Scenario & scene,
		    int index);

  //! Writes out the Control Stats.
  /*!
  */
  void WriteControlStats (const Coeff & coeffs,
                          IGrid & ingrids,
			  Proc & runinfo,
                          char *filename);

  //! Outputs to the Stats Value File.
  /*!
  */
  void WriteStatsValLine (char *filename,
			  int run,
			  int year,
			  stats_val_t * ptr,
			  int index);
  
  //! Logs the Statistics Values.
  /*!
  */
  void LogStatVal (int run,
		   int year,
		   int index,
		   stats_val_t * ptr,
		   FILE * fp);
  
  void LogStatValHdr (FILE * fp);

  //! Computes the Statistics for this year and records them.
  /*!
  */  
  void ComputeThisYearStats (const Coeff & coeffs,  
			     IGrid & ingrids,
			     PGrid & pgrids);

  //! Sets this years growth pixel number.
  /*!
  */  
  void SetNumGrowthPixels (int val);

  //! Calculates the Leesalee value.
  /*!
  */  
  void CalLeesalee (const Proc & runinfo,       
		    IGrid & ingrids,           
		    PGrid & pgrids);            
  
  //! Processes the Growth Log.
  /*!
  */
  void ProcessGrowLog (IGrid & ingrids,         
		       const Proc & runinfo,    
		       const Scenario & scene,  
		       int run,                 
		       int year);               

  //! Performs Aggregate Calculations.
  /*!
  */  
  void DoAggregate (Scenario & scene,           
		    IGrid & ingrids,            
		    double fmatch);             
  
  //! Performs Regression Analysis.
  /*!
  */
  void DoRegressions (IGrid & ingrids);         
  
  //! Performs a Line Fit Regression.
  /*!
  */
  double linefit (double *dependent,            
		  double *independent,          
		  int number_of_observations);  

  //! Logs the Control Stats.
  /*!
  */
  void LogControlStats (const Coeff & coeffs,   
			Proc & runinfo,        
			FILE * fp);             

  //! Sets the Header for the control stats Log.
  /*!
  */
  void LogControlStatsHdr (FILE * fp);  

  //! Computes all the statistical Values.
  /*!
  */
  void compute_stats (IGrid & ingrids,                    
                      GRID_P Z,                           
                      GRID_P slp,                        
                      double *stats_area,                 
                      double *stats_edges,                
                      double *stats_clusters,             
                      double *stats_pop,                  
                      double *stats_xmean,                
                      double *stats_ymean,                
                      double *stats_average_slope,        
                      double *stats_rad,                  
                      double *stats_mean_cluster_size,    
                      GRID_P scratch_gif1,                
                      GRID_P scratch_gif2);               

  //! Computes Edge value.
  /*!
  */
  void edge (IGrid & ingrids,                     
             GRID_P Z,                            
             double *stats_area,                  
             double *stats_edges);

  //! Computes the circle value.
  /*!
  */                
  void circle (IGrid & ingrids,
               GRID_P Z,                          
               GRID_P slp,                        
               int stats_area,                   
               double *stats_xmean,               
               double *stats_ymean,               
               double *stats_average_slope,       
               double *stats_rad);

  //! Computes the cluster values.
  /*!
  */                
  void cluster (IGrid & ingrids,
		GRID_P Z,                         
		double *stats_clusters,           
		double *stats_pop,                
		double *stats_mean_cluster_size,  
		GRID_P scratch_gif1,              
		GRID_P scratch_gif2);             

  //! Removes valus from Stat arrays.
  /*!
  */
  void ClearStatsValArrays ();

  //! Computes the Base Statistics.
  /*!
  */
  void ComputeBaseStats (const Proc & runinfo,    
			 IGrid & ingrids);        
  
  //! Calculates the standard deviation for each statistic.
  /*!
  */
  void CalStdDev (const Scenario & scene,
		  int index);

  //! Computes the Leesalee value.
  /*!
  */
  void compute_leesalee (GRID_P Z,                      /* IN     */
                         GRID_P urban,                  /* IN     */
                         double *leesalee);             /* OUT    */
  

};

#endif


