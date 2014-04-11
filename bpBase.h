#pragma once
#ifndef bpBase_h__
#define bpBase_h__

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h>
class bpBase{
public:
	virtual void bpRegister(btDiscreteDynamicsWorld* dynamicsWorld);
	virtual void bpUnregister(btDiscreteDynamicsWorld* dynamicsWorld);
};
#endif // bpBase_h__
