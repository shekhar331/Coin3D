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
  \class SoComposeMatrix SoComposeMatrix.h Inventor/engines/SoComposeMatrix.h
  \brief The SoComposeMatrix class is used to compose a matrix from miscellaneous transformations.
  \ingroup engines
*/

#include <Inventor/engines/SoComposeMatrix.h>
#include <Inventor/lists/SoEngineOutputList.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/engines/SoSubEngineP.h>

SO_ENGINE_SOURCE(SoComposeMatrix);

/*!
  \var SoMFVec3f SoComposeMatrix::translation
  Input field with set of translation vectors for the output matrices.
*/
/*!
  \var SoMFRotation SoComposeMatrix::rotation
  Input field with set of rotations for the output matrices.
*/
/*!
  \var SoMFVec3f SoComposeMatrix::scaleFactor
  Input field with set of scale vectors for the output matrices.
*/
/*!
  \var SoMFRotation SoComposeMatrix::scaleOrientation
  Input field with set of scale orientations for the output matrices.
*/
/*!
  \var SoMFVec3f SoComposeMatrix::center
  Input field with set of center positions for the output matrices.
*/
/*!
  \var SoEngineOutput SoComposeMatrix::matrix

  (SoMFMatrix) A set of matrices calculated from the input fields.
  The matrices is calculated by the SbMatrix::setTransform() function.
*/

#ifndef DOXYGEN_SKIP_THIS // No need to document these.

// Default constructor.
SoComposeMatrix::SoComposeMatrix()
{
  SO_ENGINE_INTERNAL_CONSTRUCTOR(SoComposeMatrix);

  SO_ENGINE_ADD_INPUT(translation,(0,0,0));
  SO_ENGINE_ADD_INPUT(rotation,(0,0,0,0));
  SO_ENGINE_ADD_INPUT(scaleFactor,(0,0,0));
  SO_ENGINE_ADD_INPUT(scaleOrientation,(0,0,0,0));
  SO_ENGINE_ADD_INPUT(center,(0,0,0));

  SO_ENGINE_ADD_OUTPUT(matrix,SoMFMatrix);
}

// overloaded from parent
void
SoComposeMatrix::initClass()
{
  SO_ENGINE_INTERNAL_INIT_CLASS(SoComposeMatrix);
}

//
// private members
//
SoComposeMatrix::~SoComposeMatrix()
{
}

// overloaded from parent
void
SoComposeMatrix::evaluate()
{
  int numTranslation = this->translation.getNum();
  int numRotation = this->rotation.getNum();
  int numScaleFactor = this->scaleFactor.getNum();
  int numScaleOrientation = this->scaleOrientation.getNum();
  int numCenter = this->center.getNum();

  int numOut = numTranslation > numRotation? numTranslation:numRotation;
  int numOut2 =
    numScaleFactor>numScaleOrientation?numScaleFactor:numScaleOrientation;
  numOut2 = numOut2>numCenter?numOut2:numCenter;
  numOut = numOut>numOut2?numOut:numOut2;

  SO_ENGINE_OUTPUT(matrix,SoMFMatrix,setNum(numOut));

  int i;

  for (i=0;i<numOut;i++) {
    const SbVec3f translationVal=
      i<numTranslation?this->translation[i]:this->translation[numTranslation-1];
    const SbVec3f scaleFactorVal=
      i<numScaleFactor?this->scaleFactor[i]:this->scaleFactor[numScaleFactor-1];
    const SbVec3f centerVal=i<numCenter?this->center[i]:this->center[numCenter-1];
    const SbRotation rotationVal=
      i<numRotation?this->rotation[i]:this->rotation[numRotation-1];
    const SbRotation scaleOrientationVal=
      i<numScaleOrientation?
      this->scaleOrientation[i]:this->scaleOrientation[numScaleOrientation-1];

    SbMatrix mat;
    mat.setTransform(translationVal,rotationVal,scaleFactorVal,
                     scaleOrientationVal,centerVal);
    SO_ENGINE_OUTPUT(matrix,SoMFMatrix,set1Value(i,mat));
  }
}

#endif // !DOXYGEN_SKIP_THIS
