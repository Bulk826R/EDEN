#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <unistd.h>
#include "halo_props.h"

//RW Function that loads in UniverseMachine M* history for the MW host
double Ms_UM(double z);
double Fs_Guo(double z); 
