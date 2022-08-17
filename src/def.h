#pragma once

#define v2 Vector2
#define v3 Vector3
#define v4 Vector4

#define SetShader(shader, loc, value, type) SetShaderValue(shader, GetShaderLocation(shader,loc), value, type)
#define SetShaderV(shader, loc, value, type, count) SetShaderValueV(shader, GetShaderLocation(shader, loc), value, type, count)
#define SetShaderMatrix(shader, loc, mat) SetShaderValueMatrix(shader, GetShaderLocation(shader, loc), mat)
#define SetShaderTexture(shader, loc, texture) SetShaderValueTexture(shader, GetShaderLocation(shader, loc), texture)