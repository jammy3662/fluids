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

int8 running = 0;

int main(int argc, char** argv)
{
	SetTraceLogLevel(LOG_WARNING);
	SetTraceLogLevel(LOG_INFO);
	
	InitWindow(wwidth, wheight, "wow look a test digital style - v" VERSION);
	
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	
	running = 1;
	
	Shader poops = LoadShader(0, "res/shader/paintclip.fs");
	
	Texture test = LoadTexture("res/texture/720p.png");
	Texture test2 = LoadTexture("res/texture/test-splotch64.png");
	Texture t = LoadTexture("res/texture/test.png");
	
	int loc = GetShaderLocation(poops, "texture1");
	SetShaderValueTexture(poops, loc, t);
	
	while (running)
	{
		BeginDrawing();
		ClearBackground({100,100,100,255});
		
		BeginShaderMode(poops);
		SetShaderValueTexture(poops, loc, t);
		DrawTexture(test, 0,0, {255,255,255,255});
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

