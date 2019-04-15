#ifndef KARIN_OPENGL2_PORT_H
#define KARIN_OPENGL2_PORT_H

/* Errors */
#define GL_STACK_OVERFLOW GL2_STACK_OVERFLOW
#define GL_STACK_UNDERFLOW GL2_STACK_UNDERFLOW

/* Matrix Mode */
#define GL_MATRIX_MODE GL2_MATRIX_MODE
#define GL_MODELVIEW GL2_MODELVIEW
#define GL_PROJECTION GL2_PROJECTION

/* Implementation limits */
#define GL_MAX_ATTRIB_STACK_DEPTH GL2_MAX_ATTRIB_STACK_DEPTH
#define GL_MAX_MODELVIEW_STACK_DEPTH GL2_MAX_MODELVIEW_STACK_DEPTH
#define GL_MAX_PROJECTION_STACK_DEPTH GL2_MAX_PROJECTION_STACK_DEPTH
#define GL_MAX_TEXTURE_STACK_DEPTH GL2_MAX_TEXTURE_STACK_DEPTH
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH GL2_MAX_CLIENT_ATTRIB_STACK_DEPTH

/* Gets */
#define GL_ATTRIB_STACK_DEPTH GL2_ATTRIB_STACK_DEPTH
#define GL_CLIENT_ATTRIB_STACK_DEPTH GL2_CLIENT_ATTRIB_STACK_DEPTH
#define GL_MODELVIEW_MATRIX GL2_MODELVIEW_MATRIX
#define GL_MODELVIEW_STACK_DEPTH GL2_MODELVIEW_STACK_DEPTH
#define GL_PROJECTION_MATRIX GL2_PROJECTION_MATRIX
#define GL_PROJECTION_STACK_DEPTH GL2_PROJECTION_STACK_DEPTH
#define GL_TEXTURE_MATRIX GL2_TEXTURE_MATRIX
#define GL_TEXTURE_STACK_DEPTH GL2_TEXTURE_STACK_DEPTH

#define GL_CURRENT_COLOR GL2_CURRENT_COLOR
#define GL_POINT_SMOOTH GL2_POINT_SMOOTH
#define GL_POINT_SIZE GL2_POINT_SIZE
#define GL_LINE_SMOOTH GL2_LINE_SMOOTH

// for attributes bit defines
#define GL_CURRENT_BIT GL2_CURRENT_BIT
#define GL_POINT_BIT GL2_POINT_BIT
#define GL_LINE_BIT GL2_LINE_BIT
#define GL_POLYGON_BIT GL2_POLYGON_BIT
#define GL_POLYGON_STIPPLE_BIT GL2_POLYGON_STIPPLE_BIT
#define GL_PIXEL_MODE_BIT GL2_PIXEL_MODE_BIT
#define GL_LIGHTING_BIT GL2_LIGHTING_BIT
#define GL_FOG_BIT GL2_FOG_BIT
#define GL_ACCUM_BUFFER_BIT GL2_ACCUM_BUFFER_BIT
#define GL_VIEWPORT_BIT GL2_VIEWPORT_BIT
#define GL_TRANSFORM_BIT GL2_TRANSFORM_BIT
#define GL_ENABLE_BIT GL2_ENABLE_BIT
#define GL_HINT_BIT GL2_HINT_BIT
#define GL_EVAL_BIT GL2_EVAL_BIT
#define GL_LIST_BIT GL2_LIST_BIT
#define GL_TEXTURE_BIT GL2_TEXTURE_BIT
#define GL_SCISSOR_BIT GL2_SCISSOR_BIT
#define GL_ALL_ATTRIB_BITS GL2_ALL_ATTRIB_BITS

// client state
#define GL_VERTEX_ARRAY GL2_VERTEX_ARRAY
#define GL_NORMAL_ARRAY GL2_NORMAL_ARRAY
#define GL_COLOR_ARRAY GL2_COLOR_ARRAY
#define GL_TEXTURE_COORD_ARRAY GL2_TEXTURE_COORD_ARRAY

// fog
#define GL_FOG GL2_FOG
#define GL_FOG_DENSITY GL2_FOG_DENSITY
#define GL_FOG_START GL2_FOG_START
#define GL_FOG_END GL2_FOG_END
#define GL_FOG_MODE GL2_FOG_MODE
#define GL_FOG_COLOR GL2_FOG_COLOR
#define GL_EXP GL2_EXP
#define GL_EXP2 GL2_EXP2
#define GL2_LINEAR GL_LINEAR

// other
#define GL_SHADE_MODEL GL2_SHADE_MODEL
#define GL_FLAT GL2_FLAT
#define GL_SMOOTH GL2_SMOOTH
#define GL_ALPHA_TEST GL2_ALPHA_TEST
#define GL_ALPHA_TEST_REF GL2_ALPHA_TEST_REF
#define GL_ALPHA_TEST_FUNC GL2_ALPHA_TEST_FUNC
#define GL_BLEND_SRC GL2_BLEND_SRC
#define GL_BLEND_DST GL2_BLEND_DST

// alias for gles1
#define glTranslatef(x, y, z) gl2Translate(x, y, z)
#define glRotatef(a, x, y, z) gl2Rotate(a, x, y, z)
#define glScalef(x, y, z) gl2Scale(x, y, z);
#define glOrthof(l, r, b, t, n, f) gl2Ortho(l, r, b, t, n, f)
#define glFrustumf(l, r, b, t, n, f) gl2Frustum(l, r, b, t, n, f)
#define glPushMatrix gl2PushMatrix
#define glPopMatrix gl2PopMatrix
#define glMatrixMode(m) gl2MatrixMode(m)
#define glLoadIdentity gl2LoadIdentity
#define glLoadMatrixf(m) gl2LoadMatrix(m)
#define glMultMatrixf(m) gl2MultMatrix(m)
#define glPushAttrib(m) gl2PushAttrib(m)
#define glPopAttrib gl2PopAttrib
#define glOrtho glOrthof
#define glGetDoublev(m, p) glGetFloatv(m, p)
#define glPointParameteri(t, v) glPointParameterf(t, v)
#define glColor4fv(v) gl2Color4(v[0], v[1], v[2], v[3])
#define glColor4f(r, g, b, a) gl2Color4(r, g, b, a)
#define glPointSize(s) gl2PointSize(s)
#define glEnableClientState(c) gl2EnableClientState(c)
#define glDisableClientState(c) gl2DisableClientState(c)
#define glVertexPointer(size, type, stride, ptr) gl2VertexPointer(size, type, stride, ptr)
#define glNormalPointer(type, stride, ptr) gl2NormalPointer(type, stride, ptr)
#define glColorPointer(size, type, stride, ptr) gl2ColorPointer(size, type, stride, ptr)
#define glTexCoordPointer(size, type, stride, ptr) gl2TexCoordPointer(size, type, stride, ptr)
#define glShadeModel(m) gl2ShadeModel(m)
#define glAlphaFunc(f, r) gl2AlphaFunc(f, r)
#define glFogf(e, v) gl2Fogf(e, v)
#define glFogfv(e, p) gl2Fogfv(e, p)
#define glFogi(e, v) gl2Fogi(e, v)
#define glFogiv(e, p) gl2Fogiv(e, p)

#endif
