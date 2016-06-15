/*! \file growth.cpp
    \brief Implementation file for the growth object.
    
    Implementation file for the growth object which runs the
    deltatron and spread portions of the simultion.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "output.h"
#include "utilities.h"
#include "growth.h"
#include "spread.h"
#include "deltatron.h"


/*
 Constructor for class.
*/
Growth::Growth( Proc & inruninfo, Scenario & inscene,    
        Landclass & inlclasses, Coeff &incoeffs,
        IGrid & iningrids,  ColorDirectory & incolortable,
        PGrid & inpgrids,  Transition & intrans,
        Stats & instats,  MathLib::RandomLEcuyerBD & inrandomgen)
  : runinfo(inruninfo), scene(inscene),    
    lclasses(inlclasses), coeffs(incoeffs),
    ingrids(iningrids),  colortable(incolortable),
    pgrids(inpgrids),  trans(intrans),
    stats(instats), randomgen(inrandomgen)
{}


/*
   FUNCTION NAME: grow
   PURPOSE:       loop over simulated years
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Growth::grow (GRID_P z_ptr, GRID_P land1_ptr)
{
  char func[] = "grow";
  char gif_filename[MAX_FILENAME_LEN];
  char date_str[4];
  GRID_P deltatron_ptr;
  GRID_P seed_ptr;
  int total_pixels;
  float average_slope;
  int num_growth_pix = 0;
  int sng;
  int sdg;
  int sdc;
  int og;
  int rt;
  int pop;
  ImageIO imageout;


  total_pixels = mem_GetTotalPixels ();
  deltatron_ptr = pgrids.GetDeltatronPtr ();
  assert (total_pixels > 0);
  assert (deltatron_ptr != NULL);


  if (runinfo.GetProcessingType () == PREDICTING)
  {
    runinfo.SetCurrentYear (scene.GetPredictionStartDate ());
  }
  else
  {
    runinfo.SetCurrentYear(ingrids.GetUrbanYear (0));
  }
  util_init_grid (z_ptr, 0);
  if (scene.GetDoingLanduseFlag ())
  {
    
    landuse_init (deltatron_ptr,
                      land1_ptr);
  }

  seed_ptr = ingrids.GetUrbanGridPtr (__FILE__, func, __LINE__, 0);
  util_condition_gif (total_pixels,
                      seed_ptr,
                      GT,
                      0,
                      z_ptr,
                      PHASE0G);
  seed_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, seed_ptr);

  if (runinfo.GetProcessingType () == PREDICTING)
  {
    printf ("%s %u Monte Carlo = %u of %u\n", __FILE__, __LINE__,
    runinfo.GetCurrentMonteCarlo () + 1, scene.GetMonteCarloIterations ());
    printf ("%s %u proc_GetCurrentYear=%u\n",
             __FILE__, __LINE__, runinfo.GetCurrentYear ());
    printf ("%s %u proc_GetStopYear=%u\n\n",
             __FILE__, __LINE__, runinfo.GetStopYear ());
  }


  while (runinfo.GetCurrentYear () < runinfo.GetStopYear ())
  {
    /*
     
      INCREMENT CURRENT YEAR
     
     */
    runinfo.IncrementCurrentYear ();

    /*
     
      APPLY THE CELLULAR AUTOMATON RULES FOR THIS YEAR
     
     */
    sng = 0;
    sdg = 0;
    sdc = 0;
    og = 0;
    rt = 0;
    pop = 0;

    //again passing objects
    Spread spr(runinfo, scene,
         lclasses, coeffs,
         ingrids, colortable,
         pgrids, trans,
         stats, randomgen);
    spr.spread (&average_slope,
                &num_growth_pix,
                &sng,
                &sdc,
                &og,
                &rt,
                &pop,
                z_ptr);
    stats.SetSNG (sng);
    stats.SetSDG (sdg);
    stats.SetSDG (sdc);
    stats.SetOG (og);
    stats.SetRT (rt);
    stats.SetPOP (pop);

    if (scene.GetViewGrowthTypesFlag (runinfo))
    {
      sprintf (gif_filename, "%sz_growth_types_%u_%u_%u.gif",
               scene.GetOutputDir (), runinfo.GetCurrentRun (),
               runinfo.GetCurrentMonteCarlo (), runinfo.GetCurrentYear ());
      sprintf (date_str, "%u", runinfo.GetCurrentYear ());
      imageout.WriteGRID (z_ptr,
                          colortable.GetColortable (GROWTH_COLORTABLE),
                          scene, ingrids,
                          gif_filename,
                          date_str,
                          255);
    }

    if (scene.GetDoingLanduseFlag ())
    {
      landuse (land1_ptr, num_growth_pix);
    }
    else
    {
      non_landuse (z_ptr);
    }
    seed_ptr = ingrids.GetUrbanGridPtr (__FILE__, func, __LINE__, 0);
    util_condition_gif (total_pixels,
                        seed_ptr,
                        GT,
                        0,
                        z_ptr,
                        PHASE0G);
    seed_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, seed_ptr);

    /*
     
      DO STATISTICS
     
     */
    stats.Update (coeffs, ingrids, scene, runinfo, pgrids, num_growth_pix);

    /*
     
      DO SELF MODIFICATION
     
     */
    coeffs.SelfModication (scene.GetCriticalHigh(),
                           scene.GetCriticalLow(),
                           scene.GetSlopeSensitivity(),
                           scene.GetRdGrvtySensitivity(),
                           scene.GetBoom(),
                           scene.GetBust(),
                           stats.GetGrowthRate (), stats.GetPercentUrban ());
    if(scene.GetWriteCoeffFileFlag())
      coeffs.WriteCurrentCoeff ();
  }
}


/*
   FUNCTION NAME: landuse_init
   PURPOSE:       initial variables for doing landuse
   AUTHOR:
   PROGRAMMER:
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Growth::landuse_init (GRID_P deltatron_ptr,          /* OUT    */
                    GRID_P land1_ptr)                     /* OUT    */
{
  char func[] = "landuse_init";
  int i;
  int total_pixels;
  GRID_P landuse0_ptr;
  GRID_P landuse1_ptr;


  total_pixels = mem_GetTotalPixels ();
  assert (deltatron_ptr != NULL);
  assert (land1_ptr != NULL);
  assert (total_pixels > 0);
  /*
   
    INITIALIZE DELTATRON GRID TO ZERO
   
   */
  for (i = 0; i < total_pixels; i++)
  {
    deltatron_ptr[i] = 0;
  }
  /*
   
    IF PREDICTING USE LANDUSE 1 AS THE STARTING LANDUSE
    ELSE USE LANDUSE 0 AS THE STARTING LANDUSE
   
   */
  if (runinfo.GetProcessingType () == PREDICTING)
  {
    landuse1_ptr = ingrids.GetLanduseGridPtr (__FILE__, func, __LINE__, 1);
    assert (landuse1_ptr != NULL);
    for (i = 0; i < total_pixels; i++)
    {
      land1_ptr[i] = landuse1_ptr[i];
    }
    landuse1_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, landuse1_ptr);
  }
  else
  {
    landuse0_ptr = ingrids.GetLanduseGridPtr (__FILE__, func, __LINE__, 0);
    assert (landuse0_ptr != NULL);
    for (i = 0; i < total_pixels; i++)
    {
      land1_ptr[i] = landuse0_ptr[i];
    }
    landuse0_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, landuse0_ptr);
  }
}

/*
   FUNCTION NAME: landuse
   PURPOSE:       routine for handling landuse type of processing
   AUTHOR:
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Growth::landuse ( GRID_P land1_ptr,                       /* OUT    */
                       int num_growth_pix                      /* IN     */
                       )

{

  char func[] = "landuse";
  char gif_filename[MAX_FILENAME_LEN];
  char date_str[4];
  int ticktock;
  int landuse0_year;
  int landuse1_year;
  int urban_code;
  int *new_indices;
  Classes *landuse_classes;
  Classes *class_indices;
  GRID_P background_ptr;
  GRID_P grw_landuse_ws1;
  GRID_P deltatron_ptr;
  GRID_P z_ptr;
  GRID_P deltatron_workspace1;
  GRID_P slp_ptr;
  GRID_P land2_ptr;
  double *class_slope;
  double *ftransition;
  ImageIO imageout;
  

  ticktock = runinfo.GetCurrentYear ();
  landuse0_year = ingrids.GetLanduseYear (0);
  landuse1_year = ingrids.GetLanduseYear (1);
  urban_code = lclasses.GetUrbanCode ();
  new_indices = lclasses.GetNewIndicesPtr ();
  landuse_classes = lclasses.GetClassesPtr ();
  class_indices = lclasses.GetReducedClassesPtr ();
  background_ptr = ingrids.GetBackgroundGridPtr (__FILE__, func, __LINE__);
  grw_landuse_ws1 = mem_GetWGridPtr (__FILE__, func, __LINE__);
  deltatron_workspace1 = mem_GetWGridPtr (__FILE__, func, __LINE__);
  slp_ptr = ingrids.GetSlopeGridPtr (__FILE__, func, __LINE__);
  deltatron_ptr = pgrids.GetDeltatronPtr ();
  z_ptr = pgrids.GetZPtr ();
  land2_ptr = pgrids.GetLand2Ptr ();
  class_slope = trans.GetClassSlope ();
  ftransition = trans.GetFTransition ();

  assert (ticktock >= 0);
  assert (z_ptr != NULL);
  assert (urban_code > 0);
  assert (new_indices != NULL);
  assert (landuse_classes != NULL);
  assert (class_indices != NULL);
  assert (grw_landuse_ws1 != NULL);
  assert (deltatron_workspace1 != NULL);
  assert (deltatron_ptr != NULL);
  assert (land1_ptr != NULL);
  assert (land2_ptr != NULL);
  assert (slp_ptr != NULL);
  assert (class_slope != NULL);
  assert (ftransition != NULL);

  /* influence land use */
  if (ticktock >= landuse0_year)
  {

    /*
     
      PLACE THE NEW URBAN SIMULATION INTO THE LAND USE IMAGE
     
     */
    util_condition_gif (mem_GetTotalPixels (),
                        z_ptr,
                        GT,
                        0,
                        land1_ptr,
                        urban_code);
    Deltatron del (runinfo, scene,    
                   lclasses, coeffs,
                   ingrids, colortable,
                   pgrids, trans,
                   stats, randomgen);
    del.delta(new_indices,                            /* IN     */
              landuse_classes,                        /* IN     */
              class_indices,                          /* IN     */
              deltatron_workspace1,                   /* MOD    */
              deltatron_ptr,                          /* IN/OUT */
              land1_ptr,                              /* IN     */
              land2_ptr,                              /* OUT    */
              slp_ptr,                                /* IN     */
              num_growth_pix,                         /* IN     */
              class_slope,                            /* IN     */
              ftransition);                         /* IN     */

    /*
     
      SWITCH THE OLD AND THE NEW
     
     */
    util_copy_grid (land2_ptr,
                    land1_ptr);
  }

  if ((runinfo.GetProcessingType () == PREDICTING) ||
      (runinfo.GetProcessingType () == TESTING) &&
      (runinfo.GetLastMonteCarloFlag ()))
  {
    /*
     
      WRITE LAND1 GIF TO FILE
     
     */


    /* swicthed the next two line around, there is a memory problem
       that was placing a null character as the first character in the
       gif_filename causing the routine gdif_WriteGIF to terminate 
       incorrectly rp/mf
   was
    sprintf (gif_filename, "%s%s_land_n_urban.%u.gif",
    sprintf (date_str, "%u", proc_GetCurrentYear ());

    */

    sprintf (date_str, "%u", runinfo.GetCurrentYear ());
    sprintf (gif_filename, "%s%s_land_n_urban.%u.gif",
     scene.GetOutputDir (), ingrids.GetLocation (), runinfo.GetCurrentYear ());

    imageout.WriteGRID(land1_ptr,
                       colortable.GetColortable (LANDUSE_COLORTABLE),
                       scene, ingrids,
                       gif_filename,
                       date_str,
                       255);
  }

  /*
   
    COMPUTE FINAL MATCH STATISTIC FOR LANDUSE
   
   */
  if (runinfo.GetCurrentYear () == landuse1_year)
  {

    util_condition_gif (mem_GetTotalPixels (),
                        z_ptr,
                        GT,
                        0,
                        land1_ptr,
                        urban_code);
  }
  background_ptr =
    ingrids.GridRelease (__FILE__, func, __LINE__, background_ptr);
  grw_landuse_ws1 =
    mem_GetWGridFree (__FILE__, func, __LINE__, grw_landuse_ws1);
  deltatron_workspace1 =
    mem_GetWGridFree (__FILE__, func, __LINE__, deltatron_workspace1);
  slp_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, slp_ptr);
}

/*
   FUNCTION NAME: non_landuse
   PURPOSE:       routine for handling non landuse processing
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Growth::non_landuse (GRID_P z_ptr)
{
  char func[] = "non_landuse";
  char command[2 * MAX_FILENAME_LEN + 20];
  GRID_P workspace1;
  GRID_P workspace2;
  int num_monte_carlo;
  char name[] = "_urban_";
  char gif_filename[MAX_FILENAME_LEN];
  GRID_P cumulate_monte_carlo;
  int i;

 
  workspace1 = mem_GetWGridPtr (__FILE__, func, __LINE__);
  workspace2 = mem_GetWGridPtr (__FILE__, func, __LINE__);
  num_monte_carlo = scene.GetMonteCarloIterations ();

  assert (workspace1 != NULL);
  assert (workspace2 != NULL);
  assert (z_ptr != NULL);


  cumulate_monte_carlo = workspace1;

  if (runinfo.GetProcessingType () != CALIBRATING)
  {
    if (runinfo.GetCurrentMonteCarlo () == 0)
    {
      /*
       
        ZERO OUT THE ACCUMULATION GRID
       
       */

      util_init_grid (cumulate_monte_carlo, 0);
    }
    else
    {
      /*
       
        READ IN THE ACCUMULATION GRID
       
       */
      sprintf (gif_filename, "%scumulate_monte_carlo.year_%u",
               scene.GetOutputDir (), runinfo.GetCurrentYear ());
      inp_slurp (gif_filename,                               /* IN    */
                 cumulate_monte_carlo,                       /* OUT   */
                 memGetBytesPerGridRound ());              /* IN    */
    }
    /*
     
      ACCUMULATE Z OVER MONTE CARLOS
     
     */
    for (i = 0; i < mem_GetTotalPixels (); i++)
    {
      if (z_ptr[i] > 0)
      {
        cumulate_monte_carlo[i]++;
      }
    }


    if (runinfo.GetCurrentMonteCarlo () == num_monte_carlo - 1)
    {
      if (runinfo.GetProcessingType () == TESTING)
      {
        util_condition_gif (mem_GetTotalPixels (),           /* IN     */
                            z_ptr,                           /* IN     */
                            GT,                              /* IN     */
                            0,                               /* IN     */
                            cumulate_monte_carlo,            /* IN/OUT */
                            100);                          /* IN     */
      }
      else
      {

        /*
         
          NORMALIZE ACCULUMLATED GRID
         
         */
        for (i = 0; i < mem_GetTotalPixels (); i++)
        {
          cumulate_monte_carlo[i] =
            100 * cumulate_monte_carlo[i] / num_monte_carlo;
        }
      }
      util_WriteZProbGrid (runinfo, scene, ingrids, colortable,
                           cumulate_monte_carlo, name);
      if (runinfo.GetCurrentMonteCarlo () != 0)
      {
        sprintf (command, "rm %s", gif_filename);
        system (command);
      }
    }
    else
    {
      /*
       
        DUMP ACCULUMLATED GRID TO DISK
       
       */
      sprintf (gif_filename, "%scumulate_monte_carlo.year_%u",
               scene.GetOutputDir (), runinfo.GetCurrentYear ());
      out_dump (gif_filename,
                scene,
                cumulate_monte_carlo,
                memGetBytesPerGridRound ());
    }
  }

  workspace1 = mem_GetWGridFree (__FILE__, func, __LINE__, workspace1);
  workspace2 = mem_GetWGridFree (__FILE__, func, __LINE__, workspace2);
}



