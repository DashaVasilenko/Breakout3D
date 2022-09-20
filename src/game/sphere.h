#ifndef SPHERE_H
#define SPHERE_H

#include "../core/types.h"
#include "../scene/gameObject.h"
#include "../math/vector.h"

class Paddle;

class Sphere: public Bubble::GameObject {
public:
	Sphere(Bubble::Mesh* mesh, Bubble::Material* material, f32 radius, Paddle& paddle);

	//void Start();
	void Update(f32 deltaTime);
	inline Bubble::Vec3 GetPosition() const { return transform.GetPosition(); }
	inline f32 GetRadius() const { return radius; }
	inline void SpeedUp(f32 value) { Bubble::Vec3 v = moveComponent->velocity; moveComponent->velocity += v.normalize()*value; }
	inline void SpeedDown(f32 value) { Bubble::Vec3 v = moveComponent->velocity; moveComponent->velocity -= v.normalize()*value; }

	virtual ~Sphere() {}
 
private:
	Bubble::Vec3 direction;
	Paddle& paddle;
	f32 radius = 1.0f;
	f32 lineSpeed = 5.0f; 
	f32 speed = 70.0f;
	bool isMove = false;
    bool isAlive = true;
	bool isFalling = false;
};

#endif