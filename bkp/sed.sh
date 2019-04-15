#!/bin/sh

#sed -i "1,\$s/\<${O}\>/${T}/g" src/*.h src/*.c math3d/*.h math3d/*.c src/game/*.h src/game/*.c caitlyn/*.h caitlyn/*.c

O="nl_vector3_t"
T="nl_vector3_s"

#sed -i "s/\<${O}\>/${T}/g" math3d/*.c
#sed -i "s/\<${O}\>/${T}/g" math3d/*.h
#sed -i "s/\<${O}\>/${T}/g" src/*.c
#sed -i "s/\<${O}\>/${T}/g" src/*.h
#sed -i "s/\<${O}\>/${T}/g" src/gl/*.c
#sed -i "s/\<${O}\>/${T}/g" src/gl/*.h
#sed -i "s/\<${O}\>/${T}/g" src/game/*.c
#sed -i "s/\<${O}\>/${T}/g" src/game/*.h
#sed -i "s/\<${O}\>/${T}/g" src/game/page/*.c
#sed -i "s/\<${O}\>/${T}/g" src/game/page/*.h
#sed -i "s/\<${O}\>/${T}/g" src/game/component/*.c
#sed -i "s/\<${O}\>/${T}/g" src/game/component/*.h
#sed -i "s/\<${O}\>/${T}/g" lolking/*.c
#sed -i "s/\<${O}\>/${T}/g" lolking/*.h
sed -i "s/\<${O}\>/${T}/g" src/physics/*.c
sed -i "s/\<${O}\>/${T}/g" src/physics/*.h
