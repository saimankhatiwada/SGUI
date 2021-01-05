
#include "OrthographicCameraController.h"
#include "SGUI/Input.h"
#include "SGUI/KeyCodes.h"

namespace SGUI
{
	OrthographicCameraController::OrthographicCameraController(float AspectRatio, bool Rotation) :
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_ZoomLevel(1.0f), m_Rotation(Rotation),
		m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_CameraTranslationSpeed(1.0f), m_CameraRotationSpeed(125.0f), m_AspectRatio(AspectRatio)
	{

	}

	void OrthographicCameraController::OnUpdate(TimeSteps ts)
	{
		SG_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(SG_KEY_A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(SG_KEY_D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(SG_KEY_S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		else if (Input::IsKeyPressed(SG_KEY_W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		if (m_Rotation)
		{

			if (Input::IsKeyPressed(SG_KEY_Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}

			if (Input::IsKeyPressed(SG_KEY_E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		SG_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SG_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SG_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		SG_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = ((m_ZoomLevel) > (0.25f)) ? (m_ZoomLevel) : (0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		SG_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}


