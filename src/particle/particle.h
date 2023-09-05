#ifndef PARTICLE_H
#define PARTICLE_H

static const double PI = 3.14159265358979323846;

class Particle{
    protected:
        double _mass;
        double _radius;
        double _density;

    public:
        Particle(double radius, double mass) : _mass(mass), _radius(radius) {};
        // Getter functions
        double radius() const { return _radius; }
        double mass() const { return _mass; }
};

#endif