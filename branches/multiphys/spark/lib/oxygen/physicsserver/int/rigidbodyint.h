/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: space.h 102 2009-11-18 07:24:29Z a-held $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef OXYGEN_RIGIDBODYINT_H
#define OXYGEN_RIGIDBODYINT_H

#include <oxygen/oxygen_defines.h>
#include <oxygen/physicsserver/ode/odebody.h>
#include <iostream>

namespace oxygen
{

class OXYGEN_API RigidBodyInt
{

public:
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual bool IsEnabled() const = 0;
    virtual void UseGravity(bool f) = 0;
    virtual bool UsesGravity() const = 0;
    virtual void CreateBody(long world) = 0;
    virtual void SetMass(float mass) = 0;
    virtual void SetMassParameters(const float& mass) = 0;
    virtual float GetMass() const = 0;
    virtual void SetSphere(float density, float radius) = 0;
    virtual void AddSphere(float density, float radius, const salt::Matrix& matrix) = 0;
    virtual void SetSphereTotal(float total_mass, float radius) = 0;
    virtual void AddSphereTotal(float total_mass, float radius, const salt::Matrix& matrix) = 0;
    virtual void SetBox(float density, const salt::Vector3f& size) = 0;
    virtual void AddBox(float density, const salt::Vector3f& size, const salt::Matrix& matrix) = 0;
    virtual void SetBoxTotal(float total_mass, const salt::Vector3f& size) = 0;
    virtual void AddBoxTotal(float total_mass, const salt::Vector3f& size, const salt::Matrix& matrix) = 0;
    virtual void SetCylinder(float density, float radius, float length) = 0;
    virtual void AddCylinder(float density, float radius, float length, const salt::Matrix& matrix) = 0;
    virtual void SetCylinderTotal(float total_mass, float radius, float length) = 0;
    virtual void AddCylinderTotal(float total_mass, float radius, float length, const salt::Matrix& matrix) = 0;
    virtual void SetCapsule(float density, float radius, float length) = 0;
    virtual void AddCapsule(float density, float radius, float length, const salt::Matrix& matrix) = 0;
    virtual void SetCapsuleTotal(float total_mass, float radius, float length) = 0;
    virtual void AddCapsuleTotal(float total_mass, float radius, float length, const salt::Matrix& matrix) = 0;
    virtual void TranslateMass(const salt::Vector3f& v) = 0;
    virtual salt::Vector3f GetVelocity() const = 0;
    virtual void SetVelocity(const salt::Vector3f& vel) = 0;
    virtual void SetRotation(const salt::Matrix& rot) = 0;
    virtual salt::Matrix GetRotation() const = 0;
    virtual salt::Vector3f GetAngularVelocity() const = 0;
    virtual void SetAngularVelocity(const salt::Vector3f& vel) = 0;
    virtual void AddForce(const salt::Vector3f& force) = 0;
    virtual void AddTorque(const salt::Vector3f& torque) = 0;
    virtual void SetPosition(const salt::Vector3f& pos) = 0;
    virtual salt::Vector3f GetPosition() const = 0;
    virtual void DestroyPhysicsObject() = 0;
    virtual salt::Matrix GetSynchronisationMatrix() = 0;
    virtual void BodySetData(RigidBody* rb) = 0;
    virtual RigidBody* BodyGetData(long bodyID) = 0;
    
    virtual long GetBodyID() = 0;
    virtual salt::Vector3f GetMassTrans() = 0;
    virtual void SetMassTrans(salt::Vector3f massTrans) = 0; 
    virtual bool GetMassTransformed() = 0;
    virtual void SetMassTransformed(bool f) = 0;
    
    // Here, we have to cheat with the preprocessor, since a static method
    // is required, and the bridge pattern requires member variables to
    // be used (so we cannot use the bridge pattern)            
    static RigidBody* GetBodyPointer(long bodyID){
        #ifdef OXYGEN_ODEWRAPPER_H
        return static_cast<RigidBody*>(dBodyGetData( (dBodyID) bodyID));
        #endif
    }
    
protected:
    /** The ID of the managed body. This must be unique within the simulation.
        It is used externally to reference this partcular body.
    */
    long mBodyID;
    
    salt::Vector3f mMassTrans;
    bool mMassTransformed;
};

} //namespace oxygen

#endif //OXYGEN_RIGIDBODYINT_H