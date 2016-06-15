#ifndef COLOR_H
#define COLOR_H
/*! \file color.h
    \brief Definition file for the color object.
    
    Definition file for the color object which keeps track
    of the color tables used in the simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include <string>
#include "scenario.h"
#include "landclass.h"


#define LANDUSE_COLORTABLE 0
#define NONLANDUSE_COLORTABLE 1
#define PROBABILITY_COLORTABLE 2
#define GROWTH_COLORTABLE 3
#define DELTATRON_COLORTABLE 4
#define GRAYSCALE_COLORTABLE 5

#define WATER_COLOR_INDEX 0
#define SEED_COLOR_INDEX 1
#define DATE_COLOR_INDEX 255

#define MAX_COLORS 256
#define RED_MASK   0XFF0000
#define GREEN_MASK 0X00FF00
#define BLUE_MASK  0X0000FF
#define START_INDEX_FOR_PROBABILITY_COLORS 2
#define PHASE0G 3
#define PHASE1G 4
#define PHASE2G 5
#define PHASE3G 6
#define PHASE4G 7
#define PHASE5G 8

//! Simple utililty structure for color components.
typedef struct RGB
{
  int red;
  int green;
  int blue;
} RGB_t;

//! Colortable storage class.
/*! This class represents a simple storage unit for
    a single 256 color table.
*/
class Colortable 
{
public:  
  //! Constructor
  /*! Initilizes the interally stored color table.
   */
  Colortable();
  
  //! Destructor
  /*! Returns all class memory to the system.
   */
  virtual ~Colortable();

  //public data for now
  int size;
  std::string name;
  RGB_t color[MAX_COLORS];
};


//! Storage class for groups of colortables.
/*! Class stores colortables for each data layer.
 */
class ColorDirectory
{
 public:
  
  //! Constructor.
  /*! Initializes the color tables based off information given
      in the scenario and landclass objects.
  */
  ColorDirectory(const Scenario & scene, const Landclass & land);
  
  //! Destructor.
  /*! Any class allocated memory is returned to the system.
   */
  virtual ~ColorDirectory();
  
  //! Colortable accessor.
  /*! Returns a const point to the specified colortable.
      If the index is out of range then NULL is returned.
      \param i the index of desired color table.
  */
  const Colortable* GetColortable(int i) throw();
  
  //! Class validation.
  /*! This allows the colordirectory to validated after creation.
   */
  bool isValid() throw();
 
 private:
 
  //! Initializing function.
  /*! Initializes the colortables based off the scenerio and landclasses.
   */
  void Init(const Scenario & scene, const Landclass & land) throw();
  
  //! Fills out the color pallettes.
  /*! Fills each color table based off the given infomation.
   */
  void color_fill (const Scenario & scene, const Landclass & land) throw();


  bool initialized;
  //the colormap table
  Colortable colormap[6];
};



#endif
