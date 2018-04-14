#include "netlizard/netlizard.h"
#include "src/netlizard_viewer.h"
#include "src/netlizard_converter.h"
#include "src/gl_3d_main.h"
#include "src/nl_struct_info.h"
#include "src/nl_std.h"
#include "src/game/game_main.h"

#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SPLASH_FILE _KARIN_RESOURCE_DIR"resource/caitlyn_splash.png"

static void Main_ParseOpt(int argc, char *argv[]);
static void Main_PrintHelp(const char *bin);
static void Main_PrintVersion(void);
static void Main_ClearNLPCMDOpt(void);
static void Main_Running(void);
static void Main_ShowSplash(void);
static void Main_PlayGame(void);

static int show_help = 0;
static int fail = 0;
/*
 * m/view = map item role texture struct / m i r t s or null for view convert texture
 * x/decode = texture string text / p s t
 * e/encode = texture string text / p s t
 * g/game = ct3d ct3dep2 spacnaz3d egypt3d clone3d re3d ct3dep3 2d old tex_v2 tex_v3 tex_v3z
 * d/directory = directory path
 * l/level = level
 * a/animation = animation
 * f/fullscreen = fs
 * h/help = show help
 * o/output = output file or null for print decode text
 * t/format = output format
 * n/game-mode = play game
 * s/source = input
 * q/quiet = quiet
 * p/splash = showsplash
 */

static const char *Short_Arg = "v::e:x:g:d:l:a:s:o::t:fnpqh";
static const struct option Long_Arg[] = {
	{"view", 2, NULL, 'v'},
	{"encode", 1, NULL, 'e'},
	{"decode", 1, NULL, 'x'},
	{"game", 1, NULL, 'g'},
	{"directory", 1, NULL, 'd'},
	{"level", 1, NULL, 'l'},
	{"animation", 1, NULL, 'a'},
	{"source", 1, NULL, 's'},
	{"output", 2, NULL, 'o'},
	{"format", 1, NULL, 't'},
	{"fullscreen", 0, NULL, 'f'},
	{"game-mode", 0, NULL, 'n'},
	{"splash", 0, NULL, 'p'},
	{"quiet", 0, NULL, 'q'},
	{"help", 0, NULL, 'h'}
};
static const char *Arg_Desc[] = {
	"View 3D model or texture. ["
		"m/map - 3D level map, "
		"i/item - 3D item, "
		"r/role - 3D animation role(Egypt 3D and Clone 3D un*.png file), "
		"t/texture - NETLizard image or texture, "
		"s/struct - NETLizard file struct info."
		"]",
	"Encode normal file to NETLizard resource file. ["
		"p/texture - texture file, "
		"s/string - string, "
		"t/text - text file"
		"]",
	"Decode NETLizard resource file to normal file. ["
		"p/texture - texture file, "
		"s/int_array - int array, "
		"t/text - text file"
		"]",
	"Specify NETLizard game name. ["
		"ct3d : Contr Terrorism 3D, "
		"specnaz3d : Army Ranger 3D - Opereation Arctic, "
		"ct3dep2 : Contr Terrorism 3D Episode 2, "
		"egypt3d : Shadows of Egypt 3D, "
		"clone3d : Clone 3D, "
		"ct3dep3 : Contr Terrorism 3D Episode 3, "
		"re3d : Racing Evolution 3D, "
		"2d : Other games, "
		"old : Old games, "
		"tex_v2 : NETLizard 3D engine v2 texture, "
		"tex_v3 : NETLizard 3D engine v3 texture, "
		"tex_v3z : NETLizard 3D engine v3 compress texture (Egypt 3D and Clone 3D fp*.png file)"
		"]",
	"Specify NETLizard game resource path.",
	"Specify map level, item index or role index of NETLizard game.",
	"Specify role model animation index.",
	"Specify input file or source.",
	"Specify output file.",
	"Specify output image file format.",
	"Run with fullscreen.",
	"Run game-mode.",
	"Show splash.",
	"Quiet.",
	"Show help text."
};

static const char *Arg_Value[] = {
	"type",
	"type",
	"type",
	"game name / texture type",
	"resource path",
	"level/index",
	"animation index",
	"file/source",
	"file",
	"format subfix",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

typedef struct _NLP_CMDopts
{
	int option;
	char *game;
	char *dir;
	int level;
	int animation;
	char *source;
	char *output;
	char *format;
} NLP_CMDopts;

static NLP_CMDopts cmdopts = {
	0,
	NULL,
	NULL,
	-1,
	0,
	NULL,
	NULL,
	NULL
};

typedef enum _NLP_CMDOption
{
	Unknow_Option = 0,
	View_3DScene_Option = 1,
	View_3DItem_Option = 1 << 1,
	View_3DAnimation_Option = 1 << 2,
	View_Texture_Option = 1 << 3,
	View_Struct_Option = 1 << 4,
	View_DecodeEncode_Option = 1 << 5,

	Encode_Image_Option = 1 << 6,
	Encode_Text_Option = 1 << 7,
	Encode_String_Option = 1 << 8,

	Decode_Image_Option = 1 << 9,
	Decode_Text_Option = 1 << 10,
	Decode_String_Option = 1 << 11,

	Save_DecodeEncode_Option = 1 << 12,

	Play_Game = 1 << 13,
	Show_Fullscreen = 1 << 14,
	Show_Splash = 1 << 15,
	Quiet_Mode = 1 << 16,
	Show_Help_Version = 1 << 17
} NLP_CMDOption;

int main(int argc, char *argv[])
{
	//printfi(2293760>>16);
	//printfi(0x8a);
	Main_ParseOpt(argc, argv);
	//printfi(cmdopts.option);
	if(argc == 1)
	{
#if 0
		show_help = 1;
		fail = 1;
#endif
		printf("Game mode\n");
		Main_PlayGame();
	}
	else
	{
		if(cmdopts.option & Show_Help_Version)
			show_help = 1;
		else if(cmdopts.option & Show_Splash)
		{
			Main_ShowSplash();
		}
		else if(cmdopts.option & Play_Game)
		{
			Main_PlayGame();
		}
		else
		{
			Main_Running();
		}
	}
	if(show_help && ((cmdopts.option & Quiet_Mode) == 0))
		Main_PrintHelp(_KARIN_APPLICATION);
	Main_ClearNLPCMDOpt();
	if(fail)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);

	return 0;
}

void Main_ShowSplash(void)
{
	if(Viewer_ImageInitMain("Bridge Interactive", SPLASH_FILE))
	{
		Main3D_InitGLK(0, 0, 640, 360, "OpenGL NETLizard 3D - caitlyn", 30, 1);
		Viewer_ImageRegisterFunction();
		Main3D_MainLoop();
	}
}

void Main_PlayGame(void)
{
	MainGame_Run();
}

void Main_Running(void)
{
	int need_gl = 0;
	if(cmdopts.option & View_3DScene_Option || cmdopts.option & View_3DItem_Option || cmdopts.option & View_3DAnimation_Option)
	{
		if(!cmdopts.game)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing game argument.\n");
		}
		if(!cmdopts.dir)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing resource path argument.\n");
		}
		if(cmdopts.level < 0 && !cmdopts.source)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing level or source argument.\n");
		}
		if(!fail)
		{
			if(strcmp(cmdopts.game, "re3d") == 0)
			{
				if(cmdopts.option & View_3DScene_Option)
				{
					if(Viewer_RE3DInitMain(cmdopts.game, "map", cmdopts.dir, cmdopts.source, cmdopts.level))
					{
						Viewer_RE3DRegisterFunction();
						need_gl = 1;
					}
				}
				else if(cmdopts.option & View_3DItem_Option)
				{
					if(cmdopts.level < 0)
					{
						show_help = 1;
						fail = 1;
						fprintf(stderr, "Missing level argument.\n");
					}
					else
					{
						if(Viewer_RE3DInitMain(cmdopts.game, "car", cmdopts.dir, cmdopts.source, cmdopts.level))
						{
							Viewer_RE3DRegisterFunction();
							need_gl = 1;
						}
					}
				}
			}
			else
			{
				if(cmdopts.option & View_3DScene_Option)
				{
					if(Viewer_NETLizard3DMapInitMain(cmdopts.game, cmdopts.dir, cmdopts.source, cmdopts.level))
					{
						Viewer_NETLizard3DMapRegisterFunction();
						need_gl = 1;
					}
				}
				else if(cmdopts.option & View_3DItem_Option)
				{
					if(Viewer_NETLizard3DItemInitMain(cmdopts.game, cmdopts.dir, cmdopts.source, cmdopts.level))
					{
						Viewer_NETLizard3DItemRegisterFunction();
						need_gl = 1;
					}
				}
				else if(cmdopts.option & View_3DAnimation_Option)
				{
					if(cmdopts.level <= 0)
					{
						show_help = 1;
						fail = 1;
						fprintf(stderr, "Missing level argument.\n");
					}
					else
					{
						if(Viewer_NETLizard3DAnimationInitMain(cmdopts.game, cmdopts.dir, cmdopts.source, cmdopts.level, cmdopts.animation))
						{
							Viewer_NETLizard3DAnimationRegisterFunction();
							need_gl = 1;
						}
					}
				}
			}
		}
	}
	else if(cmdopts.option & View_Texture_Option)
	{
		if(!cmdopts.source)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing source file argument.\n");
		}
		if(!fail)
		{
			if(Viewer_ImageInitMain(cmdopts.game, cmdopts.source))
			{
				Viewer_ImageRegisterFunction();
				need_gl = 1;
			}
		}
	}
	else if(cmdopts.option & Decode_Image_Option)
	{
		if(!cmdopts.source)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing source file argument.\n");
		}
		if(!fail)
		{
			if(Converter_DecodeImageFile(cmdopts.game, cmdopts.source, cmdopts.output, cmdopts.format))
			{
				printf("Decode image successful.\n");
				printf("Output format -> %s\n", dst_format);
				printf("Output file -> %s\n", dst_file);
				if(cmdopts.option & View_DecodeEncode_Option)
				{
					if(Viewer_ImageInitMain("Bridge Interactive", dst_file))
					{
						Viewer_ImageRegisterFunction();
						need_gl = 1;
					}
				}
			}
			else
				fprintf(stderr, "Decode image fail.\n");
		}
	}
	else if(cmdopts.option & Encode_Image_Option)
	{
		if(!cmdopts.game)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing game argument.\n");
		}
		if(!cmdopts.source)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing source file argument.\n");
		}
		if(!fail)
		{
			if(Converter_EncodeImageFile(cmdopts.game, cmdopts.source, cmdopts.output))
			{
				printf("Encode image successful.\n");
				printf("Output format -> %s\n", dst_format);
				printf("Output file -> %s\n", dst_file);
				if(cmdopts.option & View_DecodeEncode_Option)
				{
					if(Viewer_ImageInitMain(cmdopts.game, dst_file))
					{
						Viewer_ImageRegisterFunction();
						need_gl = 1;
					}
				}
			}
			else
				fprintf(stderr, "Encode image fail.\n");
		}
	}
	else if(cmdopts.option & Decode_String_Option)
	{
		if(!cmdopts.source)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing source text argument.\n");
		}
		if(!fail)
		{
			if(Converter_DecodeIntArrayToString(cmdopts.source))
			{
				printf("Decode text successful.\n");
				printf("Source digit array -> [ ");
				int i;
				for(i = 0; i < dst_digit_size; i++)
					printf("%d ", dst_digit_array[i]);
				printf("]\n");
				printf("Decode Text -> %s\n", dst_string);
				Converter_FreeString();
			}
			else
				fprintf(stderr, "Decode text fail.\n");
		}
	}
	else if(cmdopts.option & Encode_String_Option)
	{
		if(!cmdopts.source)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing source digit array argument.\n");
		}
		if(!fail)
		{
			if(Converter_EncodeStringToIntArray(cmdopts.source))
			{
				printf("Encode Text successful.\n");
				printf("Source text -> %s\n", dst_string);
				printf("Encode Digit array -> [ ");
				int i;
				for(i = 0; i < dst_digit_size; i++)
					printf("%d ", dst_digit_array[i]);
				printf("]\n");
				Converter_FreeString();
			}
			else
				fprintf(stderr, "Encode text fail.\n");
		}
	}
	else if(cmdopts.option & Decode_Text_Option)
	{
		if(!cmdopts.source)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing source text argument.\n");
		}
		if(!fail)
		{
			if(Converter_DecodeTextFile(cmdopts.source, cmdopts.output, cmdopts.option & Save_DecodeEncode_Option ? 1 : 0))
			{
				printf("Decode text file successful.\n");
				if(dst_text_file)
				{
					printf("Output file -> %s\n", dst_text_file);
				}
				if(cmdopts.option & View_DecodeEncode_Option || (cmdopts.option & Save_DecodeEncode_Option) == 0)
				{
					printf("Text -> \n%s\n", decode_text);
				}
				Converter_FreeText();
			}
			else
				fprintf(stderr, "Decode text file fail.\n");
		}
	}
	else if(cmdopts.option & Encode_Text_Option)
	{
		printf("Unsupport to encode text file now.\n");
	}
	else if(cmdopts.option & View_Struct_Option)
	{
		if(!cmdopts.game)
		{
			show_help = 1;
			fail = 1;
			fprintf(stderr, "Missing game argument.\n");
		}
		if(!fail)
		{
			if(Info_ShowNETLizardStruct(cmdopts.game, 0))
				printf("\n");
			else
				fprintf(stderr, "Unknow type or file not exists.");
		}
	}
	if(need_gl)
	{
		Main3D_InitGLK(0, 0, 640, 360, "OpenGL NETLizard 3D - caitlyn", 30, cmdopts.option & Show_Fullscreen);
		Main3D_MainLoop();
	}
}

static void Main_ParseOpt(int argc, char *argv[])
{
	int ch;
	while((ch = getopt_long(argc, argv, Short_Arg, Long_Arg, NULL)) != -1)
	{
		switch(ch)
		{
			case 'v':
				if(optarg && strlen(optarg))
				{
					if(strcasecmp(optarg, "map") == 0 || strcasecmp(optarg, "m") == 0)
						cmdopts.option |= View_3DScene_Option;
					else if(strcasecmp(optarg, "item") == 0 || strcasecmp(optarg, "i") == 0)
						cmdopts.option |= View_3DItem_Option;
					else if(strcasecmp(optarg, "role") == 0 || strcasecmp(optarg, "r") == 0)
						cmdopts.option |= View_3DAnimation_Option;
					else if(strcasecmp(optarg, "texture") == 0 || strcasecmp(optarg, "t") == 0)
						cmdopts.option |= View_Texture_Option;
					else if(strcasecmp(optarg, "struct") == 0 || strcasecmp(optarg, "s") == 0)
						cmdopts.option |= View_Struct_Option;
					else
						cmdopts.option = Unknow_Option;
				}
				else
					cmdopts.option |= View_DecodeEncode_Option;
				break;
			case 'e':
				if(strlen(optarg))
				{
					if(strcasecmp(optarg, "text") == 0 || strcasecmp(optarg, "t") == 0)
						cmdopts.option |= Encode_Text_Option;
					else if(strcasecmp(optarg, "string") == 0 || strcasecmp(optarg, "s") == 0)
						cmdopts.option |= Encode_String_Option;
					else if(strcasecmp(optarg, "texture") == 0 || strcasecmp(optarg, "p") == 0)
						cmdopts.option |= Encode_Image_Option;
					else
						cmdopts.option = Unknow_Option;
				}
				break;
			case 'x':
				if(strlen(optarg))
				{
					if(strcasecmp(optarg, "text") == 0 || strcasecmp(optarg, "t") == 0)
						cmdopts.option |= Decode_Text_Option;
					else if(strcasecmp(optarg, "string") == 0 || strcasecmp(optarg, "s") == 0)
						cmdopts.option |= Decode_String_Option;
					else if(strcasecmp(optarg, "texture") == 0 || strcasecmp(optarg, "p") == 0)
						cmdopts.option |= Decode_Image_Option;
					else
						cmdopts.option = Unknow_Option;
				}
				break;
			case 'g':
				if(strlen(optarg))
				{
					if(cmdopts.game)
						free(cmdopts.game);
					cmdopts.game = strdup(optarg);
				}
				break;
			case 'd':
				if(strlen(optarg))
				{
					if(cmdopts.dir)
						free(cmdopts.dir);
					cmdopts.dir = strdup(optarg);
				}
				break;
			case 'l':
				if(strlen(optarg))
				{
					char *s = strdup(optarg);
					if(s)
					{
						cmdopts.level = atol(s);
						free(s);
					}
				}
				break;
			case 'a':
				if(strlen(optarg))
				{
					char *s = strdup(optarg);
					if(s)
					{
						long anim = atol(s);
						if(anim > 0)
							cmdopts.animation = (int)anim;
						free(s);
					}
				}
				else
					cmdopts.animation = 0;
				break;
			case 's':
				if(strlen(optarg))
				{
					if(cmdopts.source)
						free(cmdopts.source);
					cmdopts.source = strdup(optarg);
				}
				break;
			case 'o':
				if(optarg)
				{
					if(cmdopts.output)
						free(cmdopts.output);
					cmdopts.output = strdup(optarg);
				}
				cmdopts.option |= Save_DecodeEncode_Option;
				break;
			case 't':
				if(strlen(optarg))
				{
					if(cmdopts.format)
						free(cmdopts.format);
					cmdopts.format = strdup(optarg);
				}
				break;
			case 'f':
				cmdopts.option |= Show_Fullscreen;
				break;
			case 'q':
				cmdopts.option |= Quiet_Mode;
				break;
			case 'p':
				cmdopts.option |= Show_Splash;
				break;
			case 'h':
				cmdopts.option |= Show_Help_Version;
				break;
			case 'n':
				cmdopts.option |= Play_Game;
				break;
			default:
				//fprintf(stderr, "Unknow argument : %c\n", ch);
				break;
		}
	}
}

static void Main_PrintVersion(void)
{
	printf("NETLizard game resource parser\n");
	printf("Version: %s\n", _KARIN_VERSION);
	printf("Release: %s\n", _KARIN_RELEASE);
}

static void Main_PrintHelp(const char *bin)
{
	Main_PrintVersion();
	printf("View 3D model : %s -v<m | i | r> [-f] -g <game> -d <game resources path> [-l <level> | -s <source file>] [-a <animation for -v=r>]\n", bin);
	printf("View texture image : %s -vt [-f] -g <game> -s <NETLizard format image path>\n", bin);
	printf("Convert image or text : %s -[e | x] [t | i | p] -g <game> -s <NETLizard format image path> [-o<output file name for -e/x=t/p>] [-t <image format for -x=p>] [-v for convert image or save decode text]\n", bin);
	printf("View file struct : %s -vs -g <game>\n", bin);
	printf("Play game : %s -n\n", bin);
	printf("\n");

	const unsigned int Arg_Count = sizeof(Long_Arg) / sizeof(struct option);
	unsigned int i;
	for(i = 0; i < Arg_Count; i++)
	{
		printf("  -%c : ", Long_Arg[i].val);
		printf("\n");
		if(Long_Arg[i].has_arg)
			printf("  --%s=<%s> : %s", Long_Arg[i].name, Arg_Value[i], Arg_Desc[i]);
		else
			printf("  --%s : %s", Long_Arg[i].name, Arg_Desc[i]);
		printf("\n");
	}
}

void Main_ClearNLPCMDOpt(void)
{
	if(cmdopts.game)
		free(cmdopts.game);
	if(cmdopts.dir)
		free(cmdopts.dir);
	if(cmdopts.source)
		free(cmdopts.source);
	if(cmdopts.output)
		free(cmdopts.output);
	if(cmdopts.format)
		free(cmdopts.format);
}
