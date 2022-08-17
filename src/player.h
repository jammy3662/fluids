#pragma once

#include <raylib.h>
#include <camera.h>

struct Player: Node
{
	Camera camera;
	
	// position at player feet
	v3 position = {0,0,0};
	// distance to player eyes
	float height = 1;
	
	v3 velocity = {0,0,0};
	
	// expose camera fields (hacky)
	#define yaw camera.yaw
	#define pitch camera.pitch
	
	enum surface
	{
		clear, // unpainted surface
		safe, // own paint
		harm, // enemy paint
		grate, // semisolid surface (can pass through as ceta)
	};
	
	int8 focused = false; // if set, this dummy is focused by a spectator or replay
	
	// ingame state
	int8 moving = false;
	int8 jumping = false;
	int8 floored = false;
	int8 climbing = false; // true when swimming up/down wall
	int8 surface = clear;
	int8 swimming = false; // true while in ceta form
	int8 shifting = false; // true while transitioning forms
	
	v2 wishdir = {0,0};
	v2 curdir = {0,0};
	
	int8 team = none;
	
	inline v3 eyepos()
	{
		return {position.x, position.y + height, position.z};
	}
	
	void sync()
	{
		camera.setpos(eyepos());
	}
	
	void physics()
	{
		position = Vector3Add(position, velocity);
	}
	
	// --- node interface ---
	
	void lock(int8 l)
	{
		Node::lock(l);
		camera.lock(l);
	}
	
	void init()
	{
		camera.init();
		
		sync();
	}
	
	void update()
	{
		wishdir = {0,0};
		
		if (!locked)
		{
			if (IsKeyDown(knorth))      wishdir.y = 1;
			else if (IsKeyDown(ksouth)) wishdir.y = -1;
			
			if (IsKeyDown(keast))      wishdir.x = 1;
			else if (IsKeyDown(kwest)) wishdir.x = -1;
			
			wishdir = Vector2Normalize(wishdir);
			wishdir = Vector2Rotate(wishdir, yaw);
		}
		
		physics();
		camera.update();
		sync();
	}
	
	void draw()
	{
		camera.draw();
		
		DrawSphere(position, 0.1, {0xff,0,0,0xff});
		DrawSphere({position.x, position.y + height, position.z}, 0.1, {0,0,0xff,0xff});
	}
	
	// unexpose camera fields
	#undef yaw
	#undef pitch
};