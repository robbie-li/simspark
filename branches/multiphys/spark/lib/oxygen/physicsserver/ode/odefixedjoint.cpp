/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: fixedjoint.cpp 112 2009-12-02 10:06:02Z a-held $

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

#include <oxygen/physicsserver/ode/odefixedjoint.h>

using namespace oxygen;
using namespace boost;

ODEFixedJoint::ODEFixedJoint() : ODEGeneric6DOFJoint()
{
}

void ODEFixedJoint::CreateFixedJoint(long world)
{
    dWorldID ODEworld = (dWorldID) world;
    mODEJoint = dJointCreateFixed(ODEworld, 0);
    mJointID = (long) mODEJoint;
}

void ODEFixedJoint::SetFixed()
{
    dJointSetFixed(mODEJoint);
}

long ODEFixedJoint::GetJointID(){
    return mJointID;
}
