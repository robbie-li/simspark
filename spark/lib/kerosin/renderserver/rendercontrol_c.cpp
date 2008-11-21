/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: rendercontrol_c.cpp,v 1.2 2008/02/22 16:48:18 hedayat Exp $

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
#include "rendercontrol.h"
#include <oxygen/sceneserver/sceneserver.h>

using namespace kerosin;
using namespace std;

FUNCTION(RenderControl, getFramesRendered)
{
    return obj->GetFramesRendered();
}

void CLASS(RenderControl)::DefineClass()
{
    DEFINE_BASECLASS(oxygen/SimControlNode);
    DEFINE_FUNCTION(getFramesRendered);
}
