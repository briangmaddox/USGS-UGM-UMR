#ifndef OUTPUT_H
#define OUTPUT_H
/*! \file output.h
    \brief Definition file for the output utility functions.
    
    For credit see CREDITS.TXT in this directory.
    \sa CREDITS.TXT
*/
#include "igrid.h"
#include "scenario.h"

//! Echos input grid state.
/*!
 */
void out_echotruth (IGrid & input_grid);

//! Writes the restart data.
/*! This is unsupported in this version of the model.
 */
void out_write_restart_data(char*, Scenario &,int,int,int,int,int,int,int);

//! This writes the calibrate file
/*!
 */
void out_write_calibrate_file (int stop_date,
                            int num_monte_carlo,
                            long random_seed,
                            coeff_int_info* step_coeff,
                            coeff_int_info* start_coeff,
                            coeff_int_info* stop_coeff);
//! This writes the control stats file.
/*! This is deprecated.
 */
void
  out_write_control_stats(char* filename,
                          double sum,
                          float compare,
                          float pop_r2,
                          float edge_r2,
                          float cluster_r2,
                          float mean_cluster_size_r2,
                          float leesal,
                          float average_slope_r2,
                          float pct_urban_r2,
                          float xmu_r2,
                          float ymu_r2,
                          float sdist_r2,
                          float value,
                          coeff_val_info* saved_coefficient);
//! Dumps the scenario to a output file
/*!
 */
void out_dump(char* filename,
	      Scenario & scene,
              void* ptr,
              int count);

//! This writes the output log.
/*! Deprecated.
 */
void
  out_write_param_log (char* filename,
                       coeff_val_info * current_coefficient,
                       int index,
                       IGrid & input_grid);
//! This writes the avg and dev files
/*! Deprecated.
 */
void out_write_avg_dev(char* filename,      /* IN     */
                       double* ptr,         /* IN     */
                       int row_dim,         /* IN     */
                       int col_dim,         /* IN     */
                       int row_count,       /* IN     */
                       int col_count);      /* IN     */
//! Writes debug info to a file.
/*! Deprecated.
 */
void
  out_dump_debug (char *var_name,
                  void *var_ptr,
                  char* calling_func,
                  int line,
                  int count);

//! Writes a banner for the ugm to a file.
/*!
 */
void
out_banner(FILE* fp);

//! Writes text centered to a file.
/*!
 */
void
out_center_text(FILE* fp,
                char* source,
                char* text,
                char* destination,
                int left_offset);

#endif
