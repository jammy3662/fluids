#pragma once

#include <raylib.h>
#include <def.h>
#include <scene.h>

Shader paintClipper;

Texture paintTex;

void InitPaint()
{
	paintTex = LoadTexture("res/texture/test-splotch64.png");
	paintClipper = LoadShader(0, "res/shader/paintclip.fs");
	printf("PAINT CLIPPER SHADER: %i\n", paintClipper.id);
}

struct PaintObj: Node
{
	v3 position;
	v3 normal;
	float radius;
	Color color;
	
	void draw()
	{
		DrawSphere(position, radius, color);
	}
};

struct PaintContext: Scene
{
	RenderTexture* terrain;
};