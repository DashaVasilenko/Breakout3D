#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include <vector>
#include <unordered_map>
#include "collider.h"

namespace Bubble {
    class PhysicsComponent;
    class MoveComponent;
 
    struct PairHash {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2> &pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    class PhysicsManager {
    public:
        inline static PhysicsManager* GetInstance() { if (!instance) instance = new PhysicsManager(); return instance; }

        void RegisterCollider(Collider* collider);
        void DeregisterCollider(Collider* collider);
        void RegisterMoveComponent(MoveComponent* moveComponent);
        void DeregisterMoveComponent(MoveComponent* moveComponent);

        void Update(f32 deltaTime);

    private:
        std::unordered_map<std::pair<Collider*, Collider*>, bool, PairHash> previousFrameCollisions;
        std::vector<Collider*> colliders;
        std::vector<MoveComponent*> moveComponents;

        static PhysicsManager* instance;
        PhysicsManager() {}
    };

}

#endif /* End of PHYSICS_MANAGER_H */