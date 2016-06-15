#ifndef MEMORY_H
#define MEMORY_H
/*! \file memory_obj.h
    \brief Definition file for memory utilites.
    
    Definition file for memory utility functions.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "ugm_typedefs.h"
#include "scenario.h"
#include "proc.h"
#include "igrid.h"
#include "pgrid.h"


//! Memory Initialization routine
/*!
 */
void mem_Init(Scenario & scene, const IGrid & igrid,
               const PGrid & pgrid);

//! Log the memory partition to a file.
/*!
 */
void mem_LogPartition(Scenario & scene, const IGrid & igrid,
                      const PGrid & pgrid,
		      FILE* fp);

//! Return # bytes per grid rounded to a word boundary.
/*!
 */
int mem_GetPackedBytesPerGrid();

//! Returns the pointer to the next igrid.
/*!
 */
GRID_P mem_GetIGridPtr( char* owner );

//! Returns a pointer to the next pgrid.
/*!
 */
GRID_P mem_GetPGridPtr( char* owner );

//! Returns a pointer to the next wgrid.
/*!
 */
GRID_P mem_GetWGridPtr( char* module, char* who, int line );

//! Frees a wgrid.
/*!
 */
GRID_P mem_GetWGridFree( char* module, char* who, int line,GRID_P ptr );

//! Returns the total number of pixels.
/*!
 */
int mem_GetTotalPixels();

//! Check the memory.
/*!
 */
void mem_CheckMemory(FILE* fp,char* module, char* function, int line);

//! Invalidate the memory.
/*!
 */
void mem_ReinvalidateMemory(const Scenario & scene);

//! Return the number of bytes per grid rounded to word boundary.
/*!
 */
int memGetBytesPerGridRound();

//! Log the minimum number of free grids.
/*!
 */
void mem_LogMinFreeWGrids(FILE* fp);

//! Returns the memory log file pointer.
/*!
 */
FILE* mem_GetLogFP();

//! Close the memory log.
/*!
 */
void mem_CloseLog();

#endif
