
#ifndef GL_DEBUG_DRAWER_H
#define GL_DEBUG_DRAWER_H
#include "debugDraw.h"

#include <stdio.h> //printf debugging
#include <glew.h>
#include <btBulletDynamicsCommon.h>
#include "SpriteBatch.h"

class GLDebugDrawer : public btIDebugDraw
{
	int m_debugMode;

public:

	GLDebugDrawer();

	void SetBatched(Batched* b);
	Batched* bat;

	virtual void   drawLine(const btVector3& from,const btVector3& to,const btVector3& color);

	virtual void   drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);

	virtual void   reportErrorWarning(const char* warningString);

	virtual void   draw3dText(const btVector3& location,const char* textString);

	virtual void   setDebugMode(int debugMode);

	virtual int      getDebugMode() const { return m_debugMode;}

	virtual void drawAabb(const btVector3& from,const btVector3& to,const btVector3& color);

};
#endif