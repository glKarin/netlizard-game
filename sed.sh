#!/bin/sh

#sed -i "1,\$s/\<${O}\>/${T}/g" src/*.h src/*.c math3d/*.h math3d/*.c src/game/*.h src/game/*.c caitlyn/*.h caitlyn/*.c

O=_false
T=0

#sed -i "1,\$s/\<${O}\>/${T}/g" src/m3g_map_viewer.c

sed -i "s/\<${O}\>/${T}/g" bio/*.c
sed -i "s/\<${O}\>/${T}/g" bio/*.h
