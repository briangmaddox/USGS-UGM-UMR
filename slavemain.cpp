/*! \file slavemain.cpp
    \brief Main program for a slave mpi process.
    
    Loads all input files, sets up memory and runs calibration
    or prediction based on scenario file and command line arguments.
    Accepts coeffecients from the master to produce calibration data.
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
#include <fstream>


#ifdef CATCH_SIGNALS
//! Signal handling function catches signals during program.
/*! Catches pretty much all signals.
 */
void acatch (int signo);
#endif

//! Main entry point for the slave mpi process.
/*! Sets up simulation and accepts input from the master to
    produce calibration data.
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
  int buff[5];  //buffer for sending and recieving
  int maxsize(0);

  //init mpi
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

  //simulation data objects
  Proc runinfo;      //tracks information about the model running and setup
  Scenario scene(mpi_rank);    
  //this describes the models current scenerio info and
                     //setup
  Landclass lclasses(mpi_rank);
  // this is a simple object that keeps track of land
                     // classes
  Coeff coeffs(mpi_size, mpi_rank);      //the coeffienct object.
  IGrid ingrids;     //input grids
  ColorDirectory * colortable;  //the colortable for the model
  PGrid pgrids;      //temporary grids used during model
  Transition trans;  //the transition object.
  Stats    stats(mpi_rank,mpi_size);    //the stats object
  MathLib::RandomLEcuyerBD randomgen;  //the random number generator

 
  
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

  //parse the command line
  if (argc != 3)
  {
    EXIT(1);
  }
  if ((strcmp (argv[1], "predict")) &&
      (strcmp (argv[1], "calibrate")))
  {
    EXIT(1);
  }
  if (strcmp (argv[1], "predict") == 0)
  {
    MPI_Finalize(); //shutdown mpi and exit
    return 0;
  }
  if (strcmp (argv[1], "calibrate") == 0)
  {
    runinfo.SetProcessingType (CALIBRATING);
    strcpy (processing_str, "CALIBRATING");
  }

  //initialize the scene to the current state
  scene.init (argv[2]);
  
  //init the random seed
  random_seed = scene.GetRandomSeed ();


  //set up the landclass stuff
  lclasses.SetNumClasses (scene.GetNumLanduseClasses());
  for (i = 0; i < scene.GetNumLanduseClasses (); i++)
  {
    lclasses.SetGrayscale (i, scene.GetLanduseClassGrayscale (i));
    lclasses.SetName (i, scene.GetLanduseClassName (i));
    lclasses.SetType (i, scene.GetLanduseClassType (i));
    lclasses.SetColor (i, scene.GetLanduseClassColor (i));
  }

  //set the current run
  runinfo.SetCurrentRun (0);
 

  //setup the coeffs
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


  //set up the input grids
  ingrids.init(scene, runinfo);
   
  //initilize the memory
  mem_Init (scene, ingrids, pgrids);
  
  //initilize the land class
  if (scene.GetDoingLanduseFlag ())
  {
    lclasses.Init ();
    
  }

  //initilize the colortable
  if (!(colortable = new (std::nothrow) ColorDirectory(scene, lclasses)))
      throw std::bad_alloc();


  //read the input files
  ingrids.ReadFiles (scene);
  ingrids.ValidateGrids (lclasses, NULL);
  ingrids.NormalizeRoads ();
  ingrids.VerifyInputs (scene, NULL);
  

  //init the pgrids
  pgrids.Init ();

  //count the number of runs (shouldn't need this)
  runinfo.SetTotalRuns (coeffs);
  
  runinfo.SetLastMonteCarlo (scene.GetMonteCarloIterations () - 1);
  
  //check to see if we need the transition matrix
  if (scene.GetDoingLanduseFlag ())
  {
    trans.Init (ingrids, lclasses);
  }
  
  //comput base stats
  stats.Init (runinfo, ingrids);
  
  //set the number runs
  runinfo.SetNumRunsExecThisCPU (0);
  
  if(scene.GetWriteCoeffFileFlag())
    coeffs.CreateCoeffFile (scene.GetOutputDir());
  
  randomgen.reset(random_seed);

  //create the driver object
  //Give it refrences to all the working model structures
  Driver driver( runinfo, scene,
          lclasses, coeffs, ingrids, (*colortable),
          pgrids,  trans, stats, randomgen);
  
  //Set the stop year
  runinfo.SetStopYear (ingrids.GetUrbanYear (ingrids.GetUrbanCount () - 1));

  //ask the master for work
  MPI_Send(0, 0, MPI_PACKED, 0, WORK_MSG, MPI_COMM_WORLD);
  MPI_Recv(buff, 5, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  

  //loop until the master tells me to quit
  while ( status.MPI_TAG != QUIT_MSG )
  {
    
    runinfo.SetCurrentRun(buff[4]); //set the current run
    coeffs.SetCurrentDiffusion ((double) buff[0]);
    coeffs.SetCurrentSpread ((double) buff[1]);
    coeffs.SetCurrentBreed ((double) buff[2]);
    coeffs.SetCurrentSlopeResist ((double) buff[3]);

    for (road_gravity = coeffs.GetStartRoadGravity ();
         road_gravity <= coeffs.GetStopRoadGravity ();
         road_gravity += coeffs.GetStepRoadGravity ())
    {
            
      //set the road gravity
      coeffs.SetCurrentRoadGravity ((double) road_gravity );
      
      
      //run the simulation
      driver.drv_driver ();
      runinfo.IncrementNumRunsExecThisCPU ();
      
      runinfo.IncrementCurrentRun ();
      
    } // roads
    
    MPI_Send(0, 0, MPI_PACKED, 0, WORK_MSG, MPI_COMM_WORLD);
    MPI_Recv(buff, 5, MPI_INT, 0, MPI_ANY_TAG, 
             MPI_COMM_WORLD, &status);
    
  } // while ! quit
  
  
  MPI_Finalize ();
  

  return (0);
}


#ifdef CATCH_SIGNALS
//Implemnetations for the signal catching function.
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
