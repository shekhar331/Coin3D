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
  \class SoMFNode SoMFNode.h Inventor/fields/SoMFNode.h
  \brief The SoMFNode class is a container for nodes.
  \ingroup fields

  This field container stores an array of pointers to nodes. It takes
  care of the necessary functionality for handling copy, import and
  export operations.

  Note that node pointers stored in field instances of this type may
  be \c NULL pointers.

  \sa SoNode, SoGroup, SoSFNode

*/

#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSubFieldP.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG


SO_MFIELD_REQUIRED_SOURCE(SoMFNode);
SO_MFIELD_CONSTRUCTOR_SOURCE(SoMFNode);
SO_MFIELD_MALLOC_SOURCE(SoMFNode, SoNode *);



// Override from parent class.
void
SoMFNode::initClass(void)
{
  SO_MFIELD_INTERNAL_INIT_CLASS(SoMFNode);
}


// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS

//// From the SO_MFIELD_VALUE_SOURCE macro, start. ///////////////////////////

// We can't use the macro invocation, as we need to take care of doing
// ref() and unref() on the nodes in the array.

int
SoMFNode::fieldSizeof(void) const
{
  return sizeof(SoNode *);
}

void *
SoMFNode::valuesPtr(void)
{
  return (void *)this->values;
}

void
SoMFNode::setValuesPtr(void * ptr)
{
#if COIN_DEBUG
  // We don't get any ref()'ing done here, or any notification
  // mechanisms set up.
  SoDebugError::postWarning("SoMFNode::setValuesPtr", "**dangerous code**");
#endif // COIN_DEBUG

  this->values = (SoNode **)ptr;
}

int
SoMFNode::find(SoNode * value, SbBool addifnotfound)
{
  for (int i=0; i < this->num; i++) if ((*this)[i] == value) return i;

  if (addifnotfound) this->set1Value(this->num, value);
  return -1;
}

void
SoMFNode::setValues(const int start, const int num, const SoNode ** newvals)
{
  // Disable temporarily, so we under any circumstances will not send
  // more than one notification about the changes.
  SbBool notificstate = this->enableNotify(FALSE);

  // ref() new nodes before unref()-ing old ones, in case there are
  // common nodes (we don't want any premature destruction to happen).
  { for (int i=0; i < num; i++) if (newvals[i]) newvals[i]->ref(); }

  // We favor simplicity of code over performance here.
  { for (int i=0; i < num; i++)
    this->set1Value(start+i, (SoNode *)newvals[i]); }

  // unref() to match the initial ref().
  { for (int i=0; i < num; i++) if (newvals[i]) newvals[i]->unref(); }

  // Finally, send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

void
SoMFNode::set1Value(const int idx, SoNode * newval)
{
  // Disable temporarily, so we under no circumstances will send more
  // than one notification about the change.
  SbBool notificstate = this->enableNotify(FALSE);

  // Expand array if necessary.
  if (idx >= this->getNum()) this->setNum(idx + 1);

  SoNode * oldptr = (*this)[idx];
  if (oldptr == newval) return;

  if (oldptr) {
    oldptr->removeAuditor(this, SoNotRec::FIELD);
    oldptr->unref();
  }

  if (newval) {
    newval->addAuditor(this, SoNotRec::FIELD);
    newval->ref();
  }

  this->values[idx] = newval;

  // Finally, send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

void
SoMFNode::setValue(SoNode * value)
{
  this->deleteAllValues();
  this->set1Value(0, value);
}

SbBool
SoMFNode::operator==(const SoMFNode & field) const
{
  if (this == &field) return TRUE;
  if (this->getNum() != field.getNum()) return FALSE;

  const SoNode ** const lhs = this->getValues(0);
  const SoNode ** const rhs = field.getValues(0);
  for (int i = 0; i < num; i++) if (lhs[i] != rhs[i]) return FALSE;
  return TRUE;
}

void
SoMFNode::deleteAllValues(void)
{
  if (this->getNum()) this->deleteValues(0);
}

// Overloaded to handle unref() and removeAuditor().
void
SoMFNode::deleteValues(int start, int num)
{
  if (num == -1) num = this->getNum() - 1 - start;
  for (int i=start; i < start+num; i++) {
    SoNode * n = this->values[i];
    if (n) {
      n->removeAuditor(this, SoNotRec::FIELD);
      n->unref();
    }
  }

  inherited::deleteValues(start, num);
}

// Overloaded to insert NULL pointers in new array slots.
void
SoMFNode::insertSpace(int start, int num)
{
  // Disable temporarily so we don't send notification prematurely
  // from inherited::insertSpace().
  SbBool notificstate = this->enableNotify(FALSE);

  inherited::insertSpace(start, num);
  for (int i=start; i < start+num; i++) this->values[i] = NULL;

  // Initialization done, now send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

void
SoMFNode::copyValue(int to, int from)
{
  if (to == from) return;
  this->set1Value(to, this->values[from]);
}

//// From the SO_MFIELD_VALUE_SOURCE macro, end. /////////////////////////////


// Import a single node.
SbBool
SoMFNode::read1Value(SoInput * in, int index)
{
  SoSFNode sfnode;
  SbBool result = sfnode.readValue(in);
  if (result) this->set1Value(index, sfnode.getValue());
  return result;
}

// Export a single node.
void
SoMFNode::write1Value(SoOutput * out, int idx) const
{
  SoSFNode sfnode;
  sfnode.setValue((*this)[idx]);
  sfnode.writeValue(out);
}

#endif // DOXYGEN_SKIP_THIS


// Overridden from parent to propagate write reference counting to
// node.
void
SoMFNode::countWriteRefs(SoOutput * out) const
{
  inherited::countWriteRefs(out);

  for (int i=0; i < this->getNum(); i++) {
    SoNode * n = (*this)[i];
    // Set the "from field" flag as FALSE, as that flag is meant to be
    // used for references through field-to-field connections.
    if (n) n->addWriteReference(out, FALSE);
  }
}

// Override from parent to update our node pointer references. This is
// necessary so 1) we're added as an auditor to the copied nodes (they
// have so far only been copied as pointer bits), and 2) so we
// increase the reference count.
void
SoMFNode::fixCopy(SbBool copyconnections)
{
  for (int i=0; i < this->getNum(); i++) {
    SoNode * n = (*this)[i];
    if (n) {
      SoFieldContainer * fc = SoFieldContainer::findCopy(n, copyconnections);
      this->set1Value(i, NULL); // Fool the set-as-same-value detection.
      this->set1Value(i, (SoNode *)fc);
    }
  }
}

// Override from SoField to check node pointer.
SbBool
SoMFNode::referencesCopy(void) const
{
  if (inherited::referencesCopy()) return TRUE;

  for (int i=0; i < this->getNum(); i++) {
    SoNode * n = (*this)[i];
    if (n && SoFieldContainer::checkCopy(n)) return TRUE;
  }

  return FALSE;
}
