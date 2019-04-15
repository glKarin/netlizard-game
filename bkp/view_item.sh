#!/bin/sh

#sh game dir source

BIN=./caitlyn
GAME=$1
DIR=$2

OBJ_DIR=$DIR/o/

for obj in `ls $OBJ_DIR`
do
	echo $obj
	$BIN -vi -g $GAME -d $DIR -s $OBJ_DIR/$obj
done

echo "done"
