#pragma once
#include "Layer.h"
#include <vector>


namespace SGUI
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverLay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		unsigned int  m_LayerInsertIndex = 0;
		std::vector<Layer*> m_Layers;
	};
}
