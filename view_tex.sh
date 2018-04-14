#!/bin/sh

#sh game dir source

BIN=./netlizard-parser
GAME=$1
DIR=$2

TEX_DIR=$DIR/w/

for tex in `ls $TEX_DIR`
do
	echo $tex
	$BIN -vt -g $GAME -s $TEX_DIR/$tex
done

echo "done"
