#ifndef KARIN_VECTOR_H
#define KARIN_VECTOR_H

#include "vector3.h"
#include "vector2.h"

#if 0
#define VECTOR_X(v) (v).v[0]
#define VECTOR_Y(v) (v).v[1]
#define VECTOR_Z(v) (v).v[2]
#define VECTOR_W(v) (v).v[3]

#define VECTORV_X(v) (v)->v[0]
#define VECTORV_Y(v) (v)->v[1]
#define VECTORV_Z(v) (v)->v[2]
#define VECTORV_W(v) (v)->v[3]

#define VECTOR3(x, y, z) { {x, y, z} }
#define VECTOR3V(v) { {v[0], v[1], v[2]} }

#define VECTOR2(x, y) { {x, y} }
#define VECTOR2V(v) { {v[0], v[1]} }
#else
#define VECTOR_X(v) (v).x
#define VECTOR_Y(v) (v).y
#define VECTOR_Z(v) (v).z
#define VECTOR_W(v) (v).w

#define VECTORV_X(v) (v)->x
#define VECTORV_Y(v) (v)->y
#define VECTORV_Z(v) (v)->z
#define VECTORV_W(v) (v)->w

#define VECTOR3(x, y, z) {x, y, z}
#define VECTOR3V(v) {v[0], v[1], v[2]}

#define VECTOR2(x, y) {x, y}
#define VECTOR2V(v) {v[0], v[1]}
#endif

#endif
