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

#ifndef COIN_SOLABEL_H
#define COIN_SOLABEL_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFName.h>


class COIN_DLL_EXPORT SoLabel : public SoNode {
  typedef SoNode inherited;

  SO_NODE_HEADER(SoLabel);

public:
  static void initClass(void);
  SoLabel(void);

  SoSFName label;

protected:
  virtual ~SoLabel();
};

#endif // !COIN_SOLABEL_H
