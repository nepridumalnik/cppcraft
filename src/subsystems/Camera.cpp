#include <Camera.hpp>

#include <glm/ext.hpp>

const float Camera::m_near = 0.01f;
const float Camera::m_far = 100.0f;

Camera::Camera(glm::vec3 pos, float fov, float aspect)
    : m_pos{pos},
      m_fov{fov},
      m_rotation{1.0f},
      m_aspect{aspect}
{
    updateVectors();
}

glm::mat4 Camera::GetProjection() const noexcept
{
    return glm::perspective(m_fov, m_aspect, m_near, m_far);
}

glm::mat4 Camera::GetView() const noexcept
{
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

void Camera::updateVectors() noexcept
{
    m_front = glm::vec3{m_rotation * glm::vec4{0.0f, 0.0f, -1.0f, 1.0f}};
    m_right = glm::vec3{m_rotation * glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}};
    m_up = glm::vec3{m_rotation * glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}};
}

void Camera::Rotate(float x, float y, float z) noexcept
{
    m_rotation = glm::rotate(m_rotation, z, glm::vec3{0.0f, 0.0f, 1.0f});
    m_rotation = glm::rotate(m_rotation, y, glm::vec3{0.0f, 1.0f, 0.0f});
    m_rotation = glm::rotate(m_rotation, x, glm::vec3{1.0f, 0.0f, 0.0f});

    updateVectors();
}

glm::vec3 Camera::Front() const noexcept { return m_front; }

void Camera::Front(glm::vec3 front) noexcept { m_front = front; }

glm::vec3 Camera::Right() const noexcept { return m_right; }

void Camera::Right(glm::vec3 right) noexcept { m_right = right; }

glm::vec3 Camera::Up() const noexcept { return m_up; }

void Camera::Up(glm::vec3 up) noexcept { m_up = up; }

glm::vec3 Camera::Pos() const noexcept { return m_pos; }

void Camera::Pos(glm::vec3 pos) noexcept { m_pos = pos; }

void Camera::SetAspect(uint32_t w, uint32_t h) noexcept { m_aspect = w / h; }
