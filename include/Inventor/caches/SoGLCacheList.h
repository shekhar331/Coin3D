/**************************************************************************\
 *
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
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

#ifndef COIN_SOGLCACHELIST_H
#define COIN_SOGLCACHELIST_H

#include <Inventor/SbBasic.h>
#include <Inventor/lists/SbList.h>

class SoGLRenderAction;
class SoGLRenderCache;

class SoGLCacheList {
public:
  SoGLCacheList(int numcaches = 2);
  ~SoGLCacheList();

  SbBool call(SoGLRenderAction * action, uint32_t pushattribbits = 0);

  void open(SoGLRenderAction * action, SbBool autocache = TRUE);
  void close(SoGLRenderAction * action);

  void invalidateAll(void);

private:
  SbList <SoGLRenderCache *> itemlist;
  int numcaches;
  unsigned int flags;
  SoGLRenderCache * opencache;
  SbBool savedinvalid;
  int autocachebits;
};

#endif // COIN_SOGLCACHELIST_H
