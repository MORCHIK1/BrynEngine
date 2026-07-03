#include "PreCompiledHeader.h"
#include "Camera.h"

void Camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	m_View = glm::inverse(transform);
	m_ProjectionView = m_Projection * m_View;
}
