#ifndef PROJECTIONPARAMS_CPP
#define PROJECTIONPARAMS_CPP
/*! \file ProjectionParams.cpp
    \brief Definition file for the projection params object.

    Definition file for the projection params objects.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/


#include "ProjectionParams.h"

/*
 Main constructor for class.
*/
ProjectionParams::ProjectionParams()
{
//  projtype = ProjLib::GEO;
//  datum = ProjLib::NAD83;
//  unit = ProjLib::ARC_DEGREES;
  StdParallel1 = 0.0;
  StdParallel2 = 0.0;
  NatOriginLong = 0.0;
  NatOriginLat = 0.0;
  FalseOriginLong = 0.0;
  FalseOriginLat = 0.0;
  FalseOriginEasting = 0.0;
  FalseOriginNorthing = 0.0;
  CenterLong = 0.0;
  CenterLat = 0.0;
  CenterEasting = 0.0;
  CenterNorthing = 0.0;
  ScaleAtNatOrigin = 0.0;
  AzimuthAngle = 0.0;
  StraightVertPoleLong = 0.0;
  PCSCode = 0;
  FalseEasting = 0.0;
  FalseNorthing = 0.0;
}

#endif
