// main.cpp
#include<vector>
#include<iostream>
#include<numeric>
#include "src/collisions/collisions.h"
#include "src/domain/domain3d.h"
#include "src/simulate.h"

int main(int argc, char *argv[]){
    std::vector<double> xlim{atof(argv[1]), atof(argv[2])}, ylim{atof(argv[3]), atof(argv[4])}, 
    zlim{atof(argv[5]), atof(argv[6])};
    float DT{1e-3};
    float SAVE_INTERVAL{0.5};
    float TMAX{250.0};
    ElasticParticleCollision3D pEngine;
    ElasticBoundaryCollision3D bEngine;
    Domain3D domain(10, xlim, ylim, zlim, pEngine, bEngine);
    domain.initParticles();
    std::cout<<domain._particles.size()<<std::endl;
    simulate3D(domain, TMAX, DT, SAVE_INTERVAL);
    return 0;
}


