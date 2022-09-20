#include "brick.h"
#include "score.h"
#include "sphere.h"
#include "powerUp.h"
#include "resourceManager.h"
#include "../physics/collider.h"

using namespace Bubble;

Brick::Brick(Mesh* mesh, Material* material1, Material* material2, f32 radiusIn, f32 radiusOut, f32 angle, f32 height, i32 lives, 
			 bool isPowerUp, Brick* b, Sphere& sphere, Scene& scene): material_1(material1), material_2(material2), brick(b), 
			 														  brickLives(lives), isPowerUp(isPowerUp), radiusIn(radiusIn),
																	  radiusOut(radiusOut), height(height), sphere(sphere), scene(scene) { 
	AddGraphicsComponent(mesh, material1);
	AddBrickCollider(radiusIn, radiusOut, angle, height); 
}

void Brick::SetMoveDown() { 
	deltaHeight += height;
	if (brick)  {
		brick->SetMoveDown();
	}
}

void Brick::Update(f32 deltaTime) { 
	if (isDrawWireframe) {
		material_1->SetDrawWireframe(true);
		material_2->SetDrawWireframe(true);
	}
	else {
		material_1->SetDrawWireframe(false);
		material_2->SetDrawWireframe(false);
	}

	if (deltaHeight > 0.0f) {
		f32 deltaPos = deltaTime*speed;
		transform.SetPosition(transform.GetPosition() - Vec3(0.0f, deltaPos, 0.0f));
		deltaHeight -= deltaPos;
	}
	
}

void Brick::OnCollisionEnter(Collider& collider) { 
	if (collider.gameObject.name != "Sphere")
		return;

	brickLives--;
	Score::GetInstance()->AddScore(score);
	ChangeMaterial(material_2);
	if (brickLives == 0) {
		if (brick) {
			brick->SetMoveDown(); 
		}
		
		Score::GetInstance()->DestroyBrick();
		ClearComponents();

		if (isPowerUp) {
			ResourceManager* r = ResourceManager::GetInstance();
			Vec4 pos = RotationMatrix(transform.GetRotation())*Bubble::Vec4((radiusOut + radiusIn)*0.5f, 0.05f, 0.0f, 1.0f);
			i32 random = rand()%100;

			if (random < 5) {
				PowerUp* life = new ExtraLifePowerUp(r->meshMap["Coin"], r->materialMap["HeartMaterial"], 0.35f, Vec3(pos.x, pos.y, pos.z));
				scene.AddGameObject(life);
				return;
			}
			
			if (5 < random && random < 40) {
				PowerUp* coin = new CoinPowerUp(r->meshMap["Coin"], r->materialMap["CoinMaterial"], 0.35f, Vec3(pos.x, pos.y, pos.z));
				scene.AddGameObject(coin);
				return;
			}

			if (40 < random && random < 55) {
				PowerUp* speedUp = new SpeedUpPowerUp(r->meshMap["SpeedUp"], r->materialMap["RedMaterial"], 0.35f, Vec3(pos.x, pos.y, pos.z));
				scene.AddGameObject(speedUp);
				return;
			}

			if (55 < random && random < 70) {
				PowerUp* speedDown = new SpeedDownPowerUp(r->meshMap["SpeedDown"], r->materialMap["BlueMaterial"], 0.35f, Vec3(pos.x, pos.y, pos.z));
				scene.AddGameObject(speedDown);
				return;
			}

			if (70 < random && random < 85) {
				PowerUp* paddleIncrease = new PaddleIncreasePowerUp(r->meshMap["PaddleIncrease"], r->materialMap["BlueMaterial"], 0.35f, Vec3(pos.x, pos.y, pos.z));
				scene.AddGameObject(paddleIncrease);
				return;
			}

			if (85 < random && random < 100) {
				PowerUp* paddleDecrease = new PaddleDecreasePowerUp(r->meshMap["PaddleDecrease"], r->materialMap["RedMaterial"], 0.35f, Vec3(pos.x, pos.y, pos.z));
				scene.AddGameObject(paddleDecrease);
				return;
			}

		} 
		 
	}
}