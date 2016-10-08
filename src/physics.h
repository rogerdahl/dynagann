#pragma once

#include <vector>
#include <deque>

#include <Newton.h>

class Pys
{
public:
    Pys();
    ~Pys();
    void addBox();
    void addSphere();
    void addCylinder();
    void addCone();
    void step();
    int getLen();
    glm::mat4 get(int i);
    int getType(int i);
private:
    NewtonWorld* newtonWorld_;
    NewtonCollision* floorCollision_;
    NewtonBody* rigidFloorBox_;

    NewtonCollision* boxCollision_;
    NewtonCollision* sphereCollision_;
    NewtonCollision* cylinderCollision_;
    NewtonCollision* coneCollision_;
    std::deque<NewtonBody*> newtonBodyDeque_;
    int shapeId_;
};
