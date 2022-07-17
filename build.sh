#!/bin/bash

#############
# fuck you, vscode
# rot in hell
rm -rf .vscode
#############

VERSION=$(date +%-y.%-m.%-d)
PLATFORM=$(uname -m)

IN="src/main.cc"
OUT="fluids.$PLATFORM"

FLAGS="-Wno-write-strings -g3 -Iinc -Isrc"
LINK="-lraylib -lenet -lGL -lm -lpthread -ldl -lrt -lX11 -lreactphysics3d"

RUN_ON_BUILD=0
[ -z $1 ] && RUN_ON_BUILD=1

clear
clang++ $IN -o "$OUT" $FLAGS $LINK -DVERSION="\"$VERSION\"" -DDEBUG
SUCCESS=$?

if [ $RUN_ON_BUILD = 0 ] && [ ! $SUCCESS -ne 0 ]; then
	"./$OUT"
fi

exit $SUCCESS
