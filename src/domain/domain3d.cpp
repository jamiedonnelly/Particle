#include "domain3d.h"
#include "../utils.h"
#include<random> 
#include<fstream>
#include<iostream>

void Domain3D::initParticles(){
    static const int max_iter = 500;
    int counter{0};
    while (_particles.size()<N() && counter<max_iter){
        double x = randomvalue(xlim()[0], xlim()[1]);
        double y = randomvalue(ylim()[0], ylim()[1]);
        double z = randomvalue(zlim()[0], zlim()[1]);
        double u = randomvalue(-1*0.02*(xlim()[1]-xlim()[0]), 0.02*(xlim()[1]-xlim()[0]));
        double v = randomvalue(-1*0.02*(ylim()[1]-ylim()[0]), 0.02*(ylim()[1]-ylim()[0]));
        double w = randomvalue(-1*0.02*(zlim()[1]-zlim()[0]), 0.02*(zlim()[1]-zlim()[0]));
        double mass = randomvalue(100, 500);
        double radius = randomvalue(0.01, 0.05);
        Particle3D p(radius, mass, x, y, z, u, v, w);
        bool hasCollision=false;
        if (bEngine.checkCollision(p, xlim(), ylim(), zlim())){
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
    return;
}

void Domain3D::findPairs(){
    std::vector<std::vector<Particle3D*>> results;
    long int n_particles = _particles.size();
    for (int i=0; i<n_particles; i++){
        for (int j=i+1; j<n_particles; j++){
            std::vector<Particle3D*> pair = {&_particles[i], &_particles[j]};
            results.push_back(pair);
        }
    }
    _pairs = results;
};

void Domain3D::updateParticles(double DT){
    for (auto& ref : _particles){
        ref.update(DT);
    }
};

void Domain3D::logParticles(double time){
    std::string filename = "./output/";
    filename.append(std::to_string(time));
    filename.append(".csv");
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        throw;
    }
    outFile<<"radius,x,y,z,u,v,w"<<std::endl;
    for (int i=0; i<this->_particles.size(); i++){
        outFile << _particles[i].radius() << ",";
        outFile << _particles[i].x() << ","; 
        outFile << _particles[i].y() << ",";
        outFile << _particles[i].z() << ",";
        outFile << _particles[i].u() << ",";
        outFile << _particles[i].v() << ",";
        outFile << _particles[i].w() << std::endl;
    }
    outFile.close();
};