#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "halo_props.h"
#include "disk_mass.h"

int main(void){
  double Mstar_pred = Ms_UM(1.);
  double Fstar_pred = Fs_Guo(1.);
  printf("Mstar_pred, Fstar_pred = %f %f \n", Mstar_pred, Fstar_pred);
}
     
