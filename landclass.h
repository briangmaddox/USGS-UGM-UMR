#ifndef LANDCLASS_H
#define LANDCLASS_H
/*! \file landclass.h
    \brief Definition file for the landclass object.
    
    Definition file for the landclass object which
    stores landclass infomation during the simulation.
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/

#include "ugm_defines.h"
#include "scenario.h"

#define MAX_NUM_CLASSES 20
#define MAX_NEW_INDICES 256
#define MAX_LINE_LEN 256

//! Structure to hold landuse class identification data
/*!
 */
typedef struct
{
   int   num;
   char  id[25];
   char  name[50];
   int   idx;
   int   red;
   int   green;
   int   blue;
   bool   EXC;
   bool   trans;
}  Classes;

//! Landclass for storing landclass info.
/*!
 */
class Landclass
{
 public:
  //! Constructor.
  /*! \param inmpi_rank the mpi rank of the process.
   */  
  Landclass (int inmpi_rank); 
  
  //! Destructor.
  /*!
   */
  virtual ~Landclass() {}

  //! Initialization routine for landclasses.
  /*!
   */
  void Init();
    
  //! Returns a pointer to the class_indices.
  /*!
   */
  Classes* GetReducedClassesPtr();

  //! Returns a pointer to to the landuse classes.
  /*!
   */
  Classes* GetClassesPtr();
  
  //! Returns a pointer to the new indices.
  /*!
   */
  int* GetNewIndicesPtr();
  
  //! Returns the urban code.
  /*!
   */
  int GetUrbanCode() const;
  
  //! Returns the number of landclasses.
  /*!
   */
  int GetNumLandclasses() const;

  //! Return the number of reduced classes.
  /*!
   */
  int GetNumReducedclasses() const;
  
  //! Retruns the maximum number of land class.
  /*!
   */
  int GetMaxLandclasses() const;
  
  //! Returns the landclass number for a given index.
  /*! \param i the index of the landclass number.
   */
  int GetClassNum(int i) const;
  
  //! Returns the idx for a given index.
  /*! \param i the index of the idx.
   */
  int GetClassIDX(int i) const;
  
  //! Return the color value for a given landclass.
  /*! \param i the index of the class color.
   */
  int GetClassColor(int i) const;
  
  //! Returns if this is excluded class.
  /*! \param i the class index to be tested.
   */
  bool GetClassEXC(int i) const;
  
  //! Returns if this is a transition class.
  /*! \param i the class index to be tested.
   */
  bool GetClassTrans(int i) const;
  
  //! Return class num for given class_indices index.
  /*! \param i the class_indices index.
   */
  int GetReducedNum(int i) const;
 
  //! Return idx for a given class_indices index
  /*! \param i the class_indices index.
   */
  int GetReducedIDX(int i) const;
  
  //! Return color for given class_indices index.
  /*! \param i the class_indices index.
   */
  int GetReducedColor(int i) const;
  
  //! Is class at class_indices[i] excluded.
  /*! \param i the class_indices index.
   */
  bool GetReducedEXC(int i) const;
  
  //! Is this a transition class.
  /*! \param i the class_indices index.
   */
  bool GetReducedTrans(int i) const;
  
  //! Initializes the annual_class_probabilities file with 0's.
  /*!
   */
  void AnnualProbInit(Scenario & scen);
  
  //! Update the annual_prob_filename.
  /*!
   */
  void AnnualProbUpdate(GRID_P land1_ptr, Scenario & scen);
  
  //! Build prob images from annual_prob_filename.
  /*!
   */
  void BuildProbImage(GRID_P cum_probability_ptr, 
                      GRID_P cum_uncertainty_ptr, Scenario & scen);
  
  //! Test to see if a value is a landclass.
  /*! \param val the value to test for landclass.
   */
  bool IsAlandclass(int val);

   //! Set the grey color of a landclass.
  /*! \param index the index of the class.
      \param val the grey color to set for the class.
  */
  void SetGrayscale (int index, int val);
  
  //! Set the color of a landclass.
  /*! \param index the index of the class.
      \param val the color to set for the class.
  */
  void SetColor (int index, int val);
  
  //! Set the type of a landclass.
  /*! \param index the index of the class.
      \param string the type of the class.
  */
  void SetType (int index, const char* string);
  
  //! Sets the name of a class.
  /*! \param index the index of the class.
      \param string the name of the class.
  */
  void SetName (int index, const char* string);
  
  //! Sets the number of landclasses.
  /*! \param val the number of landclass values.
   */
  void SetNumClasses (int val);
  
 private:
 
  //! Set the maximum the landclass val.
  /*! 
   */
  void SetMaxLandclassNum ();
  
  //! Set the urban code field.
  /*!
   */
  void SetUrbanCode ();
  
  //!  Create mapping from landuse class num back into idx.
  /*!
   */
  void MapLandclassNum_2_idx ();
  
  //! Create the reduced classes.
  /*!
   */
  void CreateReducedClasses ();
  

  Classes class_indices[MAX_NUM_CLASSES];
  int new_indices[MAX_NEW_INDICES];
  Classes landuse_classes[MAX_NUM_CLASSES];
  int urban_code;
  int num_landclasses;
  char filename[MAX_FILENAME_LEN];
  int max_landclass_num;
  int num_reduced_classes;
  char annual_prob_filename[MAX_FILENAME_LEN];
  bool ugm_read;
  int mpi_rank;

};
#endif
