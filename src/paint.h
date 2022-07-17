#pragma once

#include <raylib.h>
#include <def.h>

Shader paintClipper;

Texture paintTex;

void InitPaint()
{
	paintTex = LoadTexture("res/texture/test-splotch64.png");
	paintClipper = LoadShader(0x0, "res/shader/paintClip.fs");
	printf("PAINT CLIPPER SHADER: %i\n", paintClipper.id);
}

struct PaintObj
{
	v3 position;
	v3 normal;
	float radius;
};

struct PaintContext
{
	Array<PaintObj> paint;
	
	RenderTexture buffer;
	RenderTexture terrain;
};

PaintContext CreatePaintContext(RenderTexture terrain)
{
	PaintContext ctx;
	
	ctx.buffer = LoadRenderTextureWithDepthTexture(fwidth, fheight);
	ctx.terrain = terrain;
	
	SetShaderValueTexture(paintClipper, GetShaderLocation(paintClipper, "depth"), ctx.buffer.depth);
	SetShaderValueTexture(paintClipper, GetShaderLocation(paintClipper, "terrain"), terrain.depth);
	
	return ctx;
}

void DrawPaint(PaintContext& ctx, Camera3D* cam)
{
	BeginTextureMode(ctx.buffer);
	ClearBackground({0,0,0,0});
	BeginMode3D(*cam);
	fori (obj, ctx.paint,
	{
		v2 topleft = GetWorldToScreen(obj.position, *cam);
		DrawSphere(obj.position, obj.radius, {0xff,0xff,0xff,0xff});
		DrawTextureQuad(paintTex, {1,1}, {0,0},
			{topleft.x, topleft.y, obj.radius, obj.radius},
			{0xff,0xff,0xff,0xff});
	})
	EndMode3D();
	EndTextureMode();
	
	//BeginShaderMode(paintClipper);
	DrawFrame(ctx.buffer.texture, fwidth, fheight);
	//EndShaderMode();
}

void DrawPaintMasked(PaintContext& ctx)
{
	
}