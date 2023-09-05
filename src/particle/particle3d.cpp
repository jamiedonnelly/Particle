#include "particle3d.h"
#include<cmath>
#include<vector>

Particle3D init_random_particle3D(std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim, double density){
    double x, y, z, u, v, w;
    double mass, radius;
    x = randomvalue(xlim[0], xlim[1]);
    y = randomvalue(ylim[0], ylim[1]);
    z = randomvalue(zlim[0], zlim[1]);
    u = randomvalue(-1*0.05*(xlim[1]-xlim[0]), 0.05*(xlim[1]-xlim[0]));
    v = randomvalue(-1*0.05*(ylim[1]-ylim[0]), 0.05*(ylim[1]-ylim[0]));
    w = randomvalue(-1*0.05*(zlim[1]-zlim[0]), 0.05*(zlim[1]-zlim[0]));
    mass = randomvalue(10, 50);
    radius = particle_radius3D(mass, density);
    return Particle3D(radius, mass, x, y, z, u, v, w);
}

double particle_radius3D(double mass, double density){
    return cbrt(((3/4)*mass)/density);
}