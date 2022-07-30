#pragma once

#define v2 Vector2
#define v3 Vector3
#define v4 Vector4

#define SetShaderTexture(shader, loc, texture) SetShaderValueTexture(shader, GetShaderLocation(shader, loc), texture)