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

#ifndef OXYGEN_ODEUNIVERSALJOINT_H
#define OXYGEN_ODEUNIVERSALJOINT_H

#include <oxygen/physicsserver/int/universaljointint.h>
#include <oxygen/physicsserver/ode/odegeneric6dofjoint.h>

namespace oxygen
{

class OXYGEN_API ODEUniversalJoint : public UniversalJointInt, public ODEGeneric6DOFJoint
{
    /** See physicsserver/int/universaljointint.h for documentation */
    
public:
    ODEUniversalJoint();
    long CreateUniversalJoint(long world);
    void SetAnchor(const salt::Vector3f& anchor, long jointID);
    salt::Vector3f GetAnchor1(long jointID);
    salt::Vector3f GetAnchor2(long jointID);
    void SetAxis1(const salt::Vector3f& axis, long jointID);
    void SetAxis2(const salt::Vector3f& axis, long jointID);
    salt::Vector3f GetAxis1(long jointID) const;
    salt::Vector3f GetAxis2(long jointID) const;
    float GetAngle1(long jointID) const;
    float GetAngle2(long jointID) const;
    float GetAngleRate1(long jointID) const;
    float GetAngleRate2(long jointID) const;
};

} //namespace oxygen

#endif //OXYGEN_ODEUNIVERSALJOINT_H
