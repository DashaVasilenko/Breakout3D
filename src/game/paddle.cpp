#include "paddle.h"
#include "../window/input.h"
#include "score.h"
#include "lives.h"
#include "resourceManager.h"

using namespace Bubble;

Paddle::Paddle(Mesh* mesh, Material* material, f32 radiusIn, f32 radiusOut, f32 angle, f32 height): angle(angle) { 
	name = "Paddle";
	AddGraphicsComponent(mesh, material);
	AddBrickCollider(radiusIn, radiusOut, angle, height);
}

void Paddle::Update(f32 deltaTime) { 
	bool flag = Score::GetInstance()->GetTowerSize() != 0 && Lives::GetInstance()->GetLives() > 0;
	if (flag && Input::GetKey(LeftArrow)) {
		f32 angle = this->transform.GetRotation().y;
		this->transform.Rotate(0.0f, deltaTime*speed, 0.0f);
    }
	if (flag && Input::GetKey(RightArrow)) {
        f32 angle = this->transform.GetRotation().y;
		this->transform.Rotate(0.0f, -deltaTime*speed, 0.0f);
    }
}

void Paddle::OnCollisionEnter(Collider& collider) { 
	if (collider.gameObject.name == "SpeedUp") {
		sphere->SpeedUp(1.0f);
		return;
	}	
	if (collider.gameObject.name == "SpeedDown") {
		sphere->SpeedDown(1.0f);
		return;
	}	
	if (collider.gameObject.name == "PaddleIncrease") {
		if (angle >= 80.0f) return;

		angle += 10.0f; 
		paddle_1->SetAngle(angle);
		paddle_2->SetAngle(angle);
		std::string str = "Paddle";
		std::string s = std::to_string((i32)angle);
		str.append(s);
		const char* text = str.c_str();

		graphicsComponent.mesh = ResourceManager::GetInstance()->meshMap[text];
		BrickCollider* brickCollider = (BrickCollider*)this->collider;
		brickCollider->angle = angle;

		paddle_1->graphicsComponent.mesh = ResourceManager::GetInstance()->meshMap[text];
		brickCollider = (BrickCollider*)paddle_1->collider;
		brickCollider->angle = angle;

		paddle_2->graphicsComponent.mesh = ResourceManager::GetInstance()->meshMap[text];
		brickCollider = (BrickCollider*)paddle_2->collider;
		brickCollider->angle = angle;
		return;
	}	
	if (collider.gameObject.name == "PaddleDecrease") {
		if (angle <= 40.0f) return;

		angle -= 10.0f; 
		paddle_1->SetAngle(angle);
		paddle_2->SetAngle(angle);
		std::string str = "Paddle";
		std::string s = std::to_string((i32)angle);
		str.append(s);
		const char* text = str.c_str();

		graphicsComponent.mesh = ResourceManager::GetInstance()->meshMap[text];
		BrickCollider* brickCollider = (BrickCollider*)this->collider;
		brickCollider->angle = angle;

		paddle_1->graphicsComponent.mesh = ResourceManager::GetInstance()->meshMap[text];
		brickCollider = (BrickCollider*)paddle_1->collider;
		brickCollider->angle = angle;

		paddle_2->graphicsComponent.mesh = ResourceManager::GetInstance()->meshMap[text];
		brickCollider = (BrickCollider*)paddle_2->collider;
		brickCollider->angle = angle;
		return;
	}	
}