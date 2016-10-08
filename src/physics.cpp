#include <algorithm>
#include <cstdlib>
#include <iostream>

#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cppformat/format.h>

#include "physics.h"

using namespace std;

//#pragma warning (disable: 4100) //unreferenced formal parameter
//#pragma warning (disable: 4702) //unreachable code

void applyForceAndTorque(const NewtonBody* const body, dFloat timestep, int threadIndex)
{
//    auto n = static_cast<int>(reinterpret_cast<intptr_t>(NewtonBodyGetUserData(body)));
//    fmt::print("applyForceAndTorque: {}\n", n);

    float gravity = -9.8f;
    float mass, ix, iy, iz;
    NewtonBodyGetMassMatrix(body, &mass, &ix, &iy, &iz);
    float force[4] = { 0.0f, gravity * mass, 0.0f, 1.0f };
    NewtonBodySetForce(body, force);
}

void setObjectTransformCallback(const NewtonBody* body, const float* matrix, int)
{
//    auto n = static_cast<int>(reinterpret_cast<intptr_t>(NewtonBodyGetUserData(body)));
//    fmt::print("setObjectTransformCallback: {}\n", n);

//    glm::mat4 newMatrix;
//    NewtonBodyGetMatrix(newtonBodyDeque_[0], glm::value_ptr(newMatrix));
////    newMatrix = glm::rotate(newMatrix, 0.25f, glm::vec3(0, 0, 1));
//    newMatrix = glm::transpose(newMatrix);
//    NewtonBodySetMatrix(newtonBodyDeque_[0], glm::value_ptr(newMatrix));
}

Pys::Pys()
: shapeId_(0)
{
    newtonWorld_ = NewtonCreate();
    NewtonSetSolverModel(newtonWorld_, 1);
    NewtonSetThreadsCount(newtonWorld_, 8);

// auto boxMatrix = glm::mat4();
// boxMatrix = glm::translate(boxMatrix, glm::vec3(0.0f, -0.5f, 0.0f));
// collision_ = NewtonCreateBox(newtonWorld_, 10, 10, 10, shapeId, glm::value_ptr(boxMatrix));
    // floor

    auto floorModelMatrix = glm::mat4();
//    floorModelMatrix = glm::rotate(floorModelMatrix, 0.25f, glm::vec3(0, 0, 1));
    floorModelMatrix = glm::translate(floorModelMatrix, glm::vec3(0.0f, -10 / 2.0 - 0.5, 0.0f));
//    floorModelMatrix = glm::translate(floorModelMatrix, glm::vec3(0.0f, -5.5f, 0.0f)); // fits with edges on 10, 10, 10 floor

//    floorModelMatrix = glm::scale(floorModelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
//    floorCollision_ = NewtonCreateBox(newtonWorld_, 1, 1, 1, shapeId_, glm::value_ptr(floorModelMatrix));
    floorCollision_ = NewtonCreateBox(newtonWorld_, 10, 10, 10, shapeId_++, NULL);
    rigidFloorBox_ = NewtonCreateDynamicBody(newtonWorld_, floorCollision_, glm::value_ptr(floorModelMatrix));

    // When Newton creates a rigid body, the mass is set to infinity, making the body static. We need to tell Newton we
    // want this body to be dynamic. This is done by calling this piece of code :
//    NewtonBodySetMassMatrix(rigidFloorBox_, 1000, 1, 1, 1);
//    NewtonBodySetForceAndTorqueCallback(rigidFloorBox_, applyForceAndTorque);
//    NewtonBodySetTransformCallback(rigidFloorBox_, setObjectTransformCallback);
    NewtonBodySetUserData(rigidFloorBox_, (void*)100);

    boxCollision_ = NewtonCreateBox(newtonWorld_, 1, 1, 1, shapeId_++, NULL);
    sphereCollision_ = NewtonCreateSphere(newtonWorld_, 0.5f, shapeId_++, NULL);
    cylinderCollision_ = NewtonCreateCylinder(newtonWorld_, 0.5f, 0.5f, shapeId_++, NULL);
    coneCollision_ = NewtonCreateCone(newtonWorld_, 0.5f, 2.0f, shapeId_++, NULL);
}

void Pys::addBox()
{
    static float rot = 0.0f;
    rot += .1f;
    
    auto boxModelMatrix = glm::mat4();
    boxModelMatrix = glm::translate(boxModelMatrix, glm::vec3(0.0f, 7.0f, 0.0f));
    boxModelMatrix = glm::rotate(boxModelMatrix, rot, glm::vec3(0.5, 0.1, 1));
    boxModelMatrix = glm::scale(boxModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));

    NewtonBody* rigidBodyBox = NewtonCreateDynamicBody(newtonWorld_, boxCollision_, glm::value_ptr(boxModelMatrix));
    NewtonBodySetForceAndTorqueCallback(rigidBodyBox, applyForceAndTorque);
    NewtonBodySetMassMatrix(rigidBodyBox, 10, 1, 1, 1);
    NewtonBodySetUserData(rigidBodyBox, (void*)0);

    newtonBodyDeque_.push_back(rigidBodyBox);
}

void Pys::addSphere()
{
    auto sphereModelMatrix = glm::mat4();
//    sphereModelMatrix = glm::scale(sphereModelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
    sphereModelMatrix = glm::translate(sphereModelMatrix, glm::vec3(0.0f, 7.0f, 0.0f));

    NewtonBody* rigidBodySphere = NewtonCreateDynamicBody(newtonWorld_, sphereCollision_, glm::value_ptr(sphereModelMatrix));
    NewtonBodySetForceAndTorqueCallback(rigidBodySphere, applyForceAndTorque);
    NewtonBodySetMassMatrix(rigidBodySphere, 20, 1, 1, 1);
    NewtonBodySetUserData(rigidBodySphere, (void*)1);
    
    newtonBodyDeque_.push_back(rigidBodySphere);
}

void Pys::addCylinder()
{
    auto cylinderModelMatrix = glm::mat4();
//    cylinderModelMatrix = glm::scale(cylinderModelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
    cylinderModelMatrix = glm::translate(cylinderModelMatrix, glm::vec3(0.0f, 7.0f, 0.0f));

    NewtonBody* rigidBodyCylinder = NewtonCreateDynamicBody(newtonWorld_, cylinderCollision_, glm::value_ptr(cylinderModelMatrix));
    NewtonBodySetForceAndTorqueCallback(rigidBodyCylinder, applyForceAndTorque);
    NewtonBodySetMassMatrix(rigidBodyCylinder, 20, 1, 1, 1);
    NewtonBodySetUserData(rigidBodyCylinder, (void*)2);

    newtonBodyDeque_.push_back(rigidBodyCylinder);
}

void Pys::addCone()
{
    static float rot = 0.0f;
    rot += .1f;

    auto coneModelMatrix = glm::mat4();
//    coneModelMatrix = glm::scale(coneModelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
    coneModelMatrix = glm::translate(coneModelMatrix, glm::vec3(0.0f, 7.0f, 0.0f));
    coneModelMatrix = glm::rotate(coneModelMatrix, rot, glm::vec3(0.5, 0.1, 1));

    NewtonBody* rigidBodyCone = NewtonCreateDynamicBody(newtonWorld_, coneCollision_, glm::value_ptr(coneModelMatrix));
    NewtonBodySetForceAndTorqueCallback(rigidBodyCone, applyForceAndTorque);
    NewtonBodySetMassMatrix(rigidBodyCone, 20, 1, 1, 1);
    // The center of mass of a cone is a quarter of the way from the base to the tip.
    const float coneCenterOfMassOffsetArr[] = {-0.5, 0, 0};
	NewtonBodySetCentreOfMass(rigidBodyCone, coneCenterOfMassOffsetArr);
    NewtonBodySetUserData(rigidBodyCone, (void*)3);

    newtonBodyDeque_.push_back(rigidBodyCone);
}

Pys::~Pys()
{
    NewtonDestroyAllBodies(newtonWorld_);
    NewtonDestroyCollision(floorCollision_);
    NewtonDestroyCollision(boxCollision_);
    NewtonDestroy(newtonWorld_);
}

void Pys::step()
{
    float elapsedSec = 1.0f / 60.0f;
    NewtonUpdate(newtonWorld_, elapsedSec);

    // Prune the bodies that fell off the floor.
    for (auto it = newtonBodyDeque_.begin(); it != newtonBodyDeque_.end();) {
        glm::mat4 m;
        NewtonBodyGetMatrix(*it, glm::value_ptr(m));
        if (m[3][1] < -20.0f) {
            NewtonDestroyBody(*it);
            it = newtonBodyDeque_.erase(it);
        }
        else {
            ++it;
        }
    }
}

int Pys::getLen()
{
    return newtonBodyDeque_.size();
}

glm::mat4 Pys::get(int i)
{
    glm::mat4 newMatrix;
    NewtonBodyGetMatrix(newtonBodyDeque_[i],  glm::value_ptr(newMatrix));
    return newMatrix;
}

int Pys::getType(int i)
{
    return static_cast<int>(reinterpret_cast<intptr_t>(NewtonBodyGetUserData(newtonBodyDeque_[i])));
}
