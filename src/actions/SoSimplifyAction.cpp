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
  \class SoSimplifyAction Inventor/include/SoSimplifyAction.h
  \brief The SoSimplifyAction class is the base class for the simplify
  action classes.
*/

#include <Inventor/SbName.h>
#include <Inventor/actions/SoSimplifyAction.h>
#include <coindefs.h> // COIN_STUB()


SO_ACTION_SOURCE(SoSimplifyAction);

// Overridden from parent class.
void
SoSimplifyAction::initClass(void)
{
  SO_ACTION_INIT_CLASS(SoSimplifyAction, SoAction);
}


/*!
  A constructor.
*/

SoSimplifyAction::SoSimplifyAction(void)
{
  COIN_STUB();
}

/*!
  The destructor.
*/

SoSimplifyAction::~SoSimplifyAction(void)
{
}

/*!
  This method is called before a scene graph traversal.
*/

void
SoSimplifyAction::beginTraversal(SoNode * /* node */)
{
  COIN_STUB();
}
