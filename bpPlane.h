#pragma once
#include "bpBase.h"
#include <BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h>

class bpPlane
{
public:
	bpPlane(void);
	~bpPlane(void);

	void bpRegister(btDiscreteDynamicsWorld* dynamicsWorld);
	void bpUnregister(btDiscreteDynamicsWorld* dynamicsWorld);

	btCollisionShape* groundShape;
	btDefaultMotionState* groundMotionState;
	btRigidBody* groundRigidBody;
};

