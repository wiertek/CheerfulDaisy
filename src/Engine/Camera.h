#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
  private:
    glm::vec3 front_{glm::vec3(0.0f, 0.0f, -1.0f)};
    glm::vec3 right_;
    glm::vec3 up_;
    glm::vec3 worldUp_{glm::vec3(0.0f, 1.0f, 0.0f)};

    float yaw_{-90.0f};
    float pitch_{0.0f};

    float movementSpeed_{2.5f};
    double rotationSpeed_{50.0f};

  public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 getViewMatrix() const;
    void updateCameraVectors();
    void processKeyboard(int key, double deltaTime);
    void processMouse(int key, double xOffset, double yOffset);

    glm::vec3 position_;
};

#endif