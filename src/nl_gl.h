#ifndef KARIN_NL_GL_H
#define KARIN_NL_GL_H

#include "netlizard/netlizard_3d.h"
#include "gl_util.h"
#include "netlizard/racingevolution3d_reader.h"
#include "math3d/vector3.h"
#include "nl_std.h"

#define OPENGL_RENDER_VERTEX_DATA NL_MASK(0)
#define OPENGL_RENDER_VERTEX_BUFFER NL_MASK(1)

#define OPENGL_RENDER_VERTEX_USING_UNION 0

typedef texture * (*new_netlizard_texture_from_file)(const char *name);

texture * new_texture_from_nl_file(const char *name);
texture * new_texture_from_nl_v2_3d_file(const char *name);
texture * new_texture_from_nl_v3_3d_file(const char *name);
texture * new_texture_from_nl_v3_3d_compress_file(const char *name);

typedef struct _GL_RE3D_Mesh
{
	GLuint buffers[total_buffer_type];
	GLfloat translations[3];
	GLuint *strips;
	GLuint primitive;
	GLint tex_index;
	GLfloat ortho[6];
} GL_RE3D_Mesh;

typedef struct _GL_RE3D_Model
{
	GL_RE3D_Mesh *meshes;
	GLuint count;
	texture **texes;
	GLuint tex_count;
	texture *bg_tex;
} GL_RE3D_Model;

GL_RE3D_Model * NETLizard_MakeGL2RE3DModel(const RE3D_Model *model);
GLvoid delete_GL_RE3D_Model(GL_RE3D_Model *model);
GLvoid delete_GL_RE3D_Mesh(GL_RE3D_Mesh *mesh);
GLvoid NETLizard_RenderGLRE3DModel(const GL_RE3D_Model *model);
GLvoid NETLizard_RenderGLRE3DModelScene(const GL_RE3D_Model *model, GLint *scene, GLuint count);
GL_RE3D_Model * NETLizard_ReadGLRE3DModelFile(const char *name);
GL_RE3D_Model * NETLizard_ReadGLRE3DCarModelFile(const char *car_file, const char *tex_file);

typedef struct _GL_NETLizard_3D_Primitive
{
	GLuint index[3];
	GLfloat texcoord[6];
	GLfloat normal[3];
	GLint tex_index;
} GL_NETLizard_3D_Primitive; // UNUSED 2017 06 26

typedef struct _GL_NETLizard_3D_Plane
{
	GLfloat position[3];
	GLfloat normal[3];
} GL_NETLizard_3D_Plane;

typedef struct _GL_NETLizard_BSP_Tree_Node
{
	GLuint direction;
	GLfloat plane[4][3];
	GLint prev_scene;
	GLint next_scene;
	GLfloat normal[3];
} GL_NETLizard_BSP_Tree_Node;

typedef struct _GL_NETLizard_3D_Material
{
	GLint tex_index;
	GLuint index_start;
	GLuint index_count;
} GL_NETLizard_3D_Material;

typedef struct _GL_NETLizard_3D_Vertex
{
	GLfloat position[3];
	GLfloat normal[3];
	GLfloat texcoord[2];
} GL_NETLizard_3D_Vertex;

typedef struct _GL_NETLizard_3D_Vertex_Data
{
#if OPENGL_RENDER_VERTEX_USING_UNION
	GLuint gl;
#endif
	GLuint vertex_count;
	GLuint index_count;
	GL_NETLizard_3D_Vertex *vertex;
	GLushort *index;
} GL_NETLizard_3D_Vertex_Data;

typedef struct _GL_NETLizard_3D_Vertex_Buffer
{
#if OPENGL_RENDER_VERTEX_USING_UNION
	GLuint gl;
#endif
	GLuint vertex_count;
	GLuint index_count;
	GLuint vertex_buffer;
	GLuint index_buffer;
} GL_NETLizard_3D_Vertex_Buffer;

#if OPENGL_RENDER_VERTEX_USING_UNION
typedef union _GL_NETLizard_3D_Vertex_Array
#else
typedef struct _GL_NETLizard_3D_Vertex_Array
#endif
{
	GLuint gl;
	GL_NETLizard_3D_Vertex_Data vertex_data;
	GL_NETLizard_3D_Vertex_Buffer vertex_buffer;
} GL_NETLizard_3D_Vertex_Array;

typedef struct _GL_NETLizard_3D_Mesh
{
	GLuint count;
	GL_NETLizard_3D_Material *materials;
	GLint *tex_index;
	GL_NETLizard_3D_Vertex_Array vertex_array;
	GLuint plane_count;
	GL_NETLizard_3D_Plane *plane;
	GLfloat ortho[6];
	GLuint item_index_range[2];
	GLint *bsp;
	GLuint bsp_count;
} GL_NETLizard_3D_Mesh;

typedef struct _GL_NETLizard_3D_Item_Mesh
{
	GL_NETLizard_3D_Mesh item_mesh;
	GLfloat pos[3];
	GLfloat angle[2];
	GLint item_type;
} GL_NETLizard_3D_Item_Mesh;

typedef struct _GL_NETLizard_3D_Model
{
	GL_NETLizard_3D_Mesh *meshes;
	GLuint count;
	GL_NETLizard_3D_Item_Mesh *item_meshes;
	GLuint item_count;
	texture **texes;
	GLuint tex_count;
	texture *bg_tex;
	GLfloat start_pos[3];
	GLfloat start_angle[2];
	GL_NETLizard_BSP_Tree_Node *bsp_data;
	GLuint bsp_count;
} GL_NETLizard_3D_Model;

typedef struct _NETLizard_3D_Role_Animation
{
	GLuint begin;
	GLuint end;
	NETLizard_3D_Animation_Type type;
} NETLizard_3D_Role_Animation;

typedef struct _GL_NETLizard_3D_Animation_Model
{
	NETLizard_3D_Item_Type item_type;
	GL_NETLizard_3D_Mesh *meshes;
	GLuint count;
	texture *tex;
	NETLizard_3D_Role_Animation *animations;
	GLuint anim_count;
} GL_NETLizard_3D_Animation_Model;

typedef struct _GL_NETLizard_3D_Item_Model
{
	GL_NETLizard_3D_Mesh item_mesh;
	texture *tex;
} GL_NETLizard_3D_Item_Model;

GLvoid NETLizard_RenderGL3DModel(const GL_NETLizard_3D_Model *model);
GLvoid NETLizard_RenderGL3DItemModel(const GL_NETLizard_3D_Item_Model *m);
GLvoid NETLizard_RenderGL3DAnimationModel(const GL_NETLizard_3D_Animation_Model *m, GLuint anim, GLuint frame);
GLvoid NETLizard_RenderGL3DMapModelScene(const GL_NETLizard_3D_Model *model, GLint *scenes, GLuint count);

GLvoid delete_GL_NETLizard_3D_Mesh(GL_NETLizard_3D_Mesh *mesh);
GLvoid delete_GL_NETLizard_3D_Item_Mesh(GL_NETLizard_3D_Item_Mesh *mesh);
GLvoid delete_GL_NETLizard_3D_Model(GL_NETLizard_3D_Model *model);
GLvoid delete_GL_NETLizard_3D_Animation_Model(GL_NETLizard_3D_Animation_Model *model);

GL_NETLizard_3D_Model * NETLizard_MakeGL3DModel(const NETLizard_3D_Model *model);
GL_NETLizard_3D_Model * NETLizard_MakeGL3DItemModel(const NETLizard_3D_Model *model);
GL_NETLizard_3D_Animation_Model * NETLizard_MakeGL3DAnimationModel(const NETLizard_3D_Model *model);
GLvoid NETLizard_MakeGL23DModel(GL_NETLizard_3D_Model *model);
GLvoid NETLizard_MakeGL23DAnimationModel(GL_NETLizard_3D_Animation_Model *model);

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DMapModelFile(const char *name, int i);
GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DItemModelFile(const char *name, int index);

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DEp2MapModelFile(const char *name, int i);
GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DEp2ItemModelFile(const char *name, int index);

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DEp3MapModelFile(const char *name, int i);
GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DEp3ItemModelFile(const char *name, int index);

GL_NETLizard_3D_Model * NETLizard_ReadGLSpecnaz3DMapModelFile(const char *name, int level);
GL_NETLizard_3D_Model * NETLizard_ReadGLSpecnaz3DItemModelFile(const char *name, int index);

GL_NETLizard_3D_Model * NETLizard_ReadGLEgypt3DItemModelFile(const char *name, int index);
GL_NETLizard_3D_Model * NETLizard_ReadGLEgpyt3DMapModelFile(const char *name);
GL_NETLizard_3D_Animation_Model * NETLizard_ReadGLEgypt3DRoleModelFile(const char *name, int index);

GL_NETLizard_3D_Model * NETLizard_ReadGLClone3DMapModelFile(const char *name);
GL_NETLizard_3D_Model * NETLizard_ReadGLClone3DItemModelFile(const char *name, int index);
GL_NETLizard_3D_Animation_Model * NETLizard_ReadGLClone3DRoleModelFile(const char *name, int index);

GLvoid NETLizard_RenderGL3DMesh(const GL_NETLizard_3D_Mesh *m, texture **const texes);
GLvoid NETLizard_RenderGL3DItemMesh(const GL_NETLizard_3D_Mesh *m, const texture *tex);

typedef struct _GL_NETLizard_Font_Char
{
	GLuint buffers[total_buffer_type];
	GLfloat width;
	GLfloat height;
	GLfloat x_strip;
	GLfloat y_strip;
} GL_NETLizard_Font_Char;

typedef struct _GL_NETLizard_Font
{
	GL_NETLizard_Font_Char *char_map;
	GLuint char_map_count;
	GLbyte *offset;
	GLuint offset_count;
	GLuint char_count;

	GLboolean private_e;
  GLboolean private_l;
  GLboolean private_m;

	texture *tex;
} GL_NETLizard_Font;

GL_NETLizard_Font * NETLizard_ReadFont(const char *map_file, const char *tex_file);
GLvoid delete_GL_NETLizard_Font(GL_NETLizard_Font *fnt);
GLvoid NETLizard_RenderFontChar(const GL_NETLizard_Font *fnt, GLuint i);
GLint NETLizard_GetFontIndex(const GL_NETLizard_Font *fnt, int ch);

typedef struct _GL_NETLizard_Spirit_Cell
{
	GLuint buffers[total_buffer_type];
	GLfloat width;
	GLfloat height;
	GLfloat private_4;
	GLfloat private_5;
} GL_NETLizard_Spirit_Cell;

typedef struct _GL_NETLizard_Spirit
{
	texture *tex;
	GL_NETLizard_Spirit_Cell *spirits;
	GLuint spirit_count;
} GL_NETLizard_Spirit;

GL_NETLizard_Spirit * NETLizard_ReadSpirit(const char *map_file, const char *tex_file);
GLvoid delete_GL_NETLizard_Spirit(GL_NETLizard_Spirit *s);
GLvoid NETLizard_RenderSpirit(const GL_NETLizard_Spirit *s, GLuint i);

GLvoid NETLizard_MoveItemModel(GL_NETLizard_3D_Item_Mesh *dst, GL_NETLizard_3D_Item_Mesh *src);

#endif
