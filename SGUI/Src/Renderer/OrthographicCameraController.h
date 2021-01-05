#pragma once
#include "Renderer/OrthographicCamera.h"
#include "Time/TimeSteps.h"
#include "SGUI/Events/ApplicationEvent.h"
#include "SGUI/Events/MouseEvent.h"



namespace SGUI
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float AspectRatio, bool Rotation = false);

		void OnUpdate(TimeSteps ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel;
		float m_CameraRotation;
		float m_CameraRotationSpeed;
		float m_CameraTranslationSpeed;
		glm::vec3 m_CameraPosition;
		bool m_Rotation = false;
		OrthographicCamera m_Camera;
	};
}