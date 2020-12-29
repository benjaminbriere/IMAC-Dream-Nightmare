#include <glimac/glm.hpp>
#include <cmath>

namespace game
{
  class FreeflyCamera
  {
    private:
      glm::vec3 m_Position;
      float m_fPhi;
      float m_fTheta;
      glm::vec3 m_FrontVector;
      glm::vec3 m_LeftVector;
      glm::vec3 m_UpVector;

      void computeDirectionVectors();
    
    public:
      FreeflyCamera();
      ~FreeflyCamera();

      void moveLeft(float distance);
      void moveFront(float distance);
      void rotateLeft(float degrees);
      void rotateUp(float degrees);
      glm::mat4 getViewMatrix() const;
  };
}
