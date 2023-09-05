// main.cpp
#include<vector>
#include<iostream>
#include<numeric>
#include "src/collisions/collisions.h"
#include "src/domain/domain2d.h"
#include "src/simulate.h"

int main(int argc, char *argv[]){
    std::vector<double> xlim{atof(argv[1]), atof(argv[2])}, ylim{atof(argv[3]), atof(argv[4])};
    float DT{1e-3};
    float SAVE_INTERVAL{0.5};
    float TMAX{250.0};
    ElasticParticleCollision2D pEngine;
    ElasticBoundaryCollision2D bEngine;
    Domain2D domain(20, xlim, ylim, pEngine, bEngine);
    domain.initParticles();
    simulate2D(domain, TMAX, DT, SAVE_INTERVAL);
    return 0;
}


