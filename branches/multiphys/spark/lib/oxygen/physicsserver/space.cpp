/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id$

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

#include <oxygen/physicsserver/space.h>
#include <oxygen/physicsserver/ode/odespace.h>
#include <oxygen/physicsserver/collider.h>
#include <oxygen/physicsserver/world.h>
#include <oxygen/sceneserver/scene.h>
#include <zeitgeist/logserver/logserver.h>

using namespace boost;
using namespace oxygen;

/** set of spaces with disabled inner collision */
Space::TSpaceIdSet Space::gDisabledInnerCollisionSet;

void Space::collisionNearCallback (void *data, dGeomID obj1, dGeomID obj2)
{
    Space *space = (Space*)data;
    space->HandleCollide((long) obj1, (long) obj2);
}

Space::Space() : PhysicsObject(), mODESpace(0)
{
    mSpaceImp = shared_ptr<ODESpace>(new ODESpace());
}

Space::~Space()
{
}

long Space::GetSpaceID() const
{
    return mSpaceImp->GetSpaceID();
}

dJointGroupID Space::GetODEJointGroup() const
{
    return mSpaceImp->GetODEJointGroup();
}

void Space::Collide()
{
    // bind collision callback function to this object
    Collide(mODESpace);
}

void Space::Collide(dSpaceID space)
{
    if (gDisabledInnerCollisionSet.find(space) == gDisabledInnerCollisionSet.end())
    {
        dSpaceCollide(space, this, collisionNearCallback);
    }
}

void Space::HandleSpaceCollide(dGeomID obj1, dGeomID obj2)
{
   // collide all geoms internal to the space(s)
    dSpaceCollide2 (obj1,obj2,this,&collisionNearCallback);
    
    //mSpaceImp->HandleSpaceCollide(obj1, obj2);

    if (dGeomIsSpace (obj1))
        {
            Collide((dSpaceID)obj1);
        }

    if (dGeomIsSpace (obj2))
        {
            Collide((dSpaceID)obj2);
        }
}

void Space::HandleCollide(long obj1, long obj2)
{
    //mSpaceImp->HandleCollide(obj1, obj2);
    
    dGeomID geom1 = (dGeomID) obj1;
    dGeomID geom2 = (dGeomID) obj2; 
  
    if (
        (dGeomIsSpace (geom1)) ||
        (dGeomIsSpace (geom2))
        )
        {
            // colliding a space with something
            HandleSpaceCollide(geom1, geom2);
            return;
        }

    // colliding two non-space geoms; reject collisions
    // between bodies that are connected with joints
    const dBodyID b1 = dGeomGetBody(geom1);
    const dBodyID b2 = dGeomGetBody(geom2);

    if (
        (b1) && (b2) &&
        (dAreConnectedExcluding(b1,b2,dJointTypeContact))
        )
        {
            return;
        }

    // if obj1 and obj2 are in a space that disabled inner collision,
    // reject the collision
    const dSpaceID s1 = dGeomGetSpace(geom1);
    const dSpaceID s2 = dGeomGetSpace(geom2);

    // get shared pointers to the two corresponding Collider nodes first
    shared_ptr<Collider> collider = Collider::GetCollider(obj1);
    shared_ptr<Collider> collidee = Collider::GetCollider(obj2);

    if (
        (collider.get() == 0) ||
        (collidee.get() == 0)
        )
      {
        return;
      }

    if (s1 == s2)
    {
        const oxygen::Collider::TColliderNameSet & collider_set = collider->GetNotCollideWithSet();
        const oxygen::Collider::TColliderNameSet & collidee_set = collidee->GetNotCollideWithSet();
        if (
            (collider_set.find(collidee->GetName()) != collider_set.end()) ||
            (collidee_set.find(collider->GetName()) != collidee_set.end())
            )
            {
                return;
            }
    }

    // dSpaceCollide(), is guaranteed to pass all potentially
    // intersecting geom pairs to the callback function, but depending
    // on the internal algorithms used by the space it may also make
    // mistakes and pass non-intersecting pairs. Thus we can not
    // expect that dCollide() will return contacts for every pair
    // passed to the callback.
    static const int nContacts = 4;
    static dContact contacts[nContacts];

    int n = dCollide (geom1, geom2, nContacts,
                      &contacts[0].geom, sizeof(dContact));

    if (n == 0)
    {
        return;
    }


    for (int i=0;i<n;++i)
        {
            // notify the collider nodes
            collider->OnCollision(collidee,contacts[i],Collider::CT_DIRECT);
            collidee->OnCollision(collider,contacts[i],Collider::CT_SYMMETRIC);
        }
}

void Space::OnUnlink()
{
    mSpaceImp->DisableInnerCollision(false);
    PhysicsObject::OnUnlink();
}

void Space::OnLink()
{
    PhysicsObject::OnLink();

    shared_ptr<Space> space = GetSpace();
    long spaceID = 0;

    if (space.get() != 0)
        {
            spaceID = space->GetSpaceID();
        }

    mODESpace = dHashSpaceCreate((dSpaceID) spaceID);
    
    shared_ptr<ODESpace> odespace = shared_static_cast<ODESpace>(mSpaceImp);
    odespace->mODESpace = mODESpace;
}

long Space::GetParentSpaceID()
{
    return mSpaceImp->GetParentSpaceID();
}

bool Space::IsGlobalSpace()
{
    return mSpaceImp->IsGlobalSpace();
}

bool Space::ConstructInternal()
{
    return mSpaceImp->ConstructInternal();
}

void Space::PostPhysicsUpdateInternal()
{
    mSpaceImp->PostPhysicsUpdateInternal();
}

void Space::DestroySpaceObjects()
{
    mSpaceImp->scene = GetScene();
    
    mSpaceImp->DestroySpaceObjects();
}

void Space::DestroyPhysicsObject()
{
    mSpaceImp->DestroyPhysicsObject();
}

void Space::DisableInnerCollision(bool disable)
{
    mSpaceImp->DisableInnerCollision(disable);
}

bool Space::GetDisableInnerCollision() const
{
    return mSpaceImp->GetDisableInnerCollision();
}