
#ifndef OPENGLRENDERERSETTINGS_H
#define OPENGLRENDERERSETTINGS_H

enum class Projection {
    PERSPECTIVE, ORTHOGONAL
};

struct OpenGLRendererSettings {
    Projection projection;
    float fieldOfView;
    float orthoFieldOfViewFactor;
    float frustumMin;
    float frustumMax;
};

#endif