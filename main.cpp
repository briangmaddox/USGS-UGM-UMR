/*! \file main.cpp
    \brief Main program for the master mpi process.
    
    Loads all input files, sets up memory and runs calibration
    or prediction based on scenario file and command line arguments.
    For credits see CREDITS.TXT
*/
#include <mpi.h>
#define CATCH_SIGNALS
#ifdef CATCH_SIGNALS
#include <signal.h>
#endif
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "coeff.h"
#include "igrid.h"
#include "output.h"
#include "utilities.h"
#include "driver.h"
#include "input.h"
#include "scenario.h"
#include "proc.h"
#include "landclass.h"
#include "pgrid.h"
#include "color.h"
#include "memory_obj.h"
#include "stats.h"
#include "transition.h"
#include "ugm_macros.h"
#include "messagetags.h"
#include <new>

//! Function to print program usage.
/*! Prints the program usage
 */
static void print_usage (char *binary);

#ifdef CATCH_SIGNALS
//! Signal handling function catches signals during program.
/*! Catches pretty much all signals.
 */
void acatch (int signo);
#endif

//! Main entry point for the master mpi process.
/*! Sets up simulation and runs the model.
 */
int
  main (int argc, char *argv[])
{

  char fname[MAX_FILENAME_LEN];
  char command[5 * MAX_FILENAME_LEN];
  int restart_run = 0;
  RANDOM_SEED_TYPE random_seed;
  int diffusion_coeff;
  int breed_coeff;
  int spread_coeff;
  int slope_resistance;
  int road_gravity;
  int restart_diffusion;
  int restart_breed;
  int restart_spread;
  int restart_slope_resistance;
  int restart_road_gravity;
  time_t tp;
  char processing_str[MAX_FILENAME_LEN];
  int i;
  MPI_Status status;
  int mpi_rank;
  int mpi_size;
  int buff[5];
  int roadcount(0);


  


  //Start up mpi
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);


  //objects used by the model
  Proc runinfo;      //tracks information about the model running and setup
  Scenario scene(mpi_rank);    
  //this describes the models current scenerio info and
                     //setup
  Landclass lclasses(mpi_rank);
                     // this is a simple object that keeps track of land
                     // classes
  Coeff coeffs(mpi_size,mpi_rank);      //the coeffienct object.
  IGrid ingrids;     //input grids
  ColorDirectory * colortable;  //the colortable for the model
  PGrid pgrids;      //temporary grids used during model
  Transition trans;  //the transition object.
  Stats    stats(mpi_rank,mpi_size);    //the stats object
  MathLib::RandomLEcuyerBD randomgen;  //the random number generator


  //signal catching routinues
#ifdef CATCH_SIGNALS
  struct sigaction act, oact;


  act.sa_handler = acatch;
  sigemptyset (&act.sa_mask);
  act.sa_flags = 0;
  sigaction (SIGFPE, &act, &oact);
  sigaction (SIGINT, &act, &oact);
  sigaction (SIGSEGV, &act, &oact);
  sigaction (SIGBUS, &act, &oact);
#endif

  //Parse the command line
  if (argc != 3)
  {
    print_usage (argv[0]);
  }
  if ((strcmp (argv[1], "predict")) &&
      (strcmp (argv[1], "calibrate")))
  {
    print_usage (argv[0]);
  }
  if (strcmp (argv[1], "predict") == 0)
  {
    runinfo.SetProcessingType(PREDICTING);
    strcpy (processing_str, "PREDICTING");
  }
  if (strcmp (argv[1], "calibrate") == 0)
  {
    runinfo.SetProcessingType (CALIBRATING);
    strcpy (processing_str, "CALIBRATING");
  }

  //initialize the scene to the current state
  scene.init (argv[2]);

  //get the random seed
  random_seed = scene.GetRandomSeed ();

  //set the landclasses
  lclasses.SetNumClasses (scene.GetNumLanduseClasses());
  for (i = 0; i < scene.GetNumLanduseClasses (); i++)
  {
    lclasses.SetGrayscale (i, scene.GetLanduseClassGrayscale (i));
    lclasses.SetName (i, scene.GetLanduseClassName (i));
    lclasses.SetType (i, scene.GetLanduseClassType (i));
    lclasses.SetColor (i, scene.GetLanduseClassColor (i));
  }

  //set the current run to 0
  runinfo.SetCurrentRun (0);
  
  //set the coeffs  
  coeffs.SetStartDiffusion (scene.GetCoeffDiffusionStart ());
  coeffs.SetStartSpread (scene.GetCoeffSpreadStart ());
  coeffs.SetStartBreed (scene.GetCoeffBreedStart ());
  coeffs.SetStartSlopeResist (scene.GetCoeffSlopeResistStart ());
  coeffs.SetStartRoadGravity (scene.GetCoeffRoadGravityStart ());

  coeffs.SetStopDiffusion (scene.GetCoeffDiffusionStop ());
  coeffs.SetStopSpread (scene.GetCoeffSpreadStop ());
  coeffs.SetStopBreed (scene.GetCoeffBreedStop ());
  coeffs.SetStopSlopeResist (scene.GetCoeffSlopeResistStop ());
  coeffs.SetStopRoadGravity (scene.GetCoeffRoadGravityStop ());

  coeffs.SetStepDiffusion (scene.GetCoeffDiffusionStep ());
  coeffs.SetStepSpread (scene.GetCoeffSpreadStep ());
  coeffs.SetStepBreed (scene.GetCoeffBreedStep ());
  coeffs.SetStepSlopeResist (scene.GetCoeffSlopeResistStep ());
  coeffs.SetStepRoadGravity (scene.GetCoeffRoadGravityStep ());

  coeffs.SetBestFitDiffusion (scene.GetCoeffDiffusionBestFit ());
  coeffs.SetBestFitSpread (scene.GetCoeffSpreadBestFit ());
  coeffs.SetBestFitBreed (scene.GetCoeffBreedBestFit ());
  coeffs.SetBestFitSlopeResist (scene.GetCoeffSlopeResistBestFit ());
  coeffs.SetBestFitRoadGravity (scene.GetCoeffRoadGravityBestFit ());

  //init the input grids
  ingrids.init(scene, runinfo);

  //Initilize the memory object
  mem_Init (scene, ingrids, pgrids);
  
  //Check for landuse stuff
  if (scene.GetDoingLanduseFlag ())
  {
    lclasses.Init ();
  }

  //set up the colortable stuff
  if (!(colortable = new (std::nothrow) ColorDirectory(scene, lclasses)))
      throw std::bad_alloc();

  //read the input grids
  ingrids.ReadFiles (scene);
  ingrids.ValidateGrids (lclasses, NULL);
  ingrids.NormalizeRoads ();
  ingrids.VerifyInputs (scene, NULL);
  
  //set up the pgrids
  pgrids.Init ();

  //count the number of runs that main does
  runinfo.SetTotalRuns (coeffs);

  //set the last monte carlo number
  runinfo.SetLastMonteCarlo (scene.GetMonteCarloIterations () - 1);
  
  //see if we need to compute the landuse transition matrix
  if (scene.GetDoingLanduseFlag ())
  {
    trans.Init (ingrids, lclasses);
  }
  
  //do base statitics
  stats.Init (runinfo, ingrids);


  runinfo.SetNumRunsExecThisCPU (0);
  //create calibration output files
  if (runinfo.GetCurrentRun () == 0 && mpi_rank == 0)
  {
    if (runinfo.GetProcessingType () != PREDICTING)
    {
      sprintf (fname, "%scontrol_stats_pe_0.log", scene.GetOutputDir ());
      stats.CreateControlFile (fname);
    }
    if (scene.GetWriteStdDevFileFlag ())
    {
      sprintf (fname, "%sstd_dev_pe_0.log", scene.GetOutputDir ());
      stats.CreateStatsValFile (fname);
    }
    if (scene.GetWriteAvgFileFlag ())
    {
      sprintf (fname, "%savg_pe_0.log", scene.GetOutputDir ());
      stats.CreateStatsValFile (fname);
    }
  }

  //create the coeffiention file
  if(scene.GetWriteCoeffFileFlag()) 
    coeffs.CreateCoeffFile (scene.GetOutputDir());
  
  //seed the random number generator
  randomgen.reset(random_seed);  

  //create the driver object
  //Give it refrences to all the working model structures
  Driver driver( runinfo, scene,
          lclasses, coeffs, ingrids, (*colortable),
          pgrids,  trans, stats, randomgen);
  
  //check to see if we are predicting
  if (runinfo.GetProcessingType () == PREDICTING)
  {
    //set the year and coeff and go!
    runinfo.SetStopYear (scene.GetPredictionStopDate ());
    coeffs.SetCurrentDiffusion ((double) coeffs.GetBestFitDiffusion ());
    coeffs.SetCurrentSpread ((double) coeffs.GetBestFitSpread ());
    coeffs.SetCurrentBreed ((double) coeffs.GetBestFitBreed ());
    coeffs.SetCurrentSlopeResist ((double) coeffs.GetBestFitSlopeResist ());
    coeffs.SetCurrentRoadGravity ((double) coeffs.GetBestFitRoadGravity ());
    driver.drv_driver ();
  }
  else
  {
    //count the number of road incremnet
    for (road_gravity = coeffs.GetStartRoadGravity ();
         road_gravity <= coeffs.GetStopRoadGravity ();
         road_gravity += coeffs.GetStepRoadGravity ())
    {
      ++roadcount;
    }
    //we are calibrating
    runinfo.SetStopYear (ingrids.GetUrbanYear (ingrids.GetUrbanCount () - 1));


    for (diffusion_coeff = coeffs.GetStartDiffusion ();
         diffusion_coeff <= coeffs.GetStopDiffusion ();
         diffusion_coeff += coeffs.GetStepDiffusion ())
    {
      for (breed_coeff = coeffs.GetStartBreed ();
           breed_coeff <= coeffs.GetStopBreed ();
           breed_coeff += coeffs.GetStepBreed ())
      {
        for (spread_coeff = coeffs.GetStartSpread ();
             spread_coeff <= coeffs.GetStopSpread ();
             spread_coeff += coeffs.GetStepSpread ())
        {
          for (slope_resistance = coeffs.GetStartSlopeResist ();
               slope_resistance <= coeffs.GetStopSlopeResist ();
               slope_resistance += coeffs.GetStepSlopeResist ())
          {
            //recieve from the slave
            MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
                         MPI_COMM_WORLD, &status);
            //pack the coeffiencts into a buffer and send the buffer
            buff[0] = diffusion_coeff;
            buff[1] = breed_coeff;
            buff[2] = spread_coeff;
            buff[3] = slope_resistance;
            buff[4] = runinfo.GetCurrentRun(); //send the run number too.
            //send the buffer
            MPI_Send(buff, 5, MPI_INT, status.MPI_SOURCE, WORK_MSG,
                     MPI_COMM_WORLD);

            //output current status
            printf ("\n%s %u ******************************************\n",
                    __FILE__, __LINE__);
            printf ("%s %u Run = %u of %u (%8.1f percent complete)\n",
                    __FILE__, __LINE__,
                    runinfo.GetCurrentRun (),
                    runinfo.GetTotalRuns (),
                    (100.0 * runinfo.GetCurrentRun ()) / 
                    runinfo.GetTotalRuns ());
            //increment the current run
            runinfo.SetCurrentRun(runinfo.GetCurrentRun() + roadcount);
                                  

          }
        }
      }
    }
  }
  
  if (runinfo.GetProcessingType () != PREDICTING)
  {
    //just for looks...
    printf ("\n%s %u ******************************************\n",
            __FILE__, __LINE__);
    printf ("%s %u Run = %u of %u (%8.1f percent complete)\n",
            __FILE__, __LINE__,
            runinfo.GetCurrentRun (),
            runinfo.GetTotalRuns (),
            (100.0 * runinfo.GetCurrentRun ()) / runinfo.GetTotalRuns ());
  }
  
  //slave termination
  for(i = 1; i < mpi_size; ++i)
  {
    //wait for the slave to ask for more work.
    MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
             MPI_COMM_WORLD, &status);
    //tell the slave to terminate
    MPI_Send(0, 0, MPI_PACKED, status.MPI_SOURCE, QUIT_MSG , MPI_COMM_WORLD);
  }
  
  //concatenate the files into one file
  if (scene.GetWriteCoeffFileFlag ())
  {
    coeffs.ConcatenateFiles (scene.GetWriteCoeffFileFlag(),
                             scene.GetOutputDir());
  }
  if (scene.GetWriteAvgFileFlag ())
  {
    stats.ConcatenateAvgFiles (scene);
  }
  if (scene.GetWriteStdDevFileFlag ())
  {
    stats.ConcatenateStdDevFiles (scene);
  }
  if (runinfo.GetProcessingType () != PREDICTING)
  {
    stats.ConcatenateControlFiles (scene);
  }


  if (scene.GetPostprocessingFlag ())
  {
    //check to see if we should produce the animated file
    if (strlen (scene.GetWhirlgifBinary ()) > 0)
    {
      if (scene.GetViewDeltatronAgingFlag (runinfo))
      {
        sprintf (command,
                 "%s -time 100 -o %sanimated_deltatron.gif %sdeltatron_*.gif",
                 scene.GetWhirlgifBinary (), scene.GetOutputDir (),
                 scene.GetOutputDir ());
        system (command);
      }
      if (scene.GetViewGrowthTypesFlag (runinfo))
      {
        sprintf (command,
                 "%s -time 100 -o %sanimated_z_growth.gif %sz_growth_types_*.gif",
                 scene.GetWhirlgifBinary (), scene.GetOutputDir (),
                 scene.GetOutputDir ());
        system (command);
      }
      if (runinfo.GetProcessingType () != CALIBRATING)
      {
        if (scene.GetDoingLanduseFlag ())
        {
          sprintf (command,
                   "%s -time 100 -o %sanimated_land_n_urban.gif %s*_land_n_urban*.gif",
                   scene.GetWhirlgifBinary (), scene.GetOutputDir (),
                   scene.GetOutputDir ());
          system (command);
        }
        else
        {
          sprintf (command,
                   "%s -time 100 -o %sanimated_urban.gif %s*_urban_*.gif",
                   scene.GetWhirlgifBinary (),
                   scene.GetOutputDir (), scene.GetOutputDir ());
          system (command);
        }
      }
    }
  }

  //shutdown mpi
  MPI_Finalize ();



  return (0);
}

//Implemnation for the print usage function
static void
  print_usage (char *binary)
{
  printf ("Usage:\n");
  printf ("%s <mode> <scenario file>\n", binary);
  printf ("Allowable modes are:\n");
  printf ("  calibrate\n");
  printf ("  predict\n");
  EXIT (1);
}
#ifdef CATCH_SIGNALS


//Implemntation for the signal catching function.
void
  acatch (int signo)
{
  if (signo == SIGBUS)
  {
    printf ("%s %u caught signo SIGBUS : bus error\n",
            __FILE__, __LINE__);
    EXIT (1);
  }
  if (signo == SIGSEGV)
  {
    printf ("%s %u caught signo SIGSEGV : Invalid storage access\n",
            __FILE__, __LINE__);
    EXIT (1);
  }
  if (signo == SIGINT)
  {
    printf ("%s %u caught signo SIGINT : Interrupt\n",
            __FILE__, __LINE__);
    EXIT(1);
  }
  if (signo == SIGFPE)
  {
    printf ("%s %u caught signo SIGFPE : Floating-point exception\n",
            __FILE__, __LINE__);
    EXIT (1);
  }
  printf ("%s %u caught signo %d\n", __FILE__, __LINE__, signo);
  EXIT (1);
}
#endif
