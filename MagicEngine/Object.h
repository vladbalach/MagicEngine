#pragma once

#include "PCH.h"

class MWorld;
class MObject
{
	
protected:
	MWorld* World = nullptr;
public:

	void SetWorld(MWorld* NewWorld);

	virtual const MWorld* GetWorld() const { return World; }
	virtual MWorld* GetWorld() { return World; }

	virtual ~MObject();

	MObject() = default;
	MObject(MObject& Obj) = default;
	MObject(MObject&& Obj) = default;
	MObject& operator=(const MObject& Obj) = default;
	MObject& operator=(MObject&& Obj) = default;
};

template <typename ObjectType>
MObject* NewObject(MWorld* World)
{
	ObjectType* NewObj = new ObjectType;
	NewObj->SetWorld(World);
	return NewObj;
}

