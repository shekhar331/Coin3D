#ifndef COIN_SOLISTENERVELOCITYELEMENT_H
#define COIN_SOLISTENERVELOCITYELEMENT_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for  more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbVec3f.h>

class COIN_DLL_API SoListenerVelocityElement : public SoReplacedElement {
  typedef SoReplacedElement inherited;

  SO_ELEMENT_HEADER(SoListenerVelocityElement);
public:
  static void initClass(void);
protected:
  virtual ~SoListenerVelocityElement();

public:
  virtual void init(SoState * state);
  static void set(SoState * const state, SoNode * const node,
                   const SbVec3f & velocity);

  static const SbVec3f & get(SoState * const state);

  virtual void print(FILE * file) const;

protected:
  SbVec3f velocity;
};

#endif // !COIN_SOLISTENERVELOCITYELEMENT_H
