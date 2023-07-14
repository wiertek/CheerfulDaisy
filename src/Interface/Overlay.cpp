#include <DearImGui/include/imgui.h>
#include <DearImGui/include/imgui_impl_glfw.h>
#include <DearImGui/include/imgui_impl_opengl3.h>

#include "Overlay.h"

#include <format>

Overlay::Overlay(GLFWwindow* window)
    : settings_{.projection = Projection::PERSPECTIVE,
                .fieldOfView = glm::radians(45.0f),
                .orthoFieldOfViewFactor = 3.0f,
                .frustumMin = 0.1f,
                .frustumMax = 100.0f,
                .lightModel = LigthModel::NONE} {
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);
}

void Overlay::loadSceneSettings(const Scene& scene) {
    materialAmbient_[0] = scene.initialSettings.material.ambient.r;
    materialAmbient_[1] = scene.initialSettings.material.ambient.g;
    materialAmbient_[2] = scene.initialSettings.material.ambient.b;

    materialDiffuse_[0] = scene.initialSettings.material.diffuse.r;
    materialDiffuse_[1] = scene.initialSettings.material.diffuse.g;
    materialDiffuse_[2] = scene.initialSettings.material.diffuse.b;

    materialSpecular_[0] = scene.initialSettings.material.specular.r;
    materialSpecular_[1] = scene.initialSettings.material.specular.g;
    materialSpecular_[2] = scene.initialSettings.material.specular.b;

    lightAmbient_[0] = scene.initialSettings.lightSource.ambient.r;
    lightAmbient_[1] = scene.initialSettings.lightSource.ambient.g;
    lightAmbient_[2] = scene.initialSettings.lightSource.ambient.b;

    lightDiffuse_[0] = scene.initialSettings.lightSource.diffuse.r;
    lightDiffuse_[1] = scene.initialSettings.lightSource.diffuse.g;
    lightDiffuse_[2] = scene.initialSettings.lightSource.diffuse.b;

    lightSpecular_[0] = scene.initialSettings.lightSource.specular.r;
    lightSpecular_[1] = scene.initialSettings.lightSource.specular.g;
    lightSpecular_[2] = scene.initialSettings.lightSource.specular.b;

    settings_.objectMaterial.shininess = scene.initialSettings.material.shininess;
}

Overlay::~Overlay() {
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Overlay::draw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    if (ImGui::CollapsingHeader("Projection", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Projection");
        const char* items[] = {"Perspective", "Orthogonal"};
        ImGui::Combo("", &projectionIndex_, items, IM_ARRAYSIZE(items));
        auto&& projection = getProjection();
        if (projection == Projection::PERSPECTIVE) {
            settings_.projection = Projection::PERSPECTIVE;
            ImGui::Text("Field of view");
            ImGui::SliderAngle("angles", &settings_.fieldOfView, 0.0f, 179.0f);
        } else if (projection == Projection::ORTHOGONAL) {
            settings_.projection = Projection::ORTHOGONAL;
            ImGui::Text("Field of view");
            ImGui::DragFloat("range", &settings_.orthoFieldOfViewFactor, 0.025f, 0.1f, 50.0f);
        }
        ImGui::Text("Frustum");
        if (settings_.frustumMin <= 0.0f) {
            settings_.frustumMin = 0.01f;
        }
        if (settings_.frustumMax <= 0.0f) {
            settings_.frustumMax = 0.01f;
        }
        if (settings_.frustumMin > settings_.frustumMax) {
            settings_.frustumMax = settings_.frustumMin;
        }
        ImGui::InputFloat("min", &settings_.frustumMin, 0.01f, 100.0f, "%.2f");
        ImGui::InputFloat("max", &settings_.frustumMax, 0.01f, 100.0f, "%.2f");
    }

    if (ImGui::CollapsingHeader("Lighting", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Light Model");
        const char* items[] = {"No Lighting", "Phong Lighting", "Gouraud Lighting"};
        ImGui::Combo("Light model", &lightModelIndex_, items, IM_ARRAYSIZE(items));
        auto&& ligthModel = getLightModel();
        if (ligthModel == LigthModel::NONE) {
            settings_.lightModel = LigthModel::NONE;
            ImGui::Text("Object Material");
            ImGui::ColorEdit3("Color", materialAmbient_);
        } else if (ligthModel == LigthModel::PHONG) {
            settings_.lightModel = LigthModel::PHONG;
            ImGui::Text("Object Material");
            ImGui::ColorEdit3("Ambient", materialAmbient_);
            ImGui::ColorEdit3("Diffuse", materialDiffuse_);
            ImGui::ColorEdit3("Specular", materialSpecular_);
            ImGui::InputFloat("Shininess", &settings_.objectMaterial.shininess, 5.0f, 10.0f, "%.1f");
            if (settings_.objectMaterial.shininess < 10.0) {
                settings_.objectMaterial.shininess = 10.0;
            }
            ImGui::Text("Light Source");
            ImGui::ColorEdit3("Light Ambient", lightAmbient_);
            ImGui::ColorEdit3("Light Diffuse", lightDiffuse_);
            ImGui::ColorEdit3("Light Specular", lightSpecular_);
        } else if (ligthModel == LigthModel::GOURAUD) {
            settings_.lightModel = LigthModel::GOURAUD;
            ImGui::Text("Object Material");
            ImGui::ColorEdit3("Ambient", materialAmbient_);
            ImGui::ColorEdit3("Diffuse", materialDiffuse_);
            ImGui::ColorEdit3("Specular", materialSpecular_);
            ImGui::InputFloat("Shininess", &settings_.objectMaterial.shininess, 5.0f, 10.0f, "%.1f");
            if (settings_.objectMaterial.shininess < 10.0) {
                settings_.objectMaterial.shininess = 10.0;
            }
            ImGui::Text("Light Source");
            ImGui::ColorEdit3("Light Ambient", lightAmbient_);
            ImGui::ColorEdit3("Light Diffuse", lightDiffuse_);
            ImGui::ColorEdit3("Light Specular", lightSpecular_);
        }
    }

    ImGui::End();
    // ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Projection Overlay::getProjection() {
    switch (projectionIndex_) {
        case 0: return Projection::PERSPECTIVE;
        case 1: return Projection::ORTHOGONAL;
        default: throw std::invalid_argument(std::format("Cannot find Projection of index {}", projectionIndex_));
    }
}

LigthModel Overlay::getLightModel() {
    switch (lightModelIndex_) {
        case 0: return LigthModel::NONE;
        case 1: return LigthModel::PHONG;
        case 2: return LigthModel::GOURAUD;
        default: throw std::invalid_argument(std::format("Cannot find LigthModel of index {}", lightModelIndex_));
    }
}

OpenGLRendererSettings Overlay::getSettings() {
    auto result = OpenGLRendererSettings(settings_);
    result.objectMaterial.ambient = glm::vec3(materialAmbient_[0], materialAmbient_[1], materialAmbient_[2]);
    result.objectMaterial.diffuse = glm::vec3(materialDiffuse_[0], materialDiffuse_[1], materialDiffuse_[2]);
    result.objectMaterial.specular = glm::vec3(materialSpecular_[0], materialSpecular_[1], materialSpecular_[2]);

    result.lightSource.ambient = glm::vec3(lightAmbient_[0], lightAmbient_[1], lightAmbient_[2]);
    result.lightSource.diffuse = glm::vec3(lightDiffuse_[0], lightDiffuse_[1], lightDiffuse_[2]);
    result.lightSource.specular = glm::vec3(lightSpecular_[0], lightSpecular_[1], lightSpecular_[2]);
    return result;
}