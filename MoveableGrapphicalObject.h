#ifndef MOVEABLEGRAPHICALOBJECT_H
#define MOVEABLEGRAPHICALOBJECT_H
#include "GraphicalObject.h"

class MoveableGrapphicalObject :public GraphicalObject {
public:
	virtual void move() = 0;
};

#endif // !MOVEABLEGRAPHICALOBJECT_H
