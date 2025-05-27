#!/bin/bash -l
#SBATCH --job-name=Halo416_8K_disk
#SBATCH --output=Halo416_8K_disk.out
#SBATCH --error=Halo416_8K_disk.err
#SBATCH -p kipac
#SBATCH -t 168:00:00
#SBATCH --nodes=8
#SBATCH --ntasks-per-node=32
#SBATCH --mem=128G
#SBATCH --mail-type=ALL
#SBATCH --mail-user=ycwang19@stanford.edu

LD_LIBRARY_PATH=/sdf/home/y/ycwang/GSL/lib
export LD_LIBRARY_PATH
module unload gcc
module unload openmpi
module load gcc/4.8.5
module load openmpi/4.0.4-gcc-4.8.5
module load hdf5 fftw2

mpirun -np 256 Gadget2disk parameters.tex 2
