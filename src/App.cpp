#include "App.h"

#include <Cool/App/RenderState.h>
#include <Cool/App/Input.h>

#include <Cool/Random/Random.h>
#include <Cool/OpenGL/SSBO.h>
#include <Cool/OpenGL/ComputeShader.h>
#include <Cool/LoadImage/LoadImage.h>
#include <Cool/ExportImage/AsPNG.h>
#include <Cool/OpenGL/Texture.h>
#include <Cool/OpenGL/TextureFB.h>
#include <Cool/OpenGL/Shader.h>
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

void exportFramebuffer(FrameBuffer& frameBuffer, const char* filepath) {
	frameBuffer.bind();
	RectSize size = RenderState::Size();
	unsigned char* data = new unsigned char[4 * size.width() * size.height()];
	glReadPixels(0, 0, size.width(), size.height(), GL_RGBA, GL_UNSIGNED_BYTE, data);
	frameBuffer.unbind();
	// Write png
	ExportImage::AsPNG(filepath, size.width(), size.height(), data);
	//
	delete[] data;
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
	ComputeShader computeShader("shaders/td1_ex2.comp");
	computeShader.compute(N);
	// CPU get data back
	ssbo1.downloadData(v1);
	std::cout << "out : ";
	printVector(v1);
}

void td1_ex3() {
	// CPU get image data
	int w, h;
	unsigned char* imageData = LoadImage::Load("img/mc.jpg", &w, &h);
	const int N = w * h * 4;
	std::vector<int> v;
	for (int i = 0; i < N; ++i) {
		v.push_back(imageData[i]);
	}
	// GPU upload data
	SSBO<int> ssbo(0);
	ssbo.uploadData(v);
	// GPU compute
	ComputeShader computeShader("shaders/td1_ex3.comp");
	computeShader.compute(N / 4);
	// CPU get data back
	ssbo.downloadData(v);
	for (int i = 0; i < N; ++i) {
		imageData[i] = v[i];
	}
	ExportImage::AsPNG("img/mcout.png", w, h, imageData);
	LoadImage::Free(imageData);
}

void App::td1_ex3_withFragmentShader() {
	// Load image in a Texture
	Texture imageTexture;
	imageTexture.genTexture();
	int w, h;
	unsigned char* data = LoadImage::Load("img/mc.jpg", &w, &h);
	imageTexture.uploadRGBA(w, h, data);
	LoadImage::Free(data);
	RenderState::setExportSize(w, h);
	RenderState::setIsExporting(true);
	// Apply shader
	Shader shader({
		ShaderCode(ShaderType::Vertex, "Cool/Renderer_Fullscreen/fullscreen.vert"),
		ShaderCode(ShaderType::Fragment, "shaders/td1_ex3.frag")
	});
	m_renderer.begin();
	{
		shader.bind();
		imageTexture.bindToSlot(0);
		m_renderer.render();
	}
	exportFramebuffer(m_renderer.renderBuffer(), "img/mcout2.jpg");
	RenderState::setIsExporting(false);
}

App::App()
{
	td1_ex2();
	td1_ex3();
	td1_ex3_withFragmentShader();
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