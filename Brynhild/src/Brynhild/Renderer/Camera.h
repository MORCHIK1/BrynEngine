#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMoveDir
{
  FORWARD,
  BACKWARD,
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Camera
{
public:
  Camera(float top, float bottom, float left, float right) : m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
  {
    
  }


  glm::mat4 GetProjectionMatrix() { return m_Projection; }
  glm::mat4 GetViewMatrix() { return m_View; }
  glm::mat4 GetProjectionViewMatrix() { return m_ProjectionView; }

  float GetRotation() { return m_Rotation; }
  void SetRotation(float angle) { m_Rotation = angle; }

  float GetZoom() { return m_Zoom; }
  void SetZoom(float zoom) { m_Zoom = zoom; }

  glm::vec3 GetPosition() { return m_Position; }
  void SetPosition(glm::vec3 position) { m_Position = position; }
private:
  glm::mat4 m_Projection = glm::mat4(0.0f);
  glm::mat4 m_View = glm::mat4(0.0f);
  glm::mat4 m_ProjectionView = glm::mat4(0.0f);

  glm::vec3 m_Position = glm::vec3(0.0f);

  float m_Zoom = 1.0f;
  float m_Rotation = 0.0f;
};

