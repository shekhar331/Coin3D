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

/*!
  \class SoFieldConverter SoFieldConverter.h Inventor/engines/SoFieldConverter.h
  \brief The SoFieldConverter class is the abstract base class for field converters.
  \ingroup engines

  When fields of different types are attempted connected, the Coin
  library tries to find a field converter class which can be inserted
  between them, acting as a filter converting values from the master
  field to values matching the type of the slave field.

  If a value type conversion is possible (like between an SoSFFloat
  field and an SoSFInt32 field, for instance, where we could do a
  simple typecast for converting the value of one to the other), an
  SoFieldConverter derived object is inserted.

  This class is the abstract base superclass which all such field
  converters needs to inherit.

  Coin comes with one built-in field converter class which takes care
  of all possible field-to-field conversions we know about. This means
  applications programmers should seldom need to care about this
  class, it will probably only be useful if you expand the Coin
  library with your own field type classes. (Doing so is considered
  advanced use of the library.)

  \sa SoDB::addConverter()
 */

#include <Inventor/engines/SoFieldConverter.h>

#include <Inventor/fields/SoField.h>
#include <Inventor/engines/SoOutputData.h>
#include <Inventor/engines/SoConvertAll.h>
#include <Inventor/lists/SoTypeList.h>
#include <assert.h>
#include <Inventor/engines/SoSubEngineP.h>
#include <coindefs.h> // COIN_OBSOLETED

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

/*!
  \fn SoField * SoFieldConverter::getInput(SoType type)

  Returns input field for the converter engine. Must be overloaded in
  non-abstract converter engine classes.
*/
/*!
  \fn SoEngineOutput * SoFieldConverter::getOutput(SoType type)

  Returns output for the converter engine. Must be overloaded in
  non-abstract converter engine classes.
*/


SO_ENGINE_ABSTRACT_SOURCE(SoFieldConverter);


/*!
  Default constructor.
*/
SoFieldConverter::SoFieldConverter(void)
{
#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoFieldConverter::SoFieldConverter", "%p", this);
#endif // debug
}

/*!
  Default destructor.
*/
SoFieldConverter::~SoFieldConverter()
{
}

void
SoFieldConverter::initClass(void)
{
  SO_ENGINE_INTERNAL_INIT_ABSTRACT_CLASS(SoFieldConverter);
  SoFieldConverter::initClasses();
}

void
SoFieldConverter::initClasses(void)
{
  SoConvertAll::initClass();
}

/*!  
  This method is obsoleted in Coin. It should probably have been
  private in OIV.  
*/
SoField *
SoFieldConverter::getConnectedInput(void)
{
  COIN_OBSOLETED();
  return NULL;
}

/*!
  Returns fields which are connected as slaves of the engine output.
*/
int
SoFieldConverter::getForwardConnections(SoFieldList & l) const
{
  const SoEngineOutputData * outputs = this->getOutputData();
  assert(outputs && outputs->getNumOutputs() == 1);

  SoEngineOutput * output = outputs->getOutput(this, 0);
  assert(output);

  int n = output->getNumConnections();
  for (int i = 0; i < n; i++) l.append((*output)[i]);
  return n;
}
