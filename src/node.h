#pragma once

#include <ext.h>
#include <def.h>

typedef void(* callback )();

#define WORLD  0 // 3d space
#define SCREEN 1 // 2d space

struct Scene;

// node interface
struct Node
{
	int8 locked = false;
	
	virtual inline uint8 mode() { return WORLD; }
	
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	
	virtual void lock(int8 l) { locked = l; }
	virtual void tlock() { lock(!locked); }
	
	// convenience support for scenes
	void addToScene(Scene&);
};