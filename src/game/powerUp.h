#ifndef POWER_UP_H
#define POWER_UP_H

#include "../core/types.h"
#include "../scene/gameObject.h"
#include "../math/vector.h"

class PowerUp: public Bubble::GameObject {
public:
	PowerUp(Bubble::Mesh* mesh, Bubble::Material* material, f32 radius, Bubble::Vec3 position);

	void Update(f32 deltaTime);

	virtual ~PowerUp() { }

private:
	Bubble::Vec3 direction;
	f32 speed = 3.0f;
	f32 angularSpeed = 30.0f;
	bool isFalling = false;
};


class ExtraLifePowerUp: public PowerUp {
public:
	ExtraLifePowerUp(Bubble::Mesh* mesh, Bubble::Material* material, f32 radius, Bubble::Vec3 position);
	void OnCollisionEnter(Bubble::Collider& collider);
	virtual ~ExtraLifePowerUp() { }	
};

class CoinPowerUp: public PowerUp {
public:
	CoinPowerUp(Bubble::Mesh* mesh, Bubble::Material* material, f32 radius, Bubble::Vec3 position);
	void OnCollisionEnter(Bubble::Collider& collider);
	virtual ~CoinPowerUp() { }
};

class SpeedUpPowerUp: public PowerUp {
public:
	SpeedUpPowerUp(Bubble::Mesh* mesh, Bubble::Material* material, f32 radius, Bubble::Vec3 position);
	void OnCollisionEnter(Bubble::Collider& collider);
	virtual ~SpeedUpPowerUp() { }
};

class SpeedDownPowerUp: public PowerUp {
public:
	SpeedDownPowerUp(Bubble::Mesh* mesh, Bubble::Material* material, f32 radius, Bubble::Vec3 position);
	void OnCollisionEnter(Bubble::Collider& collider);
	virtual ~SpeedDownPowerUp() { }
};

class PaddleIncreasePowerUp: public PowerUp {
public:
	PaddleIncreasePowerUp(Bubble::Mesh* mesh, Bubble::Material* material, f32 radius, Bubble::Vec3 position);
	void OnCollisionEnter(Bubble::Collider& collider);
	virtual ~PaddleIncreasePowerUp() { }
};

class PaddleDecreasePowerUp: public PowerUp {
public:
	PaddleDecreasePowerUp(Bubble::Mesh* mesh, Bubble::Material* material, f32 radius, Bubble::Vec3 position);
	void OnCollisionEnter(Bubble::Collider& collider);
	virtual ~PaddleDecreasePowerUp() { }
};

#endif