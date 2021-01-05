#pragma once
#include "SGUI.h"
#include "Level.h"
#include "imgui.h"

class GameLayer : public SGUI::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(SGUI::TimeSteps ts) override;
	void OnImguiRender() override;
	void OnEvent(SGUI::Event& e) override;
	bool OnMouseButtonPressed(SGUI::MouseButtonPressedEvent& e);
	bool OnWindowResize(SGUI::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	SGUI::Scope<SGUI::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};