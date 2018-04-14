#ifndef KARIN_NETLIZARD_H
#define KARIN_NETLIZARD_H

#include <stddef.h>

#define NEW(T) malloc(sizeof(T))
#define NEW_II(T, size) calloc(size, sizeof(T))
#define ZERO(ptr, T) memset(ptr, 0, sizeof(T))
#define ZERO_II(ptr, T, size) memset(ptr, 0, sizeof(T) * size)

#define ENDL printf("\n");
#define KARIN_MAX(num1, num2) (((num1) > (num2)) ? (num1) : (num2))
#define KARIN_MIN(num1, num2) (((num1) < (num2)) ? (num1) : (num2))
#define KARIN_ABS(num) (((num) >= 0) ? (num) : (-(num)))

#define UNUSED(ptr) free(ptr); ptr = NULL;
#define UNPARSED 0

#define printfi(x) printf(#x" -> %d\n", x)
#define printfu(x) printf(#x" -> %u\n", x)
#define printfl(x) printf(#x" -> %ld\n", x)
#define printful(x) printf(#x" -> %lu\n", x)
#define printff(x) printf(#x" -> %f\n", x)
#define printfx(x) printf(#x" -> %x\n", x)
#define printfs(x) printf(#x" -> %s\n", x)
#define printfc(x) printf(#x" -> %c\n", x)
#define printfp(x) printf(#x" -> %p\n", x)
#define printf2f(x) printf(#x" -> %.2f\n", x)
#define printf1f(x) printf(#x" -> %.1f\n", x)
#define printfln(fmt, args...) printf(fmt"\n", ##args) 

#define nlprintf(fmt, args...) \
{ \
	if(nl_debug_mode) \
	{ \
		printf(fmt, ##args); \
	} \
}

typedef char byte; // unsigned
typedef unsigned int boolean;
#define _true 1
#define _false 0

typedef enum _datatype
{
	nl_byte = 1,
	nl_unsigned_byte,
	nl_short,
	nl_unsigned_short,
	nl_int,
	nl_unsigned_int,
	nl_long,
	nl_unsigned_long,
	nl_float,
	nl_double,
	nl_pointer,
	nl_user
} datatype;

typedef struct _array
{
	datatype type;
	void *array;
	int length;
} array;

typedef enum _game_name
{
	nl_racing_evolution_3d = 0,
	nl_contr_terrorism_3d,
	nl_army_ranger_3d,
	nl_contr_terrorism_3d_episode_2,
	nl_shadow_of_egypt_3d,
	nl_clone_3d,
	nl_contr_terrorism_3d_episode_3,
	nl_total_game,
	nl_2d_game,
	nl_old_game
} game_name;

extern int nl_debug_mode;

void delete_array(array *arr);
array * new_array(datatype type, size_t length, void *data, size_t size);

#endif
