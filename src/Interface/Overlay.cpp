#include "Overlay.h"
#include "DearImGui\imgui.h"
#include "DearImGui\imgui_impl_glfw.h"
#include "DearImGui\imgui_impl_opengl3.h"

Overlay::Overlay(GLFWwindow* window) {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(nullptr);
}

Overlay::~Overlay() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void Overlay::draw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

	const float distance = 5.0f;
	// 		const ImVec2 pos = ImVec2(distance, distance);
	// 		const ImVec2 posPivot = ImVec2(0.0f, 0.0f);
	// 		const auto flags =
	// 			ImGuiWindowFlags_AlwaysAutoResize |
	// 			ImGuiWindowFlags_NoMove |
	// 			ImGuiWindowFlags_NoResize |
	// 			ImGuiWindowFlags_NoSavedSettings;
    // ImGui::SetNextWindowPos(pos, ImGuiCond_Always, posPivot);
	// ImGui::SetNextWindowSize(ImVec2(185, 450), ImGuiCond_Always);

    ImGui::Begin("General");
    ImGui::Text("Projection"); 
    const char* items[] = { "Perspective", "Orthogonal"};
    ImGui::Combo("", &_projectionIndex, items, IM_ARRAYSIZE(items));
    auto&& projection = getProjection();
    if(projection == Projection::PERSPECTIVE) {
        ImGui::Text("Field of view"); 
        ImGui::SliderAngle("angles", &_fieldOfView, 0.0f, 179.0f);
    } else if(projection == Projection::ORTHOGONAL) {
        ImGui::Text("Field of view");
        ImGui::DragFloat("range", &_orthoFieldOfViewFactor, 0.025f, 0.1f, 50.0f);
    }
    ImGui::Text("Frustum"); 
    if(_frustumMin <= 0.0f) {
        _frustumMin = 0.01f;
    } 
    if(_frustumMax <= 0.0f) {
        _frustumMax = 0.01f;
    }
    if(_frustumMin > _frustumMax) {
        _frustumMax = _frustumMin;
    }
    ImGui::InputFloat("min", &_frustumMin, 0.01f, 100.0f, "%.2f");
    ImGui::InputFloat("max", &_frustumMax, 0.01f, 100.0f, "%.2f");

    ImGui::End();

    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

OpenGLRendererSettings Overlay::getSettings() {
    OpenGLRendererSettings settings;
    settings.projection = getProjection();
    settings.fieldOfView = _fieldOfView;
    settings.orthoFieldOfViewFactor = _orthoFieldOfViewFactor;
    settings.frustumMin = _frustumMin;
    settings.frustumMax = _frustumMax;
    return settings;
}

Projection Overlay::getProjection() {
     switch(_projectionIndex) {
        case 0: return Projection::PERSPECTIVE;
        case 1: return Projection::ORTHOGONAL;
    }
}