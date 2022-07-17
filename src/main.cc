#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#define ZEXT_FOR
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

#include <render.h>
#include <camera.h>
#include <scene.h>
#include <mesh.h>
#include <paint.h>
#include <player.h>

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
	
	Scene scn;
	Scene paintscn;
	
	running = 1;
	
	Player pl;
	pl.position = {0,5,0};
	pl.depthvs = false;
	scn.addNode(&pl);
	
	scn.setCamera(&pl.camera);
	paintscn.setCamera(&pl.camera);
	
	Model m;
	m.rl = LoadModel("res/mesh/underpass.glb");
	scn.addNode(&m);
	
	InitScene(scn);
	
	InitPaint();
	PaintContext pcon = CreatePaintContext(scn.frame);
	
	PaintObj p;
	p.position = {0,2,0};
	p.radius = 0.5;
	
	pcon.paint.append(p);
	
	while (running)
	{
		ProcessScene(scn);
		
		BeginDrawing();
		ClearBackground({0x10,0x10,0x10,0xff});
		
		RenderScene(scn);
		
		DrawFrame(scn.frame.texture, fwidth, fheight);
		DrawPaint(pcon, scn.activeCamera);
		
		EndDrawing();
		
		if (WindowShouldClose())
		{
			printf("oops\n");
			running = 0;
		}
	}
	
	return 0;
}

