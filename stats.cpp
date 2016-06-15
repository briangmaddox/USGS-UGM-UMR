
#include "stats.h"

/*! \file stats.cpp
    \brief Code for stats.h

     Source code for functions in stats.h 
     For credits, see SREDITS.TXT in this directory.
     \sa CREDITS.TXT
*/

char *stats_val_t_names[] = {
  "sng",
  "sdg",
  "sdc",
  "og",
  "rt",
  "pop",
  "area",
  "edges",
  "clusters",
  "xmean",
  "ymean",
  "rad",
  "slope",
  "cl_size",
  "diffus",
  "spread",
  "breed",
  "slp_res",
  "rd_grav",
  "%urban",
  "%road",
  "grw_rate",
  "leesalee",
  "grw_pix"
};

/*
 FUNCTION NAME:
 PURPOSE:      Initialize stats object
 AUTHOR:       UMR group
 PROGRAMMER:  
 CREATION DATE: 11/11/2001
 DESCRIPTION:


*/
Stats::Stats(int inmpi_rank, int inmpi_size) : mpi_rank(inmpi_rank), mpi_size(inmpi_size)
{}

/*
 FUNCTION NAME:
 PURPOSE:
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats::ConcatenateControlFiles (const Scenario & scene)
{
  char line[MAX_LINE_LEN];
  char source_file[MAX_FILENAME_LEN];
  char destination_file[MAX_FILENAME_LEN];
  char command[2 * MAX_FILENAME_LEN + 20];
  FILE *fp;
  FILE *source_fp;
  int line_count;
  int i;
  char msg_buf[MAX_FILENAME_LEN]; 

  sprintf (destination_file, "%scontrol_stats.log", scene.GetOutputDir ());
  sprintf (source_file, "%scontrol_stats_pe_%u.log", scene.GetOutputDir (), 0);
  sprintf (command, "mv %s %s", source_file, destination_file);
  system (command);
  
  FILE_OPEN (fp, destination_file, "a");
  for (i = 1; i < mpi_size; i++)
  {
    sprintf (source_file, 
             "%scontrol_stats_pe_%u.log", scene.GetOutputDir (), i);

    FILE_OPEN (source_fp, source_file, "r");

    line_count = 0;
    while (fgets (line, MAX_LINE_LEN, source_fp) != NULL)
    {
      line_count++;
      if (line_count <= 2)
        continue;
      fputs (line, fp);
    }
    fclose (source_fp);
    sprintf (command, "rm %s", source_file);
    system (command);

  }
  fclose (fp);

  //sort the file
  sprintf(source_file, "%stest.temp", scene.GetOutputDir());
  //sort on second column
  sprintf(command, "sort -g -k2 %s -o %s", destination_file, source_file);
  system(command);
  sprintf(command, "mv %s %s", source_file, destination_file);
  system(command);



 
}

/*
 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: ConcatenateStdDevFiles (const Scenario & scene)
{
  char line[MAX_LINE_LEN];
  char source_file[MAX_FILENAME_LEN];
  char destination_file[MAX_FILENAME_LEN];
  char command[2 * MAX_FILENAME_LEN + 20];
  FILE *fp;
  FILE *source_fp;
  int line_count;
  int i;
  char msg_buf[MAX_FILENAME_LEN]; 

  sprintf (destination_file, "%sstd_dev.log", scene.GetOutputDir ());
  sprintf (source_file, "%sstd_dev_pe_%u.log", scene.GetOutputDir (), 0);
  sprintf (command, "mv %s %s", source_file, destination_file);
  system (command);
  
  FILE_OPEN (fp, destination_file, "a");
  for (i = 1; i < mpi_size; i++)
  {
    sprintf (source_file, "%sstd_dev_pe_%u.log", scene.GetOutputDir (), i);

    FILE_OPEN (source_fp, source_file, "r");

    line_count = 0;
    while (fgets (line, MAX_LINE_LEN, source_fp) != NULL)
    {
      line_count++;
      if (line_count <= 1)
        continue;
      fputs (line, fp);
    }
    fclose (source_fp);
    sprintf (command, "rm %s", source_file);
    system (command);

  }
  fclose (fp);

  //sort the file
  sprintf(source_file, "%stest.temp", scene.GetOutputDir());
  sprintf(command, "sort -g %s -o %s", destination_file, source_file);
  system(command);
  sprintf(command, "mv %s %s", source_file, destination_file);
  system(command);

}

/*
 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: ConcatenateAvgFiles (const Scenario & scene)
{
  char line[MAX_LINE_LEN];
  char source_file[MAX_FILENAME_LEN];
  char destination_file[MAX_FILENAME_LEN];
  char command[2 * MAX_FILENAME_LEN + 20];
  FILE *fp;
  FILE *source_fp;
  int line_count;
  int i;
  char msg_buf[MAX_FILENAME_LEN]; 

  sprintf (destination_file, "%savg.log", scene.GetOutputDir ());
  sprintf (source_file, "%savg_pe_%u.log", scene.GetOutputDir (), 0);
  sprintf (command, "mv %s %s", source_file, destination_file);
  system (command);
  

  FILE_OPEN (fp, destination_file, "a");
  for (i = 1; i < mpi_size; i++)
  {
    sprintf (source_file, "%savg_pe_%u.log", scene.GetOutputDir (), i);

    FILE_OPEN (source_fp, source_file, "r");

    line_count = 0;
    while (fgets (line, MAX_LINE_LEN, source_fp) != NULL)
    {
      line_count++;
      if (line_count <= 1)
        continue;
      fputs (line, fp);
    }
    fclose (source_fp);
    sprintf (command, "rm %s", source_file);
    system (command);

  }
  fclose (fp);

  //sort the file
  sprintf(source_file, "%stest.temp", scene.GetOutputDir());
  sprintf(command, "sort -g %s -o %s", destination_file, source_file);
  system(command);
  sprintf(command, "mv %s %s", source_file, destination_file);
  system(command);


}
/*
 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

#include "memory_obj.h"


void Stats :: Update (const Coeff & coeffs, IGrid & ingrids, const Scenario & scene, 
                      const Proc & runinfo, PGrid & pgrids, 
                      int num_growth_pix)
{
  char filename[MAX_FILENAME_LEN];
  int total_pixels;
  int road_pixel_count;
  int excluded_pixel_count;

  total_pixels = mem_GetTotalPixels ();
  road_pixel_count = ingrids.GetIGridRoadPixelCount (runinfo.GetCurrentYear ());
  excluded_pixel_count = ingrids.GetIGridExcludedPixelCount ();

  ComputeThisYearStats (coeffs, ingrids, pgrids);
  SetNumGrowthPixels (num_growth_pix);
  CalGrowthRate ();
  CalPercentUrban (total_pixels, road_pixel_count, excluded_pixel_count);

  if (ingrids.TestForUrbanYear (runinfo.GetCurrentYear ()))
  {
    CalLeesalee (runinfo, ingrids, pgrids);
    sprintf (filename, "%sgrow_%u_%u_%d.log",
    scene.GetOutputDir (), runinfo.GetCurrentRun (),
             runinfo.GetCurrentYear (), mpi_rank);
    Save (scene, ingrids, runinfo, filename);
  }
  if (runinfo.GetProcessingType () == PREDICTING)
  {
    sprintf (filename, "%sgrow_%u_%u_%d.log", scene.GetOutputDir (),
             runinfo.GetCurrentRun (), runinfo.GetCurrentYear (),
             mpi_rank);
    Save (scene, ingrids, runinfo, filename);
  }
}
/*
 FUNCTION NAME:
 PURPOSE:
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: Init (const Proc & runinfo, IGrid & ingrids)
{
  static bool first_call = TRUE;

  ClearStatsValArrays ();
  if (first_call)
  {
    ComputeBaseStats (runinfo, ingrids);
    first_call = FALSE;
  }
}

/*
 FUNCTION NAME:
 PURPOSE:
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: CalStdDev (const Scenario & scene, int index)
{
#define SD(val) pow(((val)*(val)/total_monte_carlo),0.5)
  int total_monte_carlo;

  total_monte_carlo = scene.GetMonteCarloIterations ();

  std_dev[index].sng = SD (record.this_year.sng - average[index].sng);
  std_dev[index].sdg = SD (record.this_year.sdg - average[index].sdg);
  std_dev[index].sdc = SD (record.this_year.sdc - average[index].sdc);
  std_dev[index].og = SD (record.this_year.og - average[index].og);
  std_dev[index].rt = SD (record.this_year.rt - average[index].rt);
  std_dev[index].pop = SD (record.this_year.pop - average[index].pop);
  std_dev[index].area = SD (record.this_year.area - average[index].area);
  std_dev[index].edges = SD (record.this_year.edges - average[index].edges);
  std_dev[index].clusters =
    SD (record.this_year.clusters - average[index].clusters);
  std_dev[index].xmean = SD (record.this_year.xmean - average[index].xmean);
  std_dev[index].ymean = SD (record.this_year.ymean - average[index].ymean);
  std_dev[index].rad = SD (record.this_year.rad - average[index].rad);
  std_dev[index].slope = SD (record.this_year.slope - average[index].slope);
  std_dev[index].mean_cluster_size =
    SD (record.this_year.mean_cluster_size - average[index].mean_cluster_size);
  std_dev[index].diffusion =
    SD (record.this_year.diffusion - average[index].diffusion);
  std_dev[index].spread = SD (record.this_year.spread - average[index].spread);
  std_dev[index].breed = SD (record.this_year.breed - average[index].breed);
  std_dev[index].slope_resistance =
    SD (record.this_year.slope_resistance - average[index].slope_resistance);
  std_dev[index].road_gravity =
    SD (record.this_year.road_gravity - average[index].road_gravity);
  std_dev[index].percent_urban =
    SD (record.this_year.percent_urban - average[index].percent_urban);
  std_dev[index].percent_road =
    SD (record.this_year.percent_road - average[index].percent_road);
  std_dev[index].growth_rate =
    SD (record.this_year.growth_rate - average[index].growth_rate);
  std_dev[index].leesalee =
    SD (record.this_year.leesalee - average[index].leesalee);
  std_dev[index].num_growth_pix =
    SD (record.this_year.num_growth_pix - average[index].num_growth_pix);
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: CalAverages (const Scenario & scene, int index)
{
  int total_monte_carlo;

  total_monte_carlo = scene.GetMonteCarloIterations ();

  average[index].sng = running_total[index].sng / total_monte_carlo;
  average[index].sdg = running_total[index].sdg / total_monte_carlo;
  average[index].sdc = running_total[index].sdc / total_monte_carlo;
  average[index].og = running_total[index].og / total_monte_carlo;
  average[index].rt = running_total[index].rt / total_monte_carlo;
  average[index].pop = running_total[index].pop / total_monte_carlo;
  average[index].area = running_total[index].area / total_monte_carlo;
  average[index].edges = running_total[index].edges / total_monte_carlo;
  average[index].clusters = running_total[index].clusters / total_monte_carlo;
  average[index].xmean = running_total[index].xmean / total_monte_carlo;
  average[index].ymean = running_total[index].ymean / total_monte_carlo;
  average[index].rad = running_total[index].rad / total_monte_carlo;
  average[index].slope = running_total[index].slope / total_monte_carlo;
  average[index].mean_cluster_size =
    running_total[index].mean_cluster_size / total_monte_carlo;
  average[index].diffusion =
    running_total[index].diffusion / total_monte_carlo;
  average[index].spread = running_total[index].spread / total_monte_carlo;
  average[index].breed = running_total[index].breed / total_monte_carlo;
  average[index].slope_resistance =
    running_total[index].slope_resistance / total_monte_carlo;
  average[index].road_gravity =
    running_total[index].road_gravity / total_monte_carlo;
  average[index].percent_urban =
    running_total[index].percent_urban / total_monte_carlo;
  average[index].percent_road =
    running_total[index].percent_road / total_monte_carlo;
  average[index].growth_rate =
    running_total[index].growth_rate / total_monte_carlo;
  average[index].leesalee = running_total[index].leesalee / total_monte_carlo;
  average[index].num_growth_pix =
    running_total[index].num_growth_pix / total_monte_carlo;
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: UpdateRunningTotal (int index)
{


  running_total[index].sng += record.this_year.sng;
  running_total[index].sdg += record.this_year.sdg;
  running_total[index].sdc += record.this_year.sdc;
  running_total[index].og += record.this_year.og;
  running_total[index].rt += record.this_year.rt;
  running_total[index].pop += record.this_year.pop;
  running_total[index].area += record.this_year.area;
  running_total[index].edges += record.this_year.edges;
  running_total[index].clusters += record.this_year.clusters;
  running_total[index].xmean += record.this_year.xmean;
  running_total[index].ymean += record.this_year.ymean;
  running_total[index].rad += record.this_year.rad;
  running_total[index].slope += record.this_year.slope;
  running_total[index].mean_cluster_size += record.this_year.mean_cluster_size;
  running_total[index].diffusion += record.this_year.diffusion;
  running_total[index].spread += record.this_year.spread;
  running_total[index].breed += record.this_year.breed;
  running_total[index].slope_resistance += record.this_year.slope_resistance;
  running_total[index].road_gravity += record.this_year.road_gravity;
  running_total[index].percent_urban += record.this_year.percent_urban;
  running_total[index].percent_road += record.this_year.percent_road;
  running_total[index].growth_rate += record.this_year.growth_rate;
  running_total[index].leesalee += record.this_year.leesalee;
  running_total[index].num_growth_pix += record.this_year.num_growth_pix;
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: ClearStatsValArrays ()
{

  int i;

  for (i = 0; i < MAX_URBAN_YEARS; i++)
  {
    memset ((void *) (&running_total[i]), 0, sizeof (stats_val_t));
    memset ((void *) (&average[i]), 0, sizeof (stats_val_t));
    memset ((void *) (&std_dev[i]), 0, sizeof (stats_val_t));
  }
  memset ((void *) (&regression), 0, sizeof (stats_info));
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: GetLeesalee ()
{
  return record.this_year.leesalee;
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: CalLeesalee (const Proc & runinfo, IGrid & ingrids, PGrid & pgrids)
{
  char func[] = "stats_CalLeesalee";
  GRID_P z_ptr;
  GRID_P urban_ptr;

  z_ptr = pgrids.GetZPtr ();
  urban_ptr = ingrids.GetUrbanGridPtrByYear (__FILE__, func,
                                       __LINE__, runinfo.GetCurrentYear ());
  record.this_year.leesalee = 1.0;
  if (runinfo.GetProcessingType () != PREDICTING)
  {
    compute_leesalee (z_ptr,                         /* IN     */
		      urban_ptr,                     /* IN     */
		      &record.this_year.leesalee);   /* OUT    */
  }
  urban_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, urban_ptr);

}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetNumGrowthPixels (int val)
{
  record.this_year.num_growth_pix = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
int Stats :: GetNumGrowthPixels ()
{
  return static_cast<int>(record.this_year.num_growth_pix);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: SetPercentUrban (int val)
{
  record.this_year.percent_urban = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: CalPercentUrban (int total_pixels, int road_pixels, int excld_pixels)
{
  record.this_year.percent_urban =
    (double) (100.0 * (record.this_year.pop + road_pixels) /
              (total_pixels - road_pixels - excld_pixels));
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: GetPercentUrban ()
{
  return record.this_year.percent_urban;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: CalGrowthRate ()
{
  record.this_year.growth_rate =
    record.this_year.num_growth_pix / record.this_year.pop * 100.0;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: GetGrowthRate ()
{
  return record.this_year.growth_rate;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/


void Stats :: SetSNG (int val)
{
  record.this_year.sng = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetSDG (int val)
{
  record.this_year.sdg = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetOG (int val)
{
  record.this_year.og = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetRT (int val)
{
  record.this_year.rt = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetPOP (int val)
{
  record.this_year.pop = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

int Stats :: GetSNG ()
{
  return static_cast<int>(record.this_year.sng);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
int Stats :: GetSDG ()
{
  return static_cast<int>(record.this_year.sdg);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
int Stats :: GetOG ()
{
  return static_cast<int>(record.this_year.og);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
int Stats :: GetRT ()
{
  return static_cast<int>(record.this_year.rt);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
int Stats :: GetPOP ()
{
  return static_cast<int>(record.this_year.pop);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: SetArea (int val)
{
  record.this_year.area = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetEdges (int val)
{
  record.this_year.edges = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetClusters (int val)
{
  record.this_year.clusters = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetPop (int val)
{
  record.this_year.pop = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetXmean (double val)
{
  record.this_year.xmean = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetYmean (double val)
{
  record.this_year.ymean = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetRad (double val)
{
  record.this_year.rad = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetAvgSlope (double val)
{
  record.this_year.slope = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: SetMeanClusterSize (double val)
{
  record.this_year.mean_cluster_size = val;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

int Stats :: GetArea ()
{
  return static_cast<int>(record.this_year.area);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
int Stats :: GetEdges ()
{
  return static_cast<int>(record.this_year.edges);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
int Stats :: GetClusters ()
{
  return static_cast<int>(record.this_year.clusters);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
int Stats :: GetPop ()
{
  return static_cast<int>(record.this_year.pop);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: GetXmean ()
{
  return record.this_year.xmean;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: GetYmean ()
{
  return record.this_year.ymean;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: GetRad ()
{
  return record.this_year.rad;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: GetAvgSlope ()
{
  return record.this_year.slope;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: GetMeanClusterSize ()
{
  return record.this_year.mean_cluster_size;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: ComputeThisYearStats (const Coeff & coeffs, IGrid & ingrids, PGrid & pgrids)
{
  char func[] = "stats_ComputeThisYearStats";
  int total_pixels;
  GRID_P z_ptr;
  GRID_P slope_ptr;
  GRID_P stats_workspace1;
  GRID_P stats_workspace2;
  double area;
  double edges;
  double clusters;
  double pop;
  double xmean;
  double ymean;
  double slope;
  double rad;
  double mean_cluster_size;

  total_pixels = mem_GetTotalPixels ();
  assert (total_pixels > 0);
  z_ptr = pgrids.GetZPtr ();
  assert (z_ptr != NULL);

  slope_ptr = ingrids.GetSlopeGridPtr (__FILE__, func, __LINE__);
  stats_workspace1 = mem_GetWGridPtr (__FILE__, func, __LINE__);
  stats_workspace2 = mem_GetWGridPtr (__FILE__, func, __LINE__);

  compute_stats (ingrids, 
                 z_ptr,                                /* IN     */
                       slope_ptr,                            /* IN     */
                       &area,                                /* OUT    */
                       &edges,                               /* OUT    */
                       &clusters,                            /* OUT    */
                       &pop,                                 /* OUT    */
                       &xmean,                               /* OUT    */
                       &ymean,                               /* OUT    */
                       &slope,                               /* OUT    */
                       &rad,                                 /* OUT    */
                       &mean_cluster_size,                   /* OUT    */
                       stats_workspace1,                     /* MOD    */
                       stats_workspace2);                  /* MOD    */
  record.this_year.area = area;
  record.this_year.edges = edges;
  record.this_year.clusters = clusters;
  record.this_year.pop = pop;
  record.this_year.xmean = xmean;
  record.this_year.ymean = ymean;
  record.this_year.slope = slope;
  record.this_year.rad = rad;
  record.this_year.mean_cluster_size = mean_cluster_size;
  record.this_year.diffusion = coeffs.GetCurrentDiffusion ();
  record.this_year.spread = coeffs.GetCurrentSpread ();
  record.this_year.breed = coeffs.GetCurrentBreed ();
  record.this_year.slope_resistance = coeffs.GetCurrentSlopeResist ();
  record.this_year.road_gravity = coeffs.GetCurrentRoadGravity ();

  slope_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, slope_ptr);
  stats_workspace1 = mem_GetWGridFree (__FILE__, func, __LINE__,
                                       stats_workspace1);
  stats_workspace2 = mem_GetWGridFree (__FILE__, func, __LINE__,
                                       stats_workspace2);


}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: CreateControlFile (char *filename)
{
  FILE *fp;
  char msg_buf[MAX_FILENAME_LEN]; 

  FILE_OPEN (fp, filename, "w");

  LogControlStatsHdr (fp);
  fclose (fp);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: CreateStatsValFile (char *filename)
{
  FILE *fp;
  char msg_buf[MAX_FILENAME_LEN]; 
  FILE_OPEN (fp, filename, "w");

  LogStatValHdr (fp);
  fclose (fp);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: WriteStatsValLine (char *filename, int run, int year,
                           stats_val_t * stats_ptr, int index)
{
  FILE *fp;
  char msg_buf[MAX_FILENAME_LEN]; 
  
  FILE_OPEN (fp, filename, "a");

  LogStatVal (run, year, index, &(stats_ptr[index]), fp);
  fclose (fp);
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: LogStatValHdr (FILE * fp)
{
#if 1
  int i;
  int num_elements;
  num_elements = sizeof (stats_val_t) / sizeof (double);
  fprintf (fp, "  run year index");
  for (i = 0; i < num_elements; i++)
  {
    fprintf (fp, "%8s ", stats_val_t_names[i]);
  }
  fprintf (fp, "\n");
#else
  fprintf (fp, "\n");
  fprintf (fp, "  run year index  area    edges clusters      pop    xmean");
  fprintf (fp, "    ymean      rad    slope cluster_size  sng      sdg");
  fprintf (fp, "      sdc       og       rt      pop\n");
#endif
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: LogStatVal (int run, int year, int index,
                    stats_val_t * stats_ptr, FILE * fp)
{
  int i;
  int num_elements;
  double *ptr;

  /*num_elements = sizeof(struct stats_val_t)/sizeof(double); */
  num_elements = sizeof (stats_val_t) / sizeof (double);
  ptr = (double *) stats_ptr;

  fprintf (fp, "%5u %4u %2u   ", run, year, index);
#if 1
  for (i = 0; i < num_elements; i++)
  {
    fprintf (fp, "%8.2f ", *ptr);
    ptr++;
  }
  fprintf (fp, "\n");
#else
  fprintf (fp, "%8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f ",
           stats_ptr->area,
           stats_ptr->edges,
           stats_ptr->clusters,
           stats_ptr->pop,
           stats_ptr->xmean,
           stats_ptr->ymean,
           stats_ptr->rad,
           stats_ptr->slope
    );
  fprintf (fp, "%8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f \n",
           stats_ptr->mean_cluster_size,
           stats_ptr->sng,
           stats_ptr->sdg,
           stats_ptr->sdc,
           stats_ptr->og,
           stats_ptr->rt,
           stats_ptr->pop
    );
#endif
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: LogAverages (int index, FILE * fp)
{
  LOG_INT (fp, index);
  LOG_FLOAT (fp, average[index].area);
  LOG_FLOAT (fp, average[index].edges);
  LOG_FLOAT (fp, average[index].clusters);
  LOG_FLOAT (fp, average[index].pop);
  LOG_FLOAT (fp, average[index].xmean);
  LOG_FLOAT (fp, average[index].ymean);
  LOG_FLOAT (fp, average[index].rad);
  LOG_FLOAT (fp, average[index].slope);
  LOG_FLOAT (fp, average[index].mean_cluster_size);
  LOG_FLOAT (fp, average[index].sng);
  LOG_FLOAT (fp, average[index].sdg);
  LOG_FLOAT (fp, average[index].sdc);
  LOG_FLOAT (fp, average[index].og);
  LOG_FLOAT (fp, average[index].rt);
  LOG_FLOAT (fp, average[index].pop);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: LogThisYearStats (FILE * fp)
{
  LOG_FLOAT (fp, record.this_year.area);
  LOG_FLOAT (fp, record.this_year.edges);
  LOG_FLOAT (fp, record.this_year.clusters);
  LOG_FLOAT (fp, record.this_year.pop);
  LOG_FLOAT (fp, record.this_year.xmean);
  LOG_FLOAT (fp, record.this_year.ymean);
  LOG_FLOAT (fp, record.this_year.rad);
  LOG_FLOAT (fp, record.this_year.slope);
  LOG_FLOAT (fp, record.this_year.mean_cluster_size);
  LOG_FLOAT (fp, record.this_year.sng);
  LOG_FLOAT (fp, record.this_year.sdg);
  LOG_FLOAT (fp, record.this_year.sdc);
  LOG_FLOAT (fp, record.this_year.og);
  LOG_FLOAT (fp, record.this_year.rt);
  LOG_FLOAT (fp, record.this_year.pop);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: LogRecord (FILE * fp)
{
  LOG_INT (fp, record.run);
  LOG_INT (fp, record.monte_carlo);
  LOG_INT (fp, record.year);
  LogThisYearStats (fp);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: compute_leesalee (GRID_P Z,            /* IN     */
				GRID_P urban,        /* IN     */
				double *leesalee)    /* OUT    */
{
 
  int i;
  int the_union;
  int intersection;

  assert (Z != NULL);
  assert (urban != NULL);
  assert (leesalee != NULL);

  the_union = 0;
  intersection = 0;
  for (i = 0; i < mem_GetTotalPixels (); i++)
  {
    if ((Z[i] != 0) || (urban[i] != 0))
    {
      the_union++;
    }

    if ((Z[i] != 0) && (urban[i] != 0))
    {
      intersection++;
    }
  }

  *leesalee = (double) intersection / the_union;
 
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: Analysis (const Coeff & coeffs, IGrid & ingrids, Proc & runinfo, Scenario & scene, double fmatch)
{
  char std_filename[MAX_FILENAME_LEN];
  char avg_filename[MAX_FILENAME_LEN];
  char cntrl_filename[MAX_FILENAME_LEN];
 
  int yr;
  int i;
  int run;
  static int avg_log_created = 0;
  static int std_dev_log_created = 0;
  static int control_stats_log_created = 0;

  const char *output_dir = scene.GetOutputDir ();
  run = runinfo.GetCurrentRun ();

  if (scene.GetWriteAvgFileFlag ())
  {
    sprintf (avg_filename, "%savg_pe_%u.log", output_dir, mpi_rank);
    if (!avg_log_created)
    {
      CreateStatsValFile (avg_filename);
      avg_log_created = 1;
    }
  }

  if (scene.GetWriteStdDevFileFlag ())
  {
    sprintf (std_filename, "%sstd_dev_pe_%u.log", output_dir, mpi_rank);
    if (!std_dev_log_created)
    {
      CreateStatsValFile (std_filename);
      std_dev_log_created = 1;
    }
  }

  if (runinfo.GetProcessingType () != PREDICTING)
  {
    sprintf (cntrl_filename, "%scontrol_stats_pe_%u.log", output_dir, mpi_rank);
    if (!control_stats_log_created)
    {
      CreateControlFile (cntrl_filename);
      control_stats_log_created = 1;
    }
  }

  if (runinfo.GetProcessingType () != PREDICTING)
  {
    /*
     
      start at i = 1, i = 0 is the initial seed
     
     */
    for (i = 1; i < ingrids.GetUrbanCount (); i++)
    {
      yr = ingrids.GetUrbanYear (i);
      CalAverages (scene, i);
      ProcessGrowLog (ingrids, runinfo, scene, run, yr);

      if (scene.GetWriteAvgFileFlag ())
      {
        WriteStatsValLine (avg_filename, run, yr, average, i);
      }
      if (scene.GetWriteStdDevFileFlag ())
      {
        WriteStatsValLine (std_filename, run, yr, std_dev, i);
      }
    }
    DoRegressions (ingrids);
    DoAggregate (scene, ingrids, fmatch);
    WriteControlStats (coeffs, ingrids, runinfo,  cntrl_filename);
  }
  if (runinfo.GetProcessingType () == PREDICTING)
  {
    for (yr = scene.GetPredictionStartDate () + 1;
         yr <= runinfo.GetStopYear (); yr++)
    {
#if 1
      ClearStatsValArrays ();
#endif
      ProcessGrowLog (ingrids, runinfo, scene, run, yr);
      if (scene.GetWriteAvgFileFlag ())
      {
        WriteStatsValLine (avg_filename, run, yr, average, 0);
      }
      if (scene.GetWriteStdDevFileFlag ())
      {
        WriteStatsValLine (std_filename, run, yr, std_dev, 0);
      }
#if 1
      ClearStatsValArrays ();
#endif
    }
  }
  ClearStatsValArrays ();
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: LogControlStatsHdr (FILE * fp)
{
  fprintf (fp, "                                               Cluster\n");
  fprintf (fp, "  Run  Product Compare     Pop   Edges Clusters   ");
  fprintf (fp, "Size Leesalee  Slope ");
  fprintf (fp, " %%Urban   Xmean   Ymean     Rad  Fmatch ");
  fprintf (fp, "Diff  Brd Sprd  Slp   RG\n");
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: LogControlStats (const Coeff & coeffs,  Proc & runinfo, FILE * fp)
{
  fprintf (fp, "%5u %8.5f %7.5f %7.5f %7.5f %7.5f %7.5f %7.5f %7.5f %7.5f ",
           runinfo.GetCurrentRun (),
           aggregate.product,
           aggregate.compare,
           regression.pop,
           regression.edges,
           regression.clusters,
           regression.mean_cluster_size,
           aggregate.leesalee,
           regression.average_slope,
           regression.percent_urban);
  fprintf (fp, "%7.5f %7.5f %7.5f %7.5f %4.0f %4.0f %4.0f %4.0f %4.0f\n",
           regression.xmean,
           regression.ymean,
           regression.rad,
           aggregate.fmatch,
           coeffs.GetSavedDiffusion (),
           coeffs.GetSavedBreed (),
           coeffs.GetSavedSpread (),
           coeffs.GetSavedSlopeResist (),
           coeffs.GetSavedRoadGravity ());
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: DoAggregate (Scenario & scene, IGrid & ingrids, double fmatch)
{
  int last_index;
  int i;
  double fmatch_tmp = 1.0;
  double numerator;
  double denominator;
  char msg_buf[MAX_FILENAME_LEN]; 

  last_index = ingrids.GetUrbanCount () - 1;
  aggregate.fmatch = fmatch;
  aggregate.actual = actual[last_index].pop;
  aggregate.simulated = average[last_index].pop;
  aggregate.leesalee = 0.0;
  for (i = 1; i < ingrids.GetUrbanCount (); i++)
  {
    aggregate.leesalee += average[i].leesalee;
  }
  aggregate.leesalee /= (ingrids.GetUrbanCount () - 1);
  if (aggregate.actual > aggregate.simulated)
  {
    if (aggregate.actual != 0.0)
    {
      denominator = aggregate.actual;
      numerator = aggregate.simulated;
      aggregate.compare = numerator / denominator;
    }
    else
    {
      sprintf (msg_buf, "aggregate.actual = 0.0");
      LOG_ERROR (msg_buf);
      EXIT (1);
    }
  }
  else
  {
    if (aggregate.simulated != 0.0)
    {
      denominator = aggregate.simulated;
      numerator = aggregate.actual;
      aggregate.compare = numerator / denominator;
    }
    else
    {
      sprintf (msg_buf, "aggregate.simulated = 0.0");
      LOG_ERROR (msg_buf);
      EXIT (1);
    }
  }
  if (scene.GetDoingLanduseFlag ())
  {
    fmatch_tmp = fmatch;
  }
  aggregate.product =
    aggregate.compare *
    aggregate.leesalee *
    regression.edges *
    regression.clusters *
    regression.pop *
    regression.xmean *
    regression.ymean *
    regression.rad *
    regression.average_slope *
    regression.mean_cluster_size *
    regression.percent_urban *
    fmatch_tmp;

}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: DoRegressions (IGrid & ingrids)
{
  double dependent[MAX_URBAN_YEARS];
  double independent[MAX_URBAN_YEARS];
  int nobs;
  int i;

  nobs = ingrids.GetUrbanCount () - 1;
  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].area;
    independent[i - 1] = average[i].area;
  }
  regression.area = linefit (dependent, independent, nobs);

  nobs = ingrids.GetUrbanCount () - 1;
  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].edges;
    independent[i - 1] = average[i].edges;
  }
  regression.edges = linefit (dependent, independent, nobs);

  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].clusters;
    independent[i - 1] = average[i].clusters;
  }
  regression.clusters = linefit (dependent, independent, nobs);

  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].pop;
    independent[i - 1] = average[i].pop;
  }
  regression.pop = linefit (dependent, independent, nobs);

  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].xmean;
    independent[i - 1] = average[i].xmean;
  }
  regression.xmean = linefit (dependent, independent, nobs);

  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].ymean;
    independent[i - 1] = average[i].ymean;
  }
  regression.ymean = linefit (dependent, independent, nobs);

  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].rad;
    independent[i - 1] = average[i].rad;
  }
  regression.rad = linefit (dependent, independent, nobs);

  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].average_slope;
    independent[i - 1] = average[i].slope;
  }
  regression.average_slope = linefit (dependent, independent, nobs);

  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].mean_cluster_size;
    independent[i - 1] = average[i].mean_cluster_size;
  }
  regression.mean_cluster_size = linefit (dependent, independent, nobs);

  for (i = 1; i <= nobs; i++)
  {
    dependent[i - 1] = actual[i].percent_urban;
    independent[i - 1] = average[i].percent_urban;
  }
  regression.percent_urban = linefit (dependent, independent, nobs);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: Save (const Scenario & scene, IGrid & ingrids, const Proc & runinfo, char *filename)
{
  int num_written;
  int fseek_loc;
  int index;
  int i;
  char msg_buf[MAX_FILENAME_LEN]; 
  FILE *fp;
  record.run = runinfo.GetCurrentRun ();
  record.monte_carlo = runinfo.GetCurrentMonteCarlo ();
  record.year = runinfo.GetCurrentYear ();
  index = 0;
  if (runinfo.GetProcessingType () != PREDICTING)
  {
    index = ingrids.UrbanYear2Index (record.year);
  }

  UpdateRunningTotal (index);

  if (record.monte_carlo == 0)
  {
    FILE_OPEN (fp, filename, "wb");
    for (i = 0; i < scene.GetMonteCarloIterations (); i++)
    {
      num_written = fwrite (&record, sizeof (record), 1, fp);
      if (num_written != 1)
      {
        printf ("%s %u ERROR\n", __FILE__, __LINE__);
      }
    }

  }
  else
  {
    FILE_OPEN (fp, filename, "r+b");
    rewind (fp);
    fseek_loc = fseek (fp, sizeof (record) * record.monte_carlo, SEEK_SET);
    num_written = fwrite (&record, sizeof (record), 1, fp);
    if (num_written != 1)
    {
      printf ("%s %u ERROR\n", __FILE__, __LINE__);
    }

  }
  fclose (fp);

}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: ProcessGrowLog (IGrid & ingrids, const Proc & runinfo, const Scenario & scene, int run, int year)
{
  FILE *fp;
  int index;
  int mc_count = 0;
  char filename[MAX_FILENAME_LEN];
  char command[MAX_FILENAME_LEN + 3];
  char msg_buf[MAX_FILENAME_LEN]; 

  sprintf (filename, "%sgrow_%u_%u_%d.log", scene.GetOutputDir (), run, year,
        mpi_rank);
  sprintf (command, "rm %s", filename);

  FILE_OPEN (fp, filename, "rb");

  if (runinfo.GetProcessingType () != PREDICTING)
  {
    while (fread (&record, sizeof (record), 1, fp))
    {
      if (mc_count >= scene.GetMonteCarloIterations ())
      {
        sprintf (msg_buf, "mc_count >= scen_GetMonteCarloIterations ()");
        LOG_ERROR (msg_buf);
        EXIT (1);
      }
      if (feof (fp) || ferror (fp))
      {
        sprintf (msg_buf, "feof (fp) || ferror (fp)");
        LOG_ERROR (msg_buf);
        EXIT (1);
      }
      index = ingrids.UrbanYear2Index (year);
      CalStdDev (scene, index);
      mc_count++;
    }
  }
  else
  {
    while (fread (&record, sizeof (record), 1, fp))
    {
      if (mc_count >= scene.GetMonteCarloIterations ())
      {
        sprintf (msg_buf, "mc_count >= scen_GetMonteCarloIterations ()");
        LOG_ERROR (msg_buf);
        EXIT (1);
      }
      if (feof (fp) || ferror (fp))
      {
        sprintf (msg_buf, "feof (fp) || ferror (fp)");
        LOG_ERROR (msg_buf);
        EXIT (1);
      }
      UpdateRunningTotal (0);
    }
    CalAverages (scene, 0);
    rewind (fp);
    mc_count = 0;
    while (fread (&record, sizeof (record), 1, fp))
    {
      if (mc_count >= scene.GetMonteCarloIterations ())
      {
        sprintf (msg_buf, "mc_count >= scen_GetMonteCarloIterations ()");
        LOG_ERROR (msg_buf);
        sprintf (msg_buf, "mc_count= %u scen_GetMonteCarloIterations= %u",
                 mc_count, scene.GetMonteCarloIterations ());
        LOG_ERROR (msg_buf);
        EXIT (1);
      }
      if (feof (fp) || ferror (fp))
      {
        sprintf (msg_buf, "feof (fp) || ferror (fp)");
        LOG_ERROR (msg_buf);
        EXIT (1);
      }
      CalStdDev (scene, 0);
      mc_count++;
    }
  }
  fclose (fp);
  system (command);
}
/*

 FUNCTION NAME:
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
double Stats :: linefit (double *dependent,
			 double *independent,
			 int number_of_observations)
{
  double dependent_avg;
  double independent_avg;
  double cross;
  double sum_dependent;
  double sum_independent;
  double r;
  int n;
  char msg_buf[MAX_FILENAME_LEN]; 

  assert (dependent != NULL);
  assert (independent != NULL);
  assert (number_of_observations > 0);

  dependent_avg = 0;
  independent_avg = 0;

  for (n = 0; n < number_of_observations; n++)

  {
    dependent_avg += dependent[n];
    independent_avg += independent[n];
  }

  if (number_of_observations > 0)
  {
    dependent_avg /= (double) number_of_observations;
    independent_avg /= (double) number_of_observations;
  }
  else
  {
    sprintf (msg_buf, "number_of_observations = %d", number_of_observations);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  cross = 0;
  sum_dependent = 0;
  sum_independent = 0;

  for (n = 0; n < number_of_observations; n++)
  {
    cross += ((dependent[n] - dependent_avg) * (independent[n] -
                                                independent_avg));
    sum_dependent += ((dependent[n] - dependent_avg) * (dependent[n] -
                                                        dependent_avg));
    sum_independent += ((independent[n] - independent_avg) * (independent[n]
                                                     - independent_avg));
  }

  r = 0;

  if (sum_dependent * sum_independent < 1e-11)
    r = 0;
  else
    r = cross / pow (sum_dependent * sum_independent, 0.5);


  return (r * r);
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/

void Stats :: ComputeBaseStats (const Proc & runinfo, IGrid & ingrids)
{
  char func[] = "ComputeBaseStats";
  int i;
  int total_pixels;
  GRID_P urban_ptr;
  GRID_P slope_ptr;
  GRID_P stats_workspace1;
  GRID_P stats_workspace2;
  int road_pixel_count;
  int excluded_pixel_count;

  total_pixels = mem_GetTotalPixels ();
  assert (total_pixels > 0);

  for (i = 0; i < ingrids.GetUrbanCount (); i++)
  {
    urban_ptr = ingrids.GetUrbanGridPtr (__FILE__, func, __LINE__, i);
    slope_ptr = ingrids.GetSlopeGridPtr (__FILE__, func, __LINE__);
    stats_workspace1 = mem_GetWGridPtr (__FILE__, func, __LINE__);
    stats_workspace2 = mem_GetWGridPtr (__FILE__, func, __LINE__);

    compute_stats (ingrids, 
                   urban_ptr,                    /* IN     */
		   slope_ptr,                    /* IN     */
		   &actual[i].area,              /* OUT    */
		   &actual[i].edges,             /* OUT    */
		   &actual[i].clusters,          /* OUT    */
		   &actual[i].pop,               /* OUT    */
		   &actual[i].xmean,             /* OUT    */
		   &actual[i].ymean,             /* OUT    */
		   &actual[i].average_slope,     /* OUT    */
		   &actual[i].rad,               /* OUT    */
		   &actual[i].mean_cluster_size, /* OUT    */
		   stats_workspace1,             /* MOD    */
		   stats_workspace2);            /* MOD    */
    
    road_pixel_count = ingrids.GetIGridRoadPixelCount 
      (runinfo.GetCurrentYear ());
    excluded_pixel_count = ingrids.GetIGridExcludedPixelCount ();
    actual[i].percent_urban = 100.0 *
      100.0 * (actual[i].pop + road_pixel_count) /
      (ingrids.GetNumRows () * ingrids.GetNumCols () - road_pixel_count -
       excluded_pixel_count);

    urban_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, urban_ptr);
    slope_ptr = ingrids.GridRelease (__FILE__, func, __LINE__, slope_ptr);
    stats_workspace1 = mem_GetWGridFree (__FILE__, func, __LINE__,
                                         stats_workspace1);
    stats_workspace2 = mem_GetWGridFree (__FILE__, func, __LINE__,
                                         stats_workspace2);

  }
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: compute_stats (IGrid & ingrids, 
                             GRID_P Z,                             /* IN     */
			     GRID_P slp,                           /* IN     */
			     double *stats_area,                   /* OUT    */
			     double *stats_edges,                  /* OUT    */
			     double *stats_clusters,               /* OUT    */
			     double *stats_pop,                    /* OUT    */
			     double *stats_xmean,                  /* OUT    */
			     double *stats_ymean,                  /* OUT    */
			     double *stats_average_slope,          /* OUT    */
			     double *stats_rad,                    /* OUT    */
			     double *stats_mean_cluster_size,      /* OUT    */
			     GRID_P scratch_gif1,                  /* MOD    */
			     GRID_P scratch_gif2)                  /* MOD    */

{

  assert (Z != NULL);
  assert (slp != NULL);
  assert (stats_area != NULL);
  assert (stats_edges != NULL);
  assert (stats_clusters != NULL);
  assert (stats_pop != NULL);
  assert (stats_xmean != NULL);
  assert (stats_ymean != NULL);
  assert (stats_average_slope != NULL);
  assert (stats_rad != NULL);
  assert (stats_mean_cluster_size != NULL);
  assert (scratch_gif1 != NULL);
  assert (scratch_gif2 != NULL);
  /*
   
    compute the number of edge pixels
   
   */
  edge (ingrids, Z,          /* IN     */
	stats_area,          /* OUT    */
	stats_edges);        /* OUT    */


  /*
   
    compute the number of clusters
   
   */
  cluster (ingrids, 
           Z,                          /* IN     */
           stats_clusters,             /* OUT    */
           stats_pop,                  /* OUT    */
           stats_mean_cluster_size,    /* OUT    */
           scratch_gif1,               /* MOD    */
           scratch_gif2);              /* MOD    */

  /*
   
    compute means
   
   */
  circle (ingrids, 
          Z,                      /* IN     */
          slp,                    /* IN     */
          *stats_area,            /* IN     */
          stats_xmean,            /* OUT    */
          stats_ymean,            /* OUT    */
          stats_average_slope,    /* OUT    */
          stats_rad);             /* OUT    */
  
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: edge (IGrid  &ingrids,        /* IN    */
                    GRID_P Z,               /* IN    */
		    double *stats_area,     /* OUT   */
		    double *stats_edges)    /* OUT   */
{
  char func[] = "stats_edge";
  int i;
  int j;
  int edge;
  int edges;
  int area;
  int rowi[4] = {-1, 1, 0, 0};
  int colj[4] = {0, 0, -1, 1};
  int loop;
  int row;
  int col;
  int nrows;
  int ncols;

  assert (stats_area != NULL);
  assert (stats_edges != NULL);
  assert (Z != NULL);
  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();
  assert (nrows > 0);
  assert (ncols > 0);

  edges = 0;
  area = 0;

  for (i = 0; i < nrows; i++)
  {
    for (j = 0; j < ncols; j++)
    {
      edge = FALSE;

      if (Z[ncols*i +  j] != 0)
      {
        area++;

        /* this does a 4 neighbor search (N, S, E, W) */
        for (loop = 0; loop <= 3; loop++)
        {
          row = i + rowi[loop];
          col = j + colj[loop];

          if ( ((row <  nrows) &&  (col <  ncols) && (row >= 0)  
                && (col >= 0)))
          {
            if (Z[ncols*row +  col] == 0)
            {
              edge = TRUE;
            }
          }
        }

        if (edge)
        {
          edges++;
        }
      }
    }
  }
  *stats_area = area;
  *stats_edges = edges;
 
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: circle (IGrid & ingrids,                /* IN     */
                      GRID_P Z,                       /* IN     */
                      GRID_P slp,                     /* IN     */
                      int stats_area,                 /* IN     */
                      double *stats_xmean,            /* OUT    */
                      double *stats_ymean,            /* OUT    */
                      double *stats_average_slope,    /* OUT    */
                      double *stats_rad)              /* OUT    */
{
  char func[] = "stats_circle";
  int i;
  int j;
  int number;
  double xmean;
  double ymean;
  double addslope;
  int nrows;
  int ncols;
  char msg_buf[MAX_FILENAME_LEN]; 
 
  assert (stats_xmean != NULL);
  assert (stats_ymean != NULL);
  assert (stats_average_slope != NULL);
  assert (stats_rad != NULL);
  assert (Z != NULL);
  assert (slp != NULL);

  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();
  assert (nrows > 0);
  assert (ncols > 0);
  addslope = 0.0;
  ymean = 0.0;
  xmean = 0.0;
  number = 0.0;

  /*
   
    first, compute the means
   
   */
  for (i = 0; i < nrows; i++)
  {
    for (j = 0; j < ncols; j++)
    {
      if (Z[ncols*i + j] > 0)
      {
        addslope += slp[ncols*i + j];
        xmean += (double) j;
        ymean += (double) i;
        number++;
      }
    }
  }

  if (number <= 0)
  {
    sprintf (msg_buf, "number = %d", number);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  xmean /= (double) number;
  ymean /= (double) number;
  *stats_xmean = xmean;
  *stats_ymean = ymean;
  *stats_average_slope = addslope / number;

  /*
   *
   * compute the radius of the circle with same area as number
   *
   */
  *stats_rad = pow ((stats_area / PI), 0.5);


}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: cluster (IGrid & ingrids, 
                       GRID_P Z,                            /* IN     */
                       double *stats_clusters,              /* OUT    */
                       double *stats_pop,                   /* OUT    */
                       double *stats_mean_cluster_size,     /* OUT    */
                       GRID_P scratch_gif1,                 /* MOD    */
                       GRID_P scratch_gif2)                 /* MOD    */
{
  char func[] = "stats_cluster";
  int i;
  int j;
  int depth;
  int num_clusters;
  int sum;
  int row;
  int col;
  int rrow;
  int ccol;
  int rowi[4] = {1, 0, -1, 0};
  int colj[4] = {0, 1, 0, -1};
  int loop;
  long *visited;
  long *clusters;
  int total_pixels;
  int nrows;
  int ncols;
  char msg_buf[MAX_FILENAME_LEN]; 
  
  assert (stats_clusters != NULL);
  assert (stats_pop != NULL);
  assert (stats_mean_cluster_size != NULL);
  assert (Z != NULL);
  assert (scratch_gif1 != NULL);
  assert (scratch_gif2 != NULL);
  total_pixels = mem_GetTotalPixels ();
  assert (total_pixels > 0);
  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();
  assert (nrows > 0);
  assert (ncols > 0);

  sum = 0;
  *stats_pop = 0;
  depth = 0;
  num_clusters = 0;

  visited = scratch_gif1;
  clusters = scratch_gif2;
  for (i = 0; i < total_pixels; i++)
  {
    visited[i] = 0;
  }
  for (i = 0; i < total_pixels; i++)
  {
    if (Z[i] != 0)
    {
      clusters[i] = 1;
      (*stats_pop)++;
    }
    else
    {
      clusters[i] = 0;
    }
  }
  for (j = 0; j < ncols; j++)
  {
    clusters[ncols*0 +  j] = 0;
    clusters[ncols*(nrows - 1)+ j] = 0;
  }
  for (i = 0; i < nrows; i++)
  {
    clusters[ncols*i + 0] = 0;
    clusters[ncols*i + ncols - 1] = 0;
  }

  for (i = 1; i < nrows - 1; i++)
  {
    for (j = 1; j < ncols - 1; j++)
    {
      if (clusters[ncols*i + j] == 1 && visited[ncols*i + j] == 0)
      {
        sum++;
        rrow = i;
        ccol = j;
        visited[ncols*i + j] = 1;
        Q_STORE (rrow, ccol);
        do
        {
          Q_RETREIVE (row, col);
          for (loop = 0; loop <= 3; loop++)
          {
            rrow = row + rowi[loop];
            ccol = col + colj[loop];

            if ((rrow < nrows) && (ccol <  ncols) && (rrow >= 0) 
                && (ccol >= 0))
            {
              if (clusters[ncols*rrow + ccol] == 1 &&
                  !visited[ncols*rrow + ccol])
              {
                visited[ncols*rrow + ccol] = 1;
                Q_STORE (rrow, ccol);

                sum++;
              }
            }
          }
        }
        while (depth > 0);

        num_clusters++;
      }
    }
  }

  *stats_clusters = num_clusters;
  if (num_clusters > 0)
  {
    *stats_mean_cluster_size = sum / num_clusters;
  }
  else
  {
    sprintf (msg_buf, "num_clusters=%d", num_clusters);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: WriteControlStats (const Coeff & coeffs,
                                 IGrid & ingrids, Proc & runinfo,
                                 char *filename)
{
  char func[] = "stats_WriteControlStats";
  FILE *fp;
  char msg_buf[MAX_FILENAME_LEN]; 

  FILE_OPEN (fp, filename, "a");

  LogControlStats (coeffs,  runinfo,  fp);
  fclose (fp);
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: InitUrbanizationAttempts ()
{
  urbanization_attempt.successes = 0;
  urbanization_attempt.z_failure = 0;
  urbanization_attempt.delta_failure = 0;
  urbanization_attempt.slope_failure = 0;
  urbanization_attempt.excluded_failure = 0;
}

/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: IncrementUrbanSuccess ()
{
  urbanization_attempt.successes++;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: IncrementZFailure ()
{
  urbanization_attempt.z_failure++;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: IncrementDeltaFailure ()
{
  urbanization_attempt.delta_failure++;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: IncrementSlopeFailure ()
{
  urbanization_attempt.slope_failure++;
}
/*

 FUNCTION NAME: 
 PURPOSE:       
 AUTHOR:        Keith Clarke
 PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
 CREATION DATE: 11/11/1999
 DESCRIPTION:


*/
void Stats :: IncrementEcludedFailure ()
{
  urbanization_attempt.excluded_failure++;
}








