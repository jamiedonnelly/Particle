// collisions.h
#ifndef COLLISION_H
#define COLLISION_H

#include<vector>
#include "../particle/particle2d.h"
#include "../particle/particle3d.h"

enum class Boundaries2D{
    NoCollision, // no modification
    Horizontal, // -x direction
    Vertical, // -y direction
};

enum class Boundaries3D{
    NoCollision,
    xDirection,
    yDirection,
    zDirection,
    xyDirection,
    yzDirection,
    xzDirection,
    xyzDirection
};

class ElasticParticleCollision2D{    
    public:
        bool checkCollision(Particle2D& p1, Particle2D& p2) const;
        void fit(Particle2D& p1, Particle2D& p2);      
};

class ElasticParticleCollision3D{
    public:
        bool checkCollision(Particle3D& p1, Particle3D& p2) const;
        void fit(Particle3D& p1, Particle3D& p2);
};

class ElasticBoundaryCollision2D{
    private: 
       void velocityUpdate(Particle2D& p, Boundaries2D boundary);
       Boundaries2D collisionType(Particle2D& p, std::vector<double> xlim, std::vector<double> ylim) const;
    public: 
        bool checkCollision(Particle2D& p, std::vector<double> xlim, std::vector<double> ylim) const;
        void fit(Particle2D& p, std::vector<double> xlim, std::vector<double> ylim);      
};

class ElasticBoundaryCollision3D{
    private: 
       void velocityUpdate(Particle3D& p, Boundaries3D boundary);
       Boundaries3D collisionType(Particle3D& p, std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim) const;
    public: 
        bool checkCollision(Particle3D& p, std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim) const;
        void fit(Particle3D& p, std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim);      
};

#endif
