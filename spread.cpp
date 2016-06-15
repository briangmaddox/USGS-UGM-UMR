

#include "spread.h"



Spread::Spread(Proc & inruninfo, Scenario & inscene,    
       Landclass & inlclasses, Coeff &incoeffs,
       IGrid & iningrids,  ColorDirectory & incolortable,
       PGrid & inpgrids,  Transition & intrans,
       Stats & instats, MathLib::RandomLEcuyerBD & inrandomgen)
  : runinfo(inruninfo), scene(inscene),    
    lclasses(inlclasses), coeffs(incoeffs),
    ingrids(iningrids),  colortable(incolortable),
    pgrids(inpgrids),  trans(intrans),
    stats(instats), randomgen(inrandomgen)
{}


/******************************************************************************
*******************************************************************************
** FUNCTION NAME: phase1n3
** PURPOSE:       perform phase 1 & 3 growth types
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
void Spread::phase1n3 (COEFF_TYPE diffusion_coefficient,       /* IN     */
                           COEFF_TYPE breed_coefficient,          /* IN     */
                           GRID_P z,                              /* IN     */
                           GRID_P delta,                          /* IN/OUT */
                           GRID_P slp,                            /* IN     */
                           GRID_P excld,                          /* IN     */
                           SWGHT_TYPE * swght,                    /* IN     */
                           int *sng,                              /* IN/OUT */
                           int *sdc)                              /* IN/OUT */
{

  int i;
  int j;
  int i_out;
  int j_out;
  int k;
  int count;
  int tries;
  int max_tries;
  COEFF_TYPE diffusion_value;
  bool urbanized;

  assert (MIN_DIFFUSION_VALUE <= diffusion_coefficient);
  assert (diffusion_coefficient <= MAX_DIFFUSION_VALUE);
  assert (MIN_BREED_VALUE <= breed_coefficient);
  assert (breed_coefficient <= MAX_BREED_VALUE);
  assert (z != NULL);
  assert (delta != NULL);
  assert (slp != NULL);
  assert (excld != NULL);
  assert (swght != NULL);
  assert (sng != NULL);
  assert (sdc != NULL);

  diffusion_value = GetDiffusionValue (diffusion_coefficient);

  for (k = 0; k < 1 + (int) diffusion_value; k++)
  {
    i = static_cast<int>(randomgen.getRandom() * ingrids.GetNumRows());
    j = static_cast<int>(randomgen.getRandom() * ingrids.GetNumCols());

    if ((i < ingrids.GetNumRows() - 1) && 
        (j < ingrids.GetNumCols() - 1) && 
        (i > 0)  && (j > 0))
    {
      if (urbanize (i,                                     /* IN     */
                        j,                                     /* IN     */
                        z,                                     /* IN     */
                        delta,                                 /* IN/OUT */
                        slp,                                   /* IN     */
                        excld,                                 /* IN     */
                        swght,                                 /* IN     */
                        PHASE1G,                               /* IN     */
                        sng))                              /* IN/OUT */
      {
        if ((int)(randomgen.getRandom() * 101) < (int) breed_coefficient)
        {
          count = 0;
          max_tries = 8;
          for (tries = 0; tries < max_tries; tries++)
          {
            urbanized = FALSE;
            urbanized =
              urbanize_nghbr (i,                         /* IN     */
                                  j,                         /* IN     */
                                  &i_out,                    /* OUT    */
                                  &j_out,                    /* OUT    */
                                  z,                         /* IN     */
                                  delta,                     /* IN/OUT */
                                  slp,                       /* IN     */
                                  excld,                     /* IN     */
                                  swght,                     /* IN     */
                                  PHASE3G,                   /* IN     */
                                  sdc);                    /* IN/OUT */
            if (urbanized)
            {
              count++;
              if (count == MIN_NGHBR_TO_SPREAD)
              {
                break;
              }
            }
          }
        }
      }
    }
  }

}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: phase4
** PURPOSE:       perform phase 4 growth
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
void Spread::phase4 (COEFF_TYPE spread_coefficient,                 /* IN     */
              GRID_P z,                                      /* IN     */
              GRID_P excld,                                  /* IN     */
              GRID_P delta,                                  /* IN/OUT */
              GRID_P slp,                                    /* IN     */
              SWGHT_TYPE * swght,                            /* IN     */
              int *og)                                     /* IN/OUT */
{
  int row;
  int col;
  int row_nghbr;
  int col_nghbr;
  int pixel;
  int walkabout_row[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int walkabout_col[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int urb_count;
  int nrows;
  int ncols;

  
  assert (z != NULL);
  assert (excld != NULL);
  assert (delta != NULL);
  assert (slp != NULL);
  assert (swght != NULL);
  assert (og != NULL);

  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();
  assert (nrows > 0);
  assert (ncols > 0);

  /*
   *
   * LOOP OVER THE INTERIOR PIXELS LOOKING FOR URBAN FROM WHICH
   * TO PERFORM ORGANIC GROWTH
   *
   */
  for (row = 1; row < nrows - 1; row++)
  {
    for (col = 1; col < ncols - 1; col++)
    {

      /*
       *
       * IS THIS AN URBAN PIXEL AND DO WE PASS THE RANDOM 
       * SPREAD COEFFICIENT TEST
       *
       */
      if ((z[ingrids.GetNumCols()*row +  col] > 0) &&
          ((int)(randomgen.getRandom() * 101) < (int) spread_coefficient))
      {
        /*
         * EXAMINE THE EIGHT CELL NEIGHBORS
         * SPREAD AT RANDOM IF AT LEAST TWO ARE URBAN
         * PIXEL ITSELF MUST BE URBAN (3)
         *
         */
        urb_count = util_count_neighbors (z, ingrids.GetNumCols(),
                                          row, col, GT, 0);
        if ((urb_count >= 2) && (urb_count < 8))
        {
          pixel = (int)(randomgen.getRandom() * 8);

          row_nghbr = row + walkabout_row[pixel];
          col_nghbr = col + walkabout_col[pixel];

          urbanize (row_nghbr,                           /* IN     */
                        col_nghbr,                           /* IN     */
                        z,                                   /* IN     */
                        delta,                               /* IN/OUT */
                        slp,                                 /* IN     */
                        excld,                               /* IN     */
                        swght,                               /* IN     */
                        PHASE4G,                             /* IN     */
                        og);                               /* IN/OUT */
        }
      }
    }
  }
  
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: phase5
** PURPOSE:       perform phase 5 growth
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
void Spread::phase5 (COEFF_TYPE road_gravity,                       /* IN     */
              COEFF_TYPE diffusion_coefficient,              /* IN     */
              COEFF_TYPE breed_coefficient,                  /* IN     */
              GRID_P z,                                      /* IN     */
              GRID_P delta,                                  /* IN/OUT */
              GRID_P slp,                                    /* IN     */
              GRID_P excld,                                  /* IN     */
              GRID_P roads,                                  /* IN     */
              SWGHT_TYPE * swght,                            /* IN     */
              int *rt,                                       /* IN/OUT */
              GRID_P workspace)                            /* MOD    */

{
  int iii;
  int int_road_gravity;
  int growth_count;
  int *growth_row;
  int *growth_col;
  int max_search_index;
  int growth_index;
  bool road_found;
  int i_rd_start;
  int j_rd_start;
  int max_tries;
  bool spread;
  bool urbanized;
  int i_rd_end;
  int j_rd_end;
  int i_rd_end_nghbr;
  int j_rd_end_nghbr;
  int i_rd_end_nghbr_nghbr;
  int j_rd_end_nghbr_nghbr;
  int tries;
  int nrows;
  int ncols;
  int total_pixels;

  assert (road_gravity > 0.0);
  assert (diffusion_coefficient > 0.0);
  assert (breed_coefficient > 0.0);
  assert (z != NULL);
  assert (delta != NULL);
  assert (slp != NULL);
  assert (excld != NULL);
  assert (roads != NULL);
  assert (swght != NULL);
  assert (rt != NULL);
  assert (workspace != NULL);
  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();
  assert (nrows > 0);
  assert (ncols > 0);


  total_pixels = mem_GetTotalPixels ();
  assert (total_pixels > 0);
  /*
   *
   * SET UP WORKSPACE
   *
   */
  growth_row = (int *) workspace;
  growth_col = (int *) workspace + (nrows);
  /*
   *
   * DETERMINE THE TOTAL GROWTH COUNT AND SAVE THE
   * ROW AND COL LOCATIONS OF THE NEW GROWTH
   *
   */
  growth_count = 0;
#ifdef CRAY_C90
#pragma _CRI ivdep
#endif
  for (iii = 0; iii < total_pixels; iii++)
  {
    if (delta[iii] > 0)
    {
      growth_row[growth_count] = iii / ncols;
      growth_col[growth_count] = iii % ncols;
      growth_count++;
    }
  }
  /*
   *
   * PHASE 5:  ROAD TRIPS
   * IF THERE IS NEW GROWTH, BEGIN PROCESSING ROAD TRIPS
   *
   */
  if (growth_count > 0)
  {
    for (iii = 0; iii < 1 + (int) (breed_coefficient); iii++)
    {
      /*
       *
       * DETERMINE THE MAX INDEX INTO THE GLB_RD_SEARCH_INDICES ARRAY
       * for road_gravity of 1 we have  8 values
       * for road_gravity of 2 we have 16 values
       * for road_gravity of 3 we have 24 values
       *    and so on....
       *
       * if we need to cover N road_gravity values, then total number of 
       * indexed values would be
       * 8 + 16 + 24 + ... + 8*N = 8*(1+2+3+...+N) = 8*(N(1+N))/2
       *
       */
      int_road_gravity = static_cast<int>(GetRoadGravValue (road_gravity));
      max_search_index = 4 * (int_road_gravity * (1 + int_road_gravity));
      max_search_index = MAX (max_search_index, nrows);
      max_search_index = MAX (max_search_index, ncols);

      /*
       *
       * RANDOMLY SELECT A GROWTH PIXEL TO START SEARCH
       * FOR ROAD
       *
       */
      growth_index = (int) ((double) growth_count *  randomgen.getRandom());

      /*
       *
       * SEARCH FOR ROAD ABOUT THIS GROWTH POINT
       *
       */
      road_found =
        road_search (growth_row[growth_index],
                         growth_col[growth_index],
                         &i_rd_start,
                         &j_rd_start,
                         max_search_index,
                         roads);

      /*
       *
       * IF THERE'S A ROAD FOUND THEN WALK ALONG IT
       *
       */
      if (road_found)
      {
        spread = road_walk (i_rd_start,                  /* IN     */
                                j_rd_start,                  /* IN     */
                                &i_rd_end,                   /* OUT    */
                                &j_rd_end,                   /* OUT    */
                                roads,                       /* IN     */
                                diffusion_coefficient);    /* IN     */

        if (spread == TRUE)
        {
          urbanized =
            urbanize_nghbr (i_rd_end,                    /* IN     */
                                j_rd_end,                    /* IN     */
                                &i_rd_end_nghbr,             /* OUT    */
                                &j_rd_end_nghbr,             /* OUT    */
                                z,                           /* IN     */
                                delta,                       /* IN/OUT */
                                slp,                         /* IN     */
                                excld,                       /* IN     */
                                swght,                       /* IN     */
                                PHASE5G,                     /* IN     */
                                rt);                       /* IN/OUT */
          if (urbanized)
          {
            max_tries = 3;
            for (tries = 0; tries < max_tries; tries++)
            {
              urbanized =
                urbanize_nghbr (i_rd_end_nghbr,          /* IN     */
                                    j_rd_end_nghbr,          /* IN     */
                                    &i_rd_end_nghbr_nghbr,   /* OUT    */
                                    &j_rd_end_nghbr_nghbr,   /* OUT    */
                                    z,                       /* IN     */
                                    delta,                   /* IN/OUT */
                                    slp,                     /* IN     */
                                    excld,                   /* IN     */
                                    swght,                   /* IN     */
                                    PHASE5G,                 /* IN     */
                                    rt);                   /* IN/OUT */

            }
          }
        }
      }
    }
  }
  
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: get_slp_weights
** PURPOSE:       calculate the slope weights
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
void Spread::get_slp_weights (int array_size,                       /* IN     */
                       SWGHT_TYPE * lut)                   /* OUT    */
{
  float val;
  float exp;
  int i;


  assert (lut != NULL);

  exp = coeffs.GetCurrentSlopeResist () / (MAX_SLOPE_RESISTANCE_VALUE / 2.0);
  for (i = 0; i < array_size; i++)
  {
    if (i < scene.GetCriticalSlope ())
    {
      val = (scene.GetCriticalSlope () - (SWGHT_TYPE) i) / scene.GetCriticalSlope ();
      lut[i] = 1.0 - pow (val, exp);
    }
    else
    {
      lut[i] = 1.0;
    }
  }
  if (scene.GetLogFlag ())
  {
    if (scene.GetLogSlopeWeightsFlag ())
    {
      scene.Append2Log ();
      LogSlopeWeights (scene.GetLogFP (), array_size, lut);
      scene.CloseLog ();
    }
  }

}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: LogSlopeWeights
** PURPOSE:       log slope weights to FILE * fp
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
void Spread::LogSlopeWeights (FILE * fp, int array_size, SWGHT_TYPE * lut)
{
  int i;

  assert (fp != NULL);
  assert (array_size > 0);
  assert (lut != NULL);

  fprintf (fp, "\n%s %5u ***** LOG OF SLOPE WEIGHTS *****\n",
           __FILE__, __LINE__);
  fprintf (fp, "%s %5u CRITICAL_SLOPE= %f\n",
           __FILE__, __LINE__, scene.GetCriticalSlope ());
  fprintf (fp, "%s %5u coeff_GetCurrentSlopeResist= %f\n",
           __FILE__, __LINE__, coeffs.GetCurrentSlopeResist ());
  fprintf (fp, "%s %5u MAX_SLOPE_RESISTANCE_VALUE= %f\n",
           __FILE__, __LINE__, MAX_SLOPE_RESISTANCE_VALUE);
  for (i = 0; i < array_size; i++)
  {
    if (i < scene.GetCriticalSlope ())
    {
      fprintf (fp, "%s %5u lut[%3u]= %f\n",
               __FILE__, __LINE__, i, lut[i]);
    }
  }
  fprintf (fp, "All values other values to lut[%u] = 1.000000\n", array_size);

}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: GetDiffusionValue
** PURPOSE:       calculate the diffusion value
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
COEFF_TYPE Spread::GetDiffusionValue (COEFF_TYPE diffusion_coeff)
{

  COEFF_TYPE diffusion_value;
  double rows_sq;
  double cols_sq;

  rows_sq = ingrids.GetNumRows () * ingrids.GetNumRows ();
  cols_sq = ingrids.GetNumCols () * ingrids.GetNumCols ();

  /*
   * diffusion_value's MAXIMUM (IF diffusion_coeff == 100)
   * WILL BE 5% OF THE IMAGE DIAGONAL. 
   */

  diffusion_value = ((diffusion_coeff * 0.005) * sqrt (rows_sq + cols_sq));
  return diffusion_value;
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: GetRoadGravValue
** PURPOSE:       calculate the road gravity value
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
COEFF_TYPE Spread::GetRoadGravValue (COEFF_TYPE rg_coeff)
{

  int rg_value;
  int row;
  int col;

  row = ingrids.GetNumRows ();
  col = ingrids.GetNumCols ();

  /*
   * rg_value's MAXIMUM (IF rg_coeff == 100)
   * WILL BE 1/16 OF THE IMAGE DIMENSIONS. 
   */

  rg_value = static_cast<int>(
          (rg_coeff / MAX_ROAD_VALUE) * ((row + col) / 16.0));

  return rg_value;
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: urbanize
** PURPOSE:       try to urbanize a pixel
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
bool Spread::urbanize (int row,                                     /* IN     */
                int col,                                     /* IN     */
                GRID_P z,                                    /* IN     */
                GRID_P delta,                                /* IN/OUT */
                GRID_P slp,                                  /* IN     */
                GRID_P excld,                                /* IN     */
                SWGHT_TYPE * swght,                          /* IN     */
                PIXEL pixel_value,                           /* IN     */
                int *stat)                                 /* IN/OUT */
{
  bool val;
  int nrows;
  int ncols;

  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();
  assert (nrows > 0);
  assert (ncols > 0);


  assert ((row >= 0) && (row < nrows));
  assert ((col >= 0) && (col < ncols));
  assert (z != NULL);
  assert (delta != NULL);
  assert (slp != NULL);
  assert (excld != NULL);
  assert (swght != NULL);
  assert (stat != NULL);


  val = FALSE;
  if (z[ncols*row + col] == 0)
  {
    if (delta[ncols*row +  col] == 0)
    {
      if (randomgen.getRandom() > swght[slp[ncols*row + col]])
      {
        if (excld[ncols*row + col] < (int)(randomgen.getRandom() * 100))
        {
          val = TRUE;
          delta[ncols*row + col] = pixel_value;
          (*stat)++;
          stats.IncrementUrbanSuccess ();
        }
        else
        {
          stats.IncrementEcludedFailure ();
        }
      }
      else
      {
        stats.IncrementSlopeFailure ();
      }
    }
    else
    {
      stats.IncrementDeltaFailure ();
    }
  }
  else
  {
    stats.IncrementZFailure ();
  }




  return val;
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: get_neighbor
** PURPOSE:       find a neighboring pixel
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
void Spread::get_neighbor (int i_in,                                /* IN     */
                    int j_in,                                /* IN     */
                    int *i_out,                              /* OUT    */
                    int *j_out)                            /* OUT    */
{
  int i;
  int j;
  int k;
  int nrows;
  int ncols;

  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();
  assert (nrows > 0);
  assert (ncols > 0);


  assert (nrows > i_in);
  assert (ncols > j_in);
  assert (0 <= i_in);
  assert (0 <= j_in);
  assert (i_out != NULL);
  assert (j_out != NULL);

  util_get_next_neighbor (ingrids, i_in, j_in, i_out, j_out, 
                          (int)(randomgen.getRandom()*(8)));
  for (k = 0; k < 8; k++)
  {
    i = (*i_out);
    j = (*j_out);
    if ((i <  ingrids.GetNumRows()) &&
         (j <  ingrids.GetNumCols()) &&
         (i >= 0)  &&\
         (j >= 0))
    {
      break;
    }
    util_get_next_neighbor (ingrids,
                            i_in, j_in, i_out, j_out, -1);
  }

}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: urbanize_nghbr
** PURPOSE:       try to urbanize a neighbor
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
bool Spread::urbanize_nghbr (int i,                                 /* IN     */
                      int j,                                 /* IN     */
                      int *i_nghbr,                          /* OUT    */
                      int *j_nghbr,                          /* OUT    */
                      GRID_P z,                              /* IN     */
                      GRID_P delta,                          /* IN/OUT */
                      GRID_P slp,                            /* IN     */
                      GRID_P excld,                          /* IN     */
                      SWGHT_TYPE * swght,                    /* IN     */
                      PIXEL pixel_value,                     /* IN     */
                      int *stat)                           /* IN/OUT */
{
  bool status = FALSE;


  assert (i_nghbr != NULL);
  assert (j_nghbr != NULL);
  assert (z != NULL);
  assert (delta != NULL);
  assert (slp != NULL);
  assert (excld != NULL);
  assert (swght != NULL);
  assert (stat != NULL);

  if (   (i <  ingrids.GetNumRows()) &&
         (j <  ingrids.GetNumCols()) &&
         (i >= 0)  &&\
         (j >= 0))
  {
    get_neighbor (i,                                     /* IN    */
                      j,                                     /* IN    */
                      i_nghbr,                               /* OUT   */
                      j_nghbr);                            /* OUT   */

    status = urbanize ((*i_nghbr),                       /* IN     */
                           (*j_nghbr),                       /* IN     */
                           z,                                /* IN     */
                           delta,                            /* IN/OUT */
                           slp,                              /* IN     */
                           excld,                            /* IN     */
                           swght,                            /* IN     */
                           pixel_value,                      /* IN     */
                           stat);                          /* IN/OUT */
  }


  return status;
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: road_walk
** PURPOSE:       perform road walk
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
bool Spread::road_walk (int i_road_start,                           /* IN     */
                 int j_road_start,                           /* IN     */
                 int *i_road_end,                            /* OUT    */
                 int *j_road_end,                            /* OUT    */
                 GRID_P roads,                               /* IN     */
                 double diffusion_coefficient)             /* IN     */
{
  int i;
  int j;
  int i_nghbr;
  int j_nghbr;
  int k;
  bool end_of_road;
  bool spread = FALSE;
  int run_value;
  int run = 0;


  assert (i_road_end != NULL);
  assert (j_road_end != NULL);
  assert (roads != NULL);

  i = i_road_start;
  j = j_road_start;
  end_of_road = FALSE;
  while (!end_of_road)
  {
    end_of_road = TRUE;
    util_get_next_neighbor (ingrids,
                            i, j, &i_nghbr, &j_nghbr, (int)(randomgen.getRandom() * 8));
    for (k = 0; k < 8; k++)
    {
      if (    (i_nghbr <  ingrids.GetNumRows()) &&
         (j_nghbr <  ingrids.GetNumCols()) &&
         (i_nghbr >= 0)    &&  
         (j_nghbr >= 0))
      {
        if (roads[ingrids.GetNumCols()*i_nghbr + j_nghbr])
        {
          end_of_road = FALSE;
          run++;
          i = i_nghbr;
          j = j_nghbr;
          break;
        }
      }
      util_get_next_neighbor (ingrids,
                              i, j, &i_nghbr, &j_nghbr, -1);
    }
    run_value = (int) (roads[ingrids.GetNumCols()*i + j] / MAX_ROAD_VALUE *
                       diffusion_coefficient);
    if (run > run_value)
    {
      end_of_road = TRUE;
      spread = TRUE;
      (*i_road_end) = i;
      (*j_road_end) = j;
    }
  }

  return spread;
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: road_search
** PURPOSE:       perform road search
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
bool Spread::road_search (int i_grwth_center,                       /* IN     */
                   int j_grwth_center,                       /* IN     */
                   int *i_road,                              /* OUT    */
                   int *j_road,                              /* OUT    */
                   int max_search_index,                     /* IN     */
                   GRID_P roads)                           /* IN     */
{
  int i;
  int j;
  int i_offset;
  int j_offset;
  bool road_found = FALSE;
  int srch_index;

 
  assert (i_road != NULL);
  assert (j_road != NULL);
  assert (max_search_index >= 0);

  for (srch_index = 0; srch_index < max_search_index; srch_index++)
  {
    spiral (srch_index, &i_offset, &j_offset);
    i = i_grwth_center + i_offset;
    j = j_grwth_center + j_offset;

    if ( (i <  ingrids.GetNumRows()) && 
         (j <  ingrids.GetNumCols()) && 
         (i >= 0)   &&
         (j >= 0))
    {
      if (roads[ingrids.GetNumCols()*i +  j])
      {
        road_found = TRUE;
        (*i_road) = i;
        (*j_road) = j;
        break;
      }
    }
  }

 
  return road_found;
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: spiral
** PURPOSE:       generate spiral search pattern
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
void Spread::spiral (int index,                                     /* IN     */
              int *i_out,                                    /* OUT    */
              int *j_out)                                  /* OUT    */
{
  
  bool bn_found;
  int i;
  int j;
  int bn;
  int bo;
  int total;
  int left_side_len;
  int right_side_len;
  int top_len;
  int bot_len;
  int range1;
  int range2;
  int range3;
  int range4;
  int region_offset;
  int nrows;
  int ncols;
  char msg_buf[MAX_FILENAME_LEN]; 

  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();
  assert (nrows > 0);
  assert (ncols > 0);



  assert (i_out != NULL);
  assert (j_out != NULL);

  bn_found = FALSE;
  for (bn = 1; bn < MAX (ncols, nrows); bn++)
  {
    total = 8 * ((1 + bn) * bn) / 2;
    if (total > index)
    {
      bn_found = TRUE;
      break;
    }
  }
  if (!bn_found)
  {
    sprintf (msg_buf, "Unable to find road search band, bn.");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  bo = index - 8 * ((bn - 1) * bn) / 2;
  left_side_len = right_side_len = bn * 2 + 1;
  top_len = bot_len = bn * 2 - 1;
  range1 = left_side_len;
  range2 = left_side_len + bot_len;
  range3 = left_side_len + bot_len + right_side_len;
  range4 = left_side_len + bot_len + right_side_len + top_len;
  if (bo < range1)
  {
    region_offset = bo % range1;
    i = -bn + region_offset;
    j = -bn;
  }
  else if (bo < range2)
  {
    region_offset = (bo - range1) % range2;
    i = bn;
    j = -bn + 1 + region_offset;
  }
  else if (bo < range3)
  {
    region_offset = (bo - range2) % range3;
    i = bn - region_offset;
    j = bn;
  }
  else if (bo < range4)
  {
    region_offset = (bo - range3) % range4;
    i = -bn;
    j = bn - 1 - region_offset;
  }
  else
  {
    sprintf (msg_buf, "Unable to calculate (i,j) for road search");
    LOG_ERROR (msg_buf);
    EXIT (1);
  }
  *i_out = i;
  *j_out = j;
 
}

/******************************************************************************
*******************************************************************************
** FUNCTION NAME: spread
** PURPOSE:       main spread routine
** AUTHOR:        
** PROGRAMMER:    
** CREATION DATE: 11/11/1999
** DESCRIPTION:
**
**
*/
void Spread::spread (
               float *average_slope,                         /* OUT    */
               int *num_growth_pix,                          /* OUT    */
               int *sng,
               int *sdc,
               int *og,
               int *rt,
               int *pop,
               GRID_P z                                      /* IN/OUT */
  )                                                        /* MOD    */
{
  char func[] = "Spread";
  GRID_P delta;
  int i;
  int total_pixels;
  int nrows;
  int ncols;
  double road_gravity;
  COEFF_TYPE diffusion_coefficient;
  COEFF_TYPE breed_coefficient;
  COEFF_TYPE spread_coefficient;
  GRID_P excld;
  GRID_P roads;
  GRID_P slp;
  GRID_P scratch_gif1;
  GRID_P scratch_gif3;
  SWGHT_TYPE swght[SLOPE_WEIGHT_ARRAY_SZ];

  road_gravity = coeffs.GetCurrentRoadGravity ();
  diffusion_coefficient = coeffs.GetCurrentDiffusion ();
  breed_coefficient = coeffs.GetCurrentBreed ();
  spread_coefficient = coeffs.GetCurrentSpread ();

  scratch_gif1 = mem_GetWGridPtr (__FILE__, func, __LINE__);
  scratch_gif3 = mem_GetWGridPtr (__FILE__, func, __LINE__);

  excld = ingrids.GetExcludedGridPtr (__FILE__, func, __LINE__);
  roads = ingrids.GetRoadGridPtrByYear (__FILE__, func,
                                      __LINE__, runinfo.GetCurrentYear ());
  slp = ingrids.GetSlopeGridPtr (__FILE__, func, __LINE__);

  assert (road_gravity > 0.0);
  assert (diffusion_coefficient > 0.0);
  assert (breed_coefficient > 0.0);
  assert (spread_coefficient > 0.0);
  assert (z != NULL);
  assert (excld != NULL);
  assert (roads != NULL);
  assert (slp != NULL);
  assert (scratch_gif1 != NULL);
  assert (scratch_gif3 != NULL);

  total_pixels = mem_GetTotalPixels ();
  nrows = ingrids.GetNumRows ();
  ncols = ingrids.GetNumCols ();

  assert (total_pixels > 0);
  assert (nrows > 0);
  assert (ncols > 0);


  /*
   *
   * SET UP WORKSPACE
   *
   */
  delta = scratch_gif1;

  /*
   *
   * ZERO THE GROWTH ARRAY FOR THIS TIME PERIOD
   *
   */
  util_init_grid (delta, 0);

  /*
   *
   * GET SLOPE RATES
   *
   */
  get_slp_weights (SLOPE_WEIGHT_ARRAY_SZ,                /* IN     */
                       swght);                             /* OUT    */

  /*
   *
   * PHASE 1N3 - SPONTANEOUS NEIGHBORHOOD GROWTH AND SPREADING
   *
   */


  phase1n3 (diffusion_coefficient,                       /* IN     */
                breed_coefficient,                           /* IN     */
                z,                                           /* IN     */
                delta,                                       /* IN/OUT */
                slp,                                         /* IN     */
                excld,                                       /* IN     */
                swght,                                       /* IN     */
                sng,                                         /* IN/OUT */
                sdc);                                      /* IN/OUT */
  

  /*
   *
   * PHASE 4 - ORGANIC GROWTH
   *
   */
  
  phase4 (spread_coefficient,                            /* IN     */
              z,                                             /* IN     */
              excld,                                         /* IN     */
              delta,                                         /* IN/OUT */
              slp,                                           /* IN     */
              swght,                                         /* IN     */
              og);                                         /* IN/OUT */
  

  /*
   *
   * PHASE 5 - ROAD INFLUENCE GROWTH
   *
   */
  phase5 (road_gravity,                                  /* IN     */
              diffusion_coefficient,                         /* IN     */
              breed_coefficient,                             /* IN     */
              z,                                             /* IN     */
              delta,                                         /* IN/OUT */
              slp,                                           /* IN     */
              excld,                                         /* IN     */
              roads,                                         /* IN     */
              swght,                                         /* IN     */
              rt,                                            /* IN/OUT */
              scratch_gif3);                               /* MOD    */
  

  util_condition_gif (total_pixels,                          /* IN     */
                      delta,                                 /* IN     */
                      GT,                                    /* IN     */
                      PHASE5G,                               /* IN     */
                      delta,                                 /* IN/OUT */
                      0);                                  /* IN     */

  util_condition_gif (total_pixels,                          /* IN     */
                      excld,                                 /* IN     */
                      GE,                                    /* IN     */
                      100,                                   /* IN     */
                      delta,                                 /* IN/OUT */
                      0);                                  /* IN     */

  /* now place growth array into current array */
  (*num_growth_pix) = 0;
  (*average_slope) = 0.0;

  for (i = 0; i < total_pixels; i++)
  {
    if ((z[i] == 0) && (delta[i] > 0))
    {
      /* new growth being placed into array */
      (*average_slope) += (float) slp[i];
      z[i] = delta[i];
      (*num_growth_pix)++;
    }
  }
  *pop = util_count_pixels (total_pixels, z, GE, PHASE0G);

  if (*num_growth_pix == 0)
  {
    *average_slope = 0.0;
  }
  else
  {
    *average_slope /= (float) *num_growth_pix;
  }

  roads = ingrids.GridRelease (__FILE__, func, __LINE__, roads);
  excld = ingrids.GridRelease (__FILE__, func, __LINE__, excld);
  slp = ingrids.GridRelease (__FILE__, func, __LINE__, slp);
  scratch_gif1 = mem_GetWGridFree (__FILE__, func, __LINE__, scratch_gif1);
  scratch_gif3 = mem_GetWGridFree (__FILE__, func, __LINE__, scratch_gif3);
  
}
