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
	
	// key binds
	int16 knorth = KEY_W;
	int16 ksouth = KEY_S;
	int16  keast = KEY_D;
	int16  kwest = KEY_A;
	int16    kup = KEY_SPACE;
	int16  kdown = KEY_LEFT_CONTROL;
	int16  kexit = KEY_ESCAPE;
	
	int8 locked = 0;
	
	float&   yaw = camera.yaw;
	float& pitch = camera.pitch;
	
	void sync()
	{
		camera.position = position;
		camera.position.y += height;
	}
	
	void physics()
	{
		position = Vector3Add(position, velocity);
	}
	
	// --- node interface ---
	
	void init()
	{
		camera.init();
		
		sync();
	}
	
	void update()
	{
		camera.update();
		
		if (IsKeyPressed(kexit)) locked = !locked;
		
		if (locked) return;
		
		float dir = yaw;
		
		if (IsKeyDown(knorth))
		{
			dir += 0;
		}
		else if (IsKeyDown(ksouth))
		{
			dir += M_PI_2;
		}
		else
		{
			velocity.z = 0;
		}
		if (IsKeyDown(keast))
		{
			velocity.x = 0.1;
		}
		else if (IsKeyDown(kwest))
		{
			velocity.x = -0.1;
		}
		else
		{
			velocity.x = 0;
		}
		
		if (IsKeyDown(kup)) velocity.y = 0.1;
		else if (IsKeyDown(kdown)) velocity.y = -0.1;
		else velocity.y = 0;
		
		physics();
		sync();
	}
	
	void draw()
	{
		camera.draw();
		
		DrawSphere(position, 0.1, {0xff,0,0,0xff});
	}
};