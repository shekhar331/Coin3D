/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation. See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition license.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/

/*!
  \class SoPointLight SoPointLight.h Inventor/nodes/SoPointLight.h
  \brief The SoPointLight class is a node type for light sources.
  \ingroup nodes

  Pointlights emits light equally in all directions from a specified
  3D location.

  See also documentation of parent class for important information
  regarding light sources in general.
*/

#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoSubNodeP.h>

#include <Inventor/SbColor4f.h>
#include <Inventor/SbVec4f.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoEnvironmentElement.h>
#include <Inventor/elements/SoGLLightIdElement.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H
#ifdef HAVE_WINDOWS_H
#include <windows.h> // Needed to include gl.h.
#endif // HAVE_WINDOWS_H
#include <GL/gl.h>

/*!
  \var SoSFVec3f SoPointLight::location
  3D position of lightsource. Default value is <0, 0, 1>.
*/

// *************************************************************************

SO_NODE_SOURCE(SoPointLight);

/*!
  Constructor.
*/
SoPointLight::SoPointLight(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoPointLight);

  SO_NODE_ADD_FIELD(location, (0.0f, 0.0f, 1.0f));
}

/*!
  Destructor.
*/
SoPointLight::~SoPointLight()
{
}

// Doc from superclass.
void
SoPointLight::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoPointLight);
}

// Doc from superclass.
void
SoPointLight::GLRender(SoGLRenderAction * action)
{
  if (!this->on.getValue()) return;

  int idx = SoGLLightIdElement::increment(action->getState());

  if (idx < 0) {
#if COIN_DEBUG
    SoDebugError::post("SoPointLight::GLRender()",
                       "Max # lights exceeded :(\n");
#endif // COIN_DEBUG
    return;
  }

  SoState * state = action->getState();

  GLenum light = (GLenum) (idx + GL_LIGHT0);

  SbVec3f attenuation = SoEnvironmentElement::getLightAttenuation(state);
  glLightf(light, GL_QUADRATIC_ATTENUATION, attenuation[0]);
  glLightf(light, GL_LINEAR_ATTENUATION, attenuation[1]);
  glLightf(light, GL_CONSTANT_ATTENUATION, attenuation[2]);

  SbColor4f lightcolor(0.0f, 0.0f, 0.0f, 1.0f);
  lightcolor.setRGB(this->color.getValue());
  lightcolor *= this->intensity.getValue();

  glLightfv(light, GL_DIFFUSE, lightcolor.getValue());
  glLightfv(light, GL_SPECULAR, lightcolor.getValue());

  SbVec3f loc = this->location.getValue();

  // point (or spot) light when w = 1.0
  SbVec4f posvec(loc[0], loc[1], loc[2], 1.0f);
  glLightfv(light, GL_POSITION, posvec.getValue());

  // turning off spot light properties for ordinary lights
  glLightf(light, GL_SPOT_EXPONENT, 0.0);
  glLightf(light, GL_SPOT_CUTOFF, 180.0);
}
