#include "PreCompiledHeader.h"
#include "LayerStack.h"

Brynhild::LayerStack::LayerStack()
{
  m_LayersInsert = m_Layers.begin();
}

Brynhild::LayerStack::~LayerStack()
{
  for (Layer* layer : m_Layers) {
    delete layer;
  }
}

void Brynhild::LayerStack::PushLayer(Layer* layer)
{
  m_LayersInsert = m_Layers.emplace(m_LayersInsert, layer);
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
    --m_LayersInsert;
  }
}

void Brynhild::LayerStack::PopOverlay(Layer* overlay)
{
  auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);

  if (it != m_Layers.end()) {
    m_Layers.erase(it);
  }
}
