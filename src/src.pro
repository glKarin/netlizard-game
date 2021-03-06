######################################################################
# Automatically generated by qmake (2.01a) ?? 9? 17 20:37:54 2016
######################################################################

TEMPLATE = app
TARGET = netlizard-game

include(../netlizard-game.pri)

DEPENDPATH += . .. $$BUILD_DIR/renderer $$BUILD_DIR/libs game game/component template sound local physics game/page csol gl
INCLUDEPATH += . .. $$BUILD_DIR/renderer $$BUILD_DIR/libs game game/component template sound local physics game/page csol gl

LIBS += -lnetlizard -lSOIL -lglk -llolking -lmath3d -lbio -lopengl -lcsol
LIBS += -lSDL -lSDL_mixer

CONFIG += x11
PRE_TARGETDEPS += $$DESTDIR/libnetlizard.so $$DESTDIR/libSOIL.so $$DESTDIR/liblolking.so $$DESTDIR/libmath3d.so $$DESTDIR/libglk.so $$DESTDIR/libbio.so $$DESTDIR/libopengl.so $$DESTDIR/libcsol.so

# Input
HEADERS += netlizard3d_viewer.h \
           netlizard_converter.h \
					 gl_3d_main.h \
					 nl_event.h \
					 nl_algo.h \
					 nl_struct_info.h \
					 nl_gl.h \
					 game_util.h \
					 font.h \
					 page_stack.h \
					 gl/gl_util.h \
					 gl/gl_object.h \
					 nl_std.h \
					 nl_dbg.h \
					 gl/mesh.h \
					 gl/camera.h \
					 gl/shadow.h \
					 gl/lightsource.h \
					 gl/nl_shadow.h \
					 csol/studio_game.h \
					 game/game_event.h \
					 game/game_setting.h \
					 game/score_table.h \
					 game/first_person.h \
					 game/character_status_bar.h \
					 game/nl_game.h \
					 game/game_std.h \
					 game/game_algo.h \
					 game/vkb.h \
					 game/game_ai.h \
					 game/game_mode.h \
					 game/particle.h \
					 game/game_music.h \
					 game/game_sound.h \
					 game/action_signal_slot.h \
					 game/game_main.h \
					 game/game_viewer.h \
					 game/racing_game_viewer.h \
					 game/weapon.h \
					 game/bullet.h \
					 game/cross_hair.h \
					 game/radar.h \
					 game/reloading_progress_bar.h \
					 game/character.h \
					 game/page/loading.h \
					 game/page/game_menu.h \
					 game/page/about.h \
					 game/page/menu.h \
					 game/page/splash.h \
					 game/page/setting.h \
					 game/page/run_setting.h \
					 game/page/game_over.h \
					 game/page/setting_component.h \
					 game/page/keymap_setting.h \
					 game/page/weapon_chooser.h \
					 game/page/character_model_chooser.h \
					 game/page/mdl_viewer.h \
					 game/page/map_viewer.h \
					 game/page/main_menu.h \
					 game/page/file_chooser.h \
					 game/component/text_browser.h \
					 game/component/button.h \
					 game/component/progress_bar.h \
					 game/component/label.h \
					 game/component/slider_bar.h \
					 game/component/list_view.h \
					 game/component/widget_base.h \
					 game/component/flickable.h \
					 game/component/switcher.h \
					 game/component/spin_box.h \
					 game/component/time_spin_box.h \
					 game/component/comp_util.h \
					 template/list_template.h \
					 sound/sdlk_sound.h \
					 local/file_system.h \
					 physics/gravity.h

SOURCES += ../main.c \
           re3d_viewer.c \
           netlizard3d_map_viewer.c \
           netlizard3d_item_viewer.c \
           netlizard3d_animation_viewer.c \
           netlizard_image_viewer.c \
           netlizard_image_converter.c \
           netlizard_string_converter.c \
           netlizard_text_converter.c \
					 gl_3d_main.c \
					 nl_gl.c \
					 nl_algo.c \
					 nl_struct_info.c \
					 nl_event.c \
					 nl_gl_font.c \
					 nl_gl_spirit.c \
					 nl_algo_racingevolution3d.c \
					 nl_gl_render.c \
					 nl_gl_reader.c \
					 nl_gl_racingevolution3d.c \
					 game_util.c \
					 nl_std.c \
					 font.c \
					 page_stack.c \
           gl/gl_util.c \
					 gl/gl_object.c \
					 gl/mesh.c \
					 gl/camera.c \
					 gl/shadow.c \
					 gl/nl_shadow.c \
					 gl/lightsource.c \
					 csol/studio_game.c \
					 game/game_event.c \
					 game/nl_game.c \
					 game/character.c \
					 game/game_ai.c \
					 game/vkb.c \
					 game/game_algo.c \
					 game/game_mode.c \
					 game/game_main.c \
					 game/game_viewer.c \
					 game/racing_game_viewer.c \
					 game/action_signal_slot.c \
					 game/bullet.c \
					 game/first_person.c \
					 game/character_status_bar.c \
					 game/weapon.c \
					 game/game_music.c \
					 game/game_sound.c \
					 game/game_setting.c \
					 game/score_table.c \
					 game/cross_hair.c \
					 game/radar.c \
					 game/particle.c \
					 game/reloading_progress_bar.c \
					 game/page/about.c \
					 game/page/menu.c \
					 game/page/loading.c \
					 game/page/splash.c \
					 game/page/game_menu.c \
					 game/page/setting.c \
					 game/page/run_setting.c \
					 game/page/game_over.c \
					 game/page/setting_component.c \
					 game/page/keymap_setting.c \
					 game/page/weapon_chooser.c \
					 game/page/character_model_chooser.c \
					 game/page/mdl_viewer.c \
					 game/page/map_viewer.c \
					 game/page/main_menu.c \
					 game/page/file_chooser.c \
					 game/component/button.c \
					 game/component/text_browser.c \
					 game/component/progress_bar.c \
					 game/component/slider_bar.c \
					 game/component/list_view.c \
					 game/component/label.c \
					 game/component/widget_base.c \
					 game/component/switcher.c \
					 game/component/flickable.c \
					 game/component/spin_box.c \
					 game/component/time_spin_box.c \
					 game/component/comp_util.c \
					 local/file_system.c \
					 template/list_template.c \
					 sound/sdlk_sound.c \
					 physics/gravity.c

bin.files = $$DESTDIR/$${TARGET}
bin.path = /usr/bin

INSTALLS += bin
