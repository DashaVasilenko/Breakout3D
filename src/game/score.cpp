#include "score.h"
#include "../window/window.h"
#include "../window/input.h"
#include "../renderer/renderer.h"
#include "level.h"
#include "app.h"

using namespace Bubble;

Score* Score::instance = nullptr;

void Score::Init(Level* level) {
	this->level = level;
	fontBig.LoadFont((Application::path + "/../../data/font/aAlloyInk.ttf").c_str(), 128.0f);
	fontSmall.LoadFont((Application::path + "/../../data/font/aAlloyInk.ttf").c_str(), 64.0f);
}

void Score::Draw() {
	i32 height = Window::GetInstance()->GetHeight();
	i32 width = Window::GetInstance()->GetWidth();
	std::string str = "Score: ";
	std::string s = std::to_string(score);
	str.append(s);
	const char* text = str.c_str(); 
	Renderer::GetInstance()->DrawText(fontSmall, 10.0f, 60.0f, text);

	if (towerSize == 0) {
		Renderer::GetInstance()->DrawText(fontBig, width*0.5f - 288.0f, height*0.5f + 40.0f, "YOU WIN!");
		if (Input::GetKey(Enter)) {
			level->CreateLevel();
		}
	}
}