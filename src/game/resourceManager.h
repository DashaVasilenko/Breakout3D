#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>

#include "../renderer/shaderProgram.h"
#include "../scene/gameObject.h"
#include "../renderer/texture.h"

class ResourceManager {
public:
    std::unordered_map<std::string, const Bubble::ShaderProgram*> shaderProgramMap;
	std::unordered_map<std::string, Bubble::Mesh*> meshMap;
	std::unordered_map<std::string, Bubble::Texture2D*> textureMap;
	std::unordered_map<std::string, Bubble::Material*> materialMap;

    inline static ResourceManager* GetInstance() { if (!instance) instance = new ResourceManager(); return instance; }
    ~ResourceManager();
    
private:
    static ResourceManager* instance;
    ResourceManager() {}
};

#endif