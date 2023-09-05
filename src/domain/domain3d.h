//domain3d.h

#ifndef DOMAIN3D_H
#define DOMAIN3D_H

#include "../particle/particle3d.h" 
#include "../collisions/collisions.h"
#include<vector>

class Domain3D{
    private:
        int _N;
        std::vector<double> _xlim, _ylim, _zlim;

    public:
        // Constructor
        Domain3D(int N, std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim, ElasticParticleCollision3D& pEngine, ElasticBoundaryCollision3D& bEngine) : 
        _N(N), _xlim(xlim), _ylim(ylim), _zlim(zlim), pEngine(pEngine), bEngine(bEngine) {};

        // Collision engines
        ElasticParticleCollision3D pEngine;
        ElasticBoundaryCollision3D bEngine;

        // particles
        std::vector<Particle3D> _particles{};
        std::vector<std::vector<Particle3D*>> _pairs;

        // Functional 
        void addParticle(Particle3D particle) { _particles.push_back(particle);}
        void updateParticles(double DT);
        void logParticles(double time);
        void initParticles();
        void findPairs();
        
        // Getters
        int N() const{ return _N; }
        std::vector<double> xlim() const{ return _xlim;}
        std::vector<double> ylim() const{ return _ylim;}
        std::vector<double> zlim() const{ return _zlim;}
        std::vector<Particle3D> particles() const{ return _particles;}

        // Setters
        void set_xlim(std::vector<double> xlim){ _xlim = xlim;}
        void set_ylim(std::vector<double> ylim){ _ylim = ylim;}
        void set_zlim(std::vector<double> zlim){ _zlim = zlim;}
        void initParticles(std::vector<Particle3D> particles){ _particles = particles;}
};


#endif