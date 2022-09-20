#ifndef COLLIDER_H
#define COLLIDER_H

#include "../scene/gameObject.h"
#include "../math/vector.h"
#include "../core/types.h"

namespace Bubble {

    class Collider {
    public:
        Transform& transform;
        GameObject& gameObject;
        bool isTrigger = false;
        
        enum Type {
            SphereCollider = 0,
            BrickCollider = 1,
        };

        inline Type GetType() const { return type; }
        inline void SetTrigger(bool value) { isTrigger = value; }
        virtual ~Collider() { }

    protected:
        Collider(GameObject& go): transform(go.transform), gameObject(go) { }
        Type type = Type::SphereCollider;
    };

    class SphereCollider: public Collider {
    public:
        f32 radius = 1.0f;

        SphereCollider(GameObject& go, f32 radius = 1.0f): Collider(go), radius(radius) { type = Type::SphereCollider; }
        virtual ~SphereCollider() { }

    private:
    
    };

    class BrickCollider: public Collider {
    public:
        f32 radiusIn = 1.0f;
        f32 radiusOut = 2.0f; 
        f32 angle = 45.0f; 
        f32 height = 1.0f;

        BrickCollider(GameObject& go, f32 radiusIn = 1.0f, f32 radiusOut = 2.0f, f32 angle = 45.0f, f32 height = 1.0f): 
            Collider(go), radiusIn(radiusIn), radiusOut(radiusOut), angle(angle), height(height) { type = Type::BrickCollider; } 
        virtual ~BrickCollider() { }

    private:
    
    };

}

#endif /* End of COLLIDER_H */