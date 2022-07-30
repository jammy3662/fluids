#pragma once

#include <raylib.h>
#include <rlgl.h>

void DrawBillboardXY(Texture tx, Vector3 pos, Vector2 size, Camera cam)
{
	rlCheckRenderBatchLimit(10);
	rlPushMatrix();

	// get the camera view matrix
	Matrix mat = MatrixLookAt(cam.position, cam.target, cam.up);
	// peel off just the rotation
	Quaternion quat = QuaternionFromMatrix(mat);
	mat = QuaternionToMatrix(quat);

	// apply just the rotation
	rlMultMatrixf(MatrixToFloat((mat)));

	// translate backwards in the inverse rotated matrix to put the item where it goes
	pos = Vector3Transform(pos, MatrixInvert(mat));
	rlTranslatef(pos.x, pos.y, pos.z);

	// draw the billboard
	float width = size.x/2;
	float height = size.y/2;

	Color color = {255,255,255,255};

	rlSetTexture(tx.id);

	// draw quad
	rlBegin(RL_QUADS);
	rlColor4ub(color.r, color.g, color.b, color.a);
	// Front Face
	rlNormal3f(0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(-width, -height, 0);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(+width, -height, 0);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(+width, +height, 0);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(-width, +height, 0);  // Top Left Of The Texture and Quad

	rlEnd();
	rlSetTexture(0);
	rlPopMatrix();
}

Shader depthShader;

void EnableDepthBuffer()
{
	depthShader = LoadShader("res/shader/depth.vs", "res/shader/depth.fs");
	printf("DEPTH SHADER ID: %i\n", depthShader.id);
}

RenderTexture2D LoadRenderTextureWithDepthTexture(int width, int height)
{
    RenderTexture2D target = {0};

    target.id = rlLoadFramebuffer(width, height);   // Load an empty framebuffer

    if (target.id > 0)
    {
        rlEnableFramebuffer(target.id);

        // Create color texture (default to RGBA)
        target.texture.id = rlLoadTexture(NULL, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
        target.texture.width = width;
        target.texture.height = height;
        target.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        target.texture.mipmaps = 1;

        // Create depth texture
        target.depth.id = rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
        target.depth.mipmaps = 1;

        // Attach color texture and depth texture to FBO
        rlFramebufferAttach(target.id, target.texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
        rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

        // Check if fbo is complete with attachments (valid)
		if (rlFramebufferComplete(target.id)) printf("Framebuffer object %i created successfully\n", target.id);
        if (rlFramebufferComplete(target.id)) TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

        rlDisableFramebuffer();
    } 
    else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

    return target;
}