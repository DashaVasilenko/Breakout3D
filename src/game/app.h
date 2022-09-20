#ifndef APP_H
#define APP_H

#include <string>

namespace Bubble {
    class Window;
    class Renderer;
    class PhysicsManager;
}

class ResourceManager;
class Level;
class Lives;
class Score;


class Application {
public:
    static std::string path; // abs path to app
    
    int Init();
    void Run();
    ~Application();
private:
    Bubble::Window* window;
    ResourceManager* resourceManager;
    Bubble::Renderer* renderer;
    Bubble::PhysicsManager* physicsManager;
    Level* level;
    Lives* lives;
    Score* score;
};

#endif