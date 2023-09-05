//domain2d.h

#ifndef DOMAIN2D_H
#define DOMAIN2D_H

#include "../particle/particle2d.h"
#include "../collisions/collisions.h"

class Domain2D{
    private:
        int _N;
        std::vector<double> _xlim, _ylim;
        
    public:
        // Constructor 
        Domain2D(int N, std::vector<double> xlim, std::vector<double> ylim, ElasticParticleCollision2D& pEngine, ElasticBoundaryCollision2D& bEngine) 
        : _N(N), _xlim(xlim), _ylim(ylim), pEngine(pEngine), bEngine(bEngine) {};

        // Collision engines
        ElasticParticleCollision2D pEngine;
        ElasticBoundaryCollision2D bEngine;

        // particles
        std::vector<Particle2D> _particles{};
        std::vector<std::vector<Particle2D*>> _pairs;

        // Functional 
        void addParticle(Particle2D particle) { _particles.push_back(particle);};
        void updateParticles(double DT);
        void logParticles(double time);
        void initParticles();
        void findPairs();
        
        // Getters
        int N() const{ return _N; }
        std::vector<double> xlim() const{ return _xlim;}
        std::vector<double> ylim() const{ return _ylim;}
        std::vector<Particle2D> particles() const{ return _particles;}
        std::vector<std::vector<Particle2D*>> pairs() const { return _pairs; }


        // Setters
        void set_xlim(std::vector<double> xlim){ _xlim = xlim;}
        void set_ylim(std::vector<double> ylim){ _ylim = ylim;}
        void initParticles(std::vector<Particle2D> particles){ _particles = particles;}
};

#endif
