/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: soccerinput.h,v 1.6 2008/02/22 16:48:20 hedayat Exp $

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
#ifndef SOCCERINPUT_H
#define SOCCERINPUT_H

#include <kerosin/inputserver/inputitem.h>
#include <kerosin/inputserver/inputcontrol.h>
#include <oxygen/simulationserver/netclient.h>

namespace oxygen
{
    class FPSController;
    class Body;
}

class SoccerInput : public kerosin::InputItem
{
public:
    enum ECmds
        {
            CmdUser              = kerosin::InputControl::CmdUser,
            CmdKickOff           = CmdUser + 1,
            CmdMoveAgent         = CmdKickOff + 1,
            CmdDropBall          = CmdMoveAgent + 1,
            CmdShootBall         = CmdDropBall + 1,
            CmdMoveBall          = CmdShootBall + 1,
            CmdCameraLeftGoal    = CmdMoveBall + 1,
            CmdCameraLeftCorner  = CmdCameraLeftGoal + 1,
            CmdCameraMiddleLeft  = CmdCameraLeftCorner + 1,
            CmdCameraMiddleRight = CmdCameraMiddleLeft + 1,
            CmdCameraMiddle      = CmdCameraMiddleRight + 1,
            CmdCameraRightCorner = CmdCameraMiddle + 1,
            CmdCameraRightGoal   = CmdCameraRightCorner + 1,
            //JAN
            CmdFreeKickLeft      = CmdCameraRightGoal + 1,
            CmdFreeKickRight   = CmdFreeKickLeft + 1
        };

public:
    SoccerInput();
    virtual ~SoccerInput();

    /** this method is called every time an input unknown to the
        parent InputControl node is received
    */
    virtual void ProcessInput(const kerosin::Input& input);

    /** registers the soccermonitor command constants and cache
        SparkMonitorClient reference
    */
    virtual void OnLink();

    /** reset SparkMonitorClient reference */
    virtual void OnUnlink();

protected:
    void SendCommand(const std::string& cmd);

protected:
    /** cached reference to the monitor client */
    boost::shared_ptr<oxygen::NetClient> mMonitorClient;

    /** cached reference to the camera body */
    boost::shared_ptr<oxygen::Body> mCameraBody;

    boost::shared_ptr<oxygen::FPSController> mFPS;
};

DECLARE_CLASS(SoccerInput);

#endif // SOCCERINPUT_H
