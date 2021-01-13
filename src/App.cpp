#include "App.h"

#include <Cool/App/RenderState.h>
#include <Cool/App/Input.h>

#include <Cool/Random/Random.h>
#include <Cool/OpenGL/SSBO.h>
#include <Cool/OpenGL/ComputeShader.h>
#include <iostream>

std::vector<float> createRandomVector(int N) {
	std::vector<float> v;
	for (int i = 0; i < N; ++i) {
		v.push_back(Random::getMinus1to1() * 100.f);
	}
	return v;
}

template<typename T>
void printVector(const std::vector<T>& v) {
	for (auto& x : v) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

void td1_ex2() {
	constexpr int N = 10;
	// CPU create data
	std::vector<float> v1 = createRandomVector(N);
	std::vector<float> v2 = createRandomVector(N);
	std::cout << "in1  : ";
	printVector(v1);
	std::cout << "in2  : ";
	printVector(v2);
	// GPU upload data
	SSBO<float> ssbo1(0);
	ssbo1.uploadData(v1);
	SSBO<float> ssbo2(1);
	ssbo2.uploadData(v2);
	// GPU compute
	ComputeShader<256, 1, 1> computeShader("shaders/td1_ex2.comp");
	computeShader.compute(N);
	// CPU get data back
	ssbo1.downloadData(v1);
	std::cout << "out : ";
	printVector(v1);
}

App::App()
{
	td1_ex2();
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