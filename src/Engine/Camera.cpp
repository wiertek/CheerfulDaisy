#include "Camera.h"
#include "../Common/OpenGL.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : 
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), RotationSpeed(ROTATION_SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}

void Camera::processKeyboard(int key, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    float rotationVelocity = RotationSpeed * deltaTime;
    switch(key) {
        case GLFW_KEY_W: Position += Front * velocity; break;
        case GLFW_KEY_S: Position -= Front * velocity; break;
        case GLFW_KEY_A: Position -= Right * velocity; break;
        case GLFW_KEY_D: Position += Right * velocity; break;
        case GLFW_KEY_Q: Yaw -= RotationSpeed; break;
        case GLFW_KEY_E: Yaw += RotationSpeed; break;
    }
    updateCameraVectors();
}