#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 _position;
    glm::vec3 _front{ glm::vec3(0.0f, 0.0f, -1.0f) };
    glm::vec3 _right;
    glm::vec3 _up;
    glm::vec3 _worldUp { glm::vec3(0.0f, 1.0f, 0.0f) };
 
    float _yaw{ -90.0f };
    float _pitch{ 0.0f };

    float _movementSpeed{ 2.5f };
    double _rotationSpeed{ 1.5 };
    float _mouseSensitivity{ 0.1f };
    float _zoom { 45.0f };

public:


    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 getViewMatrix() const;
    void updateCameraVectors();
    void processKeyboard(int key, double deltaTime);
    void processMouse(int key, double xOffset, double yOffset);

    void setPosition(glm::vec3 position) {
        _position = position;
    }
};

#endif