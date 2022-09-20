#include "../scene/camera.h" // <------- 

#include <Windows.h>


#include <filesystem>
#include <vector>
#include <array>

#include "../window/window.h"
#include "../window/input.h"
#include "../renderer/renderer.h"
#include "../physics/physicsManager.h"
#include "resourceManager.h"
#include "app.h"
#include "level.h"
#include "score.h"
#include "lives.h"


using namespace Bubble;

std::string Application::path = "";

int Application::Init() {
    // get abs path to app
    char ownPath[MAX_PATH]; 
    HMODULE hModule = GetModuleHandle(NULL); // When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
    if (hModule != NULL) {
        if (GetModuleFileNameA(hModule, ownPath, (sizeof(ownPath))) == 0) {
            return -1;
        }
    }
    path = std::filesystem::path(ownPath).parent_path().u8string();

    srand((unsigned int)time(0));

    window = Window::GetInstance();
 	window->SetWidth(1080);
 	window->SetHeight(768);
 	window->SetName("Window");
 	window->Init();

    resourceManager  = ResourceManager::GetInstance();

	renderer = Renderer::GetInstance();
	renderer->Init();

	physicsManager = PhysicsManager::GetInstance();

	level = new Level();
	level->LoadResources();

	lives = Lives::GetInstance();
	lives->Init(level);

	score = Score::GetInstance();
	score->Init(level);

	level->CreateLevel();

    return 0;
}

void Application::Run() {
    double currentTime = 0.0;
 	double lastTime = 0.0;
    
    // application loop
    while (!glfwWindowShouldClose(window->GetPointer())) {
		currentTime = glfwGetTime();
 		float deltaTime = (float)(currentTime - lastTime);
 		lastTime = currentTime;

		level->Update(deltaTime);
		physicsManager->Update(deltaTime);

		renderer->Draw();
		lives->Draw();
		score->Draw();

     	glfwPollEvents();
		glfwSwapBuffers(window->GetPointer());
 	}
}

Application::~Application() {
    delete level;
	delete physicsManager;
	delete renderer;
	delete resourceManager;
	delete window;
}