#pragma once
#include "bpbase.h"
#include <btBulletDynamicsCommon.h>

class bpSphere
{
public:
	bpSphere(void);
	~bpSphere(void);

	void bpRegister(btDiscreteDynamicsWorld* dynamicsWorld);

	void bpUnregister(btDiscreteDynamicsWorld* dynamicsWorld);

	btCollisionShape* fallShape;
	btDefaultMotionState* fallMotionState;
	btRigidBody* fallRigidBody;
};

