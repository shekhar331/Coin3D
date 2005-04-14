#ifndef COIN_SOGLSHADERPARAMETER_H
#define COIN_SOGLSHADERPARAMETER_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef COIN_INTERNAL
#error this is a private header file
#endif

// *************************************************************************

#include <Inventor/C/glue/gl.h>
#include <Inventor/nodes/SoShader.h>

// *************************************************************************

class SoGLShaderObject;

class SoGLShaderParameter
{
public:
  virtual void set1f(const SoGLShaderObject * shader, const float value, const char * name, const int id) = 0;
  virtual void set2f(const SoGLShaderObject * shader, const float * value, const char * name, const int id) = 0;
  virtual void set3f(const SoGLShaderObject * shader, const float * value, const char * name, const int id) = 0;
  virtual void set4f(const SoGLShaderObject * shader, const float * value, const char * name, const int id) = 0;

  virtual void set1fv(const SoGLShaderObject * shader, const int num, const float * value, const char* name, const int id) = 0;
  virtual void set2fv(const SoGLShaderObject * shader, const int num, const float * value, const char* name, const int id) = 0;
  virtual void set3fv(const SoGLShaderObject * shader, const int num, const float * value, const char* name, const int id) = 0;
  virtual void set4fv(const SoGLShaderObject * shader, const int num, const float * value, const char* name, const int id) = 0;

  virtual void setMatrix(const SoGLShaderObject * shader, const float * value, const char * name, const int id) = 0;
  virtual void setMatrixArray(const SoGLShaderObject * shader, const int num, const float * value, const char * name, const int id) = 0;

  virtual void set1i(const SoGLShaderObject * shader, const int32_t value, const char * name, const int id) = 0;
  virtual void set2i(const SoGLShaderObject * shader, const int32_t * value, const char * name, const int id) = 0;
  virtual void set3i(const SoGLShaderObject * shader, const int32_t * value, const char * name, const int id) = 0;
  virtual void set4i(const SoGLShaderObject * shader, const int32_t * value, const char * name, const int id) = 0;


  virtual SoShader::Type shaderType(void) const = 0;

public: 
  void operator delete(void * obj);
  void operator delete[](void * obj);
};

#endif /* ! COIN_SOGLSHADERPARAMETER_H */
