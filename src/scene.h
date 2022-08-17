#pragma once

#include <node.h>
#include <camera.h>
#include <render.h>

struct Scene: Node
{
	Color bgColor = {0,0,0,0};
	Array<Node*> nodes;
	
	int8 tobuf = false;
	
	Camera3D* activeCamera;
	
	RenderTexture frame;
	
	inline void setCamera(Camera& c)
	{
		activeCamera = &c.rl;
	}
	
	inline void addNode(Node& n)
	{
		nodes.append(&n);
	}
	
	void update()
	{
		forin (n, nodes, n->update();)
	}
};

struct Scene2: Scene
{
	void init()
	{
		frame = LoadRenderTexture(fwidth, fheight);
		forin (n, nodes, n->init();)
	}
	
	void draw(int8 tobuf = true)
	{
		if (tobuf)
		{
			BeginTextureMode(frame);
			ClearBackground(bgColor);
		}
			
		forin (n, nodes, {
			n->draw();
		})
			
		if (tobuf)
		{
			EndTextureMode();
		}
	}
};

struct Scene3: Scene
{
	RenderTexture depth;
	
	void init()
	{
		frame = LoadRenderTextureWithDepthTexture(fwidth, fheight);
		depth = LoadRenderTexture(fwidth, fheight);
		forin (n, nodes, n->init();)
	}
	
	void draw(int8 tobuf = true)
	{
		if (tobuf)
		{
			BeginTextureMode(frame);
			ClearBackground(bgColor);
		}
			
		BeginMode3D(*activeCamera);
			
		forin (n, nodes,
		{
			n->draw();
		})
			
		EndMode3D();
			
		if (tobuf)
		{
			EndTextureMode();
			
			// normalize depth values to make them usable
			BeginTextureMode(depth);
			ClearBackground({0,0,0,0});
			BeginShaderMode(depthShader);
			DrawTexturePro(frame.depth, {0,0, fwidth, -fheight}, {0,0, fwidth, fheight}, {0,0}, 0, {255,255,255,255});
			EndShaderMode();
			EndTextureMode();
		}
	}
};

void Node::addToScene(Scene& scn) { scn.addNode(*this); }