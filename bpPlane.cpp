#include "bpPlane.h"
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h>

bpPlane::bpPlane(void)
{
	groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
}


bpPlane::~bpPlane(void)
{
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;
	delete groundShape;
}

void bpPlane::bpRegister(btDiscreteDynamicsWorld* dynamicsWorld)
{
	dynamicsWorld->addRigidBody(groundRigidBody);
}

void bpPlane::bpUnregister(btDiscreteDynamicsWorld* dynamicsWorld)
{
	dynamicsWorld->removeRigidBody(groundRigidBody);
}
