#include "LayerStack.h"

namespace Gnote {
LayerStack::LayerStack() : m_LayerStack(), m_LayerInsert(0) {}

LayerStack::~LayerStack() {}

void LayerStack::PushOverlay(Layer *overlay) {
  m_LayerStack.emplace_back(overlay);
}

void LayerStack::PopLayer(Layer *layer) {
  auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
  if (it != m_LayerStack.end()) {
    m_LayerStack.erase(it);
    m_LayerInsert--;
  }
}

void LayerStack::PopOverlay(Layer *overlay) {
  auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), overlay);
  if (it != m_LayerStack.end()) {
    m_LayerStack.erase(it);
  }
}

void LayerStack::PushLayer(Layer *layer) {
  m_LayerStack.emplace(m_LayerStack.begin() + m_LayerInsert, layer);
  m_LayerInsert++;
}
} // namespace Gnote
