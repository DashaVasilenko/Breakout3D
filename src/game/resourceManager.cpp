#include "resourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::~ResourceManager() {
    for (auto& elem: textureMap)
        delete elem.second;
    for (auto& elem: shaderProgramMap)
		delete elem.second;
	for (auto& elem: materialMap)
		delete elem.second;
	for (auto& elem: meshMap)
		delete elem.second;
}