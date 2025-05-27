#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <unistd.h>
#include "halo_props.h"
#include "disk_mass.h"

//RW Function that loads in UniverseMachine M* history for the MW host
double Ms_UM(double z) {
  FILE *myFile1, *myFile2;
  int HALO_NO = HALO_ID;
  char buffer[1024];
  if ((HALO_NO == 9749) || (HALO_NO == 9829)){
      sprintf(buffer, "%04d", HALO_NO);
  }
  else{
      sprintf(buffer, "%03d", HALO_NO);
  }
  char* halo_no_str = buffer;
  char fname1[1024];
  char fname2[1024];

  char cwd[1024]; //current working directory
  getcwd(cwd, sizeof(cwd));
  char file_head[1024];
  snprintf(file_head, sizeof(file_head), "%s/um_sfh/Halo", cwd);

  char* file_tail1 = "8_Z.txt";
  char* file_tail2 = "8_Mstar.txt";
  snprintf(fname1, sizeof(fname1), "%s%s", file_head, halo_no_str);
  snprintf(fname2,sizeof(fname2), "%s%s", file_head, halo_no_str);
  char* file_name1 = fname1;
  char* file_name2 = fname2;
  strcat(file_name1, file_tail1);
  strcat(file_name2, file_tail2);
  myFile1 = fopen(file_name1, "r");
  myFile2 = fopen(file_name2, "r");
  int snap = TOT_SNAP;

  double red[snap];
  double mstar[snap];
  int i;
  for (i = 0; i < snap; i++){
      fscanf(myFile1, "%lf", &red[i]);
      fscanf(myFile2, "%lf", &mstar[i]);
  }

  double lgms_z;
  {
    gsl_interp_accel *acc
      = gsl_interp_accel_alloc ();
    gsl_spline *spline
      = gsl_spline_alloc (gsl_interp_linear, snap);

    gsl_spline_init (spline, red, mstar, snap);
    lgms_z = gsl_spline_eval (spline, z, acc);

    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
  }

  fclose(myFile1);
  fclose(myFile2);
  return pow(10., lgms_z);
}

//RW Semi-empirical stellar/(stellar+gas) fraction from NeutralUniverseMachine Guo et al. 2023
double Fs_Guo(double z) {
  char cwd[1024]; //current working directory
  getcwd(cwd, sizeof(cwd));
  char file_head[1024];
  snprintf(file_head, sizeof(file_head), "%s/um_sfh", cwd);

  FILE *myFile1, *myFile2;
  char file1[1024];
  char file2[1024];
  snprintf(file1, sizeof(file1), "%s/Guo_Z.txt", file_head);
  snprintf(file2, sizeof(file2), "%s/Guo_Fstar.txt", file_head);
  myFile1 = fopen(file1, "r");
  myFile2 = fopen(file2, "r");
  int snap = 14;

  double red[snap];
  double fstar[snap];
  int i;
  for (i = 0; i < snap; i++){
      fscanf(myFile1, "%lf", &red[i]);
      fscanf(myFile2, "%lf", &fstar[i]);
  }

  double fs_z;
  {
    gsl_interp_accel *acc
      = gsl_interp_accel_alloc ();
    gsl_spline *spline
      = gsl_spline_alloc (gsl_interp_linear, snap);

    gsl_spline_init (spline, red, fstar, snap);
    fs_z = gsl_spline_eval (spline, z, acc);

    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
  }

  fclose(myFile1);
  fclose(myFile2);
  return fs_z;
}
