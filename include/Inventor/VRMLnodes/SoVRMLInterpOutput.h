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

#ifndef COIN_SOVRMLINTERPOUTPUT_H
#define COIN_SOVRMLINTERPOUTPUT_H

#include <Inventor/SoType.h>
#include <Inventor/lists/SoFieldList.h>

class SoVRMLInterpolator;

class COIN_DLL_EXPORT SoVRMLInterpOutput {
public:
  SoVRMLInterpOutput(void);
  virtual ~SoVRMLInterpOutput();

  SoType getConnectionType(void) const;
  int getForwardConnections(SoFieldList & list) const;

  void enable(const SbBool flag);
  SbBool isEnabled(void) const;

  SoVRMLInterpolator * getContainer(void) const;
  void setContainer(SoVRMLInterpolator * interp);

  void addConnection(SoField * f);
  void removeConnection(SoField * f);
  int getNumConnections(void) const;
  SoField * operator[](int i) const;

  void prepareToWrite(void) const;
  void doneWriting(void) const;

private:
  SbBool enabled;
  SoFieldList connectedfields;
  SoVRMLInterpolator * owner;
};

#endif // !COIN_SOVRMLINTERPOUTPUT_H
