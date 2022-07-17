#pragma once

#include <raylib.h>
#include <node.h>

#define Camera Camera_

struct Camera_: Node
{
	// raylib camera object
	Camera3D rl = 
	{
		{0,0,0},
		{0,0,0},
		{0,1,0},
		90,
		CAMERA_PERSPECTIVE
	};
	
	// expose raylib fields
	v3&      eye = rl.position;
	v3&   target = rl.target;
	v3&       up = rl.up;
	float&   fov = rl.fovy;
	int&    proj = rl.projection;
	
	// horizontal and vertical
	// camera sensitivity
	float HSENS = 0.1;
	float VSENS = 0.1;
	
	// key binds
	int16 key_lock = KEY_ESCAPE;
	int16  key_pov = KEY_TAB;
	
	// first/third person camera
	enum POV { POV_FIRST, POV_THIRD };
	int8 pov = POV_FIRST;
	v3 position = {0,0,0}; // pov-agnostic position of camera
	v3 facing = {0,0,0};
	
	int8 locked = 0;
	// in radians
	float pitch = 0;
	float   yaw = 0;
	float  roll = 0;
	// alternate names
	float& v = pitch;
	float& h = yaw;
	float& s = roll;
	
	// ---------------------------------
	// implement node interface
	// ---------------------------
	
	void init()
	{
		SetCameraMode(rl, CAMERA_CUSTOM);
		SetCameraMoveControls(0, 0, 0, 0, 0, 0);
		
		position = {0,0,0};
		  facing = {0,0,1};
		
		setPov(POV_FIRST);
		
		unlock();
		refresh();
	}
	
	void update()
	{
		if (IsKeyPressed(key_lock))
		{
			if (locked) unlock();
			else lock();
		}
		
		if (locked) return;
		
		if (IsKeyPressed(key_pov))
		{
			togglePov();
		}
		
		v2 rt = GetMouseDelta();
		rt = {RAD(rt.x) * -HSENS, RAD(rt.y) * VSENS};
		rotate(rt.y, rt.x, 0);
	}
	
	void draw() {}
	
	// -------------------------
	// camera manipulation
	// ------------------------
	
	void refresh()
	{
		target = Vector3Add(position, facing);
		if (pov == POV_FIRST)
		{
			eye = position;
		}
		else
		{
			eye = Vector3Subtract(position, facing);
		}
	}
	
	void lock()
	{
		locked = 1;
		EnableCursor();
	}
	
	void unlock()
	{
		locked = 0;
		DisableCursor();
	}
	
	void setpos(v3 pos)
	{
		position = pos;
		refresh();
	}
	
	void translate(v3 tr)
	{
		position = Vector3Add(position, tr);
	}
	
	void translate(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}
	
	void rotate(float p, float y, float r)
	{
		pitch += p;
		yaw   += y;
		roll  += r;
		
		pitch = clamp((float)-1.55, pitch, (float)1.55);
		
		facing = Vector3RotateByQuaternion({0,0,1}, QuaternionFromEuler(pitch, yaw, roll));
		refresh();
	}
	
	// --------------------------------
	// perspective handling
	// -----------------------
	
	void setPov(int8 next)
	{
		pov = next;
		printf("next: %i\n", next);
		refresh();
	}
	
	inline void togglePov() { setPov(!pov); }
};