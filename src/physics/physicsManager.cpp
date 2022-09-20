#include "physicsManager.h"
#include "../scene/gameObject.h"

namespace Bubble {
    PhysicsManager* PhysicsManager::instance = nullptr;

    struct CollisionInfo {
        Vec3 position;
        Vec3 normal; // for 1st collider
        f32 penetrationDepth;
    }; 

    static bool SphereSphere(Collider* collider1, Collider* collider2, CollisionInfo& info) {
        SphereCollider* sphereCollider1 = (SphereCollider*)collider1;
        SphereCollider* sphereCollider2 = (SphereCollider*)collider2;

        Vec3 pos1 = sphereCollider1->transform.GetPosition();
        Vec3 pos2 = sphereCollider2->transform.GetPosition();
        f32 r1 = sphereCollider1->radius;
        f32 r2 = sphereCollider2->radius;
        Vec3 distanceVec = pos1 - pos2;
        f32 distance = distanceVec.length();

        if (distance > r1 + r2)
            return false;

        info.normal = distanceVec/distance;
        info.penetrationDepth = r1 + r2 - distance;

        return true;
    }


    // collider1 - SphereCollider, collider2 - BrickCollider
    static bool SphereBrick(Collider* collider1, Collider* collider2, CollisionInfo& info) {
        SphereCollider* sphereCollider = (SphereCollider*)collider1;
        BrickCollider* brickCollider = (BrickCollider*)collider2;

        //f32 eps = 0.05f;

        f32 radiusIn = brickCollider->radiusIn;
        f32 radiusOut = brickCollider->radiusOut;
        f32 brickWidth = 0.5f*(radiusOut - radiusIn);
        f32 brickAngle = (brickCollider->angle)*0.5f;
        Vec3 spherePos = sphereCollider->transform.GetPosition();
        //printf("sphere pos [%f, %f, %f]\n", spherePos.x, spherePos.y, spherePos.z);
        f32 sphereRadius = sphereCollider->radius; // + eps;
        Vec4 pos = RotationMatrix(brickCollider->transform.GetRotation())*Vec4((radiusIn + radiusOut)*0.5f, 0.0f, 0.0f, 1.0f);
        //Vec3 brickPos = Vec3(-pos.x, pos.y, pos.z);
        Vec3 brickPos = Vec3(pos.x, brickCollider->transform.GetPosition().y, pos.z);
        //printf("sphere pos [%f, %f, %f]\n", spherePos.x, spherePos.y, spherePos.z);
        //printf("brick pos [%f, %f, %f]\n", brickPos.x, brickPos.y, brickPos.z);

        f32 rhoSphere = sqrt(spherePos.x*spherePos.x + spherePos.z*spherePos.z);
        f32 phiSphere = Degrees(atan2(spherePos.z, spherePos.x));
        if (phiSphere < 0.0f) phiSphere += 360.0f;
        //printf("sphere rho = %f phi = %f\n", rhoSphere, phiSphere);

        f32 rhoBrick = sqrt(brickPos.x*brickPos.x + brickPos.z*brickPos.z);
        f32 phiBrick = Degrees(atan2(brickPos.z, brickPos.x));
        if (phiBrick < 0.0f) phiBrick += 360.0f;
        //printf("brick rho = %f phi = %f\n", rhoBrick, phiBrick);

        //printf("brick pos [%f, %f, %f] sphere pos [%f, %f, %f]\n", brickPos.x, brickPos.y, brickPos.z, spherePos.x, spherePos.y, spherePos.z);
        if (brickPos.y - brickCollider->height*0.5f >= spherePos.y + sphereRadius) return false; // brick above the sphere and does not intersect
        if (rhoSphere + sphereRadius < rhoBrick - brickWidth) return false;
        if (rhoSphere - sphereRadius > rhoBrick + brickWidth) return false;
    /*
        if (brickPos.y - brickCollider->height*0.5f >= spherePos.y + sphereRadius) {
            printf("1\n");
            return false; // brick above the sphere and does not intersect
        }
        if (rhoSphere + sphereRadius < rhoBrick - brickWidth) {
            printf("2\n");
            return false; // brick above the sphere and does not intersect
        }
        if (rhoSphere - sphereRadius > rhoBrick + brickWidth) {
            printf("3\n");
            return false; // brick above the sphere and does not intersect
        }
    */      
        f32 angle1 = phiBrick - brickAngle - 3.0f;
        bool flag = false;
        if (angle1 < 0.0f) {
            angle1 += 360.0f;
            flag = true;
        }

        f32 angle2 = phiBrick + brickAngle + 3.0f;
        if (angle2 < 0.0f || flag) angle2 += 360.0f;
        f32 sphereAngle = phiSphere;
        if (sphereAngle < 180.0f && (flag || angle2 >= 360.0f)) sphereAngle += 360.0f;
        //printf("sphereAngle = %f angle1 = %f angle2 = %f\n", sphereAngle, angle1, angle2);

        if (angle1 < sphereAngle && sphereAngle < angle2) {
            if (rhoSphere < rhoBrick) info.normal = -spherePos/spherePos.length();
            else info.normal = spherePos/spherePos.length();

            //f32 distance = Vec3::distance(spherePos, spherePos.normalize()*(radiusIn + radiusOut)*0.5f);
            f32 distance = abs(spherePos.length() - (radiusIn + radiusOut)*0.5f);
            info.penetrationDepth =  std::max(0.01f, brickWidth + sphereRadius - distance);
            //printf("normal [%f, %f, %f]\n", info.normal.x, info.normal.y, info.normal.z);
            //printf("penetration %f\n", info.penetrationDepth);
            //printf("brickWidth %f, sphereRadius %f, distance %f\n", brickWidth, sphereRadius, distance);
            return true;
        }

        f32 angle;
        // sphere on the left from the brick
        if (angle2 <= sphereAngle) {
            angle = phiBrick + brickAngle;
            if (angle < 0.0f) angle += 360.0f;
        }
        // sphere on the right from the brick
        else if (sphereAngle <= angle1) {
            angle = phiBrick - brickAngle;
            if (angle < 0.0f) angle += 360.0f;
        }

        Vec2 point1 = Vec2((rhoBrick - brickWidth)*cos(Radians(angle)), (rhoBrick - brickWidth)*sin(Radians(angle)));
        Vec2 point2 = Vec2((rhoBrick + brickWidth)*cos(Radians(angle)), (rhoBrick + brickWidth)*sin(Radians(angle)));
        Vec2 q = GetClosestPointOnLineSegment(point1, point2, Vec2(spherePos.x, spherePos.z)); 
        Vec3 v = spherePos - Vec3(q.x, spherePos.y, q.y);
        f32 vLen = v.length();
        if (vLen > sphereRadius) return false;
        info.normal = v/vLen;
        info.penetrationDepth = sphereRadius - vLen;
        return true;
    }

    void PhysicsManager::RegisterCollider(Collider* collider) {
        colliders.push_back(collider);
    }

    void PhysicsManager::DeregisterCollider(Collider* collider) {
        auto it = std::find(colliders.begin(), colliders.end(), collider);
        if (it != colliders.end()) {
            (*it) = colliders.back();
            colliders.pop_back();
        }
    }

    void PhysicsManager::RegisterMoveComponent(MoveComponent* moveComponent) {
        moveComponents.push_back(moveComponent);
    }

    void PhysicsManager::DeregisterMoveComponent(MoveComponent* moveComponent) {
        auto it = std::find(moveComponents.begin(), moveComponents.end(), moveComponent);
        if (it != moveComponents.end()) {
            (*it) = moveComponents.back();
            moveComponents.pop_back();
        }
    }

    void PhysicsManager::Update(f32 deltaTime) {
        // collision detection
        for (i32 i = 0; i < colliders.size(); i++) {
            for (i32 j = i + 1; j < colliders.size(); j++) {
                CollisionInfo info;
                bool isCollision;

                if (colliders[i]->GetType() == Collider::SphereCollider && colliders[j]->GetType() == Collider::SphereCollider) {
                    isCollision = SphereSphere(colliders[i], colliders[j], info);
                }
                else if (colliders[i]->GetType() == Collider::BrickCollider && colliders[j]->GetType() == Collider::SphereCollider) {
                    isCollision = SphereBrick(colliders[j], colliders[i], info);
                }
                else if (colliders[i]->GetType() == Collider::SphereCollider && colliders[j]->GetType() == Collider::BrickCollider) {
                    isCollision = SphereBrick(colliders[i], colliders[j], info);
                }
                else {
                    continue;
                }

                // collision resolution
                if (isCollision && !colliders[i]->isTrigger && !colliders[j]->isTrigger) {
                    MoveComponent* mc_i = colliders[i]->gameObject.GetMoveComponent();
                    MoveComponent* mc_j = colliders[j]->gameObject.GetMoveComponent();

                    if (mc_i && colliders[i]->GetType() == Collider::SphereCollider) {
                        f32 dot = Vec3::dot(info.normal, mc_i->velocity);
                        if (dot < 0.0f)
                            mc_i->transform.SetPosition(mc_i->transform.GetPosition() + info.normal*info.penetrationDepth);
                        else if (dot > 0.0f)
                            mc_i->transform.SetPosition(mc_i->transform.GetPosition() - info.normal*info.penetrationDepth);
                        mc_i->velocity -= info.normal*2.0f*dot;
                    }

                    if (mc_j && colliders[j]->GetType() == Collider::SphereCollider) {
                        f32 dot = Vec3::dot(info.normal, mc_j->velocity);
                        if (dot < 0.0f)
                            mc_j->transform.SetPosition(mc_j->transform.GetPosition() + info.normal*info.penetrationDepth);
                        else if (dot > 0.0f)
                            mc_j->transform.SetPosition(mc_j->transform.GetPosition() - info.normal*info.penetrationDepth);
                        mc_j->velocity -= info.normal*2.0f*dot;
                    }
                }

                auto it = previousFrameCollisions.find(std::make_pair(colliders[i], colliders[j]));
                bool prevValue = it != previousFrameCollisions.end() && it->second;
                // collision enter
                if (!prevValue && isCollision) {
                    previousFrameCollisions.insert({std::make_pair(colliders[i], colliders[j]), true});

                    colliders[i]->gameObject.OnCollisionEnter(*colliders[j]);
                    colliders[j]->gameObject.OnCollisionEnter(*colliders[i]);
                }
                // collision exit
                else if (prevValue && !isCollision) {
                    previousFrameCollisions.erase(it);

                    colliders[i]->gameObject.OnCollisionExit(*colliders[j]);
                    colliders[j]->gameObject.OnCollisionExit(*colliders[i]);
                }

            }
        }

        // simulation
        for (MoveComponent* m: moveComponents) {
            m->transform.SetPosition(m->transform.GetPosition() + m->velocity*deltaTime);
        }
    }

}