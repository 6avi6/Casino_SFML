#ifndef MOVEABLEGRAPHICALOBJECT_H
#define MOVEABLEGRAPHICALOBJECT_H

#include "GraphicalObject.h"

// Abstract base class representing a movable graphical object
class MoveableGrapphicalObject : public GraphicalObject {
public:
    // Pure virtual function to move the object
    virtual void move() = 0;
};

#endif // !MOVEABLEGRAPHICALOBJECT_H