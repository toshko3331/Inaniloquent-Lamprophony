#include "Vertex.h"
#include "glm/glm.hpp"

Vertex::Vertex(glm::vec3 position,glm::vec3 textureCoordinate,glm::vec3 normal)
: m_position(position), m_textureCoordinate(textureCoordinate), m_normal(normal)
{

}
