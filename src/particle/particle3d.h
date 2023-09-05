#ifndef PARTICLE3D_H
#define PARTICLE3D_H

#include<vector>
#include<cmath>
#include "particle.h"
#include "../linalg.h"
#include "../utils.h"


class Particle3D : public Particle{
    private: 
        double _x, _y, _z;
        double _u, _v, _w;

    public:
        Particle3D(double radius, double mass, double x, double y, double z, double u, double v, double w) :
        Particle(radius, mass), _x(x), _y(y), _z(z), _u(u), _v(v), _w(w){};

        // Getter functions
        double x() const { return _x; }
        double y() const { return _y; }
        double z() const { return _z; }
        double u() const { return _u; }
        double v() const { return _v; }
        double w() const { return _w; }
        double volume() const { return (4/3.0) * PI * pow(_radius,3); }
        double kinetic() const{ return 0.5 * mass() * pow(magnitude(std::vector<double>{_u,_v,_w}),2);}

        // Setter functions
        void set_x(double x) { _x = x; }
        void set_y(double y) { _y = y; }
        void set_z(double z) { _z = z; }
        void set_u(double u) { _u = u; }
        void set_v(double v) { _v = v; }
        void set_w(double w) { _w = w; }

        // Update positions
        void update(double dt){
            _x += _u * dt;
            _y += _v * dt;
            _z += _w * dt;
        }
};

Particle3D init_random_particle3D(std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim, double density);

double particle_radius3D(double mass, double density);

#endif