#pragma once

#include <node.h>
#include <camera.h>
#include <render.h>

struct Scene
{
	Color bgColor = {0,0,0,0};
	Array<Node*> nodes;
	
	Camera3D* activeCamera;
	
	RenderTexture frame;
	RenderTexture depth;
	
	inline void setCamera(Camera* c)
	{
		activeCamera = &c->rl;
	}
	
	inline void addNode(Node* n)
	{
		nodes.append(n);
	}
};

void InitScene(Scene& scn)
{
	scn.frame = LoadRenderTextureWithDepthTexture(fwidth, fheight);
	scn.depth = LoadRenderTexture(fwidth, fheight);
	fori (n, scn.nodes, n->init();)
}

void ProcessScene(Scene& scn)
{
	fori (n, scn.nodes, n->update();)
}

void RenderScene(Scene& scn)
{
	BeginTextureMode(scn.frame);
	ClearBackground(scn.bgColor);
	
	BeginMode3D(*scn.activeCamera);
		
		fori (n, scn.nodes, {
			if (n->mode() == WORLD and n->visible)
				n->draw();
		})
		
	EndMode3D();
		
		fori (n, scn.nodes, {
			if (n->mode() == SCREEN and n->visible)
				n->draw();
		})
		
	EndTextureMode();
	
	// normalize depth values to make them usable
	BeginTextureMode(scn.depth);
	ClearBackground({0,0,0,0});
	BeginShaderMode(depthShader);
	DrawTexturePro(scn.frame.depth, {0,0, fwidth, -fheight}, {0,0, fwidth, fheight}, {0,0}, 0, {255,255,255,255});
	EndShaderMode();
	EndTextureMode();
}