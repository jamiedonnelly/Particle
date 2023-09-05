// particle.h
#ifndef PARTICLE2D_H
#define PARTICLE2D_H

#include<vector>
#include<cmath>
#include "particle.h"
#include "../linalg.h"
#include "../utils.h"

class Particle2D : public Particle{
    private:
        double _x, _y; // spatial coordinates
        double _u, _v; // velocity components
        std::vector<double> velocity{};

    public:
        Particle2D(double radius, double mass, double x, double y, double u, double v)
        : Particle(radius, mass), _x(x), _y(y), _u(u), _v(v) {};
        
        // Getter functions
        double x() const { return _x; }
        double y() const { return _y; }
        double u() const { return _u; }
        double v() const { return _v; }
        double area() const { return PI * pow(_radius, 2); }
        double kinetic() const{ return 0.5 * mass() * pow(magnitude(std::vector<double>{_u,_v}),2);}

        // Setter functions
        void set_x(double x) { _x = x; }
        void set_y(double y) { _y = y; }
        void set_u(double u) { _u = u; }
        void set_v(double v) { _v = v; }

        // Update positions
        void update(double dt){
            _x += _u * dt;
            _y += _v * dt;
        }

};

Particle2D init_random_particle2D(std::vector<double> xlim, std::vector<double> ylim, double density);

double particle_radius2D(double mass, double density);

#endif