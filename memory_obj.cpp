/*! \file memory_obj.cpp
    \brief Implemention file for memory utilites.
    
    Implementation file for memory utility functions.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "igrid.h"
#include "pgrid.h"
#include "scenario.h"
#include "ugm_typedefs.h"
#include "ugm_macros.h"
#include "memory_obj.h"


#define MEM_ARRAY_SIZE 50
#define INVALID_VAL 0xAAAAAAAA

//! Struct to keep track of memory.
typedef struct
{
  char previous_owner[MAX_FILENAME_LEN];
  char current_owner[MAX_FILENAME_LEN];
  char released_by[MAX_FILENAME_LEN];
  BOOLEAN free;
  GRID_P ptr;
}
mem_track_info;
static int nrows;
static int ncols;
static int total_pixels;
static PIXEL invalid_val;
static int igrid_free[MEM_ARRAY_SIZE];
static int igrid_free_tos;
static mem_track_info igrid_array[MEM_ARRAY_SIZE];
static int pgrid_free[MEM_ARRAY_SIZE];
static int pgrid_free_tos;
static mem_track_info pgrid_array[MEM_ARRAY_SIZE];
static int wgrid_free[MEM_ARRAY_SIZE];
static int wgrid_free_tos;
static int min_wgrid_free_tos;
static mem_track_info wgrid_array[MEM_ARRAY_SIZE];
static PIXEL *mem_check_array[MEM_ARRAY_SIZE];
static int mem_check_count;
static int mem_check_size;
static int igrid_size;
static int pgrid_size;
static int wgrid_size;
static int bytes_p_grid;
static int bytes_p_grid_rounded2wordboundary;
static int bytes_p_packed_grid;
static int bytes_p_packed_grid_rounded2wordboundary;
static int bytes2allocate;
static void *mem_ptr;
static int igrid_count;
static int pgrid_count;
static int wgrid_count;
static FILE *memlog_fp;
static char mem_log_filename[MAX_FILENAME_LEN];

/*
  STATIC FUNCTION PROTOTYPES  
*/
static void mem_CheckCheckArray ();
static void mem_partition (const IGrid & igrid, const PGrid &pgrid, 
 			   Scenario & scene, FILE* fp);
static void mem_allocate (Scenario & scene);
static void mem_igrid_push (int i);
static int mem_igrid_pop ();
static void mem_pgrid_push (int i);
static int mem_pgrid_pop ();
static void mem_wgrid_push (int i);
static int mem_wgrid_pop ();
static void mem_InvalidateGrid (GRID_P ptr);
static void mem_CheckInvalidateGrid (GRID_P ptr);
static void mem_InvalidateCheckArray ();
void mem_Init ();
GRID_P mem_GetIGridPtr (char *owner);
GRID_P mem_GetPGridPtr (char *owner);
GRID_P mem_GetWGridPtr (char *module, char *who, int line);
GRID_P mem_GetWGridFree (char *module, char *who, int line, GRID_P ptr);



/*
  
   FUNCTION NAME: mem_GetPackedBytesPerGrid
   PURPOSE:       return # bytes per grid rounded to a word boundary
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int
  mem_GetPackedBytesPerGrid ()
{
  return bytes_p_packed_grid_rounded2wordboundary;
}

/*
   FUNCTION NAME: mem_GetTotalPixels
   PURPOSE:       return total pixel count in a grid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int
  mem_GetTotalPixels ()
{
  return total_pixels;
}

/*
   FUNCTION NAME: mem_GetIGridPtr
   PURPOSE:       return the pointer to the next igrid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P
  mem_GetIGridPtr (char *owner)
{
  int index;

  index = mem_igrid_pop ();
  strcpy (igrid_array[index].current_owner, owner);
  return igrid_array[index].ptr;
}

/*
   FUNCTION NAME: mem_GetPGridPtr
   PURPOSE:       return ptr to next pgrid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P
  mem_GetPGridPtr (char *owner)
{
  int index;

  index = mem_pgrid_pop ();
  strcpy (pgrid_array[index].current_owner, owner);
  return pgrid_array[index].ptr;
}

/*
   FUNCTION NAME: mem_GetWGridPtr
   PURPOSE:       return ptr to next wgrid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P
  mem_GetWGridPtr (char *module, char *who, int line)
{
  int index;

  index = mem_wgrid_pop ();
  strcpy (wgrid_array[index].previous_owner, wgrid_array[index].current_owner);
  sprintf (wgrid_array[index].current_owner,
           "Module: %s Function: %s Line %u", module, who, line);
  return wgrid_array[index].ptr;
}

/*
   FUNCTION NAME: mem_GetWGridFree
   PURPOSE:       
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
GRID_P
  mem_GetWGridFree (char *module, char *who, int line, GRID_P ptr)
{
  int i;
  int index(0);
  BOOLEAN match = FALSE;
  char msg_buf[MAX_FILENAME_LEN]; 

  for (i = 0; i < wgrid_count; i++)
  {
    if (wgrid_array[i].ptr == ptr)
    {
      match = TRUE;
      index = i;
      break;
    }
  }
  if (match == FALSE)
  {
    sprintf (msg_buf, "%s %u look in module %s %s %u\n",
             __FILE__, __LINE__, module, who, line);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  if (wgrid_array[index].free == TRUE)
  {
    sprintf (msg_buf, "wgrid_array[%u].free == TRUE", index);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  strcpy (wgrid_array[index].current_owner, "");
  sprintf (wgrid_array[index].released_by,
           "Module: %s Function: %s Line %u", module, who, line);
  mem_wgrid_push (index);
  return NULL;
}

/*
   FUNCTION NAME: mem_Init
   PURPOSE:       initialization routine
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void mem_Init (Scenario & scene, const IGrid & igrid,
               const PGrid & pgrid)
{
  int check_pixel_count;
  char msg_buf[MAX_FILENAME_LEN]; 

  sprintf (mem_log_filename, "%smemory.log", scene.GetOutputDir ());

  memlog_fp = NULL;
  if (scene.GetLogMemoryMapFlag ())
  {
    FILE_OPEN (memlog_fp, mem_log_filename, "w");
  }

  invalid_val = INVALID_VAL;
  igrid_free_tos = 0;
  pgrid_free_tos = 0;
  wgrid_free_tos = 0;
  nrows = igrid.GetNumRows ();
  ncols = igrid.GetNumCols ();
  total_pixels = nrows * ncols;
  igrid_count = igrid.GetIGridCount ();
  pgrid_count = pgrid.GetPGridCount ();
  wgrid_count =  scene.GetNumWorkingGrids();

  check_pixel_count = igrid_count + pgrid_count + wgrid_count + 1;

  bytes_p_grid = BYTES_PER_PIXEL * total_pixels;
  bytes_p_grid_rounded2wordboundary =
    ROUND_BYTES_TO_WORD_BNDRY (bytes_p_grid);
#ifdef PACKING
  bytes_p_packed_grid = BYTES_PER_PIXEL_PACKED * total_pixels;
  bytes_p_packed_grid_rounded2wordboundary =
    ROUND_BYTES_TO_WORD_BNDRY (bytes_p_packed_grid);
  bytes2allocate = igrid_count * bytes_p_packed_grid_rounded2wordboundary +
    pgrid_count * bytes_p_grid_rounded2wordboundary +
    wgrid_count * bytes_p_grid_rounded2wordboundary +
    check_pixel_count * BYTES_PER_PIXEL;
  igrid_size = bytes_p_packed_grid_rounded2wordboundary / BYTES_PER_WORD;
#else
  bytes2allocate = igrid_count * bytes_p_grid_rounded2wordboundary +
    pgrid_count * bytes_p_grid_rounded2wordboundary +
    wgrid_count * bytes_p_grid_rounded2wordboundary +
    check_pixel_count * BYTES_PER_PIXEL;
  igrid_size = bytes_p_grid_rounded2wordboundary / BYTES_PER_WORD;
#endif
  mem_check_size = 1;
  pgrid_size = bytes_p_grid_rounded2wordboundary / BYTES_PER_WORD;
  wgrid_size = bytes_p_grid_rounded2wordboundary / BYTES_PER_WORD;


  if (memlog_fp)
  {
    fprintf (memlog_fp, "nrows = %u\n", nrows);
    fprintf (memlog_fp, "ncols = %u\n", ncols);
    fprintf (memlog_fp, "total_pixels = %u\n", total_pixels);
    fprintf (memlog_fp, "igrid_count = %u\n", igrid_count);
    fprintf (memlog_fp, "pgrid_count = %u\n", pgrid_count);
    fprintf (memlog_fp, "wgrid_count = %u\n", wgrid_count);
    fprintf (memlog_fp, "check_pixel_count = %u\n", check_pixel_count);
    fprintf (memlog_fp, "WORD_BIT = %u\n", WORD_BIT);
    fprintf (memlog_fp, "BYTES_PER_WORD = %u\n", BYTES_PER_WORD);
    fprintf (memlog_fp, "BYTES_PER_PIXEL = %u\n", BYTES_PER_PIXEL);
    fprintf (memlog_fp, "bytes_p_grid = %u\n", bytes_p_grid);
    fprintf (memlog_fp, "bytes_p_grid_rounded2wordboundary = %u\n",
             bytes_p_grid_rounded2wordboundary);
    fprintf (memlog_fp, "words in a grid = %u\n",
             bytes_p_grid_rounded2wordboundary / BYTES_PER_WORD);
#ifdef PACKING
    fprintf (memlog_fp, "BYTES_PER_PIXEL_PACKED = %u\n",
             BYTES_PER_PIXEL_PACKED);
    fprintf (memlog_fp, "bytes_p_packed_grid = %u\n", bytes_p_packed_grid);
    fprintf (memlog_fp, "bytes_p_packed_grid_rounded2wordboundary = %u\n",
             bytes_p_packed_grid_rounded2wordboundary);
#endif
    fprintf (memlog_fp, "igrid_size = %u words\n", igrid_size);
    fprintf (memlog_fp, "pgrid_size = %u words\n", pgrid_size);
    fprintf (memlog_fp, "wgrid_size = %u words\n", wgrid_size);
    fprintf (memlog_fp, "mem_check_size = %u words\n", mem_check_size);
    fprintf (memlog_fp, "bytes2allocate = %u\n", bytes2allocate);
  }

  mem_allocate (scene);
  mem_partition (igrid, pgrid, 
                 scene, memlog_fp);
  mem_InvalidateCheckArray ();
  mem_CloseLog ();
}

/*
   FUNCTION NAME: mem_GetLogFP
   PURPOSE:       return memory log fp
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
FILE *
  mem_GetLogFP ()
{
  char msg_buf[MAX_FILENAME_LEN]; 
  if (memlog_fp == NULL)
  {
    FILE_OPEN (memlog_fp, mem_log_filename, "a");
  }
  return memlog_fp;
}

/*
   FUNCTION NAME: mem_CloseLog
   PURPOSE:       close log file
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void
  mem_CloseLog ()
{
  /*  fclose (memlog_fp);*/
  if (memlog_fp != NULL) fclose (memlog_fp);
  memlog_fp = NULL;
}

/*
   FUNCTION NAME: mem_CheckMemory
   PURPOSE:       check memory
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void
  mem_CheckMemory (FILE * fp, char *module, char *function, int line)
{
 
  int i;
  int j;
  char msg_buf[MAX_FILENAME_LEN]; 

  fprintf (fp, "%s %u MEMORY CHECK at %s %s %u\n",
           __FILE__, __LINE__, module, function, line);
  mem_CheckCheckArray ();
  for (i = 0; i < wgrid_count; i++)
  {
    if (wgrid_array[i].free)
    {
#ifdef MEMORY_CHECK_LEVEL3
      for (j = 0; j < total_pixels; j++)
      {
        if (wgrid_array[i].ptr[j] != invalid_val)
        {
          sprintf (msg_buf, "grid %d is not invalid", wgrid_array[i].ptr);
          LOG_ERROR (msg_buf);
          sprintf (msg_buf, "current_owner: %s", wgrid_array[i].current_owner);
          LOG_ERROR (msg_buf);
          sprintf (msg_buf, "previous_owner: %s", wgrid_array[i].previous_owner);
          LOG_ERROR (msg_buf);
          EXIT (1);
        }
      }
#endif
    }
    else
    {
      for (j = 0; j < total_pixels; j++)
      {
        if (!((0 <= wgrid_array[i].ptr[j]) && (wgrid_array[i].ptr[j] < 256)))
        {
          sprintf (msg_buf, "grid %d is out of range", 
                   reinterpret_cast<unsigned int>(wgrid_array[i].ptr));
          LOG_ERROR (msg_buf);
          sprintf (msg_buf, "current_owner: %s", wgrid_array[i].current_owner);
          LOG_ERROR (msg_buf);
          sprintf (msg_buf, "previous_owner: %s", wgrid_array[i].previous_owner);
          LOG_ERROR (msg_buf);
          EXIT (1);
        }
      }
    }
  }
  fprintf (fp, "MEMORY CHECK OK\n");
}

/*
   FUNCTION NAME: mem_InvalidateCheckArray
   PURPOSE:       invalidate the check memory array elements
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_InvalidateCheckArray ()
{
  int i;
  for (i = 0; i < mem_check_count; i++)
  {
    *(mem_check_array[i]) = invalid_val;
  }
}

/*
   FUNCTION NAME: mem_CheckCheckArray
   PURPOSE:       memory check
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_CheckCheckArray ()
{

  int i;
  char msg_buf[MAX_FILENAME_LEN]; 
  for (i = 0; i < mem_check_count; i++)
  {
    if (*(mem_check_array[i]) != invalid_val)
    {
      sprintf (msg_buf, "ptr = %d failed memory check", 
               reinterpret_cast<unsigned int>(mem_check_array[i]));
      LOG_ERROR (msg_buf);
      sprintf (msg_buf, "i=%lu *ptr=%X invalid_val=%X",
               i, 
              *(mem_check_array[i]), 
               invalid_val);
      LOG_ERROR (msg_buf);
      EXIT (1);
    }
  }
}

/*
   FUNCTION NAME: mem_partition
   PURPOSE:       partition the memory
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_partition (const IGrid & igrid, const PGrid & pgrid, 
  		 Scenario & scene, FILE * fp)
{
  int i;
  PIXEL *temp_ptr = (PIXEL *) mem_ptr;
  PIXEL *end_ptr;


  if (fp)
  {
    end_ptr = (temp_ptr + bytes2allocate / (WORD_BIT / 8));
    fprintf (fp, "\n\nMemory starts at %d and ends at %d\n",
             reinterpret_cast<int>(temp_ptr), 
             reinterpret_cast<int>(end_ptr));
  }
  mem_check_count = 0;
  for (i = 0; i < igrid.GetIGridCount (); i++)
  {
    mem_check_array[mem_check_count++] = temp_ptr;
    temp_ptr += mem_check_size;
    igrid_array[i].ptr = (GRID_P) temp_ptr;
    temp_ptr += igrid_size;
    strcpy (igrid_array[i].current_owner, "");
    mem_igrid_push (i);
    if (fp)
    {
      fprintf (fp, "%d mem_check_array[%2u]\n",
               mem_check_array[mem_check_count - 1], mem_check_count - 1);
      fprintf (fp, "%d igrid_array[%2u]\n", igrid_array[i].ptr, i);
    }
  }

  for (i = 0; i < pgrid.GetPGridCount (); i++)
  {
    mem_check_array[mem_check_count++] = temp_ptr;
    temp_ptr += mem_check_size;
    pgrid_array[i].ptr = (GRID_P) temp_ptr;
    temp_ptr += pgrid_size;
    strcpy (pgrid_array[i].current_owner, "");
    mem_pgrid_push (i);
    if (fp)
    {
      fprintf (fp, "%d mem_check_array[%2u]\n",
               mem_check_array[mem_check_count - 1], mem_check_count - 1);
      fprintf (fp, "%d pgrid_array[%2u]\n", pgrid_array[i].ptr, i);
    }
  }

  for (i = 0; i <  scene.GetNumWorkingGrids(); i++)
  {
    mem_check_array[mem_check_count++] = temp_ptr;
    temp_ptr += mem_check_size;
    wgrid_array[i].ptr = (GRID_P) temp_ptr;
    mem_InvalidateGrid (wgrid_array[i].ptr);
    temp_ptr += wgrid_size;
    strcpy (wgrid_array[i].current_owner, "");
    mem_wgrid_push (i);
    if (fp)
    {
      fprintf (fp, "%d mem_check_array[%2u]\n",
               mem_check_array[mem_check_count - 1], mem_check_count - 1);
      fprintf (fp, "%d wgrid_array[%2u]\n", wgrid_array[i].ptr, i);
    }
  }
  mem_check_array[mem_check_count++] = temp_ptr;
  if (fp)
  {
    fprintf (fp, "%d mem_check_array[%2u]\n",
             mem_check_array[mem_check_count - 1], mem_check_count - 1);
    fprintf (fp, "%d End of memory \n", end_ptr);
  }
  min_wgrid_free_tos = wgrid_free_tos;

}

/*
   FUNCTION NAME: mem_InvalidateGrid
   PURPOSE:       invalidate a grid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_InvalidateGrid (GRID_P ptr)
{
  int i;

  for (i = 0; i < total_pixels; i++)
  {
    ptr[i] = invalid_val;
  }
}

/*
   FUNCTION NAME: mem_CheckInvalidateGrid
   PURPOSE:       memory check a grid
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_CheckInvalidateGrid (GRID_P ptr)
{
  char func[] = "mem_CheckInvalidateGrid";
  int i;
  char msg_buf[MAX_FILENAME_LEN]; 

  for (i = 0; i < total_pixels; i++)
  {
    if (ptr[i] != invalid_val)
    {
      sprintf (msg_buf, "grid %d is not invalid", ptr);
      LOG_ERROR (msg_buf);
      EXIT (1);
    }
  }
}

/*
   FUNCTION NAME: mem_allocate
   PURPOSE:       allocate memory
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_allocate (Scenario & scene)
{
  char msg_buf[MAX_FILENAME_LEN]; 
  mem_ptr = malloc (bytes2allocate);
  if (mem_ptr == NULL)
  {
    sprintf (msg_buf, "Unable to allocate %u bytes of memory", bytes2allocate);
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  if (scene.GetLogFlag ())
  {
    scene.Append2Log ();
    fprintf (scene.GetLogFP (), "%s %u Allocated %u bytes of memory\n",
             __FILE__, __LINE__, bytes2allocate);
    scene.CloseLog ();
  }

  memset (mem_ptr, 0, bytes2allocate);
}

/*
   FUNCTION NAME: mem_igrid_push
   PURPOSE:       push igrid onto a stack
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_igrid_push (int i)
{
  char msg_buf[MAX_FILENAME_LEN]; 
  if (igrid_free_tos >= 50)
  {
    sprintf (msg_buf, "igrid_free_tos >= 50");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  igrid_free[igrid_free_tos] = i;
  igrid_array[i].free = TRUE;
  igrid_free_tos++;
}

/*
   FUNCTION NAME: mem_igrid_pop
   PURPOSE:       pop an igrid from the stack
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static int
  mem_igrid_pop ()
{
  char msg_buf[MAX_FILENAME_LEN]; 
  igrid_free_tos--;
  if (igrid_free_tos < 0)
  {
    sprintf (msg_buf, "igrid_free_tos < 0");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  igrid_array[igrid_free_tos].free = FALSE;
  return igrid_free[igrid_free_tos];
}

/*
   FUNCTION NAME: mem_pgrid_push
   PURPOSE:       push a pgrid onto a stack
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_pgrid_push (int i)
{
  char msg_buf[MAX_FILENAME_LEN]; 
  if (pgrid_free_tos >= 50)
  {
    sprintf (msg_buf, "pgrid_free_tos >= 50");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  pgrid_free[pgrid_free_tos] = i;
  pgrid_array[i].free = TRUE;
  pgrid_free_tos++;
}

/*
   FUNCTION NAME: mem_pgrid_pop
   PURPOSE:       pop a pgrid from the stack
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static int
  mem_pgrid_pop ()
{
  char msg_buf[MAX_FILENAME_LEN]; 
  pgrid_free_tos--;
  if (pgrid_free_tos < 0)
  {
    sprintf (msg_buf, "pgrid_free_tos < 0");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  pgrid_array[pgrid_free_tos].free = FALSE;
  return pgrid_free[pgrid_free_tos];
}

/*
   FUNCTION NAME: mem_wgrid_push
   PURPOSE:       push a wgrid onto the stack
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static void
  mem_wgrid_push (int i)
{
  char msg_buf[MAX_FILENAME_LEN]; 
  if (wgrid_free_tos >= 50)
  {
    sprintf (msg_buf, "wgrid_free_tos >= 50");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  wgrid_free[wgrid_free_tos] = i;
  wgrid_array[i].free = TRUE;
#ifdef MEMORY_CHECK_LEVEL3
  mem_InvalidateGrid (wgrid_array[i].ptr);
#endif
  wgrid_free_tos++;
}

/*
   FUNCTION NAME: mem_wgrid_pop
   PURPOSE:       pop a wgrid from the stack
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
static int
  mem_wgrid_pop ()
{
  char msg_buf[MAX_FILENAME_LEN]; 
  wgrid_free_tos--;
  if (wgrid_free_tos < 0)
  {
    sprintf (msg_buf, "wgrid_free_tos < 0");
    LOG_ERROR (msg_buf);
    sprintf (msg_buf, "Increase NUM_WORKING_GRIDS in scenario file");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  wgrid_array[wgrid_free[wgrid_free_tos]].free = FALSE;
  min_wgrid_free_tos = MIN (min_wgrid_free_tos, wgrid_free_tos);
#ifdef MEMORY_CHECK_LEVEL3
  mem_CheckInvalidateGrid (wgrid_array[wgrid_free[wgrid_free_tos]].ptr);
#endif
  return wgrid_free[wgrid_free_tos];
}

/*
   FUNCTION NAME: mem_ReinvalidateMemory
   PURPOSE:       invalidate the memory
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void
  mem_ReinvalidateMemory (Scenario & scene)
{
  int i;

  for (i = 0; i <  scene.GetNumWorkingGrids(); i++)
  {
    mem_InvalidateGrid (wgrid_array[i].ptr);
  }
  mem_InvalidateCheckArray ();
}

/*
   FUNCTION NAME: memGetBytesPerGridRound
   PURPOSE:       return # bytes per grid rounded to word boundary
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
int
  memGetBytesPerGridRound ()
{
  return bytes_p_grid_rounded2wordboundary;
}

/*
   FUNCTION NAME: mem_LogMinFreeWGrids
   PURPOSE:       log the minmum # of free grids
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void
  mem_LogMinFreeWGrids (FILE * fp)
{
  fprintf (fp, "Minmum number of Free working grids=%u\n",
           min_wgrid_free_tos);
  fprintf (fp,
   "For max efficiency of memory usage reduce NUM_WORKING_GRIDS by %u\n",
           min_wgrid_free_tos);
}

/*
   FUNCTION NAME: mem_LogPartition
   PURPOSE:       log memory partition to FILE * fp_in
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void
  mem_LogPartition (Scenario & scene, const IGrid & igrid,
                    const PGrid & pgrid,
		    FILE * fp_in)
{
  int i;
  FILE *fp;

  fp = fp_in ? fp_in : stdout;
  if (!((fp == stdout) && (!scene.GetEchoFlag ())))
  {
    for (i = 0; i < igrid.GetIGridCount (); i++)
    {
      fprintf (fp, "%d igrid_array[%u].ptr\n", igrid_array[i].ptr, i);
    }
    for (i = 0; i < pgrid.GetPGridCount (); i++)
    {
      fprintf (fp, "pgrid_array[%u].ptr = %d\n", i, pgrid_array[i].ptr);
    }
    for (i = 0; i <  scene.GetNumWorkingGrids(); i++)
    {
      fprintf (fp, "wgrid_array[%u].ptr = %d\n", i, wgrid_array[i].ptr);
    }
    for (i = 0; i < mem_check_count; i++)
    {
      fprintf (fp, "mem_check_array[%u].ptr = %d\n", i, mem_check_array[i]);
    }
  }
}
