#pragma once

#include <Cool/App/IApp.h>

using namespace Cool;

class App : public Cool::IApp {
public:
	App();
	~App() = default;

	void update() override;
	void ImGuiWindows() override;
	void ImGuiMenus() override;
	void onEvent(const SDL_Event & e) override;

private:
#ifndef NDEBUG
	bool m_bShow_Debug = true;
	bool m_bShow_ImGuiDemo = false;
#endif
};