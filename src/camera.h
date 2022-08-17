#pragma once

#include <raylib.h>
#include <node.h>

#define Camera Camera_

struct Camera_: Node
{
	// expose raylib fields (hacky)
	#define    eye rl.position
	#define target rl.target
	#define     up rl.up
	#define    fov rl.fovy
	#define   proj rl.projection
	
	// raylib camera object
	Camera3D rl = 
	{
		{0,0,0},
		{0,0,0},
		{0,1,0},
		90,
		CAMERA_PERSPECTIVE
	};
	
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
	
	// in radians
	float pitch = 0;
	float   yaw = 0;
	float  roll = 0;
	
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
		
		lock(false);
		refresh();
	}
	
	void update()
	{
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
	
	inline void lock(int8 l)
	{
		Node::lock(l);
		(l) ? EnableCursor() : DisableCursor();
	}
	
	void setpos(v3 pos)
	{
		position = pos;
		refresh();
	}
	
	void setpos(float x, float y, float z)
	{
		position = {x, y, z};
		refresh();
	}
	
	void translate(v3 tr)
	{
		position = Vector3Add(position, tr);
		refresh();
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
	
	// unexpose raylib fields
	#undef    eye
	#undef target
	#undef     up
	#undef    fov
	#undef   proj
};