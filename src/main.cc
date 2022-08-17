#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <ext.h>

// render output width and height
const float fwidth = 1280;
const float fheight = 720;

// window width and height
float wwidth = 1280;
float wheight = 720;

void DrawFrame(Texture frame, float w, float h)
{
	DrawTexturePro(frame, {0,0,w,-h},
			{0,0,wwidth,wheight}, {0,0},
			0, {0xff,0xff,0xff,0xff});
}

Camera3D* active_camera;

// key binds
int16 knorth = KEY_W;
int16 ksouth = KEY_S;
int16  keast = KEY_D;
int16  kwest = KEY_A;

int16 kshift = KEY_LEFT_SHIFT;
int16  kctrl = KEY_LEFT_CONTROL;
int16  kjump = KEY_SPACE;
int16   ktab = KEY_TAB;

int16    kup = KEY_UP;
int16  kdown = KEY_DOWN;
int16 kright = KEY_RIGHT;
int16  kleft = KEY_LEFT;

int16  kexit = KEY_ESCAPE;

enum teams
{
	ghost, // no interaction with world ~ for spectating or replays
	none,  // cannot paint, kill, or be killed ~ for hub world or testing
	alpha, // arbitrary team 1
	beta,  // arbitrary team 2
	delta, // arbitrary team 3
	sigma, // arbitrary team 4
};

#include <render.h>
#include <camera.h>
#include <scene.h>
#include <mesh.h>
#include <paint.h>
#include <fluid.h>
#include <player.h>
#include "world.h"

int8 running = 0;

Shader
	blurShader,
	sunShader;

int main(int argc, char** argv)
{
	SetTraceLogLevel(LOG_WARNING);
	
	InitWindow(wwidth, wheight, "wow look a test digital style - v" VERSION);
	
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	
	EnableDepthBuffer();
	InitPaint();
	InitFluid();
	
	running = 1;
	
	Scene scn;
	World game;
	Player pl;
	
	pl.position = {0,5,0};
	pl.addToScene(scn);
	
	Model m;
	m.rl = LoadModel("res/mesh/underpass.glb");
	m.addToScene(scn);
	
	active_camera = &pl.camera.rl;
	
	scn.setCamera(pl.camera);
	scn.init();
	
	while (running)
	{
		scn.update();
		//fluidscn.update();
		
		BeginDrawing();
		ClearBackground({0x10,0x10,0x10,0xff});
		
		scn.draw();
		//DrawFluid();
		
		DrawFrame(scn.frame.texture, fwidth, fheight);
		
		EndDrawing();
		
		if (WindowShouldClose())
		{
			printf("oops\n");
			running = 0;
		}
	}
	
	return 0;
}

