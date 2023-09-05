#!/bin/bash 

export x_lower=$1 
export x_upper=$2
export y_lower=$3
export y_upper=$4
export z_lower=$5
export z_upper=$6

source /opt/homebrew/Caskroom/miniforge/base/etc/profile.d/conda.sh
conda activate network

# clear the output directory of current outputs
rm -f /Users/jamie/Documents/particle_sim/output/*
rm -f /Users/jamie/Documents/particle_sim/videos/*

# compile file
make clean
make --file=Makefile.3D all

# run simulation 
./run3D $x_lower $x_upper $y_lower $y_upper $z_lower $z_upper

# generate animation 
mpirun -np 6 python ./src/visualisation/plotting3D.py \
--fdir="./output" \
--odir="./videos" \
--xl=$x_lower \
--xu=$x_upper \
--yl=$y_lower \
--yu=$y_upper \
--zl=$z_lower \
--zu=$z_upper 
