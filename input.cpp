/*! \file input.cpp
    \brief Implementation file for the input utility functions
    
    Implementation file for the input utility functions.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include "ugm_typedefs.h"
#include "input.h"

/*
     MACROS 
 */
#define GIF_ID "GIF87a"
#define GIF_ROW_OFFSET 8
#define GIF_COL_OFFSET 6
#define GIF_RES_OFFSET 10
#define MAX_ANSWER_STR_LEN 20
#define MAX_DUMMY_STR_LEN 80
#define MAX_CMD_STR_LEN 120
#ifdef DEBUG
#define CHECK_EOF(arg0,arg1,arg2,arg3)                           \
  if((arg0) != 2)                                                \
  {                                                              \
    printf("%s Line %d EOF occurred while reading file: %s\n",   \
           (arg1),(arg2),(arg3));                                \
    EXIT(1);                                                     \
  }
#else
#define CHECK_EOF(arg0,arg1,arg2,arg3)
#endif

/* 
  FUNCTION NAME: inp_slurp
  PURPOSE:       read count chars from filename into ptr
  AUTHOR:        
  PROGRAMMER:    
  CREATION DATE: 11/11/1999
  DESCRIPTION:
 
 
 */
void
  inp_slurp (char *filename,
             void *ptr,
             int count)
{
  FILE *fp;
  int actual;
  char msg_buf[MAX_FILENAME_LEN]; 
  assert (filename != NULL);
  assert (ptr != NULL);
  assert (count > 0);

  FILE_OPEN (fp, (filename), "r");

  actual = fread (ptr, sizeof (char), count, fp);
  if (actual != count)
  {
    sprintf (msg_buf, "Read failed. %u bytes of %u read from file %s",
             actual, count, filename);
    LOG_ERROR (msg_buf);
  }
  fclose (fp);

}

/*
  FUNCTION NAME: inp_read_restart_file
  PURPOSE:       read the restart file
  AUTHOR:        
  PROGRAMMER:    
  CREATION DATE: 11/11/1999
  DESCRIPTION:
 
 
 */
void
  inp_read_restart_file (Scenario & scene, int *diffusion,
                         int *breed,
                         int *spread,
                         int *slope_resistance,
                         int *road_gravity,
                         long *random_seed,
                         int *counter, int mpi_rank)
{
  char filename[MAX_FILENAME_LEN];
  FILE *FileToRead;
  int rc;
  char msg_buf[MAX_FILENAME_LEN]; 
  
  assert (diffusion != NULL);
  assert (breed != NULL);
  assert (spread != NULL);
  assert (slope_resistance != NULL);
  assert (road_gravity != NULL);
  assert (random_seed != NULL);
  assert (counter != NULL);


  sprintf (filename, "%s%s%u", scene.GetOutputDir (), RESTART_FILE, mpi_rank);

  FILE_OPEN (FileToRead, filename, "r");

  /*
    Read the restart file
   */
  printf ("Reading restart file: %s\n", filename);
  rc = fscanf (FileToRead, "%d %d %d %d %d %ld %d",
               diffusion,
               breed,
               spread,
               slope_resistance,
               road_gravity,
               random_seed,
               counter);
  if (rc != 7)
  {
    sprintf (msg_buf, "EOF occurred when reading file %s", filename);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  fclose (FileToRead);

}
