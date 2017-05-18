#include "Plane.h"
#include "Gizmos.h"
#include <iostream>
// gui
#include "imgui_glfw3.h"
#include <glm/gtc/type_ptr.hpp>


Plane::Plane()
{
	m_shapeID = PLANE;
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_normal = glm::vec3(0.0f, 1.0f, 0.0f);
	m_distanceToOrigin = 50.0f;
	m_position = m_normal;
	m_2D = false;
}

Plane::Plane(glm::vec3 normal, float distance, bool twoD)
{
	m_shapeID = PLANE;
	m_normal = normal;
	m_distanceToOrigin = distance;
	m_2D = twoD;
}


Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec3 gravity, float timeStep)
{
}

void Plane::debug()
{
	std::string windowName = "Plane";
	ImGui::Text(windowName.c_str());
	ImGui::DragFloat3("position", glm::value_ptr(m_position), 0.05f, -100.0f, 100.0f, "%.2f");
	ImGui::DragFloat3("normal", glm::value_ptr(m_normal), 0.05f, -100.0f, 100.0f, "%.2f");
	ImGui::DragFloat("distance", &m_distanceToOrigin, 0.05f, 0.01f, 100.0f, "%.2f");
}

void Plane::makeGizmo()
{
	if (m_2D) {
		float lineLength = m_distanceToOrigin;
		glm::vec2 centerPoint(m_normal.x, m_normal.y);
		glm::vec2 parallel(m_normal.y, -m_normal.x);
		// set colour
		glm::vec4 colour(0.0f, 0.5f, 1.0f, 1.0f);
		// define start and end point
		glm::vec2 start = centerPoint + (parallel * lineLength);
		glm::vec2 end = centerPoint - (parallel * lineLength);
		// add line
		aie::Gizmos::add2DLine(start, end, colour);
	}
	else {
		float lineLength = m_distanceToOrigin;
		glm::vec3 centerPoint(m_normal);
		glm::vec3 parallel(m_normal.y, -m_normal.x, m_normal.z);
		glm::vec3 start = centerPoint + (parallel * lineLength);
		glm::vec3 end = centerPoint - (parallel * lineLength);
		// draw a simple grid with gizmos
		glm::vec4 blue(0.0f, 0.5f, 1.0f, 1.0f);
		glm::vec4 lightBlue(0.0f, 0.75f, 1.0f, 1.0f);

		int offset = parallel.y;
		int count = lineLength * 2 + 1;
		int length = lineLength;
		for (int i = 0; i < count; ++i) {
			// draw on the Z plane, increment along the X
			aie::Gizmos::addLine(glm::vec3(-lineLength + i, 0, lineLength),
				glm::vec3(-lineLength + i, 0, -lineLength),
				i == lineLength ? blue : lightBlue);
			// draw on the X plane, increment into the Z
			aie::Gizmos::addLine(glm::vec3(lineLength, 0, -lineLength + i),
				glm::vec3(-lineLength, 0, -lineLength + i),
				i == lineLength ? blue : lightBlue);
		}
	}
}