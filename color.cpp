/*! \file color.cpp
    \brief Implementation file for the color object.
    
    Implementation file for the color object which keeps track
    of the color tables used in the simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include "color.h"
#include "imageio.h"

/*
 Class constructor.
*/
Colortable::Colortable() : size(0)
{}

/*
 Class destructor.
*/  
Colortable::~Colortable()
{
}

/*
 Class constructor.
*/
ColorDirectory::ColorDirectory(const Scenario & scene, 
                               const Landclass & land) : initialized(false)
{
  Init(scene, land);
}

/*
 Class destructor.
*/
ColorDirectory::~ColorDirectory()
{
 
}
  
/*
 Class validation.
*/
bool ColorDirectory::isValid() throw()
{
  return initialized;
}

/*
 returns a pointer to a specific color table.
*/
const Colortable *  ColorDirectory::GetColortable (int i) throw()
{
  if (i > 5 || i < 0)
    return 0;
 
  return & colormap[i];
}
  

/*
  FUNCTION NAME: color_Init
   PURPOSE:       main driver for initializing the colortables
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void ColorDirectory::Init(const Scenario & scene, const Landclass & land)
  throw()
{
 
  ImageIO imageout;


  /*
    FILL IN COLOR VALUES
   */
  color_fill(scene, land);
  initialized = true;   //class is valid now
}


/*
   FUNCTION NAME: color_fill
   PURPOSE:       initializes RGB values for each colortable
   AUTHOR:        Keith Clarke
   PROGRAMMER:    Tommy E. Cathey of NESC (919)541-1500
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void ColorDirectory::color_fill(const Scenario & scene, const Landclass & land) throw()
{
  int i(0);
  int index(0);
  int color_val(0);

  colormap[GRAYSCALE_COLORTABLE].name = "GRAYSCALE_COLORMAP";
  colormap[GRAYSCALE_COLORTABLE].size = MAX_COLORS;
  for (i = 0; i < MAX_COLORS; i++)
  {
    colormap[GRAYSCALE_COLORTABLE].color[i].red = i;
    colormap[GRAYSCALE_COLORTABLE].color[i].green = i;
    colormap[GRAYSCALE_COLORTABLE].color[i].blue = i;
  }
  
  colormap[LANDUSE_COLORTABLE].name = "LANDUSE_COLORMAP";
  colormap[LANDUSE_COLORTABLE].size = MAX_COLORS;
  for (i = 0; i < MAX_COLORS; i++)
  {
    colormap[LANDUSE_COLORTABLE].color[i].red = i;
    colormap[LANDUSE_COLORTABLE].color[i].green = i;
    colormap[LANDUSE_COLORTABLE].color[i].blue = i;
  }
  for (i = 0; i < land.GetNumLandclasses(); i++)
  {
    color_val = land.GetClassColor (i);
    colormap[LANDUSE_COLORTABLE].color[i].red = (color_val & RED_MASK) >> 16;
    colormap[LANDUSE_COLORTABLE].color[i].green= (color_val & GREEN_MASK) >> 8;
    colormap[LANDUSE_COLORTABLE].color[i].blue = color_val & BLUE_MASK;
  }

  colormap[PROBABILITY_COLORTABLE].name = "PROBABILITY_COLORMAP";
  colormap[PROBABILITY_COLORTABLE].size = MAX_COLORS;
  for (i = 0; i < MAX_COLORS; i++)
  {
    colormap[PROBABILITY_COLORTABLE].color[i].red = i;
    colormap[PROBABILITY_COLORTABLE].color[i].green = i;
    colormap[PROBABILITY_COLORTABLE].color[i].blue = i;
  }

  colormap[DELTATRON_COLORTABLE].name = "DELTATRON_COLORMAP";
  colormap[DELTATRON_COLORTABLE].size = MAX_COLORS;
  for (i = 0; i < scene.GetDeltatronColorCount(); i++)
  {
    color_val = scene.GetDeltatronColor(i);
    colormap[DELTATRON_COLORTABLE].color[i].red = (color_val & RED_MASK) >> 16;
    colormap[DELTATRON_COLORTABLE].color[i].green =
      (color_val & GREEN_MASK) >> 8;
    colormap[DELTATRON_COLORTABLE].color[i].blue = color_val & BLUE_MASK;
  }
  for (i = scene.GetDeltatronColorCount(); i < MAX_COLORS; i++)
  {
    colormap[DELTATRON_COLORTABLE].color[i].red = i;
    colormap[DELTATRON_COLORTABLE].color[i].green = i;
    colormap[DELTATRON_COLORTABLE].color[i].blue = i;
  }
  /*
   
    USER OVER RIDES
   
   */
  index = WATER_COLOR_INDEX;
  color_val = scene.GetWaterColor ();
  colormap[PROBABILITY_COLORTABLE].color[index].red =
    (color_val & RED_MASK) >> 16;
  colormap[PROBABILITY_COLORTABLE].color[index].green =
    (color_val & GREEN_MASK) >> 8;
  colormap[PROBABILITY_COLORTABLE].color[index].blue = color_val & BLUE_MASK;

  colormap[LANDUSE_COLORTABLE].color[i].red = (color_val & RED_MASK) >> 16;
  colormap[LANDUSE_COLORTABLE].color[i].green = (color_val & GREEN_MASK) >> 8;
  colormap[LANDUSE_COLORTABLE].color[i].blue = color_val & BLUE_MASK;

  index = SEED_COLOR_INDEX;
  color_val = scene.GetSeedColor ();
  colormap[PROBABILITY_COLORTABLE].color[index].red =
    (color_val & RED_MASK) >> 16;
  colormap[PROBABILITY_COLORTABLE].color[index].green =
    (color_val & GREEN_MASK) >> 8;
  colormap[PROBABILITY_COLORTABLE].color[index].blue = color_val & BLUE_MASK;

  index = DATE_COLOR_INDEX;
  color_val = scene.GetDateColor ();
  colormap[PROBABILITY_COLORTABLE].color[index].red =
    (color_val & RED_MASK) >> 16;
  colormap[PROBABILITY_COLORTABLE].color[index].green =
    (color_val & GREEN_MASK) >> 8;
  colormap[PROBABILITY_COLORTABLE].color[index].blue = color_val & BLUE_MASK;

  for (i = 0; i < scene.GetProbabilityColorCount (); i++)
  {
    index = i + START_INDEX_FOR_PROBABILITY_COLORS;
    color_val = scene.GetProbabilityColor (i);
    colormap[PROBABILITY_COLORTABLE].color[index].red =
      (color_val & RED_MASK) >> 16;
    colormap[PROBABILITY_COLORTABLE].color[index].green =
      (color_val & GREEN_MASK) >> 8;
    colormap[PROBABILITY_COLORTABLE].color[index].blue = color_val & BLUE_MASK;
  }

  colormap[GROWTH_COLORTABLE].name = "GROWTH_COLORMAP";
  colormap[GROWTH_COLORTABLE].size = MAX_COLORS;
  for (i = 0; i < MAX_COLORS; i++)
  {
    colormap[GROWTH_COLORTABLE].color[i].red = i;
    colormap[GROWTH_COLORTABLE].color[i].green = i;
    colormap[GROWTH_COLORTABLE].color[i].blue = i;
  }
  index = PHASE0G;
  color_val = scene.GetPhase0GrowthColor ();
  colormap[GROWTH_COLORTABLE].color[index].red = (color_val & RED_MASK) >> 16;
  colormap[GROWTH_COLORTABLE].color[index].green=(color_val & GREEN_MASK) >> 8;
  colormap[GROWTH_COLORTABLE].color[index].blue = color_val & BLUE_MASK;
  index = PHASE1G;
  color_val = scene.GetPhase1GrowthColor ();
  colormap[GROWTH_COLORTABLE].color[index].red = (color_val & RED_MASK) >> 16;
  colormap[GROWTH_COLORTABLE].color[index].green=(color_val & GREEN_MASK) >> 8;
  colormap[GROWTH_COLORTABLE].color[index].blue = color_val & BLUE_MASK;
  index = PHASE2G;
  color_val = scene.GetPhase2GrowthColor ();
  colormap[GROWTH_COLORTABLE].color[index].red = (color_val & RED_MASK) >> 16;
  colormap[GROWTH_COLORTABLE].color[index].green=(color_val & GREEN_MASK) >> 8;
  colormap[GROWTH_COLORTABLE].color[index].blue = color_val & BLUE_MASK;
  index = PHASE3G;
  color_val = scene.GetPhase3GrowthColor ();
  colormap[GROWTH_COLORTABLE].color[index].red = (color_val & RED_MASK) >> 16;
  colormap[GROWTH_COLORTABLE].color[index].green=(color_val & GREEN_MASK) >> 8;
  colormap[GROWTH_COLORTABLE].color[index].blue = color_val & BLUE_MASK;
  index = PHASE4G;
  color_val = scene.GetPhase4GrowthColor ();
  colormap[GROWTH_COLORTABLE].color[index].red = (color_val & RED_MASK) >> 16;
  colormap[GROWTH_COLORTABLE].color[index].green=(color_val & GREEN_MASK) >> 8;
  colormap[GROWTH_COLORTABLE].color[index].blue = color_val & BLUE_MASK;
  index = PHASE5G;
  color_val = scene.GetPhase5GrowthColor ();
  colormap[GROWTH_COLORTABLE].color[index].red = (color_val & RED_MASK) >> 16;
  colormap[GROWTH_COLORTABLE].color[index].green=(color_val & GREEN_MASK) >> 8;
  colormap[GROWTH_COLORTABLE].color[index].blue = color_val & BLUE_MASK;

}
