/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2000 by Systems in Motion. All rights reserved.
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
  \class SoNormal SoNormal.h Inventor/nodes/SoNormal.h
  \brief The SoNormal class is a node for providing normals to the state.
  \ingroup nodes

  Coin will automatically calculate normals for you if no SoNormal
  nodes are present in the scene graph, but explicitly setting normals
  is useful for at least two purposes: 1) a potential increase in
  performance, 2) you can calculate and use "incorrect" normals to do
  various special effects.

  \sa SoNormalBinding
*/

#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/elements/SoNormalElement.h>

/*!
  \var SoMFVec3f SoNormal::vector
  Sets a pool of normal vectors in the traversal state.
*/

// *************************************************************************

SO_NODE_SOURCE(SoNormal);

/*!
  Constructor.
*/
SoNormal::SoNormal(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoNormal);

  SO_NODE_ADD_FIELD(vector, (NULL));
}

/*!
  Destructor.
*/
SoNormal::~SoNormal()
{
}

// Doc in superclass.
void
SoNormal::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoNormal);

  SO_ENABLE(SoCallbackAction, SoNormalElement);
  SO_ENABLE(SoGLRenderAction, SoNormalElement);
  SO_ENABLE(SoGetPrimitiveCountAction, SoNormalElement);
  SO_ENABLE(SoPickAction, SoNormalElement);
}

// Doc in superclass.
void
SoNormal::GLRender(SoGLRenderAction * action)
{
  //
  // FIXME: code to test if all normals are unit length, and store
  // this in some cached variable.  should be passed on to
  // SoGLNormalizeElement to optimize rendering (pederb)
  //
  SoNormal::doAction(action);
}

// Doc in superclass.
void
SoNormal::doAction(SoAction * action)
{
  SoNormalElement::set(action->getState(), this,
                       this->vector.getNum(), this->vector.getValues(0));
}

// Doc in superclass.
void
SoNormal::callback(SoCallbackAction * action)
{
  SoNormal::doAction(action);
}

// Doc in superclass.
void
SoNormal::pick(SoPickAction * action)
{
  SoNormal::doAction(action);
}

// Doc in superclass.
void
SoNormal::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  SoNormal::doAction(action);
}
