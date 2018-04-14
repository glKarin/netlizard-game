#ifndef KARIN_GAMEPARTUCLE_H
#define KARIN_GAMETPARTUCLEH

#include "nl_gl.h"
#include "nl_std.h"

typedef enum _particle_effect_type
{
	trace_particle_type = 0,
	boom_particle_type,
	blood_spot_particle_type,
	blood_block_particle_type,
	gunfire_particle_type,
	other_particle_type,
	track_particle_type,
	track2_particle_type,
	blood_particle_type,
	grenade_particle_type,
	other_3d_particle_type
} particle_effect_type;

typedef enum _particle_movement_type
{
	fixed_particle_type,
	straight_particle_type,
	parabola_particle_type
} particle_movement_type;

typedef struct _particle_spirit
{
	GL_NETLizard_Spirit *spirit;
	GL_NETLizard_3D_Model *spirit_3d;
	particle_effect_type *types;
	GLuint type_count;
} particle_spirit;

typedef struct _particle
{
	particle_effect_type type;
	particle_movement_type movement_type;
	GLfloat start_pos[3];
	GLfloat last_pos[3];
	GLfloat pos[3];
	GLfloat x_angle;
	GLfloat y_angle;
	GLfloat x_dir;
	GLfloat y_dir;
	GLfloat speed;
	long long time;
	long long interval;
	GLboolean collision;
	GLboolean finished;
} particle;

GLint Particle_GetSpiritIndexByType(particle_spirit *spirit, particle_effect_type t);
particle_spirit * new_particle_spirit(particle_spirit *sp);
void delete_particle_spirit(particle_spirit *p);
void Particle_RanderParitcle(particle_spirit *p, particle_effect_type type);
void Particle_UpdateParticle(const GL_NETLizard_3D_Model *model, particle *p, long long game_time);
particle Particle_MakeParticle(particle_effect_type type, particle_movement_type movetype, GLfloat x, GLfloat y, GLfloat z, GLfloat xr, GLfloat yr, GLfloat xdir, GLfloat ydir, GLfloat s, long long time, long long interval, GLboolean collision);

#endif
