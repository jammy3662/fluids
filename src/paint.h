#pragma once

#include <raylib.h>
#include <rlgl.h>
#include <def.h>
#include <scene.h>

Shader splatterShader;
Texture paintListBuf;

void InitPaint()
{
	paintListBuf = LoadRenderTexture(100,100).texture;
	splatterShader = LoadShader(0,"res/shader/splatter.fs");
	SetShaderValueTexture(splatterShader, GetShaderLocation(splatterShader, "paintbuf"), paintListBuf);
}