#ifndef COIN_SOGLRENDERPASSELEMENT_H
#define COIN_SOGLRENDERPASSELEMENT_H

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

#include <Inventor/elements/SoSubElement.h>

class COIN_DLL_API SoGLRenderPassElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoGLRenderPassElement);
public:
  static void initClass(void);
protected:
  virtual ~SoGLRenderPassElement();

public:
  virtual void init(SoState * state);
  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  static void set(SoState * const state, const int pass);
  static int get(SoState * const state);

protected:
  int passnr;

};

#endif // !COIN_SOGLRENDERPASSELEMENT_H
