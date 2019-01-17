#include "weapon.h"
#include "nl_std.h"
#include "game_util.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

const char *Weapon_Name[total_weapon_model_type] = {
	"Dagger", "USP", "Python", "Desert Eagle", "MP5", "M4a1", "AK47", "D3AU-1", "AWP", "Flash Grenade", "Fragmentation Grenade", 
	"SPECNAZ Dagger", "SPECNAZ Desert Eagle", "SPECNAZ MP5", "SPECNAZ M4", "SPECNAZ AK47", "M32", "SPECNAZ Fragmentation Grenade",
	"SOILDER Dagger", "SOILDER Colt Walker", "MP-40", "Mosin Nagant", "SOILDER AK47", "Plasma Gun", "The Sword of Osiris",
	"Colt Walker", "SPAS-12", "M16", "Rocket Launcher",
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

const char *Weapon_Type_Name[long_attack_type] = {
	"Dagger", NULL, "Pistol Gun", "Shot Gun", "Mini-Submachine-Gun", "Automatic Rifle Gun", "Sniper Gun", "Machine Gun", "Launcher Gun", "Rocket Launcher Gun", "Grenade", "Flash Grenade", "Smoke Grenade"
};

typedef struct _weapon_model_resource
{
	weapon_attack_type type;
	weapon_model_type model_type;
	char *mesh_file;
	int mesh_index;
	char *fp_file;
	float shot_range;
	int ammo_count;
	int ammo_total_count;
	int damage;
	float hit_rate;
	float firing_rate;
	float reload_time;
	float speed;
	float boom_range;
	float boom_damage_attenuation;
	float damage_attenuation;
	unsigned int shell_count;
	float length;
} weapon_model_resource;

static game_weapon_model *weapon_models = NULL;
static int weapon_models_loaded = 0;

static const weapon_model_resource Weapon_Model_Resource[total_weapon_model_type] = {
	// ct 3d
	{dagger_type, ct3d_Dagger, NULL, -1, _KARIN_GAME_DIR"ct3dep2/h0.png", 150, 1, 1, 40, 0.0, 1.0, 0.0, 8000, 0, 0, 0, 1, 0},
	{pistol_gun_type, ct3d_USP, NULL, -1, _KARIN_GAME_DIR"ct3dep2/h1.png", 60000, 12, 48, 15, 0.01, 2.5, 2.0, 18000, 0, 0, 0, 1, 60},
	{pistol_gun_type, ct3d_Python, _KARIN_GAME_DIR"ct3dep2/o/o1.png", 1, _KARIN_GAME_DIR"ct3dep2/h2.png", 70000, 6, 42, 25, 0.15, 1.2, 3.0, 21000, 0, 0, 0, 1, 60},
	{pistol_gun_type, ct3d_Desert_Eagle, _KARIN_GAME_DIR"ct3dep2/o/o2.png", 2, _KARIN_GAME_DIR"ct3dep2/h3.png", 80000, 7, 42, 30, 0.2, 1.0, 2.0, 23000, 0, 0, 0, 1, 60},
	{mini_submachine_gun_type, ct3d_MP5, _KARIN_GAME_DIR"ct3dep2/o/o3.png", 3, _KARIN_GAME_DIR"ct3dep2/h4.png", 75000, 30, 90, 15, 0.05, 3.0, 2.0, 20000, 0, 0, 0, 1, 150},
	{automatic_rifle_type, ct3d_M4a1, _KARIN_GAME_DIR"ct3dep2/o/o4.png", 4, _KARIN_GAME_DIR"ct3dep2/h5.png", 100000, 30, 90, 20, 0.08, 2.8, 2.0, 24000, 0, 0, 0, 1, 180},
	{automatic_rifle_type, ct3d_AK47, _KARIN_GAME_DIR"ct3dep2/o/o5.png", 5, _KARIN_GAME_DIR"ct3dep2/h6.png", 100000, 30, 90, 23, 0.1, 2.5, 2.0, 25000, 0, 0, 0, 1, 180},
	{sniper_rifle_type, ct3d_D3AU1, _KARIN_GAME_DIR"ct3dep2/o/o6.png", 6, _KARIN_GAME_DIR"ct3dep2/h7.png", 120000, 10, 30, 40, 0.3, 1.5, 3.0, 30000, 0, 0, 0, 1, 200},
	{sniper_rifle_type, ct3d_AWP, _KARIN_GAME_DIR"ct3dep2/o/o7.png", 7, _KARIN_GAME_DIR"ct3dep2/h8.png", 150000, 10, 40, 60, 1.0, 0.5, 3.0, 40000, 0, 0, 0, 1, 200},
	{flash_flares_type, ct3d_Flash_Grenade, _KARIN_GAME_DIR"ct3dep2/o/o44.png", -1, _KARIN_GAME_DIR"ct3dep2/h9.png", 6000, 1, 3, 0.0, 1.0, 0.4, 1.0, 4000, 1000, 0.1, 0, 1, 0},
	{grenades_type, ct3d_Fragmentation_Grenade, _KARIN_GAME_DIR"ct3dep2/o/o44.png", 44, _KARIN_GAME_DIR"ct3dep2/h10.png", 6000, 1, 3, 50, 1.0, 0.4, 1.0, 4000, 400, 0.25, 0, 1, 0},
	// specnaz 3d
	{dagger_type, specnaz3d_Dagger, NULL, 44, _KARIN_GAME_DIR"specnaz3d/h0.png", 180, 1, 1, 45, 0.0, 1.0, 0.0, 8000, 0, 0, 0, 1, 0},
	{pistol_gun_type, specnaz3d_Desert_Eagle, _KARIN_GAME_DIR"specnaz3d/o/o1.png", 1, _KARIN_GAME_DIR"specnaz3d/h1.png", 80000, 7, 42, 32, 0.2, 1.2, 2.0, 23000, 0, 0, 0, 1, 60},
	{mini_submachine_gun_type, specnaz3d_MP5, _KARIN_GAME_DIR"specnaz3d/o/o2.png", 2, _KARIN_GAME_DIR"specnaz3d/h2.png", 75000, 30, 120, 16, 0.05, 3.2, 2.0, 20000, 0, 0, 0, 1, 150},
	{automatic_rifle_type, specnaz3d_M4a1, _KARIN_GAME_DIR"specnaz3d/o/o3.png", 3, _KARIN_GAME_DIR"specnaz3d/h3.png", 100000, 30, 120, 21, 0.08, 3.0, 2.0, 24000, 0, 0, 0, 1, 180},
	{automatic_rifle_type, specnaz3d_AK47, _KARIN_GAME_DIR"specnaz3d/o/o4.png", 4, _KARIN_GAME_DIR"specnaz3d/h4.png", 100000, 30, 120, 25, 0.1, 2.7, 2.0, 25000, 0, 0, 0, 1, 180},
	{launcher1_gun_type, specnaz3d_M32, _KARIN_GAME_DIR"specnaz3d/o/o5.png", 5, _KARIN_GAME_DIR"specnaz3d/h5.png", 30000, 6, 42, 50, 0.5, 1.0, 3.5, 6000, 300, 0.2, 0, 1, 180},
	{grenades_type, specnaz3d_Fragmentation_Grenade, _KARIN_GAME_DIR"ct3dep2/o/o44.png", 44, _KARIN_GAME_DIR"specnaz3d/h6.png", 6000, 1, 6, 50, 1.0, 0.4, 1.0, 4000, 400, 0.25, 0, 1, 0},
	// egypt 3d
	{dagger_type, egypt3d_Dagger, NULL, -1, _KARIN_GAME_DIR"egypt3d/fp0.png", 150, 1, 1, 30, 0.0, 1.0, 0.0, 8000, 0, 0, 0, 1, 0},
	{pistol_gun_type, egypt3d_Colt_Walker, _KARIN_GAME_DIR"egypt3d/o/o24.png", 24, _KARIN_GAME_DIR"egypt3d/fp1.png", 75000, 9, 81, 18, 0.1, 2.0, 2.0, 20000, 0, 0, 0, 1, 60},
	{shot_gun_type, egypt3d_MP40, _KARIN_GAME_DIR"egypt3d/o/o25.png", 25, _KARIN_GAME_DIR"egypt3d/fp2.png", 50000, 5, 55, 30, 0.2, 1.0, 3.0, 19000, 0, 0, 0, 3, 180},
	{mini_submachine_gun_type, egypt3d_Mosin_Nagant, _KARIN_GAME_DIR"egypt3d/o/o26.png", 34, _KARIN_GAME_DIR"egypt3d/fp3.png", 80000, 30, 120, 20, 0.08, 3.0, 2.0, 23000, 0, 0, 0, 1, 160},
	{automatic_rifle_type, egypt3d_AK47, _KARIN_GAME_DIR"egypt3d/o/o27.png", 27, _KARIN_GAME_DIR"egypt3d/fp4.png", 100000, 30, 120, 25, 0.15, 2.8, 2.0, 25000, 0, 0, 0, 1, 180},
	{launcher2_gun_type, egypt3d_Plasma_Gun, _KARIN_GAME_DIR"egypt3d/o/o28.png", 28, _KARIN_GAME_DIR"egypt3d/fp5.png", 50000, 10, 60, 35, 0.5, 1.0, 3.0, 15000, 50, 0.15, 0, 1, 160},
	{dagger_type, egypt3d_The_Sword_of_Osiris, _KARIN_GAME_DIR"egypt3d/o/o29.png", 29, _KARIN_GAME_DIR"egypt3d/fp8.png", 200, 1, 1, 50, 0.0, 1.0, 0.0, 8000, 0, 0, 0, 1, 0},
	// clone 3d
	{pistol_gun_type, clone3d_Colt_Walker, _KARIN_GAME_DIR"clone3d/o/o52.png", 52, _KARIN_GAME_DIR"clone3d/fp1.png", 75000, 9, 81, 18, 0.1, 2.0, 2.0, 20000, 0, 0, 0, 1, 60},
	{shot_gun_type, clone3d_SPAS12, _KARIN_GAME_DIR"clone3d/o/o53.png", 53, _KARIN_GAME_DIR"clone3d/fp2.png", 50000, 5, 55, 20, 0.3, 1.0, 3.0, 18000, 0, 0, 0, 5, 160},
	{automatic_rifle_type, clone3d_M16, _KARIN_GAME_DIR"clone3d/o/o54.png", 54, _KARIN_GAME_DIR"clone3d/fp3.png", 100000, 30, 120, 25, 0.1, 3.0, 2.0, 25000, 0, 0, 0, 1, 180},
	{launcher2_gun_type, clone3d_Rocket_Launcher, _KARIN_GAME_DIR"clone3d/o/o55.png", 55, _KARIN_GAME_DIR"clone3d/fp4.png", 100000, 5, 35, 50, 0.5, 1.0, 3.0, 15000, 300, 0.2, 0, 1, 200},
	// egypt 3d monster
	{short_attack_type, egypt3d_Worm_Weapon, NULL, -1, NULL, 500, 1, 1, 20, 0.0, 1.0, 0.0, 6000, 0, 0, 0, 1, 0},
	{long_attack_type, egypt3d_Scorpion_Weapon, NULL, -1, NULL, 8000, -1, -1, 20, 0.1, 1.5, 0.0, 4000, 0, 0, 0, 1, 0},
	{short_attack_type, egypt3d_Fly_Fish_Weapon, NULL, -1, NULL, 500, 1, 1, 20, 0.0, 1.2, 0.0, 5000, 0, 0, 0, 1, 0},
	{short_attack_type, egypt3d_Anubis_Weapon, NULL, -1, NULL, 600, 1, 1, 35, 0.0, 1.5, 0.0, 10000, 0, 0, 0, 1, 0},
	{short_attack_type, egypt3d_Tentacle_Weapon, NULL, -1, NULL, 800, 1, 1, 30, 0.0, 1.2, 0.0, 4000, 0, 0, 0, 1, 0},
	{long_attack_type, egypt3d_Machine_Monster_Weapon, NULL, 80000, NULL, -1, 1, -1, 25, 0.1, 1.2, 0.0, 7500, 0, 0, 0, 1, 0},
	{long_attack_type, egypt3d_Fly_Machine_Weapon, NULL, -1, NULL, 75000, 1, -1, 30, 0.1, 1.0, 0.0, 7500, 0, 0, 0, 1, 0},
	// clone 3d robot
	{long_attack_type, clone3d_Machine_Weapon, NULL, -1, NULL, 80000, 1, -1, 15, 0.15, 2.3, 1.5, 25000, 0, 0, 0, 1, 0}
};

weapon * new_weapon(weapon *w, weapon_model_type type) 
{
	RETURN_PTR(wp, w, weapon);

		const weapon_model_resource *r = Weapon_Model_Resource + type;
	wp->weapon_index = type;

	wp->model = weapon_models_loaded ? weapon_models + type : NULL;
	wp->shot_range = r->shot_range;
	wp->type = r->type;
	wp->firing_rate = r->firing_rate;
	wp->damage = r->damage;
	wp->ammo_count = r->ammo_count;
	wp->ammo_total_count = r->ammo_total_count;
	wp->ammo_total_count_limit = wp->ammo_total_count;
	wp->reload_time = r->reload_time;
	wp->speed = r->speed;
	wp->hit_rate = r->hit_rate;
	wp->damage_attenuation = r->damage_attenuation;
	wp->boom_range = r->boom_range;
	wp->boom_damage_attenuation = r->boom_damage_attenuation;
	wp->length = r->length;
	wp->shell_count = r->shell_count;

	wp->status = ready_type;
	wp->firing_progress = 0.0;
	wp->time = 0;
	if(wp->ammo_count > 0)
		wp->ammo = wp->ammo_count;
	else
		wp->ammo = 1;

	return wp;
}

void delete_weapon(weapon *wp)
{
	if(!wp)
		return;
	wp->model = NULL;
}

bullet * Game_WeaponFire(bullet bt[], const weapon *wp, float w, int character_index, int group, unsigned int *count)
{
	if(!wp || !count)
		return NULL;

	if(wp->status != firing_type)
		return NULL;

	bullet *b = NULL;
	if(!bt)
		b = NEW_II(bullet, wp->shell_count);
	else
		b = bt;

	if(count)
		*count = wp->shell_count;

	bullet_type type;
	if(wp->type <= short_attack_type)
		type = no_bullet_type;
	else if(wp->type >= launcher1_gun_type && wp->type <= launcher2_gun_type)
		type = shell_bullet_type;
	else if(wp->type >= grenades_type && wp->type <= smoke_bomb_type)
		type = grenade_bullet_type;
	else
		type = normal_bullet_type;

	unsigned int i;
	for(i = 0; i < wp->shell_count; i++)
	{
		int o = (int)floor((SHOTGUN_ANGLE_MAX_OFFSET - SHOTGUN_ANGLE_MIN_OFFSET) * 100);

		float x = wp->x_angle;
		float y = wp->y_angle;

		if(i != 0)
		{
			int r = rand() % (o * 2) - o;
			x = Algo_FormatAngle(wp->x_angle + ((float)r / 100.0));
			r = rand() % (o * 2) - o;
			y = Algo_FormatAngle(wp->y_angle + ((float)r / 100.0));
		}
		nl_vector3_t wpos = {wp->position[0], wp->position[1], wp->position[2]};
		nl_vector3_t dir = Algo_ComputeDirection(y, x);
		Vector3_Inverse(&dir);
		dir = Vector3_Scale(&dir, w);
		dir = Vector3_PlusVector3(&wpos, &dir);
		float len = wp->length;
		if(wp->type == pistol_gun_type || wp->type == grenades_type || wp->type == flash_flares_type || wp->type == smoke_bomb_type || wp->type <= short_attack_type)
			len += w;

		new_bullet(b + i, dir.x, dir.y, dir.z, x, y, wp->time, wp->speed, wp->damage, wp->damage_attenuation, wp->boom_range, wp->boom_damage_attenuation, wp->shot_range, 
				wp->type == launcher1_gun_type || wp->type == grenades_type || wp->type == flash_flares_type || wp->type == smoke_bomb_type ? 1 : 0/*gravity*/, type, //流弹炮 手雷需要计算重力加速度
				character_index, group, len);
	}
	return b;
}

void Game_LoadWeaponModel(void)
{
	if(weapon_models_loaded)
		return;
	weapon_models = NEW_II(game_weapon_model, total_weapon_model_type);
	int i;
	for(i = 0; i < total_weapon_model_type; i++)
	{
		const weapon_model_resource *r = Weapon_Model_Resource + i;

		if(r->mesh_file == NULL)
			weapon_models[i].tp_model = NULL;
		else
		{
			if(i <= ct3d_Flash_Grenade)
			{
				weapon_models[i].tp_model = NETLizard_ReadGLCT3DEp2ItemModelFile(r->mesh_file, r->mesh_index);
				if(weapon_models[i].tp_model)
				{
					weapon_models[i].position[1] = 0.0 - (weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[1] - weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[4]) / 2;
					weapon_models[i].position[2] = 0.0 - (weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[2] - weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[5]) / 2;
				}
			}
			else if(i >= specnaz3d_Dagger && i <= specnaz3d_Fragmentation_Grenade)
			{
				weapon_models[i].tp_model = NETLizard_ReadGLSpecnaz3DItemModelFile(r->mesh_file, r->mesh_index);
				if(weapon_models[i].tp_model)
				{
					weapon_models[i].position[1] = 0.0 - (weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[1] - weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[4]) / 2;
					weapon_models[i].tp_model->item_meshes[0].angle[1] = 180.0;
				}
			}
			else if(i >= egypt3d_Dagger && i <= egypt3d_The_Sword_of_Osiris)
			{
				weapon_models[i].tp_model = NETLizard_ReadGLEgypt3DItemModelFile(r->mesh_file, r->mesh_index);
				if(weapon_models[i].tp_model)
				{
					weapon_models[i].position[1] = 0.0 - (weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[1] - weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[4]) / 2;
					weapon_models[i].tp_model->item_meshes[0].angle[1] = 180.0;
				}
			}
			else if(i >= clone3d_Colt_Walker && i <= clone3d_Rocket_Launcher)
			{
				weapon_models[i].tp_model = NETLizard_ReadGLClone3DItemModelFile(r->mesh_file, r->mesh_index);
				if(weapon_models[i].tp_model)
				{
					weapon_models[i].position[1] = 0.0 - (weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[1] - weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[4]) / 2;
					weapon_models[i].position[2] = 0.0 - (weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[2] - weapon_models[i].tp_model->item_meshes[0].item_mesh.ortho[5]) / 2;
				}
			}
		}

		if(r->fp_file == NULL)
			weapon_models[i].fp_tex = NULL;
		else
		{
			if(i <= ct3d_Flash_Grenade)
				weapon_models[i].fp_tex = new_texture_from_nl_v2_3d_file(r->fp_file);
			else if(i >= specnaz3d_Dagger && i <= specnaz3d_Fragmentation_Grenade)
				weapon_models[i].fp_tex = new_texture_from_nl_v2_3d_file(r->fp_file);
			else if(i >= egypt3d_Dagger && i <= egypt3d_The_Sword_of_Osiris)
				weapon_models[i].fp_tex = new_texture_from_nl_v3_3d_compress_file(r->fp_file);
			else if(i >= clone3d_Colt_Walker && i <= clone3d_Rocket_Launcher)
				weapon_models[i].fp_tex = new_texture_from_nl_v3_3d_compress_file(r->fp_file);
		}

		weapon_models[i].scale = 1.0;
		weapon_models[i].x_offset = 90.0;
	}
	weapon_models_loaded = 1;
}

void Game_FreeWeaponModel(void)
{
	if(weapon_models_loaded == 0)
		return;
	int i;
	for(i = 0; i < total_weapon_model_type; i++)
	{
		if(weapon_models[i].fp_tex)
		{
			if(glIsTexture(weapon_models[i].fp_tex->texid))
				glDeleteTextures(1, &weapon_models[i].fp_tex->texid);
			free(weapon_models[i].fp_tex);
		}
		if(weapon_models[i].tp_model)
		{
			delete_GL_NETLizard_3D_Model(weapon_models[i].tp_model);
			free(weapon_models[i].tp_model);
		}
	}
	FREE_PTR(weapon_models)
	weapon_models_loaded = 0;
}

weapon_model_type Game_RandLongWeapon(void)
{
	const weapon_model_type Types[] = {
		ct3d_MP5,
		ct3d_M4a1,
		ct3d_AK47,
		ct3d_D3AU1,
		ct3d_AWP,
		specnaz3d_MP5,
		specnaz3d_M4a1,
		specnaz3d_AK47,
		specnaz3d_M32,
		egypt3d_MP40,
		egypt3d_Mosin_Nagant,
		egypt3d_AK47,
		egypt3d_Plasma_Gun,
		clone3d_SPAS12, 
		clone3d_M16,
		clone3d_Rocket_Launcher,
	};
	return Types[rand() % (countof(Types))];
}

weapon_model_type Game_RandHeavyWeapon(void)
{
	const weapon_model_type Types[] = {
		ct3d_D3AU1,
		ct3d_AWP,
		specnaz3d_M32,
		egypt3d_Plasma_Gun,
		clone3d_Rocket_Launcher,
	};
	return Types[rand() % (countof(Types))];
}

weapon_model_type Game_RandLightWeapon(void)
{
	const const weapon_model_type Types[] = {
		ct3d_MP5,
		ct3d_M4a1,
		ct3d_AK47,
		specnaz3d_MP5,
		specnaz3d_M4a1,
		specnaz3d_AK47,
		egypt3d_MP40,
		egypt3d_Mosin_Nagant,
		egypt3d_AK47,
		clone3d_SPAS12, 
		clone3d_M16,
	};
	return Types[rand() % (countof(Types))];
}

weapon_model_type Game_RandKnifeWeapon(void)
{
	const weapon_model_type Types[] = {
		ct3d_Dagger,
		specnaz3d_Dagger,
		egypt3d_Dagger,
		egypt3d_The_Sword_of_Osiris,
	};
	return Types[rand() % (countof(Types))];
}

weapon_model_type Game_RandPistolWeapon(void)
{
	const weapon_model_type Types[] = {
		ct3d_USP,
		ct3d_Python,
		ct3d_Desert_Eagle,
		specnaz3d_Desert_Eagle,
		egypt3d_Colt_Walker,
		clone3d_Colt_Walker,
	};
	return Types[rand() % (countof(Types))];
}

weapon_model_type Game_RandGrenadeWeapon(void)
{
	const weapon_model_type Types[] = {
		ct3d_Flash_Grenade,
		ct3d_Fragmentation_Grenade,
		specnaz3d_Fragmentation_Grenade,
	};
	return Types[rand() % (countof(Types))];
}

int Game_Rand4WeaponTypes(weapon_model_type wps[], unsigned int max, unsigned mask)
{
	if(!wps || max < 4)
		return -1;
	if(mask == 0)
		return 0;
	int ret = 0;
	if(mask & fighting_weapon)
	{
		wps[FIGHTING_WEAPON_INDEX] = Game_RandKnifeWeapon();
		ret |= fighting_weapon;
	}
	if(mask & secondary_weapon)
	{
		wps[SECONDARY_WEAPON_INDEX] = Game_RandPistolWeapon();
		ret |= secondary_weapon;
	}
	if(mask & main_weapon_1)
	{
		wps[MAIN_WEAPON_1_INDEX] = Game_RandLongWeapon();
		ret |= main_weapon_1;
	}
	if(mask & launch_weapon)
	{
		wps[LAUNCH_WEAPON_INDEX] = Game_RandGrenadeWeapon();
		ret |= launch_weapon;
	}
	return ret;
}

int Game_GetWeaponPosition(weapon_model_type type)
{
	switch(type){
		case ct3d_Dagger:
		case specnaz3d_Dagger:
		case egypt3d_Dagger:
		case egypt3d_The_Sword_of_Osiris:
			return FIGHTING_WEAPON_INDEX;
		case ct3d_USP:
		case ct3d_Python:
		case ct3d_Desert_Eagle:
		case specnaz3d_Desert_Eagle:
		case egypt3d_Colt_Walker:
		case clone3d_Colt_Walker:
			return SECONDARY_WEAPON_INDEX;
		case ct3d_MP5:
		case ct3d_M4a1:
		case ct3d_AK47:
		case ct3d_D3AU1:
		case ct3d_AWP:
		case specnaz3d_MP5:
		case specnaz3d_M4a1:
		case specnaz3d_AK47:
		case specnaz3d_M32:
		case egypt3d_MP40:
		case egypt3d_Mosin_Nagant:
		case egypt3d_AK47:
		case egypt3d_Plasma_Gun:
		case clone3d_SPAS12: 
		case clone3d_M16:
		case clone3d_Rocket_Launcher:
			return MAIN_WEAPON_1_INDEX;
		case ct3d_Flash_Grenade:
		case ct3d_Fragmentation_Grenade:
		case specnaz3d_Fragmentation_Grenade:
			return LAUNCH_WEAPON_INDEX;
		case egypt3d_Worm_Weapon:
		case egypt3d_Scorpion_Weapon:
		case egypt3d_Fly_Fish_Weapon:
		case egypt3d_Anubis_Weapon:
		case egypt3d_Tentacle_Weapon:
		case egypt3d_Machine_Monster_Weapon:
		case egypt3d_Fly_Machine_Weapon:
		case clone3d_Machine_Weapon:
		case total_weapon_model_type:
		default:
			return FIGHTING_WEAPON_INDEX;
	}
}
