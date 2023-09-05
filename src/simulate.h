#ifndef SIMULATE_H
#define SIMULATE_H

#include "particle/particle2d.h"
#include "domain/domain2d.h"
#include "domain/domain3d.h"
#include "collisions/collisions.h"
#include<cmath>
#include<vector>

void simulate2D(Domain2D& domain, double TMAX, double DT, double save_freq);

void simulate3D(Domain3D& domain, double TMAX, double DT, double save_freq);

#endif