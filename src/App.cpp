#include "App.h"

#include <Cool/App/RenderState.h>
#include <Cool/App/Input.h>

#include <Cool/OpenGL/SSBO.h>
#include <Cool/OpenGL/ComputeShader.h>
#include <iostream>

App::App()
{
	constexpr int N = 150;
	// CPU create data
	std::vector<float> v;
	for (int i = 0; i < N; ++i) {
		v.push_back(i);
	}
	std::cout << "in  : ";
	for (auto x : v) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	// GPU upload data
	SSBO<float> ssbo(0);
	ssbo.uploadData(v);
	// GPU compute
	ComputeShader<256, 1, 1> computeShader("shaders/squareNumbers.comp");
	computeShader.compute(N);
	// CPU get data back
	ssbo.downloadData(v);
	std::cout << "out : ";
	for (auto x : v) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

void App::update() {
}

void App::ImGuiWindows() {
#ifndef NDEBUG
	if (m_bShow_Debug) {
		ImGui::Begin("Debug", &m_bShow_Debug);
		ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Checkbox("Show Demo Window", &m_bShow_ImGuiDemo);
		ImGui::End();
	}
	if (m_bShow_ImGuiDemo) // Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow(&m_bShow_ImGuiDemo);
#endif
}

void App::ImGuiMenus() {
}

void App::onEvent(const SDL_Event& e) {
	if (!RenderState::IsExporting()) {
		switch (e.type) {

		case SDL_MOUSEMOTION:
			if (!ImGui::GetIO().WantCaptureMouse) {

			}
			break;

		case SDL_MOUSEWHEEL:
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (!ImGui::GetIO().WantCaptureMouse) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					break;
				case SDL_BUTTON_RIGHT:
					break;
				case SDL_BUTTON_MIDDLE:
					break;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (!ImGui::GetIO().WantCaptureMouse) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					break;
				case SDL_BUTTON_RIGHT:
					break;
				case SDL_BUTTON_MIDDLE:
					break;
				}
			}
			break;

		case SDL_KEYDOWN:
			if (!ImGui::GetIO().WantTextInput) {

			}
			break;

		case SDL_KEYUP:
			if (!ImGui::GetIO().WantTextInput) {

			}
			break;

		default:
			break;
		}
	}
}