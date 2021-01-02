#include "game/FPSCamera.hpp"

namespace game
{
  FPSCamera::FPSCamera() :
    m_Position(glm::vec3(0)),
    m_fPhi(M_PI),
    m_fTheta(0),
    m_mouse_sensibility(2.0),
    m_walk_sensibility(0.4)
  {
    FPSCamera::computeDirectionVectors();
  }

  

  FPSCamera::~FPSCamera()
  {
    
  }

  void FPSCamera::setPosition(glm::vec3 position){
    m_Position = position;
  }

  void FPSCamera::setPositionY(float v){
    m_Position.y = v;
  }

  void FPSCamera::moveLeft(float distance)
  {
    m_Position += distance * m_LeftVector * m_walk_sensibility;
  }

  void FPSCamera::moveFront(float distance)
  {
    m_Position += distance * m_FrontVector * m_walk_sensibility;
  }

  void FPSCamera::rotateLeft(float degrees)
  {
    m_fPhi -= glm::radians(degrees)/m_mouse_sensibility;
    FPSCamera::computeDirectionVectors();
  }

  void FPSCamera::rotateUp(float degrees)
  {
    float m_fTheta_temp = m_fTheta;
    m_fTheta -= glm::radians(degrees)/m_mouse_sensibility;
    if(m_fTheta>glm::radians(70.0) || m_fTheta<glm::radians(-70.0)){
      m_fTheta = m_fTheta_temp;
    }
    FPSCamera::computeDirectionVectors();
  }

  void FPSCamera::computeDirectionVectors()
  {
    m_FrontVector = glm::vec3(
      cos(m_fTheta)*sin(m_fPhi),
      sin(m_fTheta),
      cos(m_fTheta)*cos(m_fPhi)
    );

    m_LeftVector = glm::vec3(
      sin(m_fPhi + (M_PI/2)),
      0,
      cos(m_fPhi + (M_PI/2))
    );

    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
  }

  glm::mat4 FPSCamera::getViewMatrix() const
  {
    return glm::lookAt(m_Position, (m_FrontVector + m_Position), m_UpVector);
  }

  glm::vec3 FPSCamera::getPosition() const
  {
    return m_Position;
  }

}
