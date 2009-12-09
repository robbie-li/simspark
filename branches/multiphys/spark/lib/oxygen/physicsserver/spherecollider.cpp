/* -*- mode: c++ -*-

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

#include <oxygen/physicsserver/spherecollider.h>
#include <oxygen/physicsserver/ode/odespherecollider.h>

using namespace oxygen;
using namespace salt;

SphereCollider::SphereCollider() : ConvexCollider()
{
    mSphereColliderImp = boost::shared_ptr<ODESphereCollider>(new ODESphereCollider());
}

void SphereCollider::SetRadius(float r)
{
    mSphereColliderImp->SetRadius(r);
}

float SphereCollider::GetRadius() const
{
    return mSphereColliderImp->GetRadius();
}

bool SphereCollider::ConstructInternal()
{
    if (!Collider::ConstructInternal())
    {
        return false;
    }
    
   // mODEGeom = dCreateSphere(0, 1.0f);

    // create a unit sphere
    mSphereColliderImp->CreateSphere();
    mODEGeom = (dGeomID) mSphereColliderImp->GetGeomID();

    return (mSphereColliderImp->GetGeomID() != 0);
}

float SphereCollider::GetPointDepth(const Vector3f& pos)
{
  Vector3f worldPos(GetWorldTransform() * pos);
  return mSphereColliderImp->GetPointDepth(worldPos);
}
