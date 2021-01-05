#pragma once

namespace SGUI
{
	class TimeSteps
	{
	public:
		TimeSteps(float time):
			m_Time(time)
		{

		}

		operator float() const { return m_Time; }

		float GetSeconds() { return m_Time; }
		float GetMilliSecounds() { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}