#include "Object.h"
#include "World.h"

void MObject::SetWorld(MWorld* NewWorld)
{
	World = NewWorld;
}

MObject::~MObject()
{
}
