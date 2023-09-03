#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 pos = {}, float fov = glm::radians(40.0f), float aspect = (1920.0f / 1080.0f));

    glm::mat4 GetProjection() const noexcept;
    glm::mat4 GetView() const noexcept;

    void Rotate(float x, float y, float z) noexcept;

    glm::vec3 Front() const noexcept;
    void Front(glm::vec3 front) noexcept;
    glm::vec3 Right() const noexcept;
    void Right(glm::vec3 right) noexcept;
    glm::vec3 Up() const noexcept;
    void Up(glm::vec3 up) noexcept;
    glm::vec3 Pos() const noexcept;
    void Pos(glm::vec3 pos) noexcept;
    void SetAspect(uint32_t w, uint32_t h) noexcept;

private:
    void updateVectors() noexcept;

private:
    glm::vec3 m_pos;
    glm::mat4 m_rotation;

    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    float m_fov;
    float m_aspect;

    static const float m_near;
    static const float m_far;
};