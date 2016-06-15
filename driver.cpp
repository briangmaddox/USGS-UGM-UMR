/*! \file driver.cpp
    \brief Implementation file for the driver object.
    
    Implementation file for the driver which will actually
    run the overal simulation given a set of coeffs.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include "driver.h"
#include "growth.h"

/*
 Simple constructor for passing the simulation state.
*/
Driver::Driver( Proc & inruninfo, Scenario & inscene,    
                Landclass & inlclasses, Coeff &incoeffs,
                IGrid & iningrids,  ColorDirectory & incolortable,
                PGrid & inpgrids,  Transition & intrans,
                Stats & instats,
                MathLib::RandomLEcuyerBD & inrandomgen)
  : runinfo(inruninfo), scene(inscene), lclasses(inlclasses),
  coeffs(incoeffs), ingrids(iningrids), colortable(incolortable),
    pgrids(inpgrids), trans(intrans), stats(instats),
    randomgen(inrandomgen)
{}

/*
  
   FUNCTION NAME: drv_driver
   PURPOSE:       main function for driving the simulation grw_growth()
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Driver::drv_driver () 
{
  char func[] = "drv_driver";
  char name[] = "_cumcolor_urban_";
  GRID_P sim_landuse_ptr;
  GRID_P z_cumulate_ptr;
  GRID_P cum_probability_ptr;
  GRID_P cum_uncertainty_ptr;
  GRID_P landuse1_ptr;
  int total_pixels;
  char filename[256];
  fmatch_t fmatch = 0.0;
 
  ImageIO imageout;

  total_pixels = mem_GetTotalPixels ();
  z_cumulate_ptr = pgrids.GetCumulatePtr ();
  sim_landuse_ptr = pgrids.GetLand1Ptr ();

  assert (total_pixels > 0);
  assert (z_cumulate_ptr != NULL);
  assert (sim_landuse_ptr != NULL);


  /*
    CREATE ANNUAL LANDUSE PROBABILITY FILE
   */
  if (runinfo.GetProcessingType () == PREDICTING)
  {
    if (scene.GetDoingLanduseFlag ())
    {
      lclasses.AnnualProbInit (scene);
    }
  }

  /*
   MONTE CARLO SIMULATION
   */
  drv_monte_carlo (z_cumulate_ptr, sim_landuse_ptr);

  if (runinfo.GetProcessingType () == PREDICTING)
  {
    /*
      OUTPUT URBAN IMAGES
     */
    sprintf (filename, "%scumulate_urban.gif", scene.GetOutputDir ());
    
    imageout.WriteGRID (z_cumulate_ptr,
                        colortable.GetColortable (GRAYSCALE_COLORTABLE),
                        scene,
                        ingrids,
                        filename,
                   "",
                   SEED_COLOR_INDEX);

    util_WriteZProbGrid (runinfo, scene, 
                         ingrids, colortable, z_cumulate_ptr, name);

    if (scene.GetDoingLanduseFlag ())
    {
      cum_probability_ptr = mem_GetWGridPtr (__FILE__, func, __LINE__);
      cum_uncertainty_ptr = mem_GetWGridPtr (__FILE__, func, __LINE__);
      assert (cum_probability_ptr != NULL);
      assert (cum_uncertainty_ptr != NULL);

      lclasses.BuildProbImage (cum_probability_ptr, cum_uncertainty_ptr, 
                               scene);

      /*
        OUTPUT CUMULATIVE PROBABILITY IMAGE
       */
      sprintf (filename, "%scumcolorlanduse.gif", scene.GetOutputDir ());
      imageout.WriteGRID (cum_probability_ptr,
                          colortable.GetColortable (LANDUSE_COLORTABLE),
                          scene,
                          ingrids,
                          filename,
                          "",
                          SEED_COLOR_INDEX);
      /*
       OUTPUT CUMULATIVE UNCERTAINTY IMAGE
       */
      sprintf (filename, "%suncertainty.landuse.gif", scene.GetOutputDir ());
      imageout.WriteGRID (cum_uncertainty_ptr,
                          colortable.GetColortable (GRAYSCALE_COLORTABLE),
                          scene,
                          ingrids,
                          filename,
                          "",
                          SEED_COLOR_INDEX);

      cum_probability_ptr = 
        mem_GetWGridFree (__FILE__, func, __LINE__, cum_probability_ptr);
      cum_uncertainty_ptr = 
        mem_GetWGridFree (__FILE__, func, __LINE__, cum_uncertainty_ptr);
    }
    /* end of:   if (scene.GetDoingLanduseFlag()) */
  }
  /* end of:    if(proc_GetProcessingType() == PREDICTING) */

  if ((!scene.GetDoingLanduseFlag ()) || 
      (runinfo.GetProcessingType () == PREDICTING))
  {
    fmatch = 0.0;
  }
  else
  {
    landuse1_ptr = ingrids.GetLanduseGridPtr (__FILE__, func, __LINE__, 1);
    fmatch = drv_fmatch (sim_landuse_ptr, landuse1_ptr);
    landuse1_ptr = ingrids.GridRelease 
      (__FILE__, func, __LINE__, landuse1_ptr);
  }

  stats.Analysis (coeffs, ingrids, runinfo, scene, fmatch);

  /* end of:  if(proc_GetProcessingType() == PREDICTING) */

 
}


/*
   FUNCTION NAME: drv_monte_carlo
   PURPOSE:       Monte Carlo loop
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/  
void Driver::drv_monte_carlo (GRID_P cumulate_ptr, GRID_P land1_ptr)
{
  int imc;
  int i;
  double *class_slope;
  double *ftransition;
  GRID_P z_ptr;
  int total_pixels;
  int num_monte_carlo;
  int *new_indices;

  class_slope = trans.GetClassSlope ();
  ftransition = trans.GetFTransition ();
  z_ptr = pgrids.GetZPtr ();
  total_pixels = mem_GetTotalPixels ();
  new_indices = lclasses.GetNewIndicesPtr ();
  num_monte_carlo = scene.GetMonteCarloIterations ();

  assert (total_pixels > 0);
  assert (land1_ptr != NULL);
  assert (z_ptr != NULL);
  assert (ftransition != NULL);
  assert (class_slope != NULL);
  assert (new_indices != NULL);
  assert (num_monte_carlo > 0);

  for (imc = 0; imc < scene.GetMonteCarloIterations (); imc++)
  {
    runinfo.SetCurrentMonteCarlo (imc);

    /*
      RESET THE PARAMETERS
     */
    coeffs.SetCurrentDiffusion (coeffs.GetSavedDiffusion ());
    coeffs.SetCurrentSpread (coeffs.GetSavedSpread ());
    coeffs.SetCurrentBreed (coeffs.GetSavedBreed ());
    coeffs.SetCurrentSlopeResist (coeffs.GetSavedSlopeResist ());
    coeffs.SetCurrentRoadGravity (coeffs.GetSavedRoadGravity ());


    /*
      RUN SIMULATION
     */
    stats.InitUrbanizationAttempts ();
    
    //need to pass the objects
    Growth grw(runinfo, scene,
           lclasses, coeffs,
           ingrids,  colortable,
           pgrids, trans,
           stats, randomgen);
    grw.grow (z_ptr, land1_ptr);
    

    /*
      UPDATE CUMULATE GRID
     */
    for (i = 0; i < total_pixels; i++)
    {
      if (z_ptr[i] > 0)
      {
        cumulate_ptr[i]++;
      }
    }

    /*
      UPDATE ANNUAL LAND CLASS PROBABILITIES
     */
    if (runinfo.GetProcessingType () == PREDICTING)
    {
      lclasses.AnnualProbUpdate (land1_ptr, scene);
    }

  }
  /*
   NORMALIZE CUMULATIVE URBAN IMAGE
   */
  for (i = 0; i < total_pixels; i++)
  {
    cumulate_ptr[i] = (100.0 * cumulate_ptr[i]) / num_monte_carlo;
  }

}

/*
   FUNCTION NAME: drv_fmatch
   PURPOSE:       calculate fmatch
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
fmatch_t Driver::drv_fmatch (GRID_P cum_probability_ptr,
                             GRID_P landuse1_ptr)
{
  int match_count;
  int trans_count;
  float fmatch;

  assert (cum_probability_ptr != NULL);
  if (scene.GetDoingLanduseFlag ())
  {
    assert (landuse1_ptr != NULL);
  }

  if (!scene.GetDoingLanduseFlag ())
  {
    fmatch = 1.0;
  }
  else
  {
    match_count = util_img_intersection (mem_GetTotalPixels (),
                                         cum_probability_ptr,
                                         landuse1_ptr);
    trans_count = mem_GetTotalPixels () - match_count;

    if ((match_count == 0) && (trans_count == 0))
    {
      fmatch = 0.0;
    }
    else
    {
      fmatch = (float) match_count / (match_count + trans_count);
    }
  }
 
  return fmatch;
}
