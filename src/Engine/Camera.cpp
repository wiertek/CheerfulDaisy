#include "Camera.h"
#include "../Common/OpenGL.h"

Camera::Camera(glm::vec3 position) {
    position_ = position;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const { return glm::lookAt(position_, position_ + front_, up_); }

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_ = glm::normalize(glm::cross(right_, front_));
}

void Camera::processKeyboard(int key, double deltaTime) {
    float velocity = static_cast<float>(movementSpeed_ * deltaTime);
    float rotationVelocity = static_cast<float>(rotationSpeed_ * deltaTime);
    switch (key) {
        case GLFW_KEY_W: position_ += front_ * velocity; break;
        case GLFW_KEY_S: position_ -= front_ * velocity; break;
        case GLFW_KEY_A: position_ -= right_ * velocity; break;
        case GLFW_KEY_D: position_ += right_ * velocity; break;
        case GLFW_KEY_R: position_ += worldUp_ * velocity; break;
        case GLFW_KEY_F: position_ -= worldUp_ * velocity; break;
        case GLFW_KEY_Q: yaw_ -= rotationVelocity; break;
        case GLFW_KEY_E: yaw_ += rotationVelocity; break;
    }
    updateCameraVectors();
}

void Camera::processMouse(int key, double xOffset, double yOffset) {
    if (key == GLFW_MOUSE_BUTTON_MIDDLE) {
        float sensitivity = 0.25f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw_ += static_cast<float>(xOffset);
        pitch_ += static_cast<float>(yOffset);

        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
        updateCameraVectors();
    }
}