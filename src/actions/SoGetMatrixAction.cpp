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
  \class SoGetMatrixAction SoGetMatrixAction.h Inventor/actions/SoGetMatrixAction.h
  \brief The SoGetMatrixAction class is an action for accumulating the transformation matrix of a subgraph.
  \ingroup actions

  This action makes it easy to calculate and convert back and from the
  global coordinate system of your scene and local coordinates of
  parts in a hierarchical model.

  As opposed to most other action types, the SoGetMatrixAction does
  not traverse children of the node it is applied to -- just the node
  itself. When applied to paths, it stops at the last node and does
  not continue further with the children of the tail node.
*/


// Implementation note: nodes with special behavior on this action
// must set both the matrix and the inverse matrix explicitly, as no
// tracking is done to see when the matrices have been modified.


#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/actions/SoSubActionP.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/nodes/SoNode.h>
#include <assert.h>



SO_ACTION_SOURCE(SoGetMatrixAction);


// Overridden from parent.
void
SoGetMatrixAction::initClass(void)
{
  SO_ACTION_INIT_CLASS(SoGetMatrixAction, SoAction);

  SO_ENABLE(SoGetMatrixAction, SoViewportRegionElement);
}


/*!
  Constructor.

  The \a region viewport specification is not used by this action, and
  is passed along in case it is needed by any nodes.
*/
SoGetMatrixAction::SoGetMatrixAction(const SbViewportRegion & region)
  : viewportregion(region)
{
  SO_ACTION_CONSTRUCTOR(SoGetMatrixAction);

  SO_ACTION_ADD_METHOD_INTERNAL(SoNode, SoNode::getMatrixS);
}

/*!
  Destructor.
*/
SoGetMatrixAction::~SoGetMatrixAction()
{
}

/*!
  Set the viewport \a region.

  \sa SoGetMatrixAction::SoGetMatrixAction()
*/
void
SoGetMatrixAction::setViewportRegion(const SbViewportRegion & region)
{
  this->viewportregion = region;
}

/*!
  Returns the viewport region for the action instance.
*/
const SbViewportRegion &
SoGetMatrixAction::getViewportRegion(void) const
{
  return this->viewportregion;
}

/*!
  Returns the accumulated transformation matrix.

  Note: don't modify the returned matrix. This should only be done if
  you are implementing your own transformation type node
  extensions. This advice is also valid for the other matrix access
  methods documented below.
*/
SbMatrix &
SoGetMatrixAction::getMatrix(void)
{
  return this->matrix;
}

/*!
  Returns the inverse of the accumulated transformation matrix.
*/
SbMatrix &
SoGetMatrixAction::getInverse(void)
{
  return this->invmatrix;
}

/*!
  Returns the accumulated texture matrix.
*/
SbMatrix &
SoGetMatrixAction::getTextureMatrix(void)
{
  return this->texmatrix;
}

/*!
  Returns the inverse of the accumulated texture matrix.
*/
SbMatrix &
SoGetMatrixAction::getTextureInverse(void)
{
  return this->invtexmatrix;
}

/*!
  Overloaded from parent class to initialize the matrices before
  traversal starts.
 */
void
SoGetMatrixAction::beginTraversal(SoNode * node)
{
  assert(this->traversalMethods);

  this->matrix.makeIdentity();
  this->invmatrix.makeIdentity();
  this->texmatrix.makeIdentity();
  this->invtexmatrix.makeIdentity();

  this->traverse(node);
}
