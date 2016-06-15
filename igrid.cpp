/*! \file igrid.cpp
    \brief Implementation file for the input grid object.
    
    Implementation file for the input grid object which keeps track
    of all input layers.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "imageio.h"
#include "igrid.h"
#include "memory_obj.h"
#include "output.h"
#include "imageio.h"
#include "utilities.h"


/*
  
   FUNCTION NAME: GetIGridRoadPixelCount
   PURPOSE:       get road year pixel count by date
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   A year is pasted into the function and it then searches
                  all the road years igrid structs looking for the road
                  eqaul to or previous to the requested year. It returns
                  the road pixel count for that year.
  
*/
int IGrid::GetIGridRoadPixelCount (int year) const throw()
{
  int i;

  for (i = road_count - 1; i > 0; i--)
  {
    if (year >= road[i].year.digit)
    {
      break;
    }
  }
  return road_pixel_count[i];
}

/*
  
   FUNCTION NAME: GetIGridExcludedPixelCount
   PURPOSE:       return the # of excluded pixels
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::GetIGridExcludedPixelCount () const throw()
{
  return excld_count;
}

/*
  
   FUNCTION NAME: GetIGridRoadPercentage
   PURPOSE:       return the % of road pixels for a given year
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
road_percent_t IGrid::GetIGridRoadPercentage (int year) const throw()
{
  int i;
  for (i = road_count - 1; i > 0; i--)
  {
    if (year > road[i].year.digit)
    {
      break;
    }
  }
  return percent_road[i];
}

/*
  
   FUNCTION NAME: GetIGridCount
   PURPOSE:       return the # of igrids (or input grids)
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::GetIGridCount () const throw()
{
  return igrid_count;
}


/*
  
   FUNCTION NAME: GetNumRows
   PURPOSE:       return the # rows in a grid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::GetNumRows () const throw()
{
  return slope.nrows;
}

/*
  
   FUNCTION NAME: GetNumCols
   PURPOSE:       return the # cols in a grid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::GetNumCols ()  const throw()
{
  return slope.ncols;
}

/*
  
   FUNCTION NAME: GetNumTotalPixels
   PURPOSE:       return the total # pixels in grid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::GetNumTotalPixels () const throw()
{
  return slope.ncols * slope.nrows;
}

/*
  
   FUNCTION NAME: GetUrbanYear
   PURPOSE:       return urban date as a digit for a given urban index
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::GetUrbanYear (int i) const throw()
{
  return urban[i].year.digit;
}

/*
  
   FUNCTION NAME: GetLanduseYear
   PURPOSE:       return landuse date as a digit for a given landuse index
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::GetLanduseYear (int i) const throw()
{
  return landuse[i].year.digit;
}

/*
  
   FUNCTION NAME: GetUrbanCount
   PURPOSE:       return the # of urban grids
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::GetUrbanCount () const throw()
{
  return urban_count;
}

/*
  
   FUNCTION NAME: GetLocation
   PURPOSE:       return location string for this scenario
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
const char * IGrid::GetLocation () const throw()
{
  return location;
}

/*
  
   FUNCTION NAME: GridRelease
   PURPOSE:       release the memory used by a grid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P IGrid::GridRelease (char *file, char *fun, int line, GRID_P ptr)
throw()
{
#ifdef PACKING
  return mem_GetWGridFree (file, fun, line, ptr);
#else
  return NULL;
#endif
}

/*
   FUNCTION NAME: GetUrbanGridPtr
   PURPOSE:       return ptr to urban data
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if the data is packed then we need to allocate space to 
                  hold the unpacked data and then unpack it.
*/
GRID_P IGrid::GetUrbanGridPtr
(char *file, char *fun, int line, int index) throw()
{
  GRID_P ptr;
#ifdef PACKING
  ptr = mem_GetWGridPtr (file, fun, line);
  _unpack ((char *) urban[index].ptr,
           ptr,
           total_pixels,
           -1);

#else
  ptr = urban[index].ptr;
#endif
  return ptr;
}

/*
   FUNCTION NAME: GetRoadGridPtr
   PURPOSE:       return ptr to road grid data
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if the data is packed then we need to allocate space to 
                  hold the unpacked data and then unpack it.
*/
GRID_P  IGrid::GetRoadGridPtr
(char *file, char *fun, int line, int index) throw()
{
  GRID_P ptr;
#ifdef PACKING
  ptr = mem_GetWGridPtr (file, fun, line);
  _unpack ((char *) road[index].ptr,
           ptr,
           total_pixels,
           -1);

#else
  ptr = road[index].ptr;
#endif
  return ptr;
}

/*
  
   FUNCTION NAME: GetUrbanGridPtrByYear
   PURPOSE:       return ptr to urban grid data by year
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if the data is packed then we need to allocate space to
                  hold the unpacked data and then unpack it.
  
*/
GRID_P  IGrid::
GetUrbanGridPtrByYear (char *file, char *fun, int line, int year) throw()
{
  GRID_P ptr;
  int i;

  assert (year >= urban[0].year.digit);

  for (i = urban_count - 1; i > 0; i--)
  {
    if (year >= urban[i].year.digit)
    {
      break;
    }
  }

#ifdef PACKING
  ptr = mem_GetWGridPtr (file, fun, line);
  _unpack ((char *) urban[i].ptr,
           ptr,
           total_pixels,
           -1);

#else
  ptr = urban[i].ptr;
#endif
  return ptr;
}

/*
  
   FUNCTION NAME: GetRoadGridPtrByYear
   PURPOSE:       return ptr to road grid data by year
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if the data is packed then we need to allocate space to
                  hold the unpacked data and then unpack it.
  
*/
GRID_P IGrid::
GetRoadGridPtrByYear (char *file, char *fun, int line, int year) throw()
{
  GRID_P ptr;
  int i;

  for (i = road_count - 1; i > 0; i--)
  {
    if (year >= road[i].year.digit)
    {
      break;
    }
  }

#ifdef PACKING
  ptr = mem_GetWGridPtr (file, fun, line);
  _unpack ((char *) road[i].ptr,
           ptr,
           total_pixels,
           -1);

#else
  ptr = road[i].ptr;
#endif
  return ptr;
}

/*
  
   FUNCTION NAME: GetLanduseGridPtr
   PURPOSE:       return ptr to landuse grid data by index
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if the data is packed then we need to allocate space to
                  hold the unpacked data and then unpack it.
  
*/
GRID_P IGrid::
GetLanduseGridPtr (char *file, char *fun, int line, int index)  throw()
{
  GRID_P ptr;
#ifdef PACKING
  ptr = mem_GetWGridPtr (file, fun, line);
  _unpack ((char *) landuse[index].ptr,
           ptr,
           total_pixels,
           -1);

#else
  ptr = landuse[index].ptr;
#endif
  return ptr;
}

/*
   FUNCTION NAME: GetSlopeGridPtr
   PURPOSE:       return ptr to slope grid data
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if the data is packed then we need to allocate space to
                  hold the unpacked data and then unpack it.
  
*/
GRID_P IGrid::GetSlopeGridPtr (char *file, char *fun, int line) throw()
{
  GRID_P ptr;
#ifdef PACKING
  ptr = mem_GetWGridPtr (file, fun, line);
  _unpack ((char *) slope.ptr,
           ptr,
           total_pixels,
           -1);

#else
  ptr = slope.ptr;
#endif
  return ptr;
}

/*
   FUNCTION NAME: GetExcludedGridPtr
   PURPOSE:       return ptr to excluded grid data
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if the data is packed then we need to allocate space to
                  hold the unpacked data and then unpack it.
  
*/
GRID_P IGrid::GetExcludedGridPtr (char *file, char *fun, int line) throw()
{
  GRID_P ptr;
#ifdef PACKING
  ptr = mem_GetWGridPtr (file, fun, line);
  _unpack ((char *) excluded.ptr,
           ptr,
           total_pixels,
           -1);

#else
  ptr = excluded.ptr;
#endif
  return ptr;
}

/*
   FUNCTION NAME: GetBackgroundGridPtr
   PURPOSE:       return ptr to background grid data
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   if the data is packed then we need to allocate space to
                  hold the unpacked data and then unpack it.
  
*/
GRID_P  IGrid::GetBackgroundGridPtr (char *file, char *fun, int line) throw()
{
  GRID_P ptr;
#ifdef PACKING
  ptr = mem_GetWGridPtr (file, fun, line);
  _unpack ((char *) background.ptr,
           ptr,
           total_pixels,
           -1);

#else
  ptr = background.ptr;
#endif
  return ptr;
}





/*
  
   FUNCTION NAME: NormalizeRoads
   PURPOSE:       normalizes road grids
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::NormalizeRoads () throw()
{
  int i;
  int j;
  PIXEL max_of_max = 0;
  GRID_P grid_ptr;
  float image_max;
  float norm_factor;

#ifdef PACKING
  grid_ptr = mem_GetWGridPtr (__FILE__, func, __LINE__);
#endif
  for (i = 0; i < road_count; i++)
  {
    max_of_max = MAX (max_of_max, road[i].max);
  }
  for (i = 0; i < road_count; i++)
  {
#ifdef PACKING
    _unpack ((char *) road[i].ptr,
             grid_ptr,
             total_pixels,
             -1);
#else
    grid_ptr = road[i].ptr;
#endif
    image_max = (float) road[i].max;
    norm_factor = image_max / (float) max_of_max;
    for (j = 0; j < total_pixels; j++)
    {
      grid_ptr[j] =
        (PIXEL) (((100.0 * grid_ptr[j]) / image_max) * norm_factor);
    }

  }
#ifdef PACKING
  mem_GetWGridFree (__FILE__, func, __LINE__, grid_ptr);
#endif
}

/*
   FUNCTION NAME: ValidateGrids
   PURPOSE:       validate all input grid values
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::ValidateGrids (Landclass & lclasses, FILE * fp) throw()
{
  FILE *loc_fp(0);
  bool AOK = true;

  if (fp)
  {
    fprintf (fp,
          "\n*******************************\n");
    fprintf (fp,
             "*******************************************************\n");
    fprintf (fp, "         VALIDATING INPUT GRIDS\n");
  }
  if (!ValidateUrbanGrids (fp))
    AOK = false;
  if (!ValidateRoadGrids (fp))
    AOK = false;
  if (!ValidateLanduseGrids (lclasses, fp))
    AOK = false;
  if (!ValidateSlopeGrid (fp))
    AOK = false;
  if (!ValidateExcludedGrid (fp))
    AOK = false;
  if (!ValidateBackgroundGrid (fp))
    AOK = false;
  if (!AOK)
  {
    if (!fp)
      loc_fp = stderr;
    fprintf (loc_fp, "\nERROR\n");
    fprintf (loc_fp, "\nInput data images contain errors.\n");
    EXIT (1);
  }
  else
  {
    if (fp)
    {
      fprintf (fp, "\nValidation OK\n");
    }
  }
  if (fp)
  {
    fprintf (fp, "*******************************************************\n");
    fprintf (fp, "*******************************************************\n");
  }
}

/*
   FUNCTION NAME: ValidateUrbanGrids
   PURPOSE:       check the validity of the urban grids
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool IGrid::ValidateUrbanGrids (FILE * fp) throw()
{
  bool rv = true;
  int i;
  int j;

  for (i = 0; i < urban_count; i++)
  {
    if (fp)
    {
      fprintf (fp, "\nValidating urban input grid: %s\n",
               urban[i].filename);
      fprintf (fp, "\nIndex Count PercentOfImage\n");
    }
    for (j = 0; j < 256; j++)
    {
      if (urban[i].histogram[j] > 0)
      {
        if (fp)
        {
          fprintf (fp, "%3u  %5u  %8.2f%%\n", j, urban[i].histogram[j],
                   100.0 * urban[i].histogram[j] / total_pixels);
        }
      }
    }
    if (urban[i].histogram[0] == 0)
    {
      if (fp)
      {
        fprintf (fp, "ERROR input grid: %s is completely urbanized\n",
                 urban[i].filename);
      }
      else
      {
        fprintf (stderr, "ERROR input grid: %s is completely urbanized\n",
                 urban[i].filename);
      }
      rv = false;
    }
  }
  return rv;
}

/*
   FUNCTION NAME: ValidateRoadGrids
   PURPOSE:       check the validity of the road grids
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool IGrid::ValidateRoadGrids (FILE * fp) throw()
{
  bool rv = true;
  int i;
  int j;

  for (i = 0; i < road_count; i++)
  {
    if (fp)
    {
      fprintf (fp, "\nValidating road input grid: %s\n", road[i].filename);
      fprintf (fp, "\nIndex Count PercentOfImage\n");
      for (j = 0; j < 256; j++)
      {
        if (road[i].histogram[j] > 0)
        {
          fprintf (fp, "%3u  %5u  %8.2f%%\n", j, road[i].histogram[j],
                   100.0 * road[i].histogram[j] / total_pixels);
        }
      }
    }
    if (road[i].histogram[0] == 0)
    {
      if (fp)
      {
        fprintf (fp, "ERROR input grid: %s is 100%% roads\n",
                 road[i].filename);
      }
      else
      {
        fprintf (stderr, "ERROR input grid: %s is 100%% roads\n",
                 road[i].filename);
      }
      rv = false;
    }
  }
  return rv;
}

/*
   FUNCTION NAME: ValidateLanduseGrids
   PURPOSE:       check validity of landuse grid values
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool IGrid::ValidateLanduseGrids (Landclass & lclasses, FILE * fp)  throw()
{
  bool rv = true;
  int i;
  int j;
  char msg_buf[MAX_FILENAME_LEN]; 

  for (i = 0; i < landuse_count; i++)
  {
    if (fp)
    {
      fprintf (fp, "\nValidating landuse input grid: %s\n",
               landuse[i].filename);
      fprintf (fp, "\nIndex Count PercentOfImage\n");
    }
    for (j = 0; j < 256; j++)
    {
      if (landuse[i].histogram[j] > 0)
      {
        if (fp)
        {
          fprintf (fp, "%3u  %5u  %8.2f%%\n", j, landuse[i].histogram[j],
                   100.0 * landuse[i].histogram[j] / total_pixels);
        }
        if (!lclasses.IsAlandclass (j))
        {
          rv = false;
          sprintf (msg_buf, "landuse type %u appears in file: %s",
                   j, landuse[i].filename);
          LOG_ERROR (msg_buf);
        }
      }
    }
  }
  return rv;
}

/*
   FUNCTION NAME: ValidateSlopeGrid
   PURPOSE:       check validity of slope grid values
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   could not think of good validity check!!!
  
  
*/
bool IGrid::ValidateSlopeGrid (FILE * fp)  throw()
{
  if (fp)
  {
    fprintf (fp, "\nValidating slope input grid: %s\n", slope.filename);
  }
  return true;
}

/*
   FUNCTION NAME: ValidateExcludedGrid
   PURPOSE:       check validity of excluded grid values
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   could not think of good validity check!!!
  
  
*/
bool IGrid::ValidateExcludedGrid (FILE * fp) throw()
{
  if (fp)
  {
    fprintf (fp, "\nValidating excluded input grid: %s\n",
             excluded.filename);
  }
  return true;
}

/*
   FUNCTION NAME: ValidateBackgroundGrid
   PURPOSE:       check validity of background grid values
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:   could not think of good validity check!!!
  
  
*/
bool IGrid::ValidateBackgroundGrid (FILE * fp)  throw()
{
  if (fp)
  {
    fprintf (fp, "\nValidating background input grid: %s\n",
             background.filename);
  }
  return true;
}

/*
   FUNCTION NAME: ReadGrid
   PURPOSE:       read input grid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::ReadGrid
(Scenario & scene, char *filepath, GRID_P scratch_pad, GRID_P grid_ptr)  throw()
{
  char *filename;
  ImageIO imagein;
  char msg_buf[MAX_FILENAME_LEN]; 

  filename = extract_filename (filepath);
  if (scratch_pad != NULL)
  {
    imagein.ReadGRID(scratch_pad, (*this), scene, filepath);
    


#ifdef PACKING
    _pack (scratch_pad, (char *) grid_ptr,
           mem_GetTotalPixels (), -1);
#else
    sprintf (msg_buf, "PACKING not defined");
    LOG_ERROR (msg_buf);
    exit (1);
#endif
  }
  else
  {
    
    imagein.ReadGRID(grid_ptr, (*this), scene, filepath);
    

    
  }
}

/*
   FUNCTION NAME: ReadFiles
   PURPOSE:       read input grids
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::ReadFiles (Scenario & scene) throw()
{
  char func[] = "ReadFiles";
  int i;
  GRID_P scratch_pad = NULL;
#ifdef PACKING
  scratch_pad = mem_GetWGridPtr (__FILE__, func, __LINE__);
  assert (scratch_pad != NULL);
#endif


  for (i = 0; i < urban_count; i++)
  {
    urban[i].ptr = mem_GetIGridPtr (func);
    ReadGrid (scene, urban[i].filename,
                    scratch_pad, urban[i].ptr);
    urban[i].SetMinMax ();
    urban[i].Histogram ();
  }

  for (i = 0; i < road_count; i++)
  {
    road[i].ptr = mem_GetIGridPtr (func);
    ReadGrid (scene, road[i].filename,
                    scratch_pad, road[i].ptr);
    road[i].SetMinMax ();
    road[i].Histogram ();
  }

  for (i = 0; i < landuse_count; i++)
  {
    landuse[i].ptr = mem_GetIGridPtr (func);
    ReadGrid (scene, landuse[i].filename,
                    scratch_pad, landuse[i].ptr);
    landuse[i].SetMinMax ();
    landuse[i].Histogram ();
  }

  excluded.ptr = mem_GetIGridPtr (func);
  ReadGrid (scene, excluded.filename,
                  scratch_pad, excluded.ptr);
  excluded.SetMinMax ();
  excluded.Histogram ();

  slope.ptr = mem_GetIGridPtr (func);
  ReadGrid (scene, slope.filename,
                  scratch_pad, slope.ptr);
  slope.SetMinMax ();
  slope.Histogram ();

  background.ptr = mem_GetIGridPtr (func);
  ReadGrid (scene, background.filename,
                  scratch_pad, background.ptr);
  background.SetMinMax ();
  //pretty sure they ment to do a histogram on the background not excluded
  //grid_histogram (&excluded);
  background.Histogram();
#ifdef PACKING
  scratch_pad = mem_GetWGridFree (__FILE__, func, __LINE__, scratch_pad);
#endif

  CountRoadPixels ();
  CalculatePercentRoads ();
}

/*
   FUNCTION NAME: init
   PURPOSE:       initialize some variables
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::init (const Scenario & scene, const Proc & proc) throw()
{

  igrid_count= 0;
  SetLocation (scene);
  SetFilenames (scene, proc);

}

/*
   FUNCTION NAME: SetLocation
   PURPOSE:       set the location string variable
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::SetLocation (const Scenario & scene) throw()
{
  char buf[256];

  strcpy (buf, scene.GetSlopeDataFilename ());
  strcpy (location, strtok (buf, "."));
}

/*
   FUNCTION NAME: SetFilenames
   PURPOSE:       set the filenames of the input files
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::SetFilenames (const Scenario & scene, const Proc & proc) throw()
{
  int i;
  int j;
  int start_year;
  int this_year;
  char *this_year_str;
  char buf[256];
  bool packed;

  start_year = scene.GetPredictionStartDate ();
#ifdef PACKING
  packed = true;
#else
  packed = false;
#endif

  j = 0;
  for (i = 0; i < scene.GetUrbanDataFileCount (); i++)
  {
    strcpy (buf, scene.GetUrbanDataFilename (i));
    strtok (buf, ".");
    strtok (NULL, ".");
    this_year_str = strtok (NULL, ".");
    this_year = atoi (this_year_str);
    if (proc.GetProcessingType () == PREDICTING)
    {
      if (this_year >= start_year)
      {
        strcpy (urban[j].filename, scene.GetInputDir ());
        strcat (urban[j].filename, scene.GetUrbanDataFilename (i));
        SetGridSizes (&urban[j], scene);
        strcpy (urban[j].year.string, this_year_str);
        urban[j].year.digit = this_year;
        urban[j].packed = packed;
        j++;
      }
    }
    else
    {
      strcpy (urban[j].filename, scene.GetInputDir ());
      strcat (urban[j].filename, scene.GetUrbanDataFilename (i));
      SetGridSizes (&urban[j], scene);
      strcpy (urban[j].year.string, this_year_str);
      urban[j].year.digit = this_year;
      urban[j].packed = packed;
      j++;
    }
  }
  urban_count = j;

  j = 0;
  for (i = 0; i < scene.GetRoadDataFileCount (); i++)
  {
    strcpy (buf, scene.GetRoadDataFilename (i));
    strtok (buf, ".");
    strtok (NULL, ".");
    this_year_str = strtok (NULL, ".");
    this_year = atoi (this_year_str);
    if (proc.GetProcessingType () == PREDICTING)
    {
      if ((this_year >= start_year) | (i = scene.GetRoadDataFileCount () - 1))
      {
        strcpy (road[j].filename, scene.GetInputDir ());
        strcat (road[j].filename, scene.GetRoadDataFilename (i));
        SetGridSizes (&road[j], scene);
        strcpy (road[j].year.string, this_year_str);
        road[j].year.digit = this_year;
        road[j].packed = packed;
        j++;
      }
    }
    else
    {
      strcpy (road[j].filename, scene.GetInputDir ());
      strcat (road[j].filename, scene.GetRoadDataFilename (i));
      SetGridSizes (&road[j], scene);
      strcpy (road[j].year.string, this_year_str);
      road[j].year.digit = this_year;
      road[j].packed = packed;
      j++;
    }
  }
  road_count = j;

  for (i = 0; i < scene.GetLanduseDataFileCount (); i++)
  {
    strcpy (buf, scene.GetLanduseDataFilename (i));
    strtok (buf, ".");
    strtok (NULL, ".");
    this_year_str = strtok (NULL, ".");
    this_year = atoi (this_year_str);
    strcpy (landuse[i].filename, scene.GetInputDir ());
    strcat (landuse[i].filename, scene.GetLanduseDataFilename (i));
    strcpy (landuse[i].year.string, this_year_str);
    landuse[i].year.digit = this_year;
    SetGridSizes (&landuse[i], scene);
    landuse[i].packed = packed;
  }
  landuse_count = scene.GetLanduseDataFileCount ();

  strcpy (excluded.filename, scene.GetInputDir ());
  strcat (excluded.filename, scene.GetExcludedDataFilename ());
  SetGridSizes (&excluded, scene);
  strcpy (excluded.year.string, "");
  excluded.year.digit = 0;
  excluded.packed = packed;
  excluded_count = 1;

  strcpy (slope.filename, scene.GetInputDir ());
  strcat (slope.filename, scene.GetSlopeDataFilename ());
  SetGridSizes (&slope, scene);
  strcpy (slope.year.string, "");
  slope.year.digit = 0;
  slope.packed = packed;
  slope_count = 1;

  strcpy (background.filename, scene.GetInputDir ());
  strcat (background.filename, scene.GetBackgroundDataFilename ());
  SetGridSizes (&background, scene);
  strcpy (background.year.string, "");
  background.year.digit = 0;
  background.packed = packed;
  background_count = 1;

  igrid_count = urban_count +
    road_count +
    landuse_count +
    excluded_count +
    slope_count +
    background_count;

}

/*
   FUNCTION NAME: SetGridSizes
   PURPOSE:       scan the input GIFs for size and other parameters
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/

void IGrid::SetGridSizes (Grid * grid_ptr, const Scenario & scene) throw()
{
  //Moved all image specific stuff the imageio class.
  ImageIO i;
  i.GetImageInfo (grid_ptr, scene);
  total_pixels = grid_ptr->ncols * grid_ptr->nrows;
 
}


/*
   FUNCTION NAME: VerifyInputs
   PURPOSE:       verify the grid sizes and some other stuff
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::VerifyInputs (const Scenario & scene, FILE * fp) throw()
{
  char buf[256];
  char *my_location;
  char *filename;
  int i;
  int rows;
  int cols;
  bool all_sizes_the_same = true;
  bool all_locations_the_same = true;
  char msg_buf[MAX_FILENAME_LEN]; 

#define CHECK_LOCATION(path)                                 \
strcpy (buf, (path));                                        \
filename = extract_filename(buf);                            \
my_location = strtok (filename, ".");                        \
if(strcmp(my_location,location) != 0)                  \
{                                                            \
  all_locations_the_same = false;                            \
}

  if (fp)
  {
    fprintf (fp, "\nVerifying Data Input Files\n");
  }
  rows = slope.nrows;
  cols = slope.ncols;
  for (i = 0; i < urban_count; i++)
  {
    if ((rows != urban[i].nrows) || (cols != urban[i].ncols))
    {
      all_sizes_the_same = false;
    }
    
    strcpy (buf, urban[i].filename);   
    filename = extract_filename(buf); 
    my_location = strtok (filename, "."); 
    if(strcmp(my_location,location) != 0)   
    {
      all_locations_the_same = false;                            
    }
    
  }
  for (i = 0; i < road_count; i++)
  {
    if ((rows != road[i].nrows) || (cols != road[i].ncols))
    {
      all_sizes_the_same = false;
    }
        
    strcpy (buf, road[i].filename);   
    filename = extract_filename(buf); 
    my_location = strtok (filename, "."); 
    if(strcmp(my_location,location) != 0)   
    {
      all_locations_the_same = false;                            
    }


  }
  for (i = 0; i < landuse_count; i++)
  {
    if ((rows != landuse[i].nrows) || (cols != landuse[i].ncols))
    {
      all_sizes_the_same = false;
    }
    
    
    strcpy (buf, landuse[i].filename);   
    filename = extract_filename(buf); 
    my_location = strtok (filename, "."); 
    if(strcmp(my_location,location) != 0)   
    {
      all_locations_the_same = false;                            
    }
  
  }
  if ((rows != excluded.nrows) || (cols != excluded.ncols))
  {
    all_sizes_the_same = false;
    
    strcpy (buf, excluded.filename);   
    filename = extract_filename(buf); 
    my_location = strtok (filename, "."); 
    if(strcmp(my_location,location) != 0)   
    {
      all_locations_the_same = false;                            
    }
  }

  if ((rows != background.nrows) || (cols != background.ncols))
  {
    all_sizes_the_same = false;
    strcpy (buf, background.filename);   
    filename = extract_filename(buf); 
    my_location = strtok (filename, "."); 
    if(strcmp(my_location,location) != 0)   
    {
      all_locations_the_same = false;                            
    }
  
  }
  if (!all_sizes_the_same)
  {
    sprintf (msg_buf, "GIFs are not all the same size.");
    LOG_ERROR (msg_buf);
    sprintf (msg_buf, "Please check your input image sizes");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  if (!all_locations_the_same)
  {
    sprintf (msg_buf, "GIFs do not all have the same location.");
    LOG_ERROR (msg_buf);
    sprintf (msg_buf, "Please check your scenario file");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  if (scene.GetDoingLanduseFlag ())
  {
    if (landuse[1].year.digit !=
        urban[urban_count - 1].year.digit)
    {
      sprintf (msg_buf, "Last landuse year does not match last urban year.");
      LOG_ERROR (msg_buf);
      sprintf (msg_buf, "last landuse year = %u last urban year = %u",
               landuse[1].year.digit,
               urban[urban_count - 1].year.digit);
      LOG_ERROR (msg_buf);
      EXIT (1);
    }
  }
  if (fp)
  {
    fprintf (fp, "%s %u Data Input Files: OK\n", __FILE__, __LINE__);
  }
}

/*
   FUNCTION NAME: CountRoadPixels
   PURPOSE:       count the number of road pixels
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::CountRoadPixels () throw()
{
  GRID_P roads;
  int i;

  assert (total_pixels > 0);

  for (i = 0; i < road_count; i++)
  {
#ifdef PACKING
    roads = mem_GetWGridPtr (__FILE__, func, __LINE__);
    _unpack ((char *) road[i].ptr,
             roads,
             total_pixels,
             -1);
#else
    roads = road[i].ptr;
#endif
    road_pixel_count[i] = util_count_pixels (total_pixels,
                                             roads,
                                             GT,
                                             0);
#ifdef PACKING
    mem_GetWGridFree (__FILE__, func, __LINE__, roads);
#endif
  }
}

/*
   FUNCTION NAME: CalculatePercentRoads
   PURPOSE:       calculate road percentage
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void IGrid::CalculatePercentRoads () throw()
{
  GRID_P excld;
  int i;
  char msg_buf[MAX_FILENAME_LEN]; 

  assert (total_pixels > 0);
#ifdef PACKING
  excld = mem_GetWGridPtr (__FILE__, func, __LINE__);
  _unpack ((char *) excluded.ptr,
           excld,
           total_pixels,
           -1);
#else
  excld = excluded.ptr;
#endif
  excld_count = util_count_pixels (total_pixels,
                                   excld,
                                   GE,
                                   100);
  if (total_pixels - excld_count <= 0)
  {
    sprintf (msg_buf, "mem_GetTotalPixels()=%d excld_count = %d\n",
             mem_GetTotalPixels (), excld_count);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  for (i = 0; i < road_count; i++)
  {
    percent_road[i] =
      (100.0 * road_pixel_count[i]) / (total_pixels - excld_count);
  }
#ifdef PACKING
  mem_GetWGridFree (__FILE__, func, __LINE__, excld);
#endif
}

/*
   FUNCTION NAME: TestForUrbanYear
   PURPOSE:       test if year matches an urban year
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool IGrid::TestForUrbanYear (int year) throw()
{
  int i;

  for (i = 0; i < urban_count; i++)
  {
    if (urban[i].year.digit == year)
      return true;
  }
  return false;
}

/*
   FUNCTION NAME: UrbanYear2Index
   PURPOSE:       convert an urban year into an urban index
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int IGrid::UrbanYear2Index (int year) throw()
{
  bool flag = false;
  int i;

  for (i = 0; i < urban_count; i++)
  {
    if (urban[i].year.digit == year)
    {
      flag = true;
      break;
    }
  }
  if (flag)
  {
    return i;
  }
  else
  {
    printf ("%s %u ERROR year=%u is not an urban year\n",
            __FILE__, __LINE__, year);
    EXIT (1);
  }
  return -1;
}

/*
   FUNCTION NAME: TestForRoadYear
   PURPOSE:       test if year is a road year
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
 
*/
bool IGrid::TestForRoadYear (int year) throw()
{
  int i;

  for (i = 0; i < road_count; i++)
  {
    if (road[i].year.digit == year)
      return true;
  }
  return false;
}








