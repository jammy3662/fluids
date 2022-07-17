#pragma once

#include <raylib.h>

#include <ext.h>
#include <node.h>

typedef Model Model3D;

#define Model Model_
struct Model_: Node
{
	// raylib model object
	Model3D rl;
	
	v3 position = {0,0,0};
	float scale = 1;
	
	// --- implement Node interface
	
	void init()
	{
		position = {0,0,0};
		scale = 1;
	}
	
	void update()
	{
		
	}
	
	void draw()
	{
		DrawModel(rl, position, scale, {0xff,0xff,0xff,0xff});
	}
	
};