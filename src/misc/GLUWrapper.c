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

#include <GLUWrapper.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#if HAVE_CONFIG_H
#include <config.h>
#else /* No config.h? Hmm. Assume the GLU library is available for linking. */
#define GLUWRAPPER_ASSUME_GLU 1
#endif /* !HAVE_CONFIG_H */
#if HAVE_DLFCN_H
#include <dlfcn.h>
#endif /* HAVE_DLFCN_H */
#ifdef HAVE_GLU /* In case we're _not_ doing runtime linking. */
#define GLUWRAPPER_ASSUME_GLU 1
#endif /* HAVE_GLU */

#if GLUWRAPPER_ASSUME_GLU
#include <Inventor/system/gl.h>
#endif /* GLUWRAPPER_ASSUME_GLU */



#ifdef HAVE_DL_LIB

  /* This should work on Linux and IRIX platforms, at least. Probably
     some other UNIX-based systems aswell. */

  #define LIBHANDLE_T void*
  #define OPEN_RUNTIME_BINDING(LIBNAME) dlopen(LIBNAME, RTLD_LAZY)
  #define CLOSE_RUNTIME_BINDING(RBHANDLE)  (void)dlclose(RBHANDLE)
  #define GET_RUNTIME_SYMBOL(RBHANDLE, FUNCNAME) dlsym(RBHANDLE, FUNCNAME)

#elif defined (HAVE_WINDLL_RUNTIME_BINDING)

  /* This should work on all MSWindows systems. */

  #define LIBHANDLE_T HINSTANCE
  #define OPEN_RUNTIME_BINDING(LIBNAME) LoadLibrary(LIBNAME)
  #define CLOSE_RUNTIME_BINDING(RBHANDLE)  (void)FreeLibrary(RBHANDLE)
  #define GET_RUNTIME_SYMBOL(RBHANDLE, FUNCNAME) GetProcAddress(RBHANDLE, FUNCNAME)

#else /* static binding */

  /* To avoid compiler error on the LIBHANDLE_T type. */
  #define LIBHANDLE_T void*

#endif  /* static binding */

/* FIXME: support HP-UX? (Doesn't have dlopen().) 20010626 mortene. */


static GLUWrapper_t * GLU_instance = NULL;
static LIBHANDLE_T GLU_libhandle = NULL;
static int GLU_failed_to_load = 0;


/* Cleans up at exit. */
static void
GLUWrapper_cleanup(void)
{
#ifdef GLU_RUNTIME_LINKING
  if (GLU_libhandle) CLOSE_RUNTIME_BINDING(GLU_libhandle);
#endif /* GLU_RUNTIME_LINKING */

  assert(GLU_instance);
  free(GLU_instance);
}


/* Set the GLU version variables in the global GLUWrapper_t. */
static void
GLUWrapper_set_version(const GLubyte * versionstr)
{
  char buffer[256];
  char * dotptr;

  GLU_instance->version.major = 0;
  GLU_instance->version.minor = 0;
  GLU_instance->version.release = 0;

#if 0 /* debug */
#if _WIN32
#error fprintf() in an MSWindows DLL is bad.
#endif /* _WIN32 */
  (void)fprintf(stderr, "GLU version string: \"%s\"\n", versionstr);
  (void)fflush(stderr);
#endif /* debug */
  (void)strncpy(buffer, (const char *)versionstr, 255);
  buffer[255] = '\0'; /* strncpy() will not null-terminate if strlen > 255 */
  dotptr = strchr(buffer, '.');
  if (dotptr) {
    char * spaceptr;
    char * start = buffer;
    *dotptr = '\0';
    GLU_instance->version.major = atoi(start);
    start = ++dotptr;

    dotptr = strchr(start, '.');
    spaceptr = strchr(start, ' ');
    if (!dotptr && spaceptr) dotptr = spaceptr;
    if (dotptr && spaceptr && spaceptr < dotptr) dotptr = spaceptr;
    if (dotptr) {
      int terminate = *dotptr == ' ';
      *dotptr = '\0';
      GLU_instance->version.minor = atoi(start);
      if (!terminate) {
        start = ++dotptr;
        dotptr = strchr(start, ' ');
        if (dotptr) *dotptr = '\0';
        GLU_instance->version.release = atoi(start);
      }
    }
    else {
      GLU_instance->version.minor = atoi(start);
    }
  }
#if 0 /* debug */
  else {
#if _WIN32
#error fprintf() in an MSWindows DLL is bad.
#endif /* _WIN32 */
    (void)fprintf(stderr, "Invalid GLU versionstring: \"%s\"\n", versionstr);
    (void)fflush(stderr);
  }
#endif /* debug */
#if 0 /* debug */
#if _WIN32
#error fprintf() in an MSWindows DLL is bad.
#endif /* _WIN32 */
  (void)fprintf(stderr, "GLU version: %d.%d.%d\n",
                GLU_instance->version.major,
                GLU_instance->version.minor,
                GLU_instance->version.release);
  (void)fflush(stderr);
#endif /* debug */
}

static int
GLUWrapper_versionMatchesAtLeast(unsigned int major,
                                 unsigned int minor,
                                 unsigned int release)
{
  assert(GLU_instance);
  if (GLU_instance->available == 0) return 0;
  if (GLU_instance->version.major < major) return 0;
  else if (GLU_instance->version.major > major) return 1;
  if (GLU_instance->version.minor < minor) return 0;
  else if (GLU_instance->version.minor > minor) return 1;
  if (GLU_instance->version.release < release) return 0;
  return 1;
}

/* Replacement function for gluGetString(). */
static const GLubyte * APIENTRY
GLUWrapper_gluGetString(GLenum name)
{
  static const GLubyte versionstring[] = "1.0.0";
  if (name == GLU_W_VERSION) return versionstring;
  return NULL;
}

/* Replacement function for gluScaleImage(). */
static GLint APIENTRY
GLUWrapper_gluScaleImage(GLenum a, GLsizei b, GLsizei c, GLenum d, const void * e, GLsizei f, GLsizei g, GLenum h, GLvoid * i)
{
  /* Just a void function (gluScaleImage() should normally be
     present). */

  /* 0 indicates success. */
  return 0;
}

/* Replacement function for gluBuild2DMipmaps(). */
static GLint APIENTRY
GLUWrapper_gluBuild2DMipmaps(GLenum a, GLint b, GLsizei c, GLsizei d, GLenum e, GLenum f, const void * g)
{
  /* Just a void function (gluBuild2DMipmaps() should normally be
     present). */

  /* 0 indicates success. */
  return 0;
}

/* Implemented by using the singleton pattern. */
const GLUWrapper_t *
GLUWrapper(void)
{
  if (!GLU_instance && !GLU_failed_to_load) {
    /* First invocation, do initializations. */
    GLUWrapper_t * gi = (GLUWrapper_t *)malloc(sizeof(GLUWrapper_t));
    /* FIXME: handle out-of-memory on malloc(). 20000928 mortene. */
    (void)atexit(GLUWrapper_cleanup);

    /* Detect recursive calls. */
    {
      static int is_initializing = 0;
      assert(is_initializing == 0);
      is_initializing = 1;
    }


    gi->versionMatchesAtLeast = GLUWrapper_versionMatchesAtLeast;

    /* The common case is that GLU is either available from the
       linking process or we're successfully going to link it in. */
    gi->available = 1;

#ifdef GLU_RUNTIME_LINKING
    {
      /* FIXME: should we get the system shared library name from an
         Autoconf check? 20000930 mortene. */
      const char * possiblelibnames[] = {
        /* MSWindows DLL name for the GLU library */
        "glu32",

        /* UNIX-style names */
        "GLU", "MesaGLU",
        "libGLU", "libMesaGLU",
        "libGLU.so", "libMesaGLU.so",
        NULL
      };

      int idx = 0;
      while (!GLU_libhandle && possiblelibnames[idx]) {
        /*
         * FIXME: Purify complains about Bad Function Parameter here.
         * Everything seems to work ok though?  pederb, 2001-02-07
         */
        GLU_libhandle = OPEN_RUNTIME_BINDING(possiblelibnames[idx]);
        idx++;
      }

      if (!GLU_libhandle) {
        gi->available = 0;
        GLU_failed_to_load = 1;

        GLU_instance = gi;
        return GLU_instance;
      }
    }

    /* Define GLUWRAPPER_REGISTER_FUNC macro. Casting the type is
       necessary for this file to be compatible with C++ compilers. */
#ifdef HAVE_HASH_QUOTING
#define GLUWRAPPER_REGISTER_FUNC(_funcname_, _funcsig_) \
    gi->_funcname_ = (_funcsig_)GET_RUNTIME_SYMBOL(GLU_libhandle, #_funcname_)
#elif defined(HAVE_APOSTROPHES_QUOTING)
#define GLUWRAPPER_REGISTER_FUNC(_funcname_, _funcsig_) \
    gi->_funcname_ = (_funcsig_)GET_RUNTIME_SYMBOL(GLU_libhandle, "_funcname_")
#else
#error Unknown quoting.
#endif

#elif defined(GLUWRAPPER_ASSUME_GLU) /* !GLU_RUNTIME_LINKING */

    /* Define GLUWRAPPER_REGISTER_FUNC macro. */
#define GLUWRAPPER_REGISTER_FUNC(_funcname_, _funcsig_) \
    gi->_funcname_ = (_funcsig_)_funcname_

#else /* !GLUWRAPPER_ASSUME_GLU */
    gi->available = 0;
    /* Define GLUWRAPPER_REGISTER_FUNC macro. */
#define GLUWRAPPER_REGISTER_FUNC(_funcname_, _funcsig_) \
    gi->_funcname_ = NULL

#endif /* !GLUWRAPPER_ASSUME_GLU */

    GLUWRAPPER_REGISTER_FUNC(gluBuild2DMipmaps, gluBuild2DMipmaps_t);
    GLUWRAPPER_REGISTER_FUNC(gluScaleImage, gluScaleImage_t);
    GLUWRAPPER_REGISTER_FUNC(gluGetString, gluGetString_t);
    GLUWRAPPER_REGISTER_FUNC(gluNewNurbsRenderer, gluNewNurbsRenderer_t);
    GLUWRAPPER_REGISTER_FUNC(gluDeleteNurbsRenderer, gluDeleteNurbsRenderer_t);
    GLUWRAPPER_REGISTER_FUNC(gluNurbsProperty, gluNurbsProperty_t);
    GLUWRAPPER_REGISTER_FUNC(gluLoadSamplingMatrices, gluLoadSamplingMatrices_t);
    GLUWRAPPER_REGISTER_FUNC(gluBeginSurface, gluBeginSurface_t);
    GLUWRAPPER_REGISTER_FUNC(gluEndSurface, gluEndSurface_t);
    GLUWRAPPER_REGISTER_FUNC(gluNurbsSurface, gluNurbsSurface_t);
    GLUWRAPPER_REGISTER_FUNC(gluBeginTrim, gluBeginTrim_t);
    GLUWRAPPER_REGISTER_FUNC(gluEndTrim, gluEndTrim_t);
    GLUWRAPPER_REGISTER_FUNC(gluBeginCurve, gluBeginCurve_t);
    GLUWRAPPER_REGISTER_FUNC(gluEndCurve, gluEndCurve_t);
    GLUWRAPPER_REGISTER_FUNC(gluNurbsCurve, gluNurbsCurve_t);
    GLUWRAPPER_REGISTER_FUNC(gluPwlCurve, gluPwlCurve_t);
    GLUWRAPPER_REGISTER_FUNC(gluNurbsCallback, gluNurbsCallback_t);
#if defined(GLU_VERSION_1_3) || defined(GLU_RUNTIME_LINKING)
    GLUWRAPPER_REGISTER_FUNC(gluNurbsCallbackData, gluNurbsCallbackData_t);
#else /* !gluNurbsCallbackData */
    gi->gluNurbsCallbackData = NULL;
#endif /* !gluNurbsCallbackData */

    /* "Backup" functions, makes it easier to be robust even when no
       GLU library can be loaded. */
    if (gi->gluScaleImage == NULL)
      gi->gluScaleImage = GLUWrapper_gluScaleImage;
    if (gi->gluBuild2DMipmaps == NULL)
      gi->gluBuild2DMipmaps = GLUWrapper_gluBuild2DMipmaps;
    if (gi->gluGetString == NULL) /* Was missing in GLU v1.0. */
      gi->gluGetString = GLUWrapper_gluGetString;

#if 0 /* debug */
    /* Test code for the GLUWrapper_set_version() parsing. */
    GLUWrapper_set_version("1.2");
    (void)fprintf(stdout, "%d.%d.%d\n",
                  gi->version.major,
                  gi->version.minor,
                  gi->version.release);
    GLUWrapper_set_version("1.2 ");
    (void)fprintf(stdout, "%d.%d.%d\n",
                  gi->version.major,
                  gi->version.minor,
                  gi->version.release);
    GLUWrapper_set_version("1.2.3");
    (void)fprintf(stdout, "%d.%d.%d\n",
                  gi->version.major,
                  gi->version.minor,
                  gi->version.release);
    GLUWrapper_set_version("1.2.3 ");
    (void)fprintf(stdout, "%d.%d.%d\n",
                  gi->version.major,
                  gi->version.minor,
                  gi->version.release);
    GLUWrapper_set_version("1.2.3 hepp");
    (void)fprintf(stdout, "%d.%d.%d\n",
                  gi->version.major,
                  gi->version.minor,
                  gi->version.release);
    (void)fflush(stdout);
#endif /* debug */

    /* Do this late, so we can detect recursive calls to this function. */
    GLU_instance = gi;

    /* Parse the version string once and expose the version numbers
       through the GLUWrapper API. */
    GLUWrapper_set_version(gi->gluGetString(GLU_W_VERSION));
  }

  return GLU_instance;
}
