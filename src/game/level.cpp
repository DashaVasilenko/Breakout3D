#include "level.h"
#include "score.h"
#include "brick.h"
#include "sphere.h"
#include "paddle.h"
#include "box.h"
#include "../renderer/renderer.h"
#include "../window/input.h"
#include "../renderer/shaderProgram.h"
#include "../renderer/texture.h"
#include "resourceManager.h"
#include "app.h"

using namespace Bubble;

void Scene::AddGameObject(GameObject* go) {
	gameObjects.push_back(go);
}

void Scene::RemoveGameObject(GameObject* go) {
	auto it = std::find(gameObjects.begin(), gameObjects.end(), go);
    if (it != gameObjects.end()) {
        (*it) = gameObjects.back();
        gameObjects.pop_back();
    }
}

void Scene::Update(f32 deltaTime) {
	for (GameObject* go: gameObjects)
		go->Update(deltaTime);
}

void Scene::ClearScene() {
	for (GameObject* go: gameObjects)
		delete go;
	gameObjects.clear();
}

Scene::~Scene() {
	for (GameObject* go: gameObjects)
		delete go;
}

//-----------------------------------------------------------------------------------------------------
void Level::LoadResources() {
	cameraPosition_1 = Vec3(0.0f, 15.0f, 12.0f);
	cameraPosition_2 = Vec3(sqrtf(108.0f), 15.0f, -6.0f);
	cameraPosition_3 = Vec3(-sqrtf(108.0f), 15.0f, -6.0f);
	cameraPosition_4 = Vec3(0.0f, 14.0f, 0.0f);
	cameraHeight = 20.0f; 
	Window* window = Window::GetInstance();
	camera.Init((f32)window->GetWidth()/(f32)window->GetHeight(), 45.0f, 0.1f, 100.0f, cameraPosition_1);
	Renderer::GetInstance()->SetMainCamera(&camera);
	ResourceManager* r = ResourceManager::GetInstance();

	std::map<GLenum, std::string> mapSources;
    mapSources[GL_VERTEX_SHADER] = Application::path + "/../../data/glsl/phong_vertex.glsl";
	mapSources[GL_FRAGMENT_SHADER] = Application::path + "/../../data/glsl/phong_fragment.glsl";
	ShaderProgram* program = new ShaderProgram();
	program->Init(mapSources);
	program->Compile();
	program->Link();
	r->shaderProgramMap["Phong"] = program;

    mapSources[GL_VERTEX_SHADER] = Application::path + "/../../data/glsl/phong_vertex.glsl";
	mapSources[GL_FRAGMENT_SHADER] = Application::path + "/../../data/glsl/phong_texture_fragment.glsl";
	ShaderProgram* phongTextureProgram = new ShaderProgram();
	phongTextureProgram->Init(mapSources);
	phongTextureProgram->Compile();
	phongTextureProgram->Link();
	r->shaderProgramMap["PhongTexture"] = phongTextureProgram;

	mapSources[GL_VERTEX_SHADER] = Application::path + "/../../data/glsl/phong_vertex.glsl";
	mapSources[GL_FRAGMENT_SHADER] = Application::path + "/../../data/glsl/phong_crack_texture_fragment.glsl";
	ShaderProgram* phongCrackTextureProgram = new ShaderProgram();
	phongCrackTextureProgram->Init(mapSources);
	phongCrackTextureProgram->Compile();
	phongCrackTextureProgram->Link();
	r->shaderProgramMap["PhongCrackTexture"] = phongCrackTextureProgram;

	mapSources[GL_VERTEX_SHADER] = Application::path + "/../../data/glsl/phong_vertex.glsl";
	mapSources[GL_FRAGMENT_SHADER] = Application::path + "/../../data/glsl/phong_texture_floor_fragment.glsl";
	ShaderProgram* phongTextureFloorProgram = new ShaderProgram();
	phongTextureFloorProgram->Init(mapSources);
	phongTextureFloorProgram->Compile();
	phongTextureFloorProgram->Link();
	r->shaderProgramMap["PhongFloorTexture"] = phongTextureFloorProgram;

	brickHeight = 1.0f;
	cntPyramidStores = 3;
	cntBricksPerStore = 12;
	brickAngle = 360.0f/cntBricksPerStore;
	paddleRadiusIn = 6.5f;
	paddleRadiusOut = 7.0f;

	r->meshMap["Floor"] = Mesh::CreateBox(15.0f, 0.1f, 15.0f);
	r->meshMap["Sphere"] = Mesh::CreateSphere(0.35f, 30, 30);
	r->meshMap["Brick"] = Mesh::CreateBrick(1.5f, 2.0f, brickAngle, 10, brickHeight);
	r->meshMap["Paddle40"] = Mesh::CreateBrick(paddleRadiusIn, paddleRadiusOut, 40.0f, 10, 0.5f);
	r->meshMap["Paddle50"] = Mesh::CreateBrick(paddleRadiusIn, paddleRadiusOut, 50.0f, 10, 0.5f);
	r->meshMap["Paddle60"] = Mesh::CreateBrick(paddleRadiusIn, paddleRadiusOut, 60.0f, 10, 0.5f);
	r->meshMap["Paddle70"] = Mesh::CreateBrick(paddleRadiusIn, paddleRadiusOut, 70.0f, 10, 0.5f);
	r->meshMap["Paddle80"] = Mesh::CreateBrick(paddleRadiusIn, paddleRadiusOut, 80.0f, 10, 0.5f);
	r->meshMap["Suzanne"] = Mesh::CreateFromObj((Application::path + "/../../data/suzanne.obj").c_str());
	r->meshMap["Heart"] = Mesh::CreateFromObj((Application::path + "/../../data/models/heart.obj").c_str());
	r->meshMap["Coin"] = Mesh::CreateFromObj((Application::path + "/../../data/models/coin.obj").c_str());
	r->meshMap["SpeedUp"] = Mesh::CreateFromObj((Application::path + "/../../data/models/speed_up.obj").c_str());
	r->meshMap["SpeedDown"] = Mesh::CreateFromObj((Application::path + "/../../data/models/speed_down.obj").c_str());
	r->meshMap["PaddleIncrease"] = Mesh::CreateFromObj((Application::path + "/../../data/models/paddle_increase.obj").c_str());
	r->meshMap["PaddleDecrease"] = Mesh::CreateFromObj((Application::path + "/../../data/models/paddle_decrease.obj").c_str());

	Texture2D* grassAmbient = new Texture2D();
	grassAmbient->Init(Application::path + "/../../data/texture/grass_ao.png");
	r->textureMap["GrassAmbient"] = grassAmbient;

	Texture2D* grassDiffuse = new Texture2D();
	grassDiffuse->Init(Application::path + "/../../data/texture/grass_diffuse.png");
	r->textureMap["GrassDiffuse"] = grassDiffuse;
	Texture2D* grassSpecular = new Texture2D();
	grassSpecular->Init(Application::path + "/../../data/texture/grass_specular.png");
	r->textureMap["GrassSpecular"] = grassSpecular;
	Texture2D* grassNormal = new Texture2D();
	grassNormal->Init(Application::path + "/../../data/texture/grass_normal.png");
	r->textureMap["GrassNormal"] = grassNormal;

	Texture2D* stoneAmbient = new Texture2D();
	stoneAmbient->Init(Application::path + "/../../data/texture/stone_ao.png");
	r->textureMap["StoneAmbient"] = stoneAmbient;
	Texture2D* stoneDiffuse = new Texture2D();
	stoneDiffuse->Init(Application::path + "/../../data/texture/stone_diffuse.png");
	r->textureMap["StoneDiffuse"] = stoneDiffuse;
	Texture2D* stoneSpecular = new Texture2D();
	stoneSpecular->Init(Application::path + "/../../data/texture/stone_specular.png");
	r->textureMap["StoneSpecular"] = stoneSpecular;
	Texture2D* stoneNormal = new Texture2D();
	stoneNormal->Init(Application::path + "/../../data/texture/stone_normal.png");
	r->textureMap["StoneNormal"] = stoneNormal;

	Texture2D* honeyAmbient = new Texture2D();
	honeyAmbient->Init(Application::path + "/../../data/texture/honey_ao.png");
	r->textureMap["HoneyAmbient"] = honeyAmbient;
	Texture2D* honeyDiffuse = new Texture2D();
	honeyDiffuse->Init(Application::path + "/../../data/texture/honey_diffuse.png");
	r->textureMap["HoneyDiffuse"] = honeyDiffuse;
	Texture2D* honeySpecular = new Texture2D();
	honeySpecular->Init(Application::path + "/../../data/texture/honey_specular.png");
	r->textureMap["HoneySpecular"] = honeySpecular;
	Texture2D* honeyNormal = new Texture2D();
	honeyNormal->Init(Application::path + "/../../data/texture/honey_normal.png");
	r->textureMap["HoneyNormal"] = honeyNormal;

	Texture2D* honeyCrackDiffuse = new Texture2D();
	honeyCrackDiffuse->Init(Application::path + "/../../data/texture/honey_crack_diffuse.png");
	r->textureMap["HoneyCrackDiffuse"] = honeyCrackDiffuse;
	Texture2D* honeyPowerUpDiffuse = new Texture2D();
	honeyPowerUpDiffuse->Init(Application::path + "/../../data/texture/honey_power_up_diffuse.png");
	r->textureMap["HoneyPowerUpDiffuse"] = honeyPowerUpDiffuse;

	Texture2D* beeLinesAmbient = new Texture2D();
	beeLinesAmbient->Init(Application::path + "/../../data/texture/bee_lines_ao.png");
	r->textureMap["BeeLinesAmbient"] = beeLinesAmbient;
	Texture2D* beeLinesDiffuse = new Texture2D();
	beeLinesDiffuse->Init(Application::path + "/../../data/texture/bee_lines_diffuse.png");
	r->textureMap["BeeLinesDiffuse"] = beeLinesDiffuse;
	Texture2D* beeLinesSpecular = new Texture2D();
	beeLinesSpecular->Init(Application::path + "/../../data/texture/bee_lines_specular.png");
	r->textureMap["BeeLinesSpecular"] = beeLinesSpecular;
	Texture2D* beeLinesNormal = new Texture2D();
	beeLinesNormal->Init(Application::path + "/../../data/texture/bee_lines_normal.png");
	r->textureMap["BeeLinesNormal"] = beeLinesNormal;

	Texture2D* coinAmbient = new Texture2D();
	coinAmbient->Init(Application::path + "/../../data/texture/coin_ao.png");
	r->textureMap["CoinAmbient"] = coinAmbient;
	Texture2D* coinDiffuse = new Texture2D();
	coinDiffuse->Init(Application::path + "/../../data/texture/coin_diffuse.png");
	r->textureMap["CoinDiffuse"] = coinDiffuse;
	Texture2D* coinSpecular = new Texture2D();
	coinSpecular->Init(Application::path + "/../../data/texture/coin_specular.png");
	r->textureMap["CoinSpecular"] = coinSpecular;
	Texture2D* coinNormal = new Texture2D();
	coinNormal->Init(Application::path + "/../../data/texture/coin_normal.png");
	r->textureMap["CoinNormal"] = coinNormal;

	PhongMaterial* boxMaterial = new PhongMaterial(r->shaderProgramMap["Phong"], Vec3(1.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	r->materialMap["BoxMaterial"] = boxMaterial;
	PhongMaterial* sphereMaterial = new PhongMaterial(r->shaderProgramMap["Phong"], Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	r->materialMap["SphereMaterial"] = sphereMaterial;
	PhongMaterial* heartMaterial = new PhongMaterial(r->shaderProgramMap["Phong"], Vec3(1.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	r->materialMap["HeartMaterial"] = heartMaterial;
	PhongMaterial* blueMaterial = new PhongMaterial(r->shaderProgramMap["Phong"], Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f));
	r->materialMap["BlueMaterial"] = blueMaterial;
	PhongMaterial* redMaterial = new PhongMaterial(r->shaderProgramMap["Phong"], Vec3(1.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	r->materialMap["RedMaterial"] = redMaterial;

	PhongTextureFloorMaterial* floorMaterial = new PhongTextureFloorMaterial(r->shaderProgramMap["PhongFloorTexture"], grassAmbient, grassDiffuse, grassSpecular/*, grassNormal*/);
	r->materialMap["FloorMaterial"] = floorMaterial;
	PhongTextureMaterial* paddleMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], stoneAmbient, stoneDiffuse, stoneSpecular/*, grassNormal*/, Vec2(2.0f, 0.2f));
	r->materialMap["PaddleMaterial"] = paddleMaterial;
	PhongTextureMaterial* brickMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], honeyAmbient, honeyDiffuse, honeySpecular/*, grassNormal*/, Vec2(1.0f, 1.0f));
	r->materialMap["BrickMaterial"] = brickMaterial;
	PhongTextureMaterial* brickCrackMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongCrackTexture"], honeyAmbient, honeyCrackDiffuse, honeySpecular/*, grassNormal*/, Vec2(1.0f, 1.0f));
	r->materialMap["BrickCrackMaterial"] = brickCrackMaterial;
	PhongTextureMaterial* brickPowerUpMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], honeyAmbient, honeyPowerUpDiffuse, honeySpecular/*, grassNormal*/, Vec2(1.0f, 1.0f));
	r->materialMap["BrickPowerUpMaterial"] = brickPowerUpMaterial;
	PhongTextureMaterial* coinMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], coinAmbient, coinDiffuse, coinSpecular/*, grassNormal*/, Vec2(1.0f, 1.0f));
	r->materialMap["CoinMaterial"] = coinMaterial;
	PhongTextureMaterial* beeLineMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], beeLinesAmbient, beeLinesDiffuse, beeLinesSpecular/*, grassNormal*/, Vec2(1.0f, 1.0f));
	r->materialMap["BeeLineMaterial"] = beeLineMaterial;
}
	
void Level::CreateLevel() {
	scene.ClearScene();
	bricks.clear();
	ResourceManager* r = ResourceManager::GetInstance();

	GameObject* dirLight_1 = new GameObject();
	dirLight_1->transform.Rotate(60.0f, 0.0f, 45.0f);
	dirLight_1->transform.SetPosition(0.0f, 14.0f, 12.0f);
	dirLight_1->AddDirectionalLight(Vec3(1.0f, 1.0f, 1.0f), 1.0f);
	scene.AddGameObject(dirLight_1);

	GameObject* dirLight_2 = new GameObject();
	dirLight_2->transform.Rotate(120.0f, 0.0f, 45.0f);
	dirLight_2->transform.SetPosition(0.0f, 14.0f, -12.0f);
	dirLight_2->AddDirectionalLight(Vec3(1.0f, 1.0f, 1.0f), 1.0f);
	scene.AddGameObject(dirLight_2);

	GameObject* dirLight_3 = new GameObject();
	dirLight_3->transform.Rotate(0.0f, 60.0f, 45.0f);
	dirLight_3->transform.SetPosition(-12.0f, 14.0f, 0.0f);
	dirLight_3->AddDirectionalLight(Vec3(1.0f, 1.0f, 1.0f), 1.0f);
	scene.AddGameObject(dirLight_3);

	GameObject* dirLight_4 = new GameObject();
	dirLight_4->transform.Rotate(0.0f, 120.0f, 45.0f);
	dirLight_4->transform.SetPosition(12.0f, 14.0f, -12.0f);
	dirLight_4->AddDirectionalLight(Vec3(1.0f, 1.0f, 1.0f), 1.0f);
	scene.AddGameObject(dirLight_4);

	//Box* suzanne = new Box(r->meshMap["Suzanne"],  r->materialMap["FloorMaterial"]);
	//suzanne->transform.SetPosition(0.0f, 10.0f, 0.0f);
	//scene.AddGameObject(suzanne);

	Box* floor = new Box(r->meshMap["Floor"],  r->materialMap["FloorMaterial"]);
	floor->transform.SetPosition(0.0f, -0.3f, 0.0f);
	scene.AddGameObject(floor);

	Paddle* paddle_1 = new Paddle(r->meshMap["Paddle60"], r->materialMap["PaddleMaterial"], paddleRadiusIn, paddleRadiusOut, 60.0f, 0.5f);
	paddle_1->SetRadii(paddleRadiusIn, paddleRadiusOut);
	paddle_1->transform.SetRotation(0.0f, -30.0f, 0.0f);
	scene.AddGameObject(paddle_1);
	Paddle* paddle_2 = new Paddle(r->meshMap["Paddle60"], r->materialMap["PaddleMaterial"], paddleRadiusIn, paddleRadiusOut, 60.0f, 0.5f);
	paddle_2->SetRadii(paddleRadiusIn, paddleRadiusOut);
	paddle_2->transform.SetRotation(0.0f, -150.0f, 0.0f);
	scene.AddGameObject(paddle_2);
	Paddle* paddle_3 = new Paddle(r->meshMap["Paddle60"], r->materialMap["PaddleMaterial"], paddleRadiusIn, paddleRadiusOut, 60.0f, 0.5f);
	paddle_3->SetRadii(paddleRadiusIn, paddleRadiusOut);
	paddle_3->transform.SetRotation(0.0f, -270.0f, 0.0f);
	scene.AddGameObject(paddle_3);

	sphere = new Sphere(r->meshMap["Sphere"], r->materialMap["BeeLineMaterial"], 0.35f, *paddle_3);
	sphere->transform.SetPosition(paddle_3->GetPosition());
	sphere->transform.Rotate(90.0f, 0.0f, 0.0f);
	scene.AddGameObject(sphere);

	paddle_1->SetSphere(sphere);
	paddle_1->SetPaddles(paddle_2, paddle_3);
	paddle_2->SetSphere(sphere);
	paddle_2->SetPaddles(paddle_1, paddle_3);
	paddle_3->SetSphere(sphere);
	paddle_3->SetPaddles(paddle_1, paddle_2);

	// top floor  diffuseColor
	for (int j = 0; j < cntBricksPerStore; j++) {
		PhongTextureMaterial* brickMaterial;
		bool isPowerUp = false;
		if (rand()%100 < 20.0f) {
			brickMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], r->textureMap["HoneyAmbient"], 
								r->textureMap["HoneyPowerUpDiffuse"], r->textureMap["HoneySpecular"], Vec2(1.0f, 1.0f));
			isPowerUp = true;
		} else {
 			brickMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], r->textureMap["HoneyAmbient"], 
								r->textureMap["HoneyDiffuse"], r->textureMap["HoneySpecular"], Vec2(1.0f, 1.0f));
		}
		PhongTextureMaterial* brickCrackMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongCrackTexture"], 
							r->textureMap["HoneyAmbient"], r->textureMap["HoneyCrackDiffuse"], r->textureMap["HoneySpecular"], Vec2(1.0f, 1.0f));
		i32 brickLives;
		if (isPowerUp || rand()%100 < 49.0f)
			brickLives = 1;
		else 
			brickLives = 2;
		bricks.push_back(new Brick(r->meshMap["Brick"], brickMaterial, brickCrackMaterial, 1.5f, 2.0f, brickAngle, brickHeight, brickLives, isPowerUp, nullptr, *sphere, scene));
		bricks[j]->transform.SetRotation(0.0f, 0.3f + brickAngle*j, 0.0f);
		bricks[j]->transform.SetPosition(0.0f, 0.3f + brickHeight*(cntPyramidStores - 1), 0.0f);
	}

	for (int i = 1; i < cntPyramidStores; i++) { 
		for (int j = 0; j < cntBricksPerStore; j++) {
			PhongTextureMaterial* brickMaterial;
			bool isPowerUp = false;
			if (rand()%100 < 20.0f) {
				brickMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], r->textureMap["HoneyAmbient"], 
									r->textureMap["HoneyPowerUpDiffuse"], r->textureMap["HoneySpecular"], Vec2(1.0f, 1.0f));
				isPowerUp = true;
			} else {
 				brickMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongTexture"], r->textureMap["HoneyAmbient"], 
									r->textureMap["HoneyDiffuse"], r->textureMap["HoneySpecular"], Vec2(1.0f, 1.0f));
			}
			PhongTextureMaterial* brickCrackMaterial = new PhongTextureMaterial(r->shaderProgramMap["PhongCrackTexture"], 
							r->textureMap["HoneyAmbient"], r->textureMap["HoneyCrackDiffuse"], r->textureMap["HoneySpecular"], Vec2(1.0f, 1.0f));
			i32 brickLives;
			if (isPowerUp || rand()%100 < 49.0f)
				brickLives = 1;
			else 
				brickLives = 2;
			bricks.push_back(new Brick(r->meshMap["Brick"], brickMaterial, brickCrackMaterial, 1.5f, 2.0f, brickAngle, brickHeight, brickLives, isPowerUp, bricks[(i - 1)*12 + j], *sphere, scene));
			bricks[i*12 + j]->transform.SetRotation(0.0f, 0.3f + brickAngle*j, 0.0f);
			bricks[i*12 + j]->transform.SetPosition(0.0f, 0.3f + brickHeight*(cntPyramidStores - 1 - i), 0.0f);
		}
	}

	for (auto& elem: bricks) 
		scene.AddGameObject(elem);

	Score::GetInstance()->SetTowerSize(cntBricksPerStore*cntPyramidStores);
}

void Level::Update(f32 deltaTime) {
	if (Input::GetKeyDown(Key1))
		camera.RecomputeCamera(cameraPosition_1);
	else if (Input::GetKeyDown(Key2))
		camera.RecomputeCamera(cameraPosition_2);
	else if (Input::GetKeyDown(Key3))
		camera.RecomputeCamera(cameraPosition_3);
	else if (Input::GetKeyDown(Key4))
		camera.TopView(cameraHeight);

	Input::Update(Window::GetInstance()->GetPointer());

	for (Brick* brick: bricks) {
		Vec3 rayOrigin = camera.GetPosition();
		Vec3 rayDir = (sphere->GetPosition() - rayOrigin).normalize();
		Vec3 brickBoundSpherePos = brick->GetPosition();
		f32 brickBoundSphereRadius = 1.0f;

		// compute ray-sphere intersection 
		Vec3 v = brickBoundSpherePos - rayOrigin;
		f32 b = Vec3::dot(v, rayDir);
		f32 c = Vec3::dot(v, v) - brickBoundSphereRadius*brickBoundSphereRadius;
		f32 d = b*b - c;

		// no intersection
		if (d < 0.0f) {
			brick->SetDrawWireframe(false);
			continue;
		}
		d = sqrt(d);

		// intersection
		//f32 t = b - d;
  		//if (t <= 0.0f)
  		//	t = b + d;

		// intersection with farthest point 
		f32 t = b + d;
  		
		Vec3 intersectionPoint = rayOrigin + rayDir*t;
		if (Vec3::distance(intersectionPoint, rayOrigin) < Vec3::distance(sphere->GetPosition(), rayOrigin)) 
			brick->SetDrawWireframe(true);
		else 
			brick->SetDrawWireframe(false);
	}

	camera.Update(deltaTime);
	scene.Update(deltaTime);
}

Level::~Level() {

}