// simulate.cpp
#include "simulate.h"
#include<iostream>
#include<numeric>


void simulate2D(Domain2D& domain, double TMAX, double DT, const double save_freq){
    std::cout<<"Beginning simulation..."<<std::endl;
    // Convert the save frequency to int
    int save_int = save_freq/DT;
    domain.findPairs();
    auto& pairs = domain._pairs;
    auto& parts = domain._particles;
    int TSTEPS = (int)(TMAX/DT);
    for (int i=0; i<TSTEPS; i++){
        if (i % save_int ==0){
            domain.logParticles(i*DT);
        }
        for (auto& ref : pairs){
            domain.pEngine.fit(*ref[0], *ref[1]);
        }
        for (auto& ref : parts){
            domain.bEngine.fit(ref, domain.xlim(), domain.ylim());
        }
        domain.updateParticles(DT); // This should be outside the inner loop.
    }
    std::cout<<"Simulation completed..."<<std::endl;
};

void simulate3D(Domain3D& domain, double TMAX, double DT, const double save_freq){
    std::cout<<"Beginning simulation..."<<std::endl;
    // Convert the save frequency to int
    int save_int = save_freq/DT;
    domain.findPairs();
    auto& pairs = domain._pairs;
    auto& parts = domain._particles;
    int TSTEPS = (int)(TMAX/DT);
    for (int i=0; i<TSTEPS; i++){
        if (i % save_int ==0){
            domain.logParticles(i*DT);
        }
        for (auto& ref : pairs){
            domain.pEngine.fit(*ref[0], *ref[1]);
        }
        for (auto& ref : parts){
            domain.bEngine.fit(ref, domain.xlim(), domain.ylim(), domain.zlim());
        }
        domain.updateParticles(DT); // This should be outside the inner loop.
    }
    std::cout<<"Simulation completed..."<<std::endl;
};



