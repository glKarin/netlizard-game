#!/bin/sh

#sed -i "1,\$s/\<${O}\>/${T}/g" src/*.h src/*.c math3d/*.h math3d/*.c src/game/*.h src/game/*.c caitlyn/*.h caitlyn/*.c

O=" -> "
T="->"

#sed -i "1,\$s/\<${O}\>/${T}/g" src/m3g_map_viewer.c

#sed -i "s/\<${O}\>/${T}/g" math3d/*.c
#sed -i "s/\<${O}\>/${T}/g" math3d/*.h
sed -i "s/${O}/${T}/g" opengl/*/*/*/*.c
sed -i "s/${O}/${T}/g" opengl/*/*/*/*.h
