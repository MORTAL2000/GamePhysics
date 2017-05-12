#pragma once
#include "glm\glm.hpp"

struct RigidBodyData {
	glm::vec3 velocity;
	glm::vec3 startVelocity;
	glm::vec3 position;
	glm::vec3 startPosition;
	glm::vec3 rotation;
	float mass;
};


class RigidBody
{
public:
	RigidBody();
	RigidBody(glm::vec3 position, glm::vec3 velocity, glm::vec3 rotation, float mass);
	RigidBody(glm::vec3 position, float angle, float speed, glm::vec3 rotation, float mass);

	~RigidBody();

	void fixedUpdate(glm::vec3 gravity, float timeStep);
	void debug();

	RigidBodyData data;
	void applyForce(glm::vec3 a_force);
	void applyForceToActor(RigidBody * a_pActor2, glm::vec3 a_force);

protected:
	glm::vec3 m_startPosition;
};

