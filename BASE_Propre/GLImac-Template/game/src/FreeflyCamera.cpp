#include "game/FreeflyCamera.hpp"

namespace game
{
  FreeflyCamera::FreeflyCamera() :
    m_Position(glm::vec3(0)),
    m_fPhi(M_PI),
    m_fTheta(0)
  {
    FreeflyCamera::computeDirectionVectors();
  }

  

  FreeflyCamera::~FreeflyCamera()
  {
    
  }

  void FreeflyCamera::setPosition(glm::vec3 position){
    m_Position = position;
  }

  void FreeflyCamera::setPositionY(float v){
    m_Position.y = v;
  }

  void FreeflyCamera::moveLeft(float distance)
  {
    m_Position += distance * m_LeftVector;
  }

  void FreeflyCamera::moveFront(float distance)
  {
    m_Position += distance * m_FrontVector;
  }

  void FreeflyCamera::rotateLeft(float degrees)
  {
    m_fPhi += glm::radians(degrees);
    FreeflyCamera::computeDirectionVectors();
  }

  void FreeflyCamera::rotateUp(float degrees)
  {
    m_fTheta += glm::radians(degrees);
    FreeflyCamera::computeDirectionVectors();
  }

  void FreeflyCamera::computeDirectionVectors()
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

  glm::mat4 FreeflyCamera::getViewMatrix() const
  {
    return glm::lookAt(m_Position, (m_FrontVector + m_Position), m_UpVector);
  }

  glm::vec3 FreeflyCamera::getPosition() const
  {
    return m_Position;
  }

}
