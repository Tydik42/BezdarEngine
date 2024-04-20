#pragma once
#include "pch.h"
#include "Events/Event.h"

namespace BZEngine {
class Layer
{
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    // TODO: imgui layer
    virtual void OnEvent(Event& event) {}

    const std::string& GetName() const { return m_DebugName; }
protected:
    std::string m_DebugName;
};

}