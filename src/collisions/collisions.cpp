// Collisions.cpp
#include<iostream>
#include<vector>
#include<cmath>
#include "collisions.h"
#include "../utils.h"
#include "../linalg.h"

static const double epsilon{1e-7};

bool ElasticParticleCollision2D::checkCollision(Particle2D& p1, Particle2D& p2) const{
    double dist = magnitude(std::vector<double>{(p2.x()-p1.x()), (p2.y()-p1.y())});
    if (dist <= p1.radius() + p2.radius()){
        return true;
    }
    return false;
};

void ElasticParticleCollision2D::fit(Particle2D& p1, Particle2D&p2){
    bool collision = checkCollision(p1, p2);
    if (!collision){
        return;
    }
    std::vector<double> normal = vectorNormal(std::vector<double>{p1.x(), p1.y()}, std::vector<double>{p2.x(), p2.y()});
    std::vector<double> velocityRel = BinaryVectorSub(std::vector<double>{p1.u(), p1.v()}, std::vector<double>{p2.u(), p2.v()});
    std::vector<double> velNorm = UnaryVectorScaling(normal, innerProduct(velocityRel, normal));
    std::vector<double> newV1 = BinaryVectorSub(std::vector<double>{p1.u(), p1.v()}, UnaryVectorAdd(velNorm, 2*p2.mass()/(p2.mass()+p1.mass())));
    std::vector<double> newV2 = BinaryVectorAdd(std::vector<double>{p2.u(), p2.v()}, UnaryVectorAdd(velNorm, 2*p1.mass()/(p2.mass()+p1.mass())));
    p1.set_u(newV1[0]);
    p1.set_v(newV1[1]);
    p2.set_u(newV2[0]);
    p2.set_v(newV2[1]);
}

bool ElasticParticleCollision3D::checkCollision(Particle3D& p1, Particle3D& p2) const{
    double dist = magnitude(std::vector<double>{(p2.x()-p1.x()), (p2.y()-p1.y()), (p2.z()-p1.z())});
    if (dist <= p1.radius() + p2.radius()){
        return true;
    }
    return false;
};

void ElasticParticleCollision3D::fit(Particle3D& p1, Particle3D&p2){
    bool collision = checkCollision(p1, p2);
    if (!collision){
        return;
    }
    std::vector<double> normal = vectorNormal(std::vector<double>{p1.x(), p1.y(), p1.z()}, std::vector<double>{p2.x(), p2.y(), p2.z()});
    std::vector<double> velocityRel = BinaryVectorSub(std::vector<double>{p1.u(), p1.v(), p1.w()}, std::vector<double>{p2.u(), p2.v(), p2.w()});
    std::vector<double> velNorm = UnaryVectorScaling(normal, innerProduct(velocityRel, normal));
    std::vector<double> newV1 = BinaryVectorSub(std::vector<double>{p1.u(), p1.v(), p1.w()}, UnaryVectorScaling(velNorm, 2*p2.mass()/(p2.mass()+p1.mass())));
    std::vector<double> newV2 = BinaryVectorAdd(std::vector<double>{p2.u(), p2.v(), p2.w()}, UnaryVectorScaling(velNorm, 2*p1.mass()/(p2.mass()+p1.mass())));
    p1.set_u(newV1[0]);
    p1.set_v(newV1[1]);
    p1.set_w(newV1[2]);
    p2.set_u(newV2[0]);
    p2.set_v(newV2[1]);
    p2.set_w(newV2[2]);
}

Boundaries2D ElasticBoundaryCollision2D::collisionType(Particle2D& p, std::vector<double> xlim, std::vector<double> ylim) const{
    double upper_dist, lower_dist, left_dist, right_dist;
    upper_dist = abs(ylim[1]-p.y());
    lower_dist = abs(p.y()-ylim[0]);
    left_dist = abs(p.x()-xlim[0]);
    right_dist = abs(xlim[1]-p.x());
    if (upper_dist<=p.radius() || lower_dist<=p.radius()){
        return Boundaries2D::Vertical;
    }
    if (left_dist<=p.radius() || right_dist<=p.radius()){
        return Boundaries2D::Horizontal;
    }
    else{
        return Boundaries2D::NoCollision;
    }
};

bool ElasticBoundaryCollision2D::checkCollision(Particle2D& p, std::vector<double> xlim, std::vector<double> ylim) const{
    Boundaries2D type = collisionType(p, xlim, ylim);
    if (type==Boundaries2D::NoCollision){
        return false;
    }
    return true;
};

void ElasticBoundaryCollision2D::velocityUpdate(Particle2D& p, Boundaries2D boundary){
    switch(boundary){
        case Boundaries2D::NoCollision:
            break;
        case Boundaries2D::Horizontal:
            p.set_u(-1*p.u());
            break;
        case Boundaries2D::Vertical:
            p.set_v(-1*p.v());
            break;
    }
    return;
}

void ElasticBoundaryCollision2D::fit(Particle2D& p, std::vector<double> xlim, std::vector<double> ylim){
    Boundaries2D collision = collisionType(p, xlim, ylim);
    velocityUpdate(p, collision);
    return;
};

Boundaries3D ElasticBoundaryCollision3D::collisionType(Particle3D& p, std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim) const{
    bool xCollision = (abs(xlim[0] - p.x()) <= p.radius()) || (abs(p.x() - xlim[1]) <= p.radius());
    bool yCollision = (abs(ylim[0] - p.y()) <= p.radius()) || (abs(p.y() - ylim[1]) <= p.radius());
    bool zCollision = (abs(zlim[0] - p.z()) <= p.radius()) || (abs(p.z() - zlim[1]) <= p.radius());

    if (xCollision && yCollision && zCollision) {
        return Boundaries3D::xyzDirection;
    } else if (xCollision && yCollision) {
        return Boundaries3D::xyDirection;
    } else if (xCollision && zCollision) {
        return Boundaries3D::xzDirection;
    } else if (yCollision && zCollision) {
        return Boundaries3D::yzDirection;
    } else if (xCollision) {
        return Boundaries3D::xDirection;
    } else if (yCollision) {
        return Boundaries3D::yDirection;
    } else if (zCollision) {
        return Boundaries3D::zDirection;
    } else {
        return Boundaries3D::NoCollision;
    }
}

bool ElasticBoundaryCollision3D::checkCollision(Particle3D& p, std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim) const{
    Boundaries3D type = collisionType(p, xlim, ylim, zlim);
    if (type==Boundaries3D::NoCollision){
        return false;
    }
    return true;
};

void ElasticBoundaryCollision3D::velocityUpdate(Particle3D& p, Boundaries3D boundary){
    switch(boundary){
        case Boundaries3D::NoCollision:
            break;
        case Boundaries3D::xDirection:
            p.set_u(-1*p.u());
            break;
        case Boundaries3D::yDirection:
            p.set_v(-1*p.v());
            break;
        case Boundaries3D::zDirection:
            p.set_w(-1*p.w());
            break;
        case Boundaries3D::xyzDirection:
            p.set_u(-1*p.u());
            p.set_v(-1*p.v());
            p.set_w(-1*p.w());
            break;
        case Boundaries3D::xyDirection:
            p.set_u(-1*p.u());
            p.set_v(-1*p.v());
            break;
        case Boundaries3D::xzDirection:
            p.set_u(-1*p.u());
            p.set_w(-1*p.w());
            break;
        case Boundaries3D::yzDirection:
            p.set_v(-1*p.v());
            p.set_w(-1*p.w());
            break;
    }
    return;
}

void ElasticBoundaryCollision3D::fit(Particle3D& p, std::vector<double> xlim, std::vector<double> ylim, std::vector<double> zlim){
    Boundaries3D collision = collisionType(p, xlim, ylim, zlim);
    velocityUpdate(p, collision);
    return;
};