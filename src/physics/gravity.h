#ifndef KARIN_PHYSICS_GRAVITY_H
#define KARIN_PHYSICS_GRAVITY_H

#include "nl_std.h"

#define GAME_G 980.0

// 重力加速位移
float Physics_GetFalldownDistance(float speed, float g, float time);
float Physics_GetJumpSpeed(float speed, float g, float time);
float Physics_GetGravityPositionH(float speed, const nl_vector3_t *start_pos, const nl_vector3_t *last_pos, float x_dir, float y_dir, long long delta_time, int gravity, nl_vector3_t *new_pos, float *rx, float *ry);
float Physics_GetGravityPosition(float speed, const nl_vector3_t *start_pos, const nl_vector3_t *last_pos, float x_dir, float y_dir, long long delta_time, int gravity, nl_vector3_t *new_pos, float *rx, float *ry);

#endif
