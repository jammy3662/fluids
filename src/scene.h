#pragma once

#include <node.h>
#include <camera.h>
#include <render.h>
#include <paint.h>

struct Scene
{
	Color bgColor = {0x10, 0x10, 0x10, 0xff};
	Array<Node*> nodes;
	
	Camera3D* activeCamera;
	
	RenderTexture frame;
	
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
}