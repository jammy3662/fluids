#pragma once

#include <ext.h>
#include <def.h>

typedef void(* callback )();

#define WORLD  0 // 3d space
#define SCREEN 1 // 2d space

// node interface
struct Node
{
	int8 visible = true;
	int8 depthvs = true;
	
	virtual inline uint8 mode() { return WORLD; }
	
	virtual void init()   {}
	virtual void draw()   {}
	virtual void update() {}
};