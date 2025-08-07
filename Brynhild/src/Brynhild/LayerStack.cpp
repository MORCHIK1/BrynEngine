#include "PreCompiledHeader.h"
#include "LayerStack.h"

Brynhild::LayerStack::LayerStack()
{
}

Brynhild::LayerStack::~LayerStack()
{
  for (Layer* layer : m_Layers) {
    delete layer;
  }
}

void Brynhild::LayerStack::PushLayer(Layer* layer)
{
  m_Layers.emplace(m_Layers.begin() + m_LayersIndex, layer);
  m_LayersIndex++;
}

void Brynhild::LayerStack::PushOverlay(Layer* overlay)
{
  m_Layers.emplace_back(overlay);
}

void Brynhild::LayerStack::PopLayer(Layer* layer)
{
  auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

  if (it != m_Layers.end()) {
    m_Layers.erase(it);
    m_LayersIndex--;
  }
}

void Brynhild::LayerStack::PopOverlay(Layer* overlay)
{
  auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);

  if (it != m_Layers.end()) {
    m_Layers.erase(it);
  }
}
