#!/bin/bash 

export x_lower=$1 
export x_upper=$2
export y_lower=$3
export y_upper=$4

source /opt/homebrew/Caskroom/miniforge/base/etc/profile.d/conda.sh
conda activate network

# clear the output directory of current outputs
rm -f /Users/jamie/Documents/particle_sim/output/*

# compile file
make clean
make --file=Makefile.2D all

# run simulation 
./run2D $x_lower $x_upper $y_lower $y_upper

# generate animation 
python ./src/visualisation/plotting2D.py \
--fdir="./output" \
--output="./animation.mp4" \
--xl=$x_lower \
--xu=$x_upper \
--yl=$y_lower \
--yu=$y_upper \