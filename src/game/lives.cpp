#include "lives.h"
#include "score.h"
#include "../window/window.h"
#include "../window/input.h"
#include "../renderer/renderer.h"
#include "level.h"
#include "app.h"

using namespace Bubble;

Lives* Lives::instance = nullptr;

void Lives::Init(Level* level) {
	this->level = level;
	fontBig.LoadFont((Application::path + "/../../data/font/aAlloyInk.ttf").c_str(), 128.0f);
	fontSmall.LoadFont((Application::path + "/../../data/font/aAlloyInk.ttf").c_str(), 64.0f);
}

void Lives::Draw() {
	i32 height = Window::GetInstance()->GetHeight();
	i32 width = Window::GetInstance()->GetWidth();
	std::string str = "Lives: ";
	std::string s = std::to_string(lives);
	str.append(s);
	const char* text = str.c_str(); 
	Renderer::GetInstance()->DrawText(fontSmall, width - 300.0f, 60.0f, text);
		
	if (lives <= 0) {
		Renderer::GetInstance()->DrawText(fontBig, width*0.5f - 370.0f, height*0.5f + 40.0f, "GAME OVER!");
		if (Input::GetKey(Enter)) {
			lives = 3;
			Score::GetInstance()->SetScore(0);
			level->CreateLevel();
		}	
	}
}