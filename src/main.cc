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
	
	EnableDepthBuffer();
	
	Scene scn;
	
	running = 1;
	
	Player pl;
	pl.position = {0,5,0};
	pl.depthvs = false;
	scn.addNode(&pl);
	
	scn.setCamera(&pl.camera);
	
	Model m;
	m.rl = LoadModel("res/mesh/underpass.glb");
	scn.addNode(&m);
	
	InitScene(scn);
	
	InitPaint();
	PaintContext pcon;
	InitScene(pcon);
	pcon.setCamera(&pl.camera);
	
	PaintObj p;
	p.position = {0,2,0};
	p.radius = 0.5;
	p.color = {0,255,0,255};
	
	pcon.addNode(&p);
	
	while (running)
	{
		ProcessScene(scn);
		ProcessScene(pcon);
		
		BeginDrawing();
		ClearBackground({0x10,0x10,0x10,0xff});
		
		RenderScene(scn);
		RenderScene(pcon);
		
		DrawFrame(scn.frame.texture, fwidth, fheight);
		
		BeginShaderMode(paintClipper);
			SetShaderTexture(paintClipper, "zpaint", pcon.depth.texture);
			SetShaderTexture(paintClipper, "zterrain", scn.depth.texture);
			DrawFrame(pcon.frame.texture, fwidth, fheight);
		EndShaderMode();
		
		EndDrawing();
		
		if (WindowShouldClose())
		{
			printf("oops\n");
			running = 0;
		}
	}
	
	return 0;
}

