#if !defined(BALL_CPP) 
#define BALL_CPP

#include "Table.h"


const float Table::bottomVertex[bottomVertex_length][3] = {
	{-30, 0, -15},
	{-30, 0,  15},
	{ 30, 0, -15},
	{ 30, 0,  15}
	};

const float Table::shortWallVertex[shortWallVertex_length][3] = {
	{30, 2, -12.878},
	{30, 0, -12.878},
	{30, 2,  12.878},
	{30, 0,  12.878}
	};

const float Table::longWallVertex[longWallVertex_length][3] = {
	{27.878, 2, 15},
	{27.878, 0, 15},
	{1.5,    2, 15},
	{1.5,    0, 15},

	};

Table::Table()
{
	;
}

void Table::add(btDiscreteDynamicsWorld *world)
{
	dynamicsWorld = world;

	btTriangleMesh *mTriMesh = new btTriangleMesh();
	for (int i = 0, length = bottomVertex_length - 2; i < length; i++)
	{
		mTriMesh->addTriangle(
				btVector3(bottomVertex[i][0], bottomVertex[i][1], bottomVertex[i][2]),
				btVector3(bottomVertex[i + 1][0], bottomVertex[i + 1][1], bottomVertex[i + 1][2]),
				btVector3(bottomVertex[i + 2][0], bottomVertex[i + 2][1], bottomVertex[i + 2][2])
				);
	}
	bottomShape = new btBvhTriangleMeshShape(mTriMesh,true);
 
	bottomMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));

	btRigidBody::btRigidBodyConstructionInfo
		bottomRigidBodyCI(0,bottomMotionState,bottomShape,btVector3(0,0,0));
	bottomRigidBody = new btRigidBody(bottomRigidBodyCI);

	dynamicsWorld->addRigidBody(bottomRigidBody);
	
	
	btTriangleMesh *mWallTriMesh = new btTriangleMesh();
	for (int i = 0, length = shortWallVertex_length - 2; i < length; i++)
	{
		mWallTriMesh->addTriangle(
				btVector3(-shortWallVertex[i][0], shortWallVertex[i][1], shortWallVertex[i][2]),
				btVector3(-shortWallVertex[i + 1][0], shortWallVertex[i + 1][1], shortWallVertex[i + 1][2]),
				btVector3(-shortWallVertex[i + 2][0], shortWallVertex[i + 2][1], shortWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(shortWallVertex[i][0], shortWallVertex[i][1], shortWallVertex[i][2]),
				btVector3(shortWallVertex[i + 1][0], shortWallVertex[i + 1][1], shortWallVertex[i + 1][2]),
				btVector3(shortWallVertex[i + 2][0], shortWallVertex[i + 2][1], shortWallVertex[i + 2][2])
				);
	}
	for (int i = 0, length = longWallVertex_length - 2; i < length; i++)
	{
		mWallTriMesh->addTriangle(
				btVector3(-longWallVertex[i][0], longWallVertex[i][1],         -longWallVertex[i][2]),
				btVector3(-longWallVertex[i + 1][0], longWallVertex[i + 1][1], -longWallVertex[i + 1][2]),
				btVector3(-longWallVertex[i + 2][0], longWallVertex[i + 2][1], -longWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(-longWallVertex[i][0], longWallVertex[i][1],         longWallVertex[i][2]),
				btVector3(-longWallVertex[i + 1][0], longWallVertex[i + 1][1], longWallVertex[i + 1][2]),
				btVector3(-longWallVertex[i + 2][0], longWallVertex[i + 2][1], longWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(longWallVertex[i][0], longWallVertex[i][1],         longWallVertex[i][2]),
				btVector3(longWallVertex[i + 1][0], longWallVertex[i + 1][1], longWallVertex[i + 1][2]),
				btVector3(longWallVertex[i + 2][0], longWallVertex[i + 2][1], longWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(longWallVertex[i][0], longWallVertex[i][1],         -longWallVertex[i][2]),
				btVector3(longWallVertex[i + 1][0], longWallVertex[i + 1][1], -longWallVertex[i + 1][2]),
				btVector3(longWallVertex[i + 2][0], longWallVertex[i + 2][1], -longWallVertex[i + 2][2])
				);
	}

	wallShape = new btBvhTriangleMeshShape(mWallTriMesh,true);
 
	wallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));

	btRigidBody::btRigidBodyConstructionInfo
		wallRigidBodyCI(0,wallMotionState,wallShape,btVector3(0,0,0));
	wallRigidBody = new btRigidBody(wallRigidBodyCI);
	//rigidBody->setRestitution(1.0);
	
	dynamicsWorld->addRigidBody(wallRigidBody);
}


void Table::draw()
{
	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0, 0.8, 0.0); // green
	for (int i = 0, length = bottomVertex_length; i < length; i++)
	{
		glVertex3f( bottomVertex[i][0], bottomVertex[i][1], bottomVertex[i][2]);	
	}
	glEnd();

	glColor3f(0.0, 0.8, 0.8); // green
	for (int j = 0; j < 2; j++) // do once positive, and once negative
	{
		int n = 1;
		if (j == 0) n = -1;
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0, length = shortWallVertex_length; i < length; i++)
		{
				glVertex3f( n * shortWallVertex[i][0], shortWallVertex[i][1], shortWallVertex[i][2]);	
		}
		glEnd();
	}

	for (int j = 0; j < 2; j++) // do once positive, once negative
	{
		int n = 1;
		if (j == 0) n = -1;
		for (int m = 0; m < 2; m++)
		{
			glBegin(GL_TRIANGLE_STRIP);
			int k = 1;
			if (m == 0) k = -1;
			for (int i = 0, length = longWallVertex_length; i < length; i++)
			{
				glVertex3f( n * longWallVertex[i][0], longWallVertex[i][1], k * longWallVertex[i][2]);	
			}
			glEnd();
		}
	}
	glPopMatrix();
}

Table::~Table()
{
	// dynamicsWorld->removeRigidBody(bottomRigidBody);
	// delete shape;
	// delete bottomRigidBody;
}
#endif
