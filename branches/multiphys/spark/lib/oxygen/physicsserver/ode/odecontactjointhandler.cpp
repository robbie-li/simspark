/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: universaljoint.cpp 112 2009-12-02 10:06:02Z a-held $

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
#include <oxygen/physicsserver/ode/odecontactjointhandler.h>

using namespace oxygen;

ODEContactJointHandler::ODEContactJointHandler() : ODECollider(){

}

void ODEContactJointHandler::Initialize(){
    // set up default contact surface parameters
    mSurfaceParameter.mode = dContactBounce;
    mSurfaceParameter.mu = dInfinity;
    mSurfaceParameter.bounce = 0.8f;
    mSurfaceParameter.bounce_vel = 2.0f;

    // In contactjointhandler_c.cpp, setContactSlip function, only
    // accept one parameter, so two parameter is a mistake, and then 
    // these two value will be not initialized, but slipe mode is open
    mSurfaceParameter.slip1 = 5e-3;
    mSurfaceParameter.slip2 = 5e-3;
}

float
ODEContactJointHandler::MixValues(const float v1, const float v2, const int n) const
{
    switch(n)
        {
        default:
        case 0:
            // undefined, default 0
            return 0.0f;

        case 1:
            // first one defined
            return v1;

        case 2:
            // second one defined
            return v2;

        case 3:
            // both defined, return average
            return (v1 + v2) / 2.0f;
        }
}

void
ODEContactJointHandler::CalcSurfaceParam(dSurfaceParameters& surface,
                                         const dSurfaceParameters& collideeParam)
{
    // init surface
    surface.mode = 0;

    // calculate average mu; mu can be dInfinity, so first multiply with
    // 0.5 and the sum up to avoid a range error
    surface.mu = mSurfaceParameter.mu*0.5f + collideeParam.mu*0.5f;

    // soft cfm
    const int nCfm =
        ((mSurfaceParameter.mode & dContactSoftCFM) ? 1:0) +
        ((collideeParam.mode & dContactSoftCFM) ? 2:0);

    if (nCfm>0)
        {
            surface.soft_cfm = MixValues
                (mSurfaceParameter.soft_cfm, collideeParam.soft_cfm, nCfm);
            surface.mode |= dContactSoftCFM;
        }

    // soft_erp
    const int nErp =
        ((mSurfaceParameter.mode & dContactSoftERP) ? 1:0) +
        ((collideeParam.mode & dContactSoftERP) ? 2:0);

    if (nErp>0)
        {
            surface.soft_erp = MixValues
                (mSurfaceParameter.soft_erp, collideeParam.soft_erp, nErp);
            surface.mode |= dContactSoftERP;
        }

    // bounce
    const int nBounce =
        ((mSurfaceParameter.mode & dContactBounce) ? 1:0) +
        ((collideeParam.mode & dContactBounce) ? 2:0);

    if (nBounce>0)
        {
            surface.bounce = MixValues
                (mSurfaceParameter.bounce, collideeParam.bounce, nBounce);

            surface.bounce_vel = MixValues
                (mSurfaceParameter.bounce_vel, collideeParam.bounce_vel, nBounce);

            surface.mode |= dContactBounce;
        }

    // slip1
    const int nSlip1 = 
        ((mSurfaceParameter.mode & dContactSlip1) ? 1 : 0) +
        ((collideeParam.mode & dContactSlip1) ? 2 : 0);

    if (nSlip1 > 0)
        {
            surface.slip1 = MixValues
                (mSurfaceParameter.slip1, collideeParam.slip1, nSlip1);

            surface.mode |= dContactSlip1;
        }

    // slip2
    const int nSlip2 = 
        ((mSurfaceParameter.mode & dContactSlip2) ? 1 : 0) +
        ((collideeParam.mode & dContactSlip2) ? 2 : 0);

    if (nSlip2 > 0)
        {
            surface.slip2 = MixValues
                (mSurfaceParameter.slip2, collideeParam.slip2, nSlip2);

            surface.mode |= dContactSlip2;
        }
}