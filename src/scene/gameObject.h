#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "mesh.h"
#include "transform.h"
#include "../renderer/material.h"

namespace Bubble {
    class GameObject;
    class Collider;
    class Light;
    class DirectionalLight;

    class MoveComponent {
    public:
        MoveComponent(const Vec3& v, Transform& t): velocity(v), transform(t) { }
        Vec3 velocity;
        Transform& transform;
    };

    class GraphicsComponent {
    public:
        GraphicsComponent(GameObject& go);
        GameObject& gameObject;
        Transform& transform;
        Mesh* mesh = nullptr;
        Material* material = nullptr;
    };

    class GameObject {
    public:
        std::string name = "";
        Transform transform;

        GameObject(): graphicsComponent(*this) {}
        virtual void Start() {};
        virtual void Update(f32 deltaTime) {};
        void ClearComponents();
        void AddGraphicsComponent(Mesh* mesh, Material* material);
        void ChangeMaterial(Material* material) { graphicsComponent.material = material; }
        void AddMoveComponent(const Vec3& velocity);
        void AddSphereCollider(f32 radius);
        void AddBrickCollider(f32 radiusIn = 1.0f, f32 radiusOut = 2.0f, f32 angle = 45.0f, f32 height = 1.0f); 
        void AddDirectionalLight(const Vec3& color, f32 intensity);

        inline GraphicsComponent& GetGraphicsComponent() { return graphicsComponent; }
        inline Collider* GetCollider() { return collider; }
        inline MoveComponent* GetMoveComponent() { return moveComponent; }
        void SetTrigger(bool value);

        virtual void OnCollisionEnter(Collider& collider) { }
        virtual void OnCollisionExit(Collider& collider) { }

        ~GameObject();
    
    protected:
        GraphicsComponent graphicsComponent;
        Collider* collider = nullptr;
        MoveComponent* moveComponent = nullptr;
        DirectionalLight* light = nullptr;
    };

}

#endif /* End of GAME_OBJECT_H */