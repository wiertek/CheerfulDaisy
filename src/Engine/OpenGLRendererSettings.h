
#ifndef OPENGLRENDERERSETTINGS_H
#define OPENGLRENDERERSETTINGS_H

#include "../Common/Definitions.h"

enum class Projection {
    PERSPECTIVE, ORTHOGONAL
};

enum class LigthModel {
    NONE, PHONG, GOURAUD
};

struct OpenGLRendererSettings {
    Projection projection;
    float fieldOfView;
    float orthoFieldOfViewFactor;
    float frustumMin;
    float frustumMax;
    Material objectMaterial;
    LigthModel lightModel;
    LightSource lightSource;
};

#endif