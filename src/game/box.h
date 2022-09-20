#ifndef BOX_H
#define BOX_H

#include "../core/types.h"
#include "../scene/gameObject.h"

class Box: public Bubble::GameObject {
public:
	Box(Bubble::Mesh* mesh, Bubble::Material* material) { AddGraphicsComponent(mesh, material); }
	void Update(f32 deltaTime) { /*transform.Rotate(0.0f, deltaTime*60.0f, 0.0f);*/ }
	virtual ~Box() {}
};

#endif