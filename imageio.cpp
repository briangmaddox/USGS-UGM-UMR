/*! \file imageio.cpp
    \brief Implementation file for the imageio object.
    
    Implementation file for the imageio object which handles
    all image file format input and output for the model.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include "GeoTIFFImageIFile.h"
#include "GeoTIFFImageOFile.h"
#include "TIFFImageIFile.h"
#include "TIFFImageOFile.h"
#include "PNGImageIFile.h"
#include "RGBPalette.h"
#include "ProjectionParams.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
extern "C"
{
#include "GD/gd.h"
#include "GD/gdfonts.h"
#include "GD/gdfontg.h"
}
#include "imageio.h"

/*
 Returns image metric info based on image type.
*/
void ImageIO::GetImageInfo (Grid * grid_ptr, const Scenario &scene)
{

  int temp1, temp2;
  long int tempwidth, tempheight;
  FILE *fp;
  unsigned char buffer[BYTES2READ + 1];
  char id_str[7];
  int resolution;
  int ncols;
  int nrows;
  int bits_per_pixel;
  int color_bits;
  USGSImageLib::TIFFImageIFile * infile;
  USGSImageLib::GeoTIFFImageIFile *ginfile;
  USGSImageLib::PNGImageIFile * pinfile;
  char msg_buf[MAX_FILENAME_LEN]; 

  std::string filename(grid_ptr->filename);

  switch (scene.GetInputImageType())
  {
     case GIF_TYPE:

       FILE_OPEN (fp, grid_ptr->filename, "rb");
       fgets ((char *) buffer, BYTES2READ, fp);
       fclose (fp);
       
   
       
       strncpy (id_str, (char *) buffer, strlen (GIF_ID));
       ncols = CONVERT2UINT 
         (buffer[GIF_COL_OFFSET], buffer[GIF_COL_OFFSET + 1]);
       nrows = CONVERT2UINT 
         (buffer[GIF_ROW_OFFSET], buffer[GIF_ROW_OFFSET + 1]);
       //       total_pixels = nrows * ncols;
       resolution = (int) buffer[GIF_RES_OFFSET];
       color_bits = (((resolution & 112) >> 4) + 1);
       bits_per_pixel = (resolution & 7) + 1;
       grid_ptr->ncols = ncols;
       grid_ptr->nrows = nrows;
       grid_ptr->color_bits = color_bits;
       grid_ptr->bits_per_pixel = bits_per_pixel;
       grid_ptr->size_bytes = BYTES_PER_PIXEL * ncols * nrows;
       grid_ptr->size_words = ROUND_BYTES_TO_WORD_BNDRY (grid_ptr->size_bytes);
       break;
     case TIFF_TYPE:
       infile = new USGSImageLib::TIFFImageIFile (filename);

       color_bits = 8;
       infile->getBitsPerSample (temp1);
       infile->getSamplesPerPixel (temp2);
       bits_per_pixel = temp1 * temp2;

       infile->getWidth(tempwidth);
       grid_ptr->ncols = tempwidth;
       infile->getHeight(tempheight);
       grid_ptr->nrows = tempheight;
       grid_ptr->color_bits = color_bits;
       grid_ptr->bits_per_pixel = bits_per_pixel;
       grid_ptr->size_bytes = 
         BYTES_PER_PIXEL * grid_ptr->ncols * grid_ptr->nrows;
       grid_ptr->size_words = 
         ROUND_BYTES_TO_WORD_BNDRY (grid_ptr->size_bytes);
       
       delete infile;
       break;
     case GEOTIFF_TYPE:
       ginfile = new USGSImageLib::GeoTIFFImageIFile (filename);

       color_bits = 8;
       ginfile->getBitsPerSample (temp1);
       ginfile->getSamplesPerPixel (temp2);
       bits_per_pixel = temp1 * temp2;

       ginfile->getWidth(tempwidth);
       grid_ptr->ncols = tempwidth;
       ginfile->getHeight(tempheight);
       grid_ptr->nrows = tempheight;
       grid_ptr->color_bits = color_bits;
       grid_ptr->bits_per_pixel = bits_per_pixel;
       grid_ptr->size_bytes = 
         BYTES_PER_PIXEL * grid_ptr->ncols * grid_ptr->nrows;
       grid_ptr->size_words = 
         ROUND_BYTES_TO_WORD_BNDRY (grid_ptr->size_bytes);
       
       delete ginfile;
       break;
     case PNG_TYPE:
       pinfile = new USGSImageLib::PNGImageIFile (filename);
       
       color_bits = 8;
       pinfile->getBitsPerSample (temp1);
       pinfile->getSamplesPerPixel (temp2);
       bits_per_pixel = temp1 * temp2;

       pinfile->getWidth(tempwidth);
       grid_ptr->ncols = tempwidth;
       pinfile->getHeight(tempheight);
       grid_ptr->nrows = tempheight;
       grid_ptr->color_bits = color_bits;
       grid_ptr->bits_per_pixel = bits_per_pixel;
       grid_ptr->size_bytes = BYTES_PER_PIXEL * grid_ptr->ncols * grid_ptr->nrows;
       grid_ptr->size_words = ROUND_BYTES_TO_WORD_BNDRY (grid_ptr->size_bytes);
       
       delete pinfile;
       break;


     default:
        printf ("Invalid format for input files\n");
        EXIT (1);       
     
  }

}



/*
   FUNCTION NAME: gdif_WriteColorKey
   PURPOSE:       write colorkeys for a given colortable
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void ImageIO::WriteColorKey(IGrid & temp, Scenario & internal, 
                            const Colortable *
                            colortable, char fname[]) 
{
  gdImagePtr im_out;
  FILE *fp;
  int i;
  int j;
  int sx;
  int sy;
  char msg_buf[MAX_FILENAME_LEN]; 
  assert (colortable != NULL);
  assert (fname != NULL);
  

  /*
   
    OPEN OUTPUT GIF FILE
   
   */
  FILE_OPEN (fp, fname, "w");

  /*
   
    CALL GD TO CREATE A GIF
   
   */
  sx = temp.GetNumCols ();
  sy = colortable->size;
  im_out = gdImageCreate (sx, sy);
  /*
   
    SET UP GD'S COLORTABLE
   
   */
  for (i = 0; i < colortable->size; i++)
  {
    gdImageColorAllocate (im_out,
                          colortable->color[i].red,
                          colortable->color[i].green,
                          colortable->color[i].blue);
  }
  /*
   
    WRITE GIF TO GD'S MEMORY
   
   */
  for (i = 0; i < colortable->size; i++)
  {
    for (j = 0; j < temp.GetNumCols (); j++)
    {
      im_out->pixels[j][i] = (unsigned char) i;
    }
  }
  /*
   
    OUTPUT THE GIF TO DISK
   
   */
  gdImageGif (im_out, fp);
  /*
   
    CLOSE THE OUTPUT FILE
   
   */
  fclose (fp);
  /*
   
    FREE GD'S MEMORY
   
   */
  gdImageDestroy (im_out);

}


/*
   FUNCTION NAME: gdif_WriteGIF
   PURPOSE:       interface to GD and Imagelib for writing an image
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void ImageIO::WriteGRID (
                  GRID_P gif,
                  const Colortable *colortable,
                  Scenario & internal,
                  IGrid & temp,
                  char fname[],
                  char date[],
                  int date_color_index
  )
{

  gdImagePtr im_out;
  FILE *fp(0);
  int i;
  int j;
  
  assert (gif != NULL);
  assert (colortable != NULL);
  assert (fname != NULL);
  std::string filename(fname);

  USGSImageLib::RGBPalette RGBPal(colortable->size);
  USGSImageLib::TIFFImageOFile * tiff_out;
  USGSImageLib::GeoTIFFImageOFile * g_tiff_out;
  USGSImageLib::RGBPixel tempRGB;  
  unsigned char * newarray;
  char msg_buf[MAX_FILENAME_LEN]; 
  
  /*
   
    OPEN OUTPUT GIF FILE
   
   */
   switch(internal.GetOutputImageType()) 
   {
     case TIFF_TYPE:
        newarray = new unsigned char[temp.GetNumCols()];
	
        tiff_out = new USGSImageLib::TIFFImageOFile 
          (filename, temp.GetNumCols(),
           temp.GetNumRows(), PHOTO_PALETTE, false);
			
   	tiff_out->setSubfileType(0);
   	tiff_out->setRowsPerStrip(1);
	tiff_out->setBitsPerSample(8);
   	tiff_out->setSamplesPerPixel(1);
   	tiff_out->setPlanarConfig(1);
			
	// Write color table
	for (i = 0; i < colortable->size; i++)
  	{
    	    tempRGB.setRed(colortable->color[i].red);
	    tempRGB.setGreen(colortable->color[i].green);
	    tempRGB.setBlue(colortable->color[i].blue);
	    RGBPal.setEntry(i,tempRGB);
	}
  
	tiff_out->setPalette(&RGBPal);
  
  	/*
	 
   	  WRITE GRID TO MEMORY
   	 
   	 */
	for (i = 0; i < temp.GetNumRows (); i++)
  	{
	    for (j = 0; j < temp.GetNumCols (); j++)
	    {
	      newarray[j] = (unsigned char) gif[temp.GetNumCols()*i+j];
    	    }
    	    tiff_out->putRawScanline((long int)i, (void *)newarray);
	}
  
  	delete []newarray;
	delete tiff_out;
	break;

      case GIF_TYPE:
        if ( fname != NULL ) FILE_OPEN (fp, fname, "wb");
	

	/*
   	 
	  CALL GD TO CREATE A GIF
	 
	 */
  	im_out = gdImageCreate (temp.GetNumCols (), temp.GetNumRows ());
	im_out->sx = temp.GetNumCols ();
  	im_out->sy = temp.GetNumRows ();

	/*
	 
	  SET UP GD'S COLORTABLE
	 
	 */
	for (i = 0; i < colortable->size; i++)
	{
	  gdImageColorAllocate (im_out,
                          colortable->color[i].red,
                          colortable->color[i].green,
                          colortable->color[i].blue);
	}
	
	/*
   	 
	  WRITE GRID TO GD'S MEMORY
	 
	 */
  	for (i = 0; i < temp.GetNumRows (); i++)
  	{
    	    for (j = 0; j < temp.GetNumCols (); j++)
     	    {
      	       im_out->pixels[j][i] = 
	            (unsigned char) gif[temp.GetNumCols()*i +  j];
	    }

	}
	
	/*
	 
	  OUTPUT THE GIF TO DISK
	 
	 */
         gdImageGif (im_out, fp);
  
  	/*
	 
 	  CLOSE THE OUTPUT FILE
	 
    	 */
   	fclose (fp);

  	/*
   	
   	 FREE GD'S MEMORY
   	
   	*/
  	gdImageDestroy (im_out);
	break;

      case GEOTIFF_TYPE:
        newarray = new unsigned char[temp.GetNumCols()];
	
        g_tiff_out = new USGSImageLib::GeoTIFFImageOFile 
          (filename, temp.GetNumCols(),
           temp.GetNumRows(), PHOTO_PALETTE);
        
   	g_tiff_out->setSubfileType(0);
   	g_tiff_out->setRowsPerStrip(1);
	g_tiff_out->setBitsPerSample(8);
   	g_tiff_out->setSamplesPerPixel(1);
   	g_tiff_out->setPlanarConfig(1);


        // Set GEO Data
        g_tiff_out->setGeoKey( ProjCoordTransGeoKey, temp.geoParams.projtype );
        g_tiff_out->setGeoKey 
          ( ProjectedCSTypeGeoKey, temp.geoParams.PCSCode );
	g_tiff_out->setGeoKey ( GeographicTypeGeoKey, temp.geoParams.datum );
        g_tiff_out->setLinearUnits ( temp.geoParams.unit );
        g_tiff_out->setGeoKey 
          ( ProjStdParallel1GeoKey, temp.geoParams.StdParallel1 );
        g_tiff_out->setGeoKey 
          ( ProjStdParallel2GeoKey, temp.geoParams.StdParallel2 );
        g_tiff_out->setGeoKey 
          ( ProjNatOriginLongGeoKey, temp.geoParams.NatOriginLong );
        g_tiff_out->setGeoKey 
          ( ProjNatOriginLatGeoKey, temp.geoParams.NatOriginLat );
        g_tiff_out->setGeoKey 
          ( ProjFalseOriginLongGeoKey, temp.geoParams.FalseOriginLong );
        g_tiff_out->setGeoKey 
          ( ProjFalseOriginLatGeoKey, temp.geoParams.FalseOriginLat );
        g_tiff_out->setGeoKey 
          ( ProjFalseOriginEastingGeoKey, temp.geoParams.FalseOriginEasting );
        g_tiff_out->setGeoKey 
          (ProjFalseOriginNorthingGeoKey, temp.geoParams.FalseOriginNorthing );
        g_tiff_out->setGeoKey 
          ( ProjCenterLongGeoKey, temp.geoParams.CenterLong );
        g_tiff_out->setGeoKey 
          ( ProjCenterLatGeoKey, temp.geoParams.CenterLat );
        g_tiff_out->setGeoKey 
          ( ProjCenterEastingGeoKey, temp.geoParams.CenterEasting );
        g_tiff_out->setGeoKey 
          ( ProjCenterNorthingGeoKey, temp.geoParams.CenterNorthing );
        g_tiff_out->setGeoKey 
          ( ProjScaleAtNatOriginGeoKey, temp.geoParams.ScaleAtNatOrigin );
        g_tiff_out->setGeoKey 
          ( ProjAzimuthAngleGeoKey, temp.geoParams.AzimuthAngle );
        g_tiff_out->setGeoKey 
        (ProjStraightVertPoleLongGeoKey, temp.geoParams.StraightVertPoleLong );
        g_tiff_out->setGeoKey 
          ( ProjFalseEastingGeoKey, temp.geoParams.FalseEasting );
        g_tiff_out->setGeoKey 
          ( ProjFalseNorthingGeoKey, temp.geoParams.FalseNorthing );

			
	// Write color table
	for (i = 0; i < colortable->size; i++)
  	{
    	    tempRGB.setRed(colortable->color[i].red);
	    tempRGB.setGreen(colortable->color[i].green);
	    tempRGB.setBlue(colortable->color[i].blue);
	    RGBPal.setEntry(i,tempRGB);
	}
  
	g_tiff_out->setPalette(&RGBPal);
  
  	/*
	 
   	  WRITE GRID TO MEMORY
   	 
   	 */
	for (i = 0; i < temp.GetNumRows (); i++)
  	{
	    for (j = 0; j < temp.GetNumCols (); j++)
	    {
	      newarray[j] = (unsigned char) gif[temp.GetNumCols()*i+j];
    	    }
    	    g_tiff_out->putRawScanline((long int)i, (void *)newarray);
	}
  
  	delete []newarray;
	delete g_tiff_out;
	break;

      default:
        printf ("ImageIO::Invalid format for input files\n");
        EXIT (1);       

   }
  
   
  
  

  

  /*
   
    WRITE THE DATE IF REQUESTED
   
   */

  /* This was commented out to prevent the date from overriding
    the prediction output file rp/mf 2/20/01
     if (strlen (date) > 0)
    {
     gdImageString (im_out, gdFontGiant, DATE_X, DATE_Y, date, date_color_index);
    }
   */


  
 // FUNC_END;

}

/*
   FUNCTION NAME: ReadGIF
   PURPOSE:       reads grids from input files
   AUTHOR:        
   PROGRAMMER:    
   CREATION DATE: 11/11/1999
   DESCRIPTION:
  
  
*/
void ImageIO::ReadGRID(GRID_P gif_ptr, 
                       IGrid & temp,
                       Scenario & internal, 
                       char *fname)
{

  FILE *in;
  int i = 0;
  int j = 0;
  gdImagePtr im_in;
  unsigned short int index_val(0);
  int red;
  int green;
  int blue;
  long int row;
  long int col;
  std::string filename(fname);
  char msg_buf[MAX_FILENAME_LEN]; 

  USGSImageLib::TIFFImageIFile * infile;
  USGSImageLib::GeoTIFFImageIFile * ginfile;
  USGSImageLib::PNGImageIFile * pnginfile;
  USGSImageLib::RGBPixel p1;
  USGSImageLib::RawRGBPixel p2;


  assert (gif_ptr != NULL);
  assert (temp.GetNumRows () > 0);
  assert (temp.GetNumCols () > 0);

  
  switch (internal.GetInputImageType())
  {
     case GIF_TYPE:
         /*
         
          OPEN THE GIF IMAGE FILE FOR READING
         
         */
         FILE_OPEN (in, fname, "rb");  // ImageLib will open file

         /*
         
          HAVE GD GET THE IMAGE AND THEN CHECK THE SIZE OF THE IMAGE
         
         */
         im_in = gdImageCreateFromGif (in);
         row = im_in->sy;
         col = im_in->sx;

         if ((row != temp.GetNumRows ()) || (col != temp.GetNumCols ()))
         {
            sprintf (msg_buf, 
                     "%4uX%4u image doesn't match expected size %4uX%4u\n",
           static_cast<unsigned int>(row), 
           static_cast<unsigned int>(col), 
           static_cast<unsigned int>(temp.GetNumRows ()), 
           static_cast<unsigned int>(temp.GetNumCols ()));
            LOG_ERROR (msg_buf);
            EXIT (1);
         }

         fclose (in);
	 
         for (j = 0; j < temp.GetNumCols (); j++)
         {
            for (i = 0; i < temp.GetNumRows (); i++)
            {
               index_val = (unsigned short int) gdImageGetPixel (im_in, j, i);
               red = gdImageRed (im_in, index_val);
               green = gdImageGreen (im_in, index_val);
               blue = gdImageBlue (im_in, index_val);
               if ((red == green) && (red == blue))
               {
                  gif_ptr[temp.GetNumCols()*i +  j] = red;
               }
               else
               {
                  sprintf (msg_buf, 
                           "file:%s is not a true gray scale image\n", fname);
                  LOG_ERROR (msg_buf);
                  sprintf (msg_buf, 
                 "index=%u RGB= (%u,%u,%u)\n", index_val, red, green, blue);
                  LOG_ERROR (msg_buf);
                  EXIT (1);
               }
            }
         }

         /*
         
          FREE GD'S MEMORY
         
         */
         gdImageDestroy (im_in);

         break;
	 
      case TIFF_TYPE:
         infile = new USGSImageLib::TIFFImageIFile ( filename );
      
         infile->getWidth ( col );
         infile->getHeight ( row );
         if ((row != temp.GetNumRows ()) || (col != temp.GetNumCols ()))
         {
            sprintf (msg_buf, 
                     "%4uX%4u image doesn't match expected size %4uX%4u\n",
                     static_cast<unsigned int>(row), 
                     static_cast<unsigned int>(col), 
                     static_cast<unsigned int>(temp.GetNumRows ()), 
                     static_cast<unsigned int>(temp.GetNumCols ()));
            LOG_ERROR (msg_buf);
            EXIT (1);
         }

         /*
         
          FILL IN THE GRID WITH VALUES FROM IMAGELIB
          CHECK THAT THE IMAGE IS A TRUE GRAYSCALE IMAGE
         
         */
         for (j = 0; j < temp.GetNumCols (); j++)
         {
            for (i = 0; i < temp.GetNumRows (); i++)
            {
               infile->getRawRGBPixel ((long)j, (long)i, &p2);
               red = p2.Red;
               green = p2.Green;
               blue = p2.Blue;

               if ((red == green) && (red == blue))
               {
                  gif_ptr[temp.GetNumCols()*i +  j] = red;
               }
               else
               {
                  sprintf (msg_buf, 
                           "file:%s is not a true gray scale image\n", fname);
                  LOG_ERROR (msg_buf);
                  sprintf (msg_buf, 
                  "index=%u RGB= (%u,%u,%u)\n", index_val, red, green, blue);
                  LOG_ERROR (msg_buf);
                  EXIT (1);
               }
            }
         }
	 delete infile;
         break;
	 
      case GEOTIFF_TYPE:
         ginfile = new USGSImageLib::GeoTIFFImageIFile ( filename );
      
         // Get GEO Data
         ginfile->getGeoKey( ProjCoordTransGeoKey, temp.geoParams.projtype );
         ginfile->getLinearUnits ( temp.geoParams.unit );
	 ginfile->getGeoKey ( ProjectedCSTypeGeoKey, temp.geoParams.PCSCode );
	 ginfile->getGeoKey ( GeographicTypeGeoKey, temp.geoParams.datum );
         ginfile->getGeoKey 
           ( ProjStdParallel1GeoKey, temp.geoParams.StdParallel1 );
         ginfile->getGeoKey 
           ( ProjStdParallel2GeoKey, temp.geoParams.StdParallel2 );
         ginfile->getGeoKey 
           ( ProjNatOriginLongGeoKey, temp.geoParams.NatOriginLong );
         ginfile->getGeoKey 
           ( ProjNatOriginLatGeoKey, temp.geoParams.NatOriginLat );
         ginfile->getGeoKey 
           ( ProjFalseOriginLongGeoKey, temp.geoParams.FalseOriginLong );
         ginfile->getGeoKey 
           ( ProjFalseOriginLatGeoKey, temp.geoParams.FalseOriginLat );
         ginfile->getGeoKey 
           ( ProjFalseOriginEastingGeoKey, temp.geoParams.FalseOriginEasting );
         ginfile->getGeoKey 
         ( ProjFalseOriginNorthingGeoKey, temp.geoParams.FalseOriginNorthing );
         ginfile->getGeoKey 
           ( ProjCenterLongGeoKey, temp.geoParams.CenterLong );
         ginfile->getGeoKey 
           ( ProjCenterLatGeoKey, temp.geoParams.CenterLat );
         ginfile->getGeoKey 
           ( ProjCenterEastingGeoKey, temp.geoParams.CenterEasting );
         ginfile->getGeoKey 
           ( ProjCenterNorthingGeoKey, temp.geoParams.CenterNorthing );
         ginfile->getGeoKey 
           ( ProjScaleAtNatOriginGeoKey, temp.geoParams.ScaleAtNatOrigin );
         ginfile->getGeoKey 
           ( ProjAzimuthAngleGeoKey, temp.geoParams.AzimuthAngle );
         ginfile->getGeoKey 
       ( ProjStraightVertPoleLongGeoKey, temp.geoParams.StraightVertPoleLong );
         ginfile->getGeoKey 
           ( ProjFalseEastingGeoKey, temp.geoParams.FalseEasting );
         ginfile->getGeoKey 
           ( ProjFalseNorthingGeoKey, temp.geoParams.FalseNorthing );

	 
         ginfile->getWidth ( col );
         ginfile->getHeight ( row );
         if ((row != temp.GetNumRows ()) || (col != temp.GetNumCols ()))
         {
            sprintf (msg_buf, 
                     "%4uX%4u image doesn't match expected size %4uX%4u\n",
                     static_cast<unsigned int>(row), 
                     static_cast<unsigned int>(col), 
                     static_cast<unsigned int>(temp.GetNumRows ()), 
                     static_cast<unsigned int>(temp.GetNumCols ()));
            LOG_ERROR (msg_buf);
            EXIT (1);
         }

         /*
         
          FILL IN THE GRID WITH VALUES FROM IMAGELIB
          CHECK THAT THE IMAGE IS A TRUE GRAYSCALE IMAGE
         
         */
         for (j = 0; j < temp.GetNumCols (); j++)
         {
            for (i = 0; i < temp.GetNumRows (); i++)
            {
               ginfile->getRawRGBPixel ((long)j, (long)i, &p2);
               red = p2.Red;
               green = p2.Green;
               blue = p2.Blue;

               if ((red == green) && (red == blue))
               {
                  gif_ptr[temp.GetNumCols()*i +  j] = red;
               }
               else
               {
                  sprintf (msg_buf, 
                           "file:%s is not a true gray scale image\n", fname);
                  LOG_ERROR (msg_buf);
                  sprintf (msg_buf, 
                 "index=%u RGB= (%u,%u,%u)\n", index_val, red, green, blue);
                  LOG_ERROR (msg_buf);
                  EXIT (1);
               }
            }
         }
	 delete ginfile;
         break;
      
      case PNG_TYPE:
         pnginfile = new USGSImageLib::PNGImageIFile ( filename );
      
         pnginfile->getWidth ( col );
         pnginfile->getHeight ( row );
         if ((row != temp.GetNumRows ()) || (col != temp.GetNumCols ()))
         {
            sprintf (msg_buf, 
                     "%4uX%4u image doesn't match expected size %4uX%4u\n",
                     static_cast<unsigned int>(row), 
                     static_cast<unsigned int>(col), 
                     static_cast<unsigned int>(temp.GetNumRows ()), 
                     static_cast<unsigned int>(temp.GetNumCols ()));
            LOG_ERROR (msg_buf);
            EXIT (1);
         }

         /*
         
          FILL IN THE GRID WITH VALUES FROM IMAGELIB
          CHECK THAT THE IMAGE IS A TRUE GRAYSCALE IMAGE
         
         */
         for (j = 0; j < temp.GetNumCols (); j++)
         {
            for (i = 0; i < temp.GetNumRows (); i++)
            {
               pnginfile->getRawRGBPixel ((long)j, (long)i, &p2);
               red = p2.Red;
               green = p2.Green;
               blue = p2.Blue;

               if ((red == green) && (red == blue))
               {
                  gif_ptr[temp.GetNumCols()*i +  j] = red;
               }
               else
               {
                  sprintf (msg_buf, 
                           "file:%s is not a true gray scale image\n", fname);
                  LOG_ERROR (msg_buf);
                  sprintf (msg_buf, 
                  "index=%u RGB= (%u,%u,%u)\n", index_val, red, green, blue);
                  LOG_ERROR (msg_buf);
                  EXIT (1);
               }
            }
         }
	 delete pnginfile;
         break;

      default:
         printf ("Imageio::Invalid format for input files\n");
         EXIT (1);       
     
   }


}















