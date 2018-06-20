#!/bin/sh

HERO=$1
SKIN=$2

MESH=lmesh
ANIM=lanim
TEX=png

MESH_URL=http://media.services.zam.com/v1/media/byName/lol/mv/models/
ANIM_URL=http://media.services.zam.com/v1/media/byName/lol/mv/models/
TEX_URL=http://media.services.zam.com/v1/media/byName/lol/mv/textures/

cd resource/
if [ ! -d model ]; then
	mkdir model
fi

cd model

echo `pwd`

if [ -z ${2} ]; then
	for index in 0 1 2 3 4 5 6 7 8 9 10 11
	do
		wget -T 10 -t 1 ${MESH_URL}${1}_${index}.${MESH}
		echo "wget ${MESH_URL}${1}_${index}.${MESH}"
		wget -T 10 -t 1 ${ANIM_URL}${1}_${index}.${ANIM}
		echo "wget ${ANIM_URL}${1}_${index}.${ANIM}"
	done
else
	wget -T 10 -t 1 ${TEX_URL}${1}/${2}.${TEX}
	echo "wget ${TEX_URL}${1}/${2}.${TEX}"
fi

ls

