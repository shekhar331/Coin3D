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

#ifndef COIN_SOGLVIEWPORTREGIONELEMENT_H
#define COIN_SOGLVIEWPORTREGIONELEMENT_H

#include <Inventor/elements/SoViewportRegionElement.h>


class COIN_DLL_EXPORT SoGLViewportRegionElement : public SoViewportRegionElement {
  typedef SoViewportRegionElement inherited;

  SO_ELEMENT_HEADER(SoGLViewportRegionElement);
public:
  static void initClass(void);
protected:
  virtual ~SoGLViewportRegionElement();

public:
  virtual void init(SoState * state);
  virtual void push(SoState * state);
  virtual void pop(SoState * state,
                   const SoElement * prevTopElement);

protected:
  virtual void setElt(const SbViewportRegion & viewportRegion);

private:
  SbBool initialized;
  void updategl() const;
};

#endif // !COIN_SOGLVIEWPORTREGIONELEMENT_H
