#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
constexpr auto ROTATION_SPEED = 1.5;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera {

public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    double RotationSpeed{ROTATION_SPEED};
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    glm::mat4 getViewMatrix();
    void updateCameraVectors();
    void processKeyboard(int key, float deltaTime);
};

#endif