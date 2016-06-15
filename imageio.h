#ifndef IMAGEIO_H
#define IMAGEIO_H
/*! \file imageio.h
    \brief Definition file for the imageio object.
    
    Definition file for the imageio object which handles
    all image file format input and output for the model.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include "color.h"
#include "scenario.h"
#include "igrid.h"

/*
  DATE_X & DATE_Y CONTROL WHERE THE DATE STRING
  IS PRINTED ON THE GIF IMAGE
 */
#define DATE_X 1
#define DATE_Y igrid_GetNumRows() - 16

#define BYTES2READ 15
#define GIF_ID "GIF"
#define GIF_ROW_OFFSET 8
#define GIF_COL_OFFSET 6
#define GIF_RES_OFFSET 10
#define CONVERT2UINT(a,b) (((b)<<8)|(a))

//! ImageIO class handles Image file format input and output.
/*! Currently the following formats are supported.
    Input: gif, tiff, geotiff, png
    Ouput: gif, tiff, geotiff(if input was a geotiff).
*/
class ImageIO
{
 public:
  
  //! Destructor for class.
  /*! All class memory is returned to system.
   */
  virtual ~ImageIO(){};

  //! Determins all image metrics for a given grid.
  /*! \param grid_ptr the grid for which metrics will be determined.
      \param scene the scenario object which has info about the grid.
  */
  virtual void GetImageInfo (Grid * grid_ptr, const Scenario &scene);
 
  //! Writes the color palette to a file.
  /*!
   */
  virtual void WriteColorKey(IGrid & temp, Scenario & internal,
                              const Colortable * colortable,
                              char fname[]);
  
  //! Reads in a grid from a given file.
  /*! \param gif_ptr the grid to use as input.
      \param temp a reference to the input grid collection.
      \param internal the reference to the scenario object.
      \param fname the file name to read.
  */
  virtual void ReadGRID (GRID_P gif_ptr, IGrid & temp,
                       Scenario & internal, char *fname);
  
  //! Writes out a grid to a given file.
  /*! \param gif the grid to output.
      \param colortable is the output colortable.
      \param internal the reference to the scenario object.
      \param fname the file name to write.
      \param date the data to annote to the image (gif only).
      \param date_color_index the color index of the date string.
  */
  virtual void WriteGRID(
                  GRID_P gif,
                  const Colortable *colortable,
                  Scenario & internal,
                  IGrid & temp,
                  char fname[],
                  char date[],
                  int date_color_index);
};
#endif
