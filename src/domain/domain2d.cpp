#include "domain2d.h"
#include "../utils.h"
#include<random> 
#include<fstream>
#include<iostream>

void Domain2D::initParticles(){
    static const int max_iter = 500;
    int counter{0};
    while (_particles.size()<N() && counter<max_iter){
        double x = randomvalue(xlim()[0], xlim()[1]);
        double y = randomvalue(ylim()[0], ylim()[1]);
        double u = randomvalue(-1*0.02*(xlim()[1]-xlim()[0]), 0.02*(xlim()[1]-xlim()[0]));
        double v = randomvalue(-1*0.02*(ylim()[1]-ylim()[0]), 0.02*(ylim()[1]-ylim()[0]));
        double mass = randomvalue(100, 1000);
        double radius = randomvalue(0.02, 0.1);
        Particle2D p(radius, mass, x, y, u, v);
        bool hasCollision=false;

        if (bEngine.checkCollision(p, xlim(), ylim())){
                hasCollision = true;
        }
        for (int j=0; j<_particles.size(); j++){
            if (pEngine.checkCollision(p, _particles[j])){
                hasCollision = true;
                break;
            }
        }
        if (!hasCollision){
            _particles.push_back(p);
        }
        counter++;
    }
}

void Domain2D::findPairs(){
    std::vector<std::vector<Particle2D*>> results;
    long int n_particles = _particles.size();
    for (int i=0; i<n_particles; i++){
        for (int j=i+1; j<n_particles; j++){
            std::vector<Particle2D*> pair = {&_particles[i], &_particles[j]};
            results.push_back(pair);
        }
    }
    _pairs = results;
};

void Domain2D::updateParticles(double DT){
    for (auto& ref : _particles){
        ref.update(DT);
    }
};

void Domain2D::logParticles(double time){
    std::string filename = "./output/";
    filename.append(std::to_string(time));
    filename.append(".csv");
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        throw;
    }
    auto ref = particles();
    outFile<<"ke,radius,x,y,u,v"<<std::endl;
    for (int i=0; i<ref.size(); i++){
        outFile << ref[i].kinetic() << ",";
        outFile << ref[i].radius() << ",";
        outFile << ref[i].x() << ","; 
        outFile << ref[i].y() << ",";
        outFile << ref[i].u() << ",";
        outFile << ref[i].v() << std::endl;
    }
    outFile.close();
};