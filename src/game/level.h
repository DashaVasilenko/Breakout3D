#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <string>
#include <string>

#include "../core/types.h"
#include "../scene/gameObject.h"
#include "../scene/camera.h"

class Brick;
class Sphere;

class Scene {
public:
	void AddGameObject(Bubble::GameObject* go);
	void RemoveGameObject(Bubble::GameObject* go);

	void Update(f32 deltaTime);
	void ClearScene();

	~Scene();

private:
	std::vector<Bubble::GameObject*> gameObjects;
};

class Level {
public:
	void LoadResources();
	void CreateLevel();
	void Update(f32 deltaTime);
	~Level();

private:
	std::vector<Brick*> bricks;
	Sphere* sphere;
	Scene scene;
	Bubble::Camera camera;

	Bubble::Vec3 cameraPosition_1;
	Bubble::Vec3 cameraPosition_2;
	Bubble::Vec3 cameraPosition_3;
	Bubble::Vec3 cameraPosition_4;
	f32 cameraHeight; 

	f32 brickHeight = 1.0f;
	i32 cntPyramidStores = 3;
	i32 cntBricksPerStore = 12;
	f32 brickAngle = 360.0f/cntBricksPerStore;
	f32 paddleRadiusIn = 6.5f;
	f32 paddleRadiusOut = 7.0f;
};

#endif