# Particle
This project outlines a rudimentary particle simulation. Simulating a collection of randomly initialised particles on a bounded domain colliding and transferring energy through elastic collisions. 

The source code is written in C++ primarily outlined in `./src/` with some visualisation code outlined in python in `./src/visualisation`. The visualisation involves rendering lots of frames through matplotlib and animating them into `.mp4` files. The visualisation has been accelerated with an MPI backend, with usage outlined in `plotting3D.py`. 

Example usage is shown in `sim2D.sh` and `sim3D.sh` for 2 and 3D simulations respectively. 

Upcoming additions:
  - More forces such as gravitational interactions.
  - MPI backend for the C++ code; using domain decomposition to accelerate computation to larger domains.
  - Currently the code is heavily bottlenecked by the Python rendering; distributed rendering has lead to near-linear speedups but need to resolve this. 

