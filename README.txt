UMR Cs39x Inc./USGS Modified Urban Growth Model.
For credit for all the people who worked on the Clarke UGM see CREDITS.TXT.

For a friendlier (and more verbose) version of this document go to 
www.umr.edu/~dscheidt/ugm/main.html

To build the ugm:

1.Make sure that you have the following libraries installed on you system/home
directory (all libraries in some version are available at
 www.umr.edu/~dscheidt/ugm/main.html):
LAM-MPI (www.lam-mpi.org)
USGS ImageLib (www.umr.edu/~dscheidt/ugm/main.html)
     USGS MathLib  (www.umr.edu/~dscheidt/ugm/main.html) 
     GD gif library    (www.umr.edu/~dscheidt/ugm/main.html) 
     zlib compressing (www.zlib.org) 
     libpng image library (www.libpng.org) 
     libtiff image library (www.libtiff.org) 
     libgeotiff image library (www.remotesensing.org) 
 
2.Build the ugm distribution by executing the following commands:
    >./configure
    >./make

This should build the distribution.  If it fails is probably means that you don't have
the proper libraries installed or that the Makefile for the ugm is not able to find the headers and libraries for those libraries.

To run the model on your custom data:

Please see www.umr.edu/~dscheidt/ugm/main.html

To run the model on the sample data through a calibration:

Boot lam and enter the distrubution directory.
Edit the schema.calibrate so that the working directory is correct and
the number of nodes is correct.
Execute the following commands:
  >mpirun -c2c ./schema.calibrate
This will produce coarse calibration output in the ./Output/demo50.

To run the model on sample data through a prediction:

Boot lam and enter the distribution directory.
Edit the schema.predict so that the working directory is correct and the
number of nodes is correct.
Execute the fillowing commands:
   >mpirun -c2c ./schema.predict
This will produce prediction output data in the ./Output/demo50.
 