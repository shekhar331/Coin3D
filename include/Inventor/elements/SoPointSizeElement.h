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

#ifndef COIN_SOPOINTSIZEELEMENT_H
#define COIN_SOPOINTSIZEELEMENT_H

#include <Inventor/elements/SoFloatElement.h>


class COIN_DLL_API SoPointSizeElement : public SoFloatElement {
  typedef SoFloatElement inherited;

  SO_ELEMENT_HEADER(SoPointSizeElement);
public:
  static void initClass(void);
protected:
  virtual ~SoPointSizeElement();

public:
  virtual void init(SoState * state);

  static  void set(SoState * const state, SoNode * const node,
                   const float pointSize);
  static  void set(SoState * const state, const float pointSize);
  static  float get(SoState * const state);
  static  float getDefault();
};

#endif // !COIN_SOPOINTSIZEELEMENT_H
