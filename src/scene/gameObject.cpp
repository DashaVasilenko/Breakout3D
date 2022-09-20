#include "gameObject.h"
#include "../renderer/renderer.h"
#include "../physics/physicsManager.h"
#include "../physics/collider.h"
#include "light.h"

namespace Bubble {
    GraphicsComponent::GraphicsComponent(GameObject& go): gameObject(go), transform(go.transform) { }
    
    void GameObject::AddGraphicsComponent(Mesh* mesh, Material* material) {
        if (!mesh || !material)
            return;

        graphicsComponent.mesh = mesh;
        graphicsComponent.material = material;

        Renderer::GetInstance()->RegisterGraphicsComponent(&graphicsComponent);

    }

    void GameObject::AddMoveComponent(const Vec3& velocity) {
        if (moveComponent)
            return;

        moveComponent = new MoveComponent(velocity, transform);
        PhysicsManager::GetInstance()->RegisterMoveComponent(moveComponent);
    }

    void GameObject::AddSphereCollider(f32 radius) {
        if (collider)
            return;

        collider = new SphereCollider(*this, radius);
        PhysicsManager::GetInstance()->RegisterCollider(collider);
    }

    void GameObject::AddBrickCollider(f32 radiusIn, f32 radiusOut, f32 angle, f32 height) {
        if (collider)
            return;

        collider = new BrickCollider(*this, radiusIn, radiusOut, angle, height);
        PhysicsManager::GetInstance()->RegisterCollider(collider);
    }

    void GameObject::SetTrigger(bool value) { collider->SetTrigger(value); }

    void GameObject::AddDirectionalLight(const Vec3& color, f32 intensity) {
        if (light)
            return;

        light = new DirectionalLight(transform, color, intensity);
        light->GenerateShadowMap(true);
        Renderer::GetInstance()->RegisterDirectionalLight(light);
    }

    void GameObject::ClearComponents() {
        Renderer::GetInstance()->DeregisterGraphicsComponent(&graphicsComponent);
        PhysicsManager::GetInstance()->DeregisterMoveComponent(moveComponent);
        PhysicsManager::GetInstance()->DeregisterCollider(collider);
        Renderer::GetInstance()->DeregisterDirectionalLight(light);

        if (light) {
            delete light;
            light = nullptr;
        }

        if (collider) {
            delete collider;
            collider = nullptr;
        }

        if (moveComponent) {
            delete moveComponent;
            moveComponent = nullptr;
        }
    }

    GameObject::~GameObject() {
        ClearComponents();
    }

}