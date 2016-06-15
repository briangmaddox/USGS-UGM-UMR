/*! \file landclass.cpp
    \brief Implementation file for the landclass object.
    
    Implementation file for the landclass object which
    stores landclass infomation during the simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "ugm_defines.h"
#include "ugm_macros.h"
#include "landclass.h"
#include "scenario.h"
#include "grid.h"
#include "memory_obj.h"
#include "utilities.h"


/*
 Main constructor which creates the landclass time.
*/
Landclass::Landclass (int inmpi_rank) : mpi_rank(inmpi_rank)
{}


/*
   FUNCTION NAME: GetReducedClassesPtr
   PURPOSE:       return ptr to class_indices
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
Classes * Landclass :: GetReducedClassesPtr ()
{
  return class_indices;
}

/*
   FUNCTION NAME: GetClassesPtr
   PURPOSE:       return ptr to landuse_classes
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
Classes * Landclass :: GetClassesPtr ()
{
  return landuse_classes;
}

/*
   FUNCTION NAME: GetNewIndicesPtr
   PURPOSE:       return ptr to new_indices
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int * Landclass :: GetNewIndicesPtr ()
{
  return new_indices;
}

/*
   FUNCTION NAME: GetUrbanCode
   PURPOSE:       return the urban code
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetUrbanCode () const
{
  return urban_code;
}

/*
   FUNCTION NAME: GetNumLandclasses
   PURPOSE:       return num_landclasses
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetNumLandclasses () const
{
  return num_landclasses;
}

/*
   FUNCTION NAME: GetNumReducedclasses
   PURPOSE:       return num_reduced_classes
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetNumReducedclasses () const
{
  return num_reduced_classes;
}

/*
   FUNCTION NAME: GetMaxLandclasses
   PURPOSE:       return max_num
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetMaxLandclasses () const
{
  return max_landclass_num;
}

/*
   FUNCTION NAME: GetClassNum
   PURPOSE:       return landclass num for a given index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetClassNum (int i) const
{
  return landuse_classes[i].num;
}

/*
   FUNCTION NAME: IsAlandclass
   PURPOSE:       test if val is a landclass value
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Landclass :: IsAlandclass (int val)
{
  bool rv = FALSE;
  int i;
  char msg_buf[MAX_FILENAME_LEN]; 

  if (!ugm_read)
  {
    sprintf (msg_buf, "landclasses file has not been read yet!");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }

  for (i = 0; i < num_landclasses; i++)
  {
    if (landuse_classes[i].num == val)
      rv = TRUE;
  }
  return rv;
}

/*
   FUNCTION NAME: GetClassIDX
   PURPOSE:       return idx for a given index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetClassIDX (int i) const
{
  return landuse_classes[i].idx;
}

/*
   FUNCTION NAME: GetClassColor
   PURPOSE:       return color val for given landclass
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetClassColor (int i) const
{
  return landuse_classes[i].red * 256 * 256 +
    landuse_classes[i].green * 256 + landuse_classes[i].blue;
}

/*
   FUNCTION NAME: GetClassEXC
   PURPOSE:       is this an excluded class
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Landclass :: GetClassEXC (int i) const
{
  return landuse_classes[i].EXC;
}

/*
   FUNCTION NAME: GetClassTrans
   PURPOSE:       is this a transition class
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Landclass :: GetClassTrans (int i) const
{
  return landuse_classes[i].trans;
}

/*
   FUNCTION NAME: GetReducedNum
   PURPOSE:       return class num for given class_indices index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetReducedNum (int i) const
{
  return class_indices[i].num;
}

/*
   FUNCTION NAME: GetReducedIDX
   PURPOSE:       return idx for a given class_indices index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetReducedIDX (int i) const
{
  return class_indices[i].idx;
}

/*
   FUNCTION NAME: GetReducedColor
   PURPOSE:       return color for given class_indices index
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int Landclass :: GetReducedColor (int i) const
{
  return class_indices[i].red * 256 * 256 +
    class_indices[i].green * 256 + class_indices[i].blue;
}

/*
   FUNCTION NAME: GetReducedEXC
   PURPOSE:       is class at class_indices[i] excluded
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Landclass :: GetReducedEXC (int i) const
{
  return class_indices[i].EXC;
}

/*
   FUNCTION NAME: GetReducedTrans
   PURPOSE:       is this a transition class
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
bool Landclass :: GetReducedTrans (int i) const
{
  return class_indices[i].trans;
}

/*
   FUNCTION NAME: AnnualProbInit
   PURPOSE:       initializes the annual_class_probabilities file with 0's
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Landclass :: AnnualProbInit ( Scenario &scen)
{
  FILE *fp;
  int i;
  int num_pixels;
  int num_written;
  int zero = 0;
  char msg_buf[MAX_FILENAME_LEN]; 

  sprintf (annual_prob_filename, "%sannual_class_probabilities_%u",
           scen.GetOutputDir (), mpi_rank);

  FILE_OPEN (fp, annual_prob_filename, "wb");

  num_pixels = mem_GetTotalPixels () * GetNumLandclasses ();
  for (i = 0; i < num_pixels; i++)
  {
    num_written = fwrite (&zero, sizeof (PIXEL), 1, fp);
    if (num_written != 1)
    {
      sprintf (msg_buf, "Unable to write to file: %s", annual_prob_filename);
      LOG_ERROR (msg_buf);
      sprintf (msg_buf, "%s", strerror (errno));
      LOG_ERROR (msg_buf);
      EXIT (1);
    }
  }
  
  fclose (fp);

}

/*
   FUNCTION NAME: AnnualProbUpdate
   PURPOSE:       update the annual_prob_filename
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Landclass :: AnnualProbUpdate (GRID_P land1_ptr, Scenario &scen)
{
  char func[] = "AnnualProbUpdate";
  FILE *fp;
  int total_pixels;
  int i;
  int cc;
  int rc;
  int offset;
  fpos_t pos_ptr;
  GRID_P current_class_ptr;
  char msg_buf[MAX_FILENAME_LEN]; 

  if (!scen.GetDoingLanduseFlag ())
  {
    return;
  }

  current_class_ptr = mem_GetWGridPtr (__FILE__, func, __LINE__);
  total_pixels = mem_GetTotalPixels ();
  if (scen.GetLogFlag ())
  {
    scen.Append2Log ();
    if (scen.GetLogWritesFlag ())
    {
      fprintf (scen.GetLogFP (), "%s %u updating file %s\n",
               __FILE__, __LINE__, annual_prob_filename);
    }
    scen.CloseLog ();
  }

  FILE_OPEN (fp, annual_prob_filename, "r+b");

  for (cc = 0; cc < GetNumLandclasses (); cc++)
  {
    offset = cc * total_pixels * sizeof (PIXEL);
    rc = fseek (fp, offset, SEEK_SET);
    if (rc != 0)
    {
      printf ("%s %u ERROR\n", __FILE__, __LINE__);
      EXIT (1);
    }
    rc = fgetpos (fp, &pos_ptr);
    if (rc != 0)
    {
      printf ("%s %u ERROR\n", __FILE__, __LINE__);
      EXIT (1);
    }
    rc = fread (current_class_ptr, total_pixels * sizeof (PIXEL), 1, fp);
    if (feof (fp) || ferror (fp))
    {
      printf ("%s %u ERROR\n", __FILE__, __LINE__);
      EXIT (1);
    }
    for (i = 0; i < total_pixels; i++)
    {
      if (cc == new_indices[land1_ptr[i]])
      {
        (current_class_ptr[i])++;
      }
    }
    rc = fsetpos (fp, &pos_ptr);
    if (rc != 0)
    {
      printf ("%s %u ERROR\n", __FILE__, __LINE__);
      EXIT (1);
    }
    rc = fwrite (current_class_ptr, total_pixels * sizeof (PIXEL), 1, fp);
    if (rc != 1)
    {
      printf ("%s %u ERROR\n", __FILE__, __LINE__);
      EXIT (1);
    }
  }
  fclose (fp);
  current_class_ptr = mem_GetWGridFree (__FILE__,
                                        func,
                                        __LINE__,
                                        current_class_ptr);
}

/*
   FUNCTION NAME: BuildProbImage
   PURPOSE:       build prob images from annual_prob_filename
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Landclass :: BuildProbImage (GRID_P cum_probability_ptr,
                                  GRID_P cum_uncertainty_ptr, Scenario &scen)
{
  char func[] = "BuildProbImage";
  char command[2 * MAX_FILENAME_LEN + 20];
  int total_pixels;
  GRID_P max_grid;
  GRID_P sum_grid;
  GRID_P inp_grid;
  int num_landclasses;
  int i;
  int k;
  FILE *fp;
  char msg_buf[MAX_FILENAME_LEN]; 
  
  num_landclasses = GetNumLandclasses ();
  total_pixels = mem_GetTotalPixels ();

  max_grid = mem_GetWGridPtr (__FILE__, func, __LINE__);
  sum_grid = mem_GetWGridPtr (__FILE__, func, __LINE__);
  inp_grid = mem_GetWGridPtr (__FILE__, func, __LINE__);
  assert (sum_grid != NULL);
  assert (max_grid != NULL);
  assert (inp_grid != NULL);
  assert (cum_probability_ptr != NULL);
  assert (cum_uncertainty_ptr != NULL);
  assert (num_landclasses > 0);
  assert (total_pixels > 0);

  

  FILE_OPEN (fp, annual_prob_filename, "rb");

  /*
   
    READ IN THE K=0 LANDCLASS DATA
   
   */
  fread (max_grid, sizeof (PIXEL), total_pixels, fp);
  if (feof (fp) || ferror (fp))
  {
    sprintf (msg_buf, "reading file: %s", annual_prob_filename);
    LOG_ERROR (msg_buf);
    sprintf (msg_buf, "%s", strerror (errno));
    LOG_ERROR (msg_buf);
    EXIT (1);
  }

  /*
   
    INITIALIZE SUM_GRID
   
   */
  memcpy (sum_grid, max_grid, sizeof (PIXEL) * total_pixels);

  for (k = 1; k < num_landclasses; k++)
  {
    /*
     
      READ IN THE K=0 LANDCLASS DATA
     
     */
    fread (inp_grid, sizeof (PIXEL), total_pixels, fp);
    if (feof (fp) || ferror (fp))
    {
      sprintf (msg_buf, "reading file: %s", annual_prob_filename);
      LOG_ERROR (msg_buf);
      sprintf (msg_buf, "%s", strerror (errno));
      LOG_ERROR (msg_buf);
      EXIT (1);
    }

    /*
     
      NOW LOOK FOR THE MAX OF THE MAX AND THE SUM
     
     */
    for (i = 0; i < total_pixels; i++)
    {
      if (inp_grid[i] > max_grid[i])
      {
        max_grid[i] = inp_grid[i];
        cum_probability_ptr[i] = k;
      }
      sum_grid[i] += inp_grid[i];
    }
  }
  fclose (fp);
  sprintf (command, "rm %s", annual_prob_filename);
  system (command);


  /*
   
    CALCULATE THE CUM_UNCERTAINTY GRID
   
   */
  for (i = 0; i < total_pixels; i++)
  {
    if (sum_grid[i] != 0)
    {
      cum_uncertainty_ptr[i] = 100 - (100 * max_grid[i]) / sum_grid[i];
    }
    else
    {
      sprintf (msg_buf, "divide by zero: sum_grid[%u] = %ld", i, sum_grid[i]);
      LOG_ERROR (msg_buf);
      EXIT (1);
    }
  }
  max_grid = mem_GetWGridFree (__FILE__, func, __LINE__, max_grid);
  sum_grid = mem_GetWGridFree (__FILE__, func, __LINE__, sum_grid);
  inp_grid = mem_GetWGridFree (__FILE__, func, __LINE__, inp_grid);
}

/*
   FUNCTION NAME: Init
   PURPOSE:       initialization routine for landclasses
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Landclass :: Init ()
{
  SetMaxLandclassNum ();
  MapLandclassNum_2_idx ();
  CreateReducedClasses ();
  SetUrbanCode ();
  ugm_read = TRUE;
}

/*
   FUNCTION NAME: SetUrbanCode
   PURPOSE:       set the urban code field
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Landclass :: SetUrbanCode ()
{
  int i;
  assert (num_landclasses > 0);
  /*
   
    FIND URBAN CODE
   
   */
  for (i = 0; i < num_landclasses; i++)
  {
    if (!strcmp (landuse_classes[i].id, "URB"))
    {
      urban_code = landuse_classes[i].num;
    }
  }
  assert (urban_code > 0);
}

/*
   FUNCTION NAME: CreateReducedClasses
   PURPOSE:       create the reduced classes
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Landclass :: CreateReducedClasses ()
{
  int i;
  int reduced_count = 0;

  /*
   
    CREATE REDUCED CLASSES ARRAY
   
   */
  for (i = 0; i < num_landclasses; i++)
  {
    if (strcmp (landuse_classes[i].id, "EXC") &&
        strcmp (landuse_classes[i].id, "URB") &&
        strcmp (landuse_classes[i].id, "UNC"))
    {
      class_indices[reduced_count].num = landuse_classes[i].num;
      class_indices[reduced_count].idx = i;
      strcpy (class_indices[reduced_count].name, landuse_classes[i].name);
      strcpy (class_indices[reduced_count].id, landuse_classes[i].id);
      class_indices[reduced_count].EXC = landuse_classes[i].EXC;
      class_indices[reduced_count].trans = landuse_classes[i].trans;
      class_indices[reduced_count].red = landuse_classes[i].red;
      class_indices[reduced_count].green = landuse_classes[i].green;
      class_indices[reduced_count].blue = landuse_classes[i].blue;
      reduced_count++;
    }
  }
  num_reduced_classes = reduced_count;
}

/*
   FUNCTION NAME: MapLandclassNum_2_idx
   PURPOSE:       CREATE MAPPING FROM LANDUSE CLASS NUM BACK INTO IDX
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void Landclass :: MapLandclassNum_2_idx ()
{
  int i;
  int idx;
  /*
   
    CREATE MAPPING FROM LANDUSE CLASS NUM BACK INTO IDX
   
   */
  for (i = 0; i < MAX_NEW_INDICES; i++)
  {
    new_indices[i] = 0;
  }
  for (idx = 0; idx < num_landclasses; idx++)
  {
    new_indices[landuse_classes[idx].num] = idx;
  }
}

/*
   FUNCTION NAME: landclassSetNumClasses
   PURPOSE:       set num_landclasses
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
void Landclass :: SetNumClasses (int val)
{
  assert (val >= 0);
  assert (val < 256);
  num_landclasses = val;
}

/*
   FUNCTION NAME: landclassSetName
   PURPOSE:       set name
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
void Landclass :: SetName (int index, const char *string)
{
  assert (index >= 0);
  assert (index < num_landclasses);
  strcpy (landuse_classes[index].name, string);
}

/*
   FUNCTION NAME: landclassSetType
   PURPOSE:       set Type
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
void Landclass :: SetType (int index, const char *string)
{
  assert (index >= 0);
  assert (index < num_landclasses);
  strcpy (landuse_classes[index].id, string);
  landuse_classes[index].EXC =
    strcmp (landuse_classes[index].id, "EXC");
  landuse_classes[index].trans = TRUE;
  if (strcmp (landuse_classes[index].id, "EXC") == 0)
  {
    landuse_classes[index].trans = FALSE;
  }
  if (strcmp (landuse_classes[index].id, "EXC") > 0)
  {
    landuse_classes[index].trans = FALSE;
  }
}

/*
   FUNCTION NAME: landclassSetColor
   PURPOSE:       set Color
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
void Landclass :: SetColor (int index, int val)
{
  assert (index >= 0);
  assert (index < num_landclasses);
  landuse_classes[index].red = (val & RED_MASK) >> 16;
  landuse_classes[index].green = (val & GREEN_MASK) >> 8;
  landuse_classes[index].blue = val & BLUE_MASK;
}

/*
   FUNCTION NAME: landclassSetGrayscale
   PURPOSE:       set Grayscale
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 12/1/2000
   DESCRIPTION:
  
  
*/
void Landclass :: SetGrayscale (int index, int val)
{
  assert (index >= 0);
  assert (index < num_landclasses);
  landuse_classes[index].num = val;
}


/*
   FUNCTION NAME: SetMaxLandclassNum
   PURPOSE:       set the max landclass val
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
 
*/
void Landclass :: SetMaxLandclassNum ()
{
  int i;
  int max = 0;
  char msg_buf[MAX_FILENAME_LEN]; 
  /*
   Find max
   */
  for (i = 0; i < num_landclasses; i++)
  {
    max = MAX (max, landuse_classes[i].num);
  }
  if (max >= MAX_NEW_INDICES)
  {
    sprintf (msg_buf, "The maximum class number = %d in file:%s\n",
             max, filename);
    strcat (msg_buf, "exceeds MAX_NEW_INDICES. Increase the value of \n");
    strcat (msg_buf,
    "MAX_NEW_INDICES and recompile or reduce the landuse class number\n");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  max_landclass_num = max;
}
