#ifndef PADDLE_H
#define PADDLE_H

#include "../core/types.h"
#include "../scene/gameObject.h"
#include "../math/vector.h"
#include "../physics/collider.h"
#include "sphere.h"

class Paddle: public Bubble::GameObject {
public:
	Paddle(Bubble::Mesh* mesh, Bubble::Material* material, f32 radiusIn, f32 radiusOut, f32 angle, f32 height);

	inline void SetRadii(f32 radiusIn, f32 radiusOut) { this->radiusIn = radiusIn; this->radiusOut = radiusOut; }
	inline void SetSphere(Sphere* sphere) { this->sphere = sphere; }
	inline void SetPaddles(Paddle* paddle1, Paddle* paddle2) { paddle_1 = paddle1; paddle_2 = paddle2; }
	inline void SetAngle(f32 angle) { this->angle = angle; }
	inline Bubble::Vec2 GetRadii() const { return Bubble::Vec2(radiusIn, radiusOut); }
	inline f32 GetRadiusIn() const { return radiusIn; }
	inline f32 GetRadiusOut() const { return radiusOut; }
	inline Bubble::Vec3 GetPosition() const { // return position for sphere
		Bubble::Vec4 position = RotationMatrix(transform.GetRotation())*Bubble::Vec4(radiusIn - 0.35f, 0.0f, 0.0f, 1.0f);
		return Bubble::Vec3(position.x, position.y, position.z);
	}

	void Update(f32 deltaTime);
	void OnCollisionEnter(Bubble::Collider& collider);

	virtual ~Paddle() {}

private:
	Sphere* sphere = nullptr;
	Paddle* paddle_1 = nullptr;
	Paddle* paddle_2 = nullptr;
	f32 radiusIn = 1.0f;
	f32 radiusOut = 2.0f;
	f32 speed = 70.0f;
	f32 angle = 60.0f;
};

#endif