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

#ifndef COIN_SNPRINTF_H
#define COIN_SNPRINTF_H

#ifdef __cplusplus
extern "C" {
#endif


#if HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#if !HAVE_SNPRINTF
#if HAVE__SNPRINTF
/* This is how it is defined in MSVC++ 5.0. */
#define snprintf _snprintf
#else /* !HAVE__SNPRINTF */
extern int snprintf(char * target, size_t n, const char * formatstr, ...);
#endif /* !HAVE__SNPRINTF */
#endif /* !HAVE_SNPRINTF */

#if !HAVE_VSNPRINTF
#if HAVE__VSNPRINTF
/* This is how it is defined in MSVC++ 5.0. */
#define vsnprintf _vsnprintf
#else /* !HAVE__VSNPRINTF */
extern int vsnprintf(char * target, size_t n, const char * formatstr, va_list args);
#endif /* !HAVE__VSNPRINTF */
#endif /* !HAVE_VSNPRINTF */

#ifdef __cplusplus
}
#endif

#endif /* COIN_SNPRINTF_H */
