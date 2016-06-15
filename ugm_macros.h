#ifndef UGM_MACROS_H
#define UGM_MACROS_H
/*! \file ugm_macros.h
    \brief Definition file for useful macros.
    
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/


#include <unistd.h>
#include <iostream>
#include "ugm_defines.h"

#define EXIT(code) exit(code)


#define TRANS_OFFSET(i,j) (i)*lclasses.GetNumLandclasses() + (j)

#define PRINT_INT(x) printf("%s = %d\n",#x,(x))

#define PRINT_FLOAT(x) printf("%s = %f\n",#x,(x))

#define LOG_INT(fp,x) fprintf(fp,"%s %u %s = %d\n",                       \
           __FILE__,__LINE__,#x,(x))

#define LOG_FLOAT(fp,x) fprintf(fp,"%s %u %s = %f\n",                     \
          __FILE__,__LINE__,#x,(x))

#define LOG_STRING(fp,x) fprintf(fp,"%s %u %s = %s\n",                    \
          __FILE__,__LINE__,#x,(x))

#ifndef lint
  #define LOG_MEM_CHAR_ARRAY(fp,ptr,size,count)                           \
        fprintf(fp,"%d s %-27s size=%5u bytes count=%4u %s %u\n",         \
               (ptr),#ptr,(size),(count),__FILE__,__LINE__)

  #define LOG_MEM(fp,ptr,size,count)                                      \
        fprintf(fp,"%d s %-27s size=%5u bytes count=%4u %s %u\n",         \
               (ptr),#ptr,(size),(count),__FILE__,__LINE__);              \
        fprintf(fp,"%d e %-27s END OF %s %u\n",                           \
               (ptr)+count,#ptr,__FILE__,__LINE__)
#else
  #define LOG_MEM_CHAR_ARRAY(fp,ptr,size,count)                           \
        fprintf(fp,"lint test\n")
  #define LOG_MEM(fp,ptr,size,count)                                      \
        fprintf(fp,"lint test\n")
#endif


#define LOG_ERROR(str) std::cerr << str << std::endl;
      
#define MAX(a,b) (((a)>(b))?(a):(b))

#define MIN(a,b) (((a)<(b))?(a):(b))

#define OFFSET(i,j)    ((i)*ingrids.GetNumCols() + (j))

#define IMAGE_PT(row,col)                                                 \
        (((row) <  ingrids.GetNumRows()) &&                                 \
         ((col) <  ingrids.GetNumCols()) &&                                 \
         ((row) >= 0)         &&                                          \
         ((col) >= 0))

#define INTERIOR_PT(row,col)                                              \
        (((row) < igrid_GetNumRows() - 1) &&                              \
         ((col) < igrid_GetNumCols() - 1) &&                              \
         ((row) > 0)             &&                                       \
         ((col) > 0))

#define URBANIZE(row,col)                                                 \
        (z[OFFSET ((row),(col))] == 0) &&                                 \
        (delta[OFFSET ((row),(col))] == 0) &&                             \
        (RANDOM_FLOAT < swght[slp[OFFSET ((row),(col))]]) &&              \
        (excld[OFFSET ((row),(col))] < RANDOM_INT (100))


#define ROUND_BYTES_TO_WORD_BNDRY(bytes) (((bytes)+(BYTES_PER_WORD)-1)/   \
         (BYTES_PER_WORD))*(BYTES_PER_WORD)


#define PRINT_ERROR(str)                                                  \
        printf("\n\nERROR at line: %d Module: %s \n%s\n", \
          __LINE__,__FILE__,(str))

#define PRINT_MSG(str)                                                    \
        printf("\nline: %d Module: %s \n%s\n",            \
         __LINE__,__FILE__,(str))

                          
#define FILE_OPEN(fp,name,options)                                        \
        (fp) = fopen((name),(options));                                   \
        while((EMFILE==errno)&&(fp==NULL))                                \
        {                                                                 \
          sprintf (msg_buf,"%s %s\n%s %s\n",                              \
            "Unable to open file: ",(name),strerror (errno),              \
            " Trying again");                                             \
          sleep(3);                                                       \
          (fp) = fopen((name),(options));                                 \
          if(fp)                                                          \
          {                                                               \
            sprintf(msg_buf,"Successfully opened file: %s",(name));       \
            PRINT_MSG(msg_buf);                                           \
          }                                                               \
        }                                                                 \
        if(fp==NULL)                                                      \
        {                                                                 \
          sprintf (msg_buf,"Unable to open file: %s\n", (name));          \
          PRINT_MSG(msg_buf);                                             \
          EXIT(1);                                                        \
        }


#endif
