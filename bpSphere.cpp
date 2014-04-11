#include "bpSphere.h"


bpSphere::bpSphere(void)
{
	fallShape = new btSphereShape(1);//

	fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(rand()%2+4,rand()%10+10,rand()%2+4)));
	btScalar mass = 1;
	btVector3 fallInertia(0,0,0);
	fallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
	
}


bpSphere::~bpSphere(void)
{
	
	delete fallRigidBody->getMotionState();
	delete fallRigidBody;
	delete fallShape;
}

void bpSphere::bpRegister(btDiscreteDynamicsWorld* dynamicsWorld)
{
	dynamicsWorld->addRigidBody(fallRigidBody);
}

void bpSphere::bpUnregister(btDiscreteDynamicsWorld* dynamicsWorld)
{
	dynamicsWorld->removeRigidBody(fallRigidBody);
}
