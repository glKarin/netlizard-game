#ifndef KARIN_NETLIZARD_3D_H
#define KARIN_NETLIZARD_3D_H

#include "netlizard.h"

#define CT3D_LEVEL 10
#define CT3DEP2_LEVEL 9
#define RE3D_LEVEL 7
#define EGYPT3D_LEVEL 19
#define CLONE3D_LEVEL 12
#define CT3DEP3_LEVEL 15
#define SPECNAZ3D_LEVEL 10

#define LVL_CODE 1819700224 // lvl
#define O_SPLASH_O_CODE 1865379584 // o/o

#define CLONE3D_TEX_COUNT 57
#define CT3D_TEX_COUNT 72
#define EGYPT3D_TEX_COUNT 58 // 50
#define SPECNAZ3D_TEX_COUNT 56 // 39
#define CT3DEP2_TEX_COUNT 52 // 55
#define CT3DEP3_TEX_COUNT 52 // 55

#define CLONE3D_TEX_SUBFIX "w/w%d.png"
#define CT3D_TEX_SUBFIX "tex/l%d.png"
#define CT3DEP2_TEX_SUBFIX "w/l%d.png"
#define SPECNAZ3D_TEX_SUBFIX "w/w%d.png"
#define EGYPT3D_TEX_SUBFIX "w/w%d.png"
#define CT3DEP3_TEX_SUBFIX "w/l%d.png"

#define CT3D_SKY_FILE "sky_0.png"
#define CT3DEP2_SKY_FILE "s.png"
#define CT3DEP3_SKY_FILE "s.png"
#define SPECNAZ3D_SKY_FILE "s.png"
#define RE3D_SKY_FILE "sky.png"

#define ROLE_FILE_SUBFIX "un%d.png"
#define V3_FP_FILE_SUBFIX "fp%d.png"
#define LEVEL_FILE_SUBFIX "lvl%d.png"
#define RE3D_CAR_FILE_SUBFIX "car%d.png"
#define RE3D_LEVEL_FILE_SUBFIX "track0%d.png"

#define SUBFIX_LENGTH 12
#define SKYFILE_LENGTH 10

#define CLONE3D_OBJ_SUBFIX "o/o%d.png"
#define CT3D_OBJ_SUBFIX "obj/obj%d.png"
#define CT3DEP2_OBJ_SUBFIX "o/o%d.png"
#define SPECNAZ3D_OBJ_SUBFIX "o/o%d.png"
#define EGYPT3D_OBJ_SUBFIX "o/o%d.png"
#define CT3DEP3_OBJ_SUBFIX "o/o%d.png"

extern const int Game_Count;
extern const char *Game_Names[];
extern const int Game_Level[];

extern const char *CT3D_Level[];
extern const char *Specnaz3D_Level[];
extern const char *CT3DEp2_Level[];
extern const char *Egypt3D_Level[];
extern const char *Clone3D_Level[];
extern const char *RE3D_Level[];
extern const char *CT3DEp3_Level[];
extern const char **Game_Level_Name[];

extern char * game_resource_path[nl_total_game];

// 变量命名规则
/*
 * array 数组
 * int int型
 * short short型
 * byte byte型
 *
 * scene 场景
 * item 物品
 * role 角色动画
 *
 * vertex 顶点坐标
 * primitive 图元（顶点索引，纹理坐标索引，纹理索引，法线）
 * plane 平面（法线索引，顶点索引）
 * aabb AABB盒子（最大， 最小）
 * begin 场景中物品起始索引
 * end 场景中物品最后索引
 * translation 位置移动
 * rotation 角度旋转
 * obj 物品索引
 */

typedef enum _NETLizard_3D_Item_Type
{
	Item_Other_Type = 0,
	Item_Tiny_Type = 1,
	Item_2D_Type = 1 << 1,
	Item_FanV_Type = 1 << 2,
	Item_FanH_Type = 1 << 3,
	Item_Role_Type = 1 << 4,
	Item_Box_Type = 1 << 5,
	Item_DoorV_Type = 1 << 6,
	Item_DoorH_Type = 1 << 7,
	Item_Elevator_Type = 1 << 8,
	Item_Ladder_Type = 1 << 9,
	Item_Weapon_Type = 1 << 10,
	Item_Skyline_Type = 1 << 11,
	Item_Portal_Type = 1 << 12,
	Item_Switcher_Type = 1 << 13
} NETLizard_3D_Item_Type;

typedef enum _NETLizard_3D_Animation_Type
{
	Animation_Idle_Type = 0,
	Animation_Walk_Type = 1,
	Animation_Run_Type = 2,
	Animation_Fighting1_Type = 3,
	Animation_Fighting2_Type = 4,
	Animation_Attack1_Type = 5,
	Animation_Attack2_Type = 6,
	Animation_Dead1_Type = 7,
	Animation_Dead2_Type = 8,
	Animation_Total_Type = 9,
	Animation_Unknow_Type
} NETLizard_3D_Animation_Type;

typedef enum _NETLizard_Texture_Type
{
	Texture_NormalPNG_Type = 0,
	Texture_EncodePNG_Type,
	Texture_3DEngineV2_Type,
	Texture_3DEngineV3_Type,
	Texture_3DEngineV3Compress_Type,
	Texture_Unknow_Type
} NETLizard_Texture_Type;

typedef enum _NETLizard_3D_Model_Type
{
	CT_3D_Map = 0,
	CT_3D_Item,
	CT_3D_Ep2_Map,
	CT_3D_Ep2_Item,
	Army_Ranger_3D_Map,
	Army_Ranger_3D_Item,
	Egypt_3D_Map,
	Egypt_3D_Item,
	Egypt_3D_Role,
	Clone_3D_Map,
	Clone_3D_Item,
	Clone_3D_Role,
	CT_3D_Ep3_Map,
	CT_3D_Ep3_Item
} NETLizard_3D_Model_Type;

typedef struct _NETLizard_BSP_Tree_Node
{
	int direction;
	int plane[4][3];
	int prev_scene;
	int next_scene;
	int normal[3];
} NETLizard_BSP_Tree_Node;

typedef struct _NETLizard_3D_Plane
{
	int position[3];
	int normal[3];
} NETLizard_3D_Plane;

typedef struct _NETLizard_3D_Primitive
{
	unsigned int index[3];
	unsigned int texcoord[6];
	int tex_index;
	NETLizard_3D_Plane plane;
} NETLizard_3D_Primitive;

typedef struct _NETLizard_3D_Mesh
{
	int ortho[6];
	array *vertex;
	array *plane;
	array *primitive;
	unsigned int item_index_range[2];
	array *bsp;
} NETLizard_3D_Mesh;

typedef struct _NETLizard_3D_Item_Mesh
{
	int pos[3];
	int angle[2];
	unsigned int obj_index;
	NETLizard_3D_Mesh item_mesh;
} NETLizard_3D_Item_Mesh;

typedef struct _NETLizard_3D_Model
{
	NETLizard_3D_Model_Type game;
	int start_pos[3];
	int start_angle[2];
	array *data;
	array *item_data;
	int has_sky;
	array *bsp_data;
} NETLizard_3D_Model;

void delete_NETLizard_3D_Mesh(NETLizard_3D_Mesh *mesh);
void delete_NETLizard_3D_Item_Mesh(NETLizard_3D_Item_Mesh *mesh);
void delete_NETLizard_3D_Model(NETLizard_3D_Model *model);
NETLizard_Texture_Type nlCheckPNGType(const array *data);
NETLizard_Texture_Type nlCheckPNGFileType(const char *file);
const char * nlGetAnimationName(NETLizard_3D_Animation_Type anim);
int nlGetItemType(game_name game, int index);
int nlGetAnimationBeginAndEnd(game_name game, int index, int animation[]);

void nlSetResourcePath(game_name name, const char *path);
int nlCheckLevelIsAvailable(game_name game, int level);

#endif
