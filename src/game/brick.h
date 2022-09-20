#ifndef BRICK_H
#define BRICK_H

#include "../core/types.h"
#include "../scene/gameObject.h"
#include "level.h"

class Sphere;

class Brick: public Bubble::GameObject {
public:
	Brick(Bubble::Mesh* mesh, Bubble::Material* material1, Bubble::Material* material2, f32 radiusIn, 
		  f32 radiusOut, f32 angle, f32 height, i32 lives, bool isPowerUp, Brick* b, Sphere& sphere, Scene& scene);

	void SetMoveDown();
	void SetDrawWireframe(bool value) { isDrawWireframe = value; }
	inline Bubble::Vec3 GetPosition() const {
		Bubble::Vec4 position = RotationMatrix(transform.GetRotation())*Bubble::Vec4((radiusIn + radiusOut)*0.5f, 
											   transform.GetPosition().y, 0.0f, 1.0f);
		return Bubble::Vec3(position.x, position.y, position.z);
	}

	void Update(f32 deltaTime);
	void OnCollisionEnter(Bubble::Collider& collider);

	virtual ~Brick() {}

private:
	Brick* brick = nullptr; // brick over this brick
	Bubble::Material* material_1 = nullptr;
	Bubble::Material* material_2 = nullptr;
	Scene& scene;
	Sphere& sphere;
	f32 radiusOut = 2.0f;
	f32 radiusIn = 1.0f;
	f32 height;
	f32 deltaHeight = 0.0f;
	f32 speed = 3.0f;
	i32 score = 50;
	i32 brickLives = 2;
	bool isPowerUp = false;
	bool isDrawWireframe = false;
};

#endif