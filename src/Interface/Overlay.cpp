#include "Overlay.h"
#include "DearImGui/imgui.h"
#include "DearImGui/imgui_impl_glfw.h"
#include "DearImGui/imgui_impl_opengl3.h"

Overlay::Overlay(GLFWwindow *window)
    : _settings{.projection = Projection::PERSPECTIVE,
                .fieldOfView = glm::radians(45.0f),
                .orthoFieldOfViewFactor = 3.0f,
                .frustumMin = 0.1f,
                .frustumMax = 100.0f,
                .lightModel = LigthModel::NONE} {
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);
}

void Overlay::LoadSceneSettings(const Scene &scene) {
    _materialAmbient[0] = scene.initialSettings.material.ambient.r;
    _materialAmbient[1] = scene.initialSettings.material.ambient.g;
    _materialAmbient[2] = scene.initialSettings.material.ambient.b;

    _materialDiffuse[0] = scene.initialSettings.material.diffuse.r;
    _materialDiffuse[1] = scene.initialSettings.material.diffuse.g;
    _materialDiffuse[2] = scene.initialSettings.material.diffuse.b;

    _materialSpecular[0] = scene.initialSettings.material.specular.r;
    _materialSpecular[1] = scene.initialSettings.material.specular.g;
    _materialSpecular[2] = scene.initialSettings.material.specular.b;

    _lightAmbient[0] = scene.initialSettings.lightSource.ambient.r;
    _lightAmbient[1] = scene.initialSettings.lightSource.ambient.g;
    _lightAmbient[2] = scene.initialSettings.lightSource.ambient.b;

    _lightDiffuse[0] = scene.initialSettings.lightSource.diffuse.r;
    _lightDiffuse[1] = scene.initialSettings.lightSource.diffuse.g;
    _lightDiffuse[2] = scene.initialSettings.lightSource.diffuse.b;

    _lightSpecular[0] = scene.initialSettings.lightSource.specular.r;
    _lightSpecular[1] = scene.initialSettings.lightSource.specular.g;
    _lightSpecular[2] = scene.initialSettings.lightSource.specular.b;

    _settings.objectMaterial.shininess = scene.initialSettings.material.shininess;
}

Overlay::~Overlay() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Overlay::Draw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    if (ImGui::CollapsingHeader("Projection", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Projection");
        const char *items[] = {"Perspective", "Orthogonal"};
        ImGui::Combo("", &_projectionIndex, items, IM_ARRAYSIZE(items));
        auto &&projection = GetProjection();
        if (projection == Projection::PERSPECTIVE) {
            _settings.projection = Projection::PERSPECTIVE;
            ImGui::Text("Field of view");
            ImGui::SliderAngle("angles", &_settings.fieldOfView, 0.0f, 179.0f);
        } else if (projection == Projection::ORTHOGONAL) {
            _settings.projection = Projection::ORTHOGONAL;
            ImGui::Text("Field of view");
            ImGui::DragFloat("range", &_settings.orthoFieldOfViewFactor, 0.025f, 0.1f, 50.0f);
        }
        ImGui::Text("Frustum");
        if (_settings.frustumMin <= 0.0f) {
            _settings.frustumMin = 0.01f;
        }
        if (_settings.frustumMax <= 0.0f) {
            _settings.frustumMax = 0.01f;
        }
        if (_settings.frustumMin > _settings.frustumMax) {
            _settings.frustumMax = _settings.frustumMin;
        }
        ImGui::InputFloat("min", &_settings.frustumMin, 0.01f, 100.0f, "%.2f");
        ImGui::InputFloat("max", &_settings.frustumMax, 0.01f, 100.0f, "%.2f");
    }

    if (ImGui::CollapsingHeader("Lighting", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Light Model");
        const char *items[] = {"No Lighting", "Phong Lighting", "Gouraud Lighting"};
        ImGui::Combo("Light model", &_lightModelIndex, items, IM_ARRAYSIZE(items));
        auto &&ligthModel = GetLightModel();
        if (ligthModel == LigthModel::NONE) {
            _settings.lightModel = LigthModel::NONE;
            ImGui::Text("Object Material");
            ImGui::ColorEdit3("Color", _materialAmbient);
        } else if (ligthModel == LigthModel::PHONG) {
            _settings.lightModel = LigthModel::PHONG;
            ImGui::Text("Object Material");
            ImGui::ColorEdit3("Ambient", _materialAmbient);
            ImGui::ColorEdit3("Diffuse", _materialDiffuse);
            ImGui::ColorEdit3("Specular", _materialSpecular);
            ImGui::InputFloat("Shininess", &_settings.objectMaterial.shininess, 5.0f, 10.0f, "%.1f");
            if (_settings.objectMaterial.shininess < 10.0) {
                _settings.objectMaterial.shininess = 10.0;
            }
            ImGui::Text("Light Source");
            ImGui::ColorEdit3("Light Ambient", _lightAmbient);
            ImGui::ColorEdit3("Light Diffuse", _lightDiffuse);
            ImGui::ColorEdit3("Light Specular", _lightSpecular);
        } else if (ligthModel == LigthModel::GOURAUD) {
            _settings.lightModel = LigthModel::GOURAUD;
            ImGui::Text("Object Material");
            ImGui::ColorEdit3("Ambient", _materialAmbient);
            ImGui::ColorEdit3("Diffuse", _materialDiffuse);
            ImGui::ColorEdit3("Specular", _materialSpecular);
            ImGui::InputFloat("Shininess", &_settings.objectMaterial.shininess, 5.0f, 10.0f, "%.1f");
            if (_settings.objectMaterial.shininess < 10.0) {
                _settings.objectMaterial.shininess = 10.0;
            }
            ImGui::Text("Light Source");
            ImGui::ColorEdit3("Light Ambient", _lightAmbient);
            ImGui::ColorEdit3("Light Diffuse", _lightDiffuse);
            ImGui::ColorEdit3("Light Specular", _lightSpecular);
        }
    }

    ImGui::End();
    // ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Projection Overlay::GetProjection() {
    switch (_projectionIndex) {
        case 0: return Projection::PERSPECTIVE;
        case 1: return Projection::ORTHOGONAL;
    }
}

LigthModel Overlay::GetLightModel() {
    switch (_lightModelIndex) {
        case 0: return LigthModel::NONE;
        case 1: return LigthModel::PHONG;
        case 2: return LigthModel::GOURAUD;
    }
}

OpenGLRendererSettings Overlay::GetSettings() {
    auto result = OpenGLRendererSettings(_settings);
    result.objectMaterial.ambient = glm::vec3(_materialAmbient[0], _materialAmbient[1], _materialAmbient[2]);
    result.objectMaterial.diffuse = glm::vec3(_materialDiffuse[0], _materialDiffuse[1], _materialDiffuse[2]);
    result.objectMaterial.specular = glm::vec3(_materialSpecular[0], _materialSpecular[1], _materialSpecular[2]);

    result.lightSource.ambient = glm::vec3(_lightAmbient[0], _lightAmbient[1], _lightAmbient[2]);
    result.lightSource.diffuse = glm::vec3(_lightDiffuse[0], _lightDiffuse[1], _lightDiffuse[2]);
    result.lightSource.specular = glm::vec3(_lightSpecular[0], _lightSpecular[1], _lightSpecular[2]);
    return result;
}