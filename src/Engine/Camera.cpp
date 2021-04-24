#include "Camera.h"
#include "../Common/OpenGL.h"

Camera::Camera(glm::vec3 position)
{
    position = position;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + _front, _up);
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up    = glm::normalize(glm::cross(_right, _front));
}

void Camera::processKeyboard(int key, double deltaTime)
{
    float velocity = _movementSpeed * deltaTime;
    float rotationVelocity = _rotationSpeed * deltaTime;
    switch(key) {
        case GLFW_KEY_W: position += _front * velocity; break;
        case GLFW_KEY_S: position -= _front * velocity; break;
        case GLFW_KEY_A: position -= _right * velocity; break;
        case GLFW_KEY_D: position += _right * velocity; break;
        case GLFW_KEY_R: position += _worldUp * velocity; break;
        case GLFW_KEY_F: position -= _worldUp * velocity; break;
        case GLFW_KEY_Q: _yaw -= _rotationSpeed; break;
        case GLFW_KEY_E: _yaw += _rotationSpeed; break;
    }
    updateCameraVectors();
}

void Camera::processMouse(int key, double xOffset, double yOffset) {
    if(key == GLFW_MOUSE_BUTTON_MIDDLE) {
        float sensitivity = 0.25f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        _yaw   += xOffset;
        _pitch += yOffset;

        if(_pitch > 89.0f)
            _pitch = 89.0f;
        if(_pitch < -89.0f)
            _pitch = -89.0f;
         updateCameraVectors();
    }
}