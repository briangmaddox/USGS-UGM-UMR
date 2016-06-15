#ifndef PROJECTIONPARAMS_H
#define PROJECTIONPARAMS_H
/*! \file ProjectionParams.h
    \brief Definition file for the projection params object.

    Definition file for the projection params objects.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/


#include "tiff.h"

//! Simple class to hold projection parameters.
class ProjectionParams
{
public:
  
  //!Main Constructor for the class.
  ProjectionParams();

  //public data
  uint16 projtype;  //Geotiff getprojtype
  uint16 datum;  //same
  uint16 unit;  //same
  double StdParallel1;
  double StdParallel2;
  double NatOriginLong;
  double NatOriginLat;
  double FalseOriginLong;
  double FalseOriginLat;
  double FalseOriginEasting;
  double FalseOriginNorthing;
  double CenterLong;
  double CenterLat;
  double CenterEasting;
  double CenterNorthing;
  double ScaleAtNatOrigin;
  double AzimuthAngle;
  double StraightVertPoleLong;
  uint16 PCSCode;
  double FalseEasting;
  double FalseNorthing;
};

#endif
