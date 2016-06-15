#ifndef IGRID_H
#define IGRID_H
/*! \file igrid.h
    \brief Definition file for the input grid object.
    
    Definition file for the input grid object which keeps track
    of all input layers.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "grid.h"
#include "ugm_typedefs.h"
#include "landclass.h"
#include "proc.h"
#include "ProjectionParams.h"

//! Input layer management class.
class IGrid
{
 public:
  
  //! Performs input grid validation.
  /*! \param lclasses the landclass object to valid with.
      \param fp is a file to write the result to.
   */
  void ValidateGrids (Landclass & lclasses, FILE* fp) throw();
  
  //! Read all the input layers specified in the scenario file.
  /*!
   */
  void ReadFiles(Scenario & scene) throw();
  
  //! Returns the # of igrids (or input grids).
  /*!
   */
  int GetIGridCount() const throw();

  //! Returns the # rows in a grid.
  /*!
   */
  int GetNumRows() const throw();
  
  //! Returns the number of cols in a grid.
  /*!
   */
  int GetNumCols() const throw();
  
  //! Returns the total number of pixels in a grid.
  /*!
   */
  int GetNumTotalPixels() const throw();
  
  //! Returns the location string for this scenario.
  /*! Directory path to input is returned.
   */
  const char* GetLocation() const throw();
 
  //! Returns the landuse date as a digit.
  /*! \param i is the landuse index to get the date.
   */
  int GetLanduseYear(int i) const throw();
  
  //! Returns the urban date as a digit for a given urban index.
  /*! \param i the urban index for the desired urban date.
   */
  int GetUrbanYear(int i) const throw();
  
  //! Returns the number of urban grids.
  /*!
   */
  int GetUrbanCount() const throw();
  
  //! Normalizes the road grids.
  /*!
   */
  void NormalizeRoads() throw();
  
  //! Verifies the input grid sizes.
  /*!
   */
  void VerifyInputs(const Scenario & scene, FILE*fp) throw();
 
  //!  Get road year pixel count by date
  /*!  A year is pasted into the function and it then searches
       all the road years igrid structs looking for the road
       eqaul to or previous to the requested year. It returns
       the road pixel count for that year.
  */
  int GetIGridRoadPixelCount(int year) const throw();
  
  //! Return the # of excluded pixels
  /*! \sa GetIGridRoadPixelCount
   */
  int GetIGridExcludedPixelCount() const throw();
  
  //! Return the % of road pixels for a given year
  /*! \param year is the year to get the percentage for.
   */
  road_percent_t GetIGridRoadPercentage(int year) const throw();
  
  //! Releases memory used by a grid.
  /*! 
   */
  GRID_P GridRelease(char* file, char* fun, int line, GRID_P ptr) throw();
  
  //! Returns a pointer to urban data.
  /*! \param index the index specifing the urban layer
   */
  GRID_P GetUrbanGridPtr(char* file, char* fun,int line, int index) throw();
  
  //! Returns a pointer to urban data.
  /*! \param year the year specifing the urban layer
      \sa GetUrbanGridPtr
  */
  GRID_P GetUrbanGridPtrByYear(char* file, char* fun,int line, int year)
      throw();
  
  //! Returns a pointer to road data.
  /*! \param index the index specifing the road layer
   */
  GRID_P GetRoadGridPtr(char* file, char* fun,int line, int index) throw();
  
  //! Returns a pointer to road data.
  /*! \param year the year specifing the road layer
      \sa GetRoadGridPtr
  */
  GRID_P GetRoadGridPtrByYear(char* file, char* fun,int line, int year)
      throw();

  //! Returns a pointer to landuse data.
  /*! \param index the index specifing the landuse layer
   */
  GRID_P GetLanduseGridPtr(char* file, char* fun,int line, int index)
      throw();

  //! Returns a pointer to slope data.
  /*!
   */
  GRID_P GetSlopeGridPtr(char* file, char* fun,int line) throw();
  
  //! Returns a pointer to excluded data.
  /*!
   */
  GRID_P GetExcludedGridPtr(char* file, char* fun,int line) throw();
  
  //! Returns a pointer to background data.
  /*!
   */
  GRID_P GetBackgroundGridPtr(char* file, char* fun,int line) throw();
  
  //! Tests to see if a given year matches a urban year.
  /*! \param year the year to query for urban year.
   */
  bool TestForUrbanYear(int year) throw();

  //! Tests to see if a given year matches a road year.
  /*! \param year the year to query for road year.
   */
  bool TestForRoadYear(int year) throw();
  
  //! Initializes the igrid object so that is ready to read the files.
  /*!
   */
  void init(const Scenario & scene, const Proc & proc) throw();
  
  //! Converts an urban year into a urban index.
  /*! \param year the year to convert into a urban index.
   */
  int UrbanYear2Index(int year) throw();

  //geotiff storage params
  ProjectionParams geoParams;

protected:

  //! Extracts a filename from a full path.
  /*!
   */
  char * extract_filename(char * inpath) throw();

  //! Computes the precentage of road pixels.
  /*!
   */
  void CalculatePercentRoads () throw();
  
  //! Checks the validity of urban grids.
  /*!
   */
  bool ValidateUrbanGrids (FILE * fp) throw();
 
  //! Checks the validity of road grids.
  /*!
   */
  bool ValidateRoadGrids (FILE * fp) throw();
  
  //! Checks the validity of landuse grids.
  /*!
   */
  bool ValidateLanduseGrids (Landclass & lclasses, FILE * fp) throw();
  
  //! Checks the validity of the slope grid.
  /*!
   */
  bool ValidateSlopeGrid (FILE * fp) throw();
  
  //! Checks the validity of the excluded grid.
  /*!
   */
  bool ValidateExcludedGrid (FILE * fp) throw();
  
  //! Checks the validity of the background grid.
  /*!
   */
  bool ValidateBackgroundGrid (FILE * fp) throw();
  
  //! Counts the number of road pixels.
  /*!
   */
  void CountRoadPixels () throw();
  
  //! Sets the path to where the input layers are located.
  /*!
   */
  void SetLocation (const Scenario & scene) throw();
  
  //! Sets the filenames of the input grids.
  /*!
   */
  void SetFilenames (const Scenario & scene, const Proc & proc) throw();
  
  //! Determins the sizes of the various input grids.
  /*!
   */
  void SetGridSizes (Grid * grid_ptr, const Scenario & scene) throw();
  
  //! Reads a particular input grid input the pool of input layers.
  /*!
   */
  void ReadGrid (Scenario & scene, char *filepath, 
                 GRID_P scrtch_pad, GRID_P grid_p) throw();
  

  int igrid_count;
  int road_pixel_count[MAX_ROAD_YEARS];
  int excld_count;
  road_percent_t percent_road[MAX_ROAD_YEARS];
  int total_pixels;
  
  char       location[MAX_FILENAME_LEN];
  int        urban_count;
  int        road_count;
  int        landuse_count;
  int        excluded_count;
  int        slope_count;
  int        background_count;
  
  Grid   urban[MAX_URBAN_YEARS];
  Grid   road[MAX_ROAD_YEARS];
  Grid   landuse[MAX_LANDUSE_YEARS];
  Grid   excluded;
  Grid   slope;
  Grid   background;
  
};

/*
 Filename extraction function used interally to the
 class.
 */
inline char *  IGrid::extract_filename(char * inpath) throw()
{
  char * filename(0);
  
  //find the last / in the path
  filename = strrchr (inpath, '/'); 
  if (filename)                    
  {                                
    filename++;                    
  }
  else 
  {    
    filename = inpath;            
  }

  return filename;
}


#endif



