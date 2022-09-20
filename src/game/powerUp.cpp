#include "powerUp.h"
#include "lives.h"
#include "score.h"
#include "../physics/collider.h"

using namespace Bubble;

PowerUp::PowerUp(Mesh* mesh, Material* material, f32 radius, Vec3 position) { 
	AddGraphicsComponent(mesh, material);
	AddSphereCollider(radius); 
	SetTrigger(true);
	transform.SetPosition(position);
	direction = position.normalize();
}

void PowerUp::Update(f32 deltaTime) {
	transform.SetPosition(transform.GetPosition() + direction*deltaTime*speed);
	transform.Rotate(deltaTime*angularSpeed, deltaTime*angularSpeed, deltaTime*angularSpeed);
	
	if (!isFalling && (transform.GetPosition().length() > 7.5f || Score::GetInstance()->GetTowerSize() == 0)) {
		isFalling = true;
		direction = Vec3(0.0f, -1.0f, 0.0f);
		return;
	}
		
	if (isFalling && transform.GetPosition().y < -20.0f) {
		ClearComponents();
	}
}

//------------------------------------------------------------------------------------------------------------------------
ExtraLifePowerUp::ExtraLifePowerUp(Mesh* mesh, Material* material, f32 radius, Vec3 position): 
 													PowerUp(mesh, material, radius, position) { }

void ExtraLifePowerUp::OnCollisionEnter(Collider& collider) { 
	if (collider.gameObject.name == "Paddle") {
		Lives::GetInstance()->AddLives(1);	
		ClearComponents();
	}
}

//------------------------------------------------------------------------------------------------------------------------
CoinPowerUp::CoinPowerUp(Mesh* mesh, Material* material, f32 radius, Vec3 position): 
 							PowerUp(mesh, material, radius, position) { }

void CoinPowerUp::OnCollisionEnter(Collider& collider) { 
	if (collider.gameObject.name == "Paddle") {
		Score::GetInstance()->AddScore(100);
		ClearComponents();
	}
}

//------------------------------------------------------------------------------------------------------------------------
SpeedUpPowerUp::SpeedUpPowerUp(Mesh* mesh, Material* material, f32 radius, Vec3 position): 
 									PowerUp(mesh, material, radius, position) { name = "SpeedUp"; }

void SpeedUpPowerUp::OnCollisionEnter(Collider& collider) { 
	if (collider.gameObject.name == "Paddle") {
		ClearComponents();
	}
}

//------------------------------------------------------------------------------------------------------------------------
SpeedDownPowerUp::SpeedDownPowerUp(Mesh* mesh, Material* material, f32 radius, Vec3 position): 
 									PowerUp(mesh, material, radius, position) { name = "SpeedDown"; }

void SpeedDownPowerUp::OnCollisionEnter(Collider& collider) { 
	if (collider.gameObject.name == "Paddle") {
		ClearComponents();
	}
}

//------------------------------------------------------------------------------------------------------------------------
PaddleIncreasePowerUp::PaddleIncreasePowerUp(Mesh* mesh, Material* material, f32 radius, Vec3 position): 
 												PowerUp(mesh, material, radius, position) { name = "PaddleIncrease"; }

void PaddleIncreasePowerUp::OnCollisionEnter(Collider& collider) { 
	if (collider.gameObject.name == "Paddle") {
		ClearComponents();
	}
}

//------------------------------------------------------------------------------------------------------------------------
PaddleDecreasePowerUp::PaddleDecreasePowerUp(Mesh* mesh, Material* material, f32 radius, Vec3 position): 
 												PowerUp(mesh, material, radius, position) { name = "PaddleDecrease"; }

void PaddleDecreasePowerUp::OnCollisionEnter(Collider& collider) { 
	if (collider.gameObject.name == "Paddle") {
		ClearComponents();
	}
}