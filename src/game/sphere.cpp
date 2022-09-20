#include "sphere.h"
#include "paddle.h"
#include "../window/input.h"
#include "lives.h"
#include "score.h"

using namespace Bubble;

Sphere::Sphere(Mesh* mesh, Material* material, f32 radius, Paddle& paddle): paddle(paddle), radius(radius) { 
	name = "Sphere";
	AddGraphicsComponent(mesh, material);
	AddSphereCollider(radius); 
	AddMoveComponent(Vec3(0.0f));
	direction = transform.GetPosition().normalize();
}

//void Start() {
//	direction = transform.GetPosition().normalize();
//}

void Sphere::Update(f32 deltaTime) { 
/*
	Vec3 pos = transform.GetPosition();
	if (Input::GetKey(GLFW_KEY_Y)) {
		transform.SetPosition(pos + Vec3(0.0f, 0.0f, -1.0f)*deltaTime*3.0f);
	}
	
	if (Input::GetKey(GLFW_KEY_H)) {
		transform.SetPosition(pos + Vec3(0.0f, 0.0f, 1.0f)*deltaTime*3.0f);
	}
	if (Input::GetKey(GLFW_KEY_G)) {
		transform.SetPosition(pos + Vec3(-1.0f, 0.0f, 0.0f)*deltaTime*3.0f);
	}
	if (Input::GetKey(GLFW_KEY_J)) {
		transform.SetPosition(pos + Vec3(1.0f, 0.0f, 0.0f)*deltaTime*3.0f);
	}
	//transform.SetPosition(transform.GetPosition() + Vec3(1.0f, 0.0f, 0.0f)*deltaTime);
	//transform.Rotate(0.0f, deltaTime*60.0f, 0.0f); 
	//transform.SetPosition(transform.GetPosition() - direction*deltaTime*3.0f);
*/
	if (!isAlive) return;

	if (Score::GetInstance()->GetTowerSize() == 0 || Lives::GetInstance()->GetLives() <= 0) {
        transform.SetPosition(Vec3(100.0f, 100.0f, 100.0f));
        isAlive = false;
        return;
    }

	if (!isFalling && transform.GetPosition().length() > 7.5f) {
		isFalling = true;
		direction = Vec3(0.0f, -1.0f, 0.0f);
		return;
	}

	if (isFalling) {
		transform.SetPosition(transform.GetPosition() + direction*deltaTime*5.0f);
	}

	if (isFalling && transform.GetPosition().y < -2.0f) {
		isFalling = false;
		Lives::GetInstance()->SubtractLife();
		if (Lives::GetInstance()->GetLives() <= 0) {
            transform.SetPosition(Vec3(100.0f, 100.0f, 100.0f));
            isAlive = false;
            return;

        }
		isMove = false;
		moveComponent->velocity = Vec3(0.0f);
		transform.SetPosition(paddle.GetPosition());
        direction = transform.GetPosition().normalize();
	}

	//if (Input::GetKey(Space)) {
	if (!isMove && Input::GetKey(UpArrow)) {
		isMove = true;
		direction = transform.GetPosition() + Vec3(0.1f, 0.0f, 0.1f);
		moveComponent->velocity = direction.normalize()*lineSpeed;
	}
	if (!isMove) {
		Vec3 position = transform.GetPosition();
		f32 rho = sqrt(position.x*position.x + position.z*position.z);
    	f32 phi = Degrees(atan2(position.z, position.x));
		if (Input::GetKey(LeftArrow)) {
			phi += deltaTime*speed;
			transform.SetPosition(Vec3(rho*cos(Radians(phi)), position.y, rho*sin(Radians(phi))));
			transform.Rotate(0.0f, deltaTime*speed, 0.0f);
    	}
		if (Input::GetKey(RightArrow)) {
			phi -= deltaTime*speed;
			transform.SetPosition(Vec3(rho*cos(Radians(phi)), position.y, rho*sin(Radians(phi))));
			transform.Rotate(0.0f, -deltaTime*speed, 0.0f);
    	}
	}	
}