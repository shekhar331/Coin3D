/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

#ifndef COIN_SOPOINTLIGHT_H
#define COIN_SOPOINTLIGHT_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoLight.h>


class COIN_DLL_EXPORT SoPointLight : public SoLight {
  typedef SoLight inherited;

  SO_NODE_HEADER(SoPointLight);

public:
  static void initClass(void);
  SoPointLight(void);

  SoSFVec3f location;

  virtual void GLRender(SoGLRenderAction * action);

protected:
  virtual ~SoPointLight();
};

#endif // !COIN_SOPOINTLIGHT_H
