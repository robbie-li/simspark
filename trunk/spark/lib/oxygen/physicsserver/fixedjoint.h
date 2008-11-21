/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: fixedjoint.h,v 1.4 2007/02/12 19:17:57 rollmark Exp $

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
#ifndef OXYGEN_FIXEDJOINT_H
#define OXYGEN_FIXEDJOINT_H

#include "joint.h"

namespace oxygen
{
/** The fixed joint maintains a fixed relative position and
    orientation between two bodies, or between a body and the static
    environment.
*/
class FixedJoint : public Joint
{
public:
    FixedJoint();
    virtual ~FixedJoint();

    /** Call this on the fixed joint after it has been attached to remember 
        the current desired relative offset and desired relative rotation 
        between the bodies. */
    void SetFixed();

protected:
    /** creates a new fixed joint */
    virtual void OnLink();

    /** sets a joint parameter value */
    virtual void SetParameter(int parameter, float value);

    /** returns a joint parameter value */
    virtual float GetParameter(int parameter) const;
};

DECLARE_CLASS(FixedJoint);

} // namespace oxygen

#endif // OXYGEN_FIXEDJOINT_H
