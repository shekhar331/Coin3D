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

#if NBINDING==PER_VERTEX_INDEXED || NBINDING==PER_TRIANGLE_INDEXED || NBINDING==PER_STRIP_INDEXED
#define NINDEX TRUE
#else
#define NINDEX FALSE
#endif

#if MBINDING==PER_VERTEX_INDEXED || MBINDING==PER_TRIANGLE_INDEXED || MBINDING==PER_STRIP_INDEXED
#define MINDEX TRUE
#else
#define MINDEX FALSE
#endif
(const SoGLCoordinateElement * const vertexlist,
 const int32_t *vertexindices,
 int numindices,
 const SbVec3f *normals,
 const int32_t *normalindices,
 SoMaterialBundle *materials,
 const int32_t *matindices,
 const SoTextureCoordinateBundle * const texcoords,
 const int32_t *texindices)
{
  // to avoid compiler warnings
#if NINDEX==FALSE && !defined(_WIN32)
  if (normalindices);
#endif
#if MINDEX==FALSE && !defined(_WIN32)
  if (matindices);
#endif
#if TEXTURES==FALSE && !defined(_WIN32)
  if (texcoords && texindices);
#else
  int texidx = 0;
#endif
  const int32_t *viptr = vertexindices;
  const int32_t *viendptr = viptr + numindices;
  int32_t v1, v2, v3;
  SbVec3f dummynormal(0.0f, 0.0f, 1.0f);

#if NBINDING==PER_VERTEX || NBINDING==PER_TRIANGLE || NBINDING==PER_STRIP || NBINDING==PER_VERTEX_INDEXED || NBINDING==PER_TRIANGLE_INDEXED || NBINDING==PER_STRIP_INDEXED || TEXTURES==TRUE
  const SbVec3f *currnormal = &dummynormal;
  if (normals) currnormal = normals;
#endif // currnormal wrapper

#if MBINDING==PER_TRIANGLE || MBINDING==PER_STRIP || MBINDING==PER_VERTEX
  int matnr = 0;
#endif

#if NBINDING==OVERALL && !defined(_WIN32)
  if (normals);
#endif
#if MBINDING==OVERALL && !defined(_WIN32)
  if (materials);
#endif

  while (viptr < viendptr) {
    v1 = *viptr++;
    v2 = *viptr++;
    v3 = *viptr++;
    assert(v1 >= 0 && v2 >= 0 && v3 >= 0);

    glBegin(GL_TRIANGLE_STRIP);

    /* vertex 1 *********************************************************/
#if MBINDING==PER_VERTEX || MBINDING==PER_STRIP
    materials->send(matnr++, TRUE);
#elif MBINDING==PER_VERTEX_INDEXED || MBINDING==PER_STRIP_INDEXED
    materials->send(*matindices++, TRUE);
#endif
#if NBINDING==PER_VERTEX || NBINDING==PER_STRIP
    currnormal = normals++;
    glNormal3fv((const GLfloat*)currnormal);
#elif NBINDING==PER_VERTEX_INDEXED || NBINDING==PER_STRIP_INDEXED
    currnormal = &normals[*normalindices++];
    glNormal3fv((const GLfloat*)currnormal);
#endif
#if TEXTURES==TRUE
    texcoords->send(texindices ? *texindices++ : texidx++,
                    vertexlist->get3(v1),
                    *currnormal);
#endif
    vertexlist->send(v1);

    /* vertex 2 *********************************************************/
#if MBINDING==PER_VERTEX
    materials->send(matnr++, TRUE);
#elif MBINDING==PER_VERTEX_INDEXED
    materials->send(*matindices++, TRUE);
#endif
#if NBINDING==PER_VERTEX
    currnormal = normals++;
    glNormal3fv((const GLfloat*)currnormal);
#elif NBINDING==PER_VERTEX_INDEXED
    currnormal = &normals[*normalindices++];
    glNormal3fv((const GLfloat*)currnormal);
#endif
#if TEXTURES==TRUE
    texcoords->send(texindices ? *texindices++ : texidx++,
                    vertexlist->get3(v2),
                    *currnormal);
#endif
    vertexlist->send(v2);

    /* vertex 3 *********************************************************/
#if MBINDING==PER_VERTEX || MBINDING==PER_TRIANGLE
    materials->send(matnr++, TRUE);
#elif MBINDING==PER_VERTEX_INDEXED || MBINDING==PER_TRIANGLE_INDEXED
    materials->send(*matindices++, TRUE);
#endif
#if NBINDING==PER_VERTEX || NBINDING==PER_TRIANGLE
    currnormal = normals++;
    glNormal3fv((const GLfloat*)currnormal);
#elif NBINDING==PER_VERTEX_INDEXED || NBINDING==PER_TRIANGLE_INDEXED
    currnormal = &normals[*normalindices++];
    glNormal3fv((const GLfloat*)currnormal);
#endif
#if TEXTURES==TRUE
    texcoords->send(texindices ? *texindices++ : texidx++,
                    vertexlist->get3(v3),
                    *currnormal);
#endif
    vertexlist->send(v3);

    v1 = *viptr++;
    while (v1 >= 0) {
#if MBINDING==PER_VERTEX || MBINDING==PER_TRIANGLE
      materials->send(matnr++, TRUE);
#elif MBINDING==PER_VERTEX_INDEXED || MBINDING==PER_TRIANGLE_INDEXED
      materials->send(*matindices++, TRUE);
#endif
#if NBINDING==PER_VERTEX || NBINDING==PER_TRIANGLE
      currnormal = normals++;
      glNormal3fv((const GLfloat*)currnormal);
#elif NBINDING==PER_VERTEX_INDEXED || NBINDING==PER_TRIANGLE_INDEXED
      currnormal = &normals[*normalindices++];
      glNormal3fv((const GLfloat*)currnormal);
#endif
#if TEXTURES==TRUE
      texcoords->send(texindices ? *texindices++ : texidx++,
                      vertexlist->get3(v1),
                      *currnormal);
#endif
      vertexlist->send(v1);
      v1 = *viptr++;
    }
    glEnd(); // end of tristrip

#if MBINDING==PER_VERTEX_INDEXED || MBINDING==PER_TRIANGLE_INDEXED
    matindices++;
#endif
#if NBINDING==PER_VERTEX_INDEXED || NBINDING==PER_TRIANGLE_INDEXED
    normalindices++;
#endif
#if TEXTURES==TRUE
    if (texindices) texindices++;
#endif

  }
}

#undef MINDEX
#undef NINDEX
