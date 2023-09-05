#include "particle2d.h"
#include "../utils.h"
#include<cmath>
#include<vector>

double particle_radius2D(double mass, double density){
    return sqrt(mass / (density * M_PI));
}

Particle2D init_random_particle2D(std::vector<double> xlim, std::vector<double> ylim, double density){
    double x, y, u, v;
    double mass, radius;
    x = randomvalue(xlim[0], xlim[1]);
    y = randomvalue(ylim[0], ylim[1]);
    u = randomvalue(-1*0.05*(xlim[1]-xlim[0]), 0.05*(xlim[1]-xlim[0]));
    v = randomvalue(-1*0.05*(ylim[1]-ylim[0]), 0.05*(ylim[1]-ylim[0]));
    mass = randomvalue(10, 50);
    radius = particle_radius2D(mass, density);
    return Particle2D(radius, mass, x, y, u, v);
}