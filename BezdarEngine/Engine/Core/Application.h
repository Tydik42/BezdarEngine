#pragma once

#include "pch.h"
#include "Events/ApplicationEvent.h"
#include "Core/IWindow.h"
#include "LayerStack.h"

namespace BZEngine
{
class Application
{
public:
    Application();

    virtual ~Application();

    void Run();

    void OnEvent(BZEngine::Event& e);

    void PushLayer(Layer* layer);

    void PushOverlay(Layer* layer);

private:
    bool OnWindowClose(WindowCloseEvent& e);

private:
    std::unique_ptr<IWindow> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;

};
//should be implemented by the client
Application* CreateApplication();

} // namespace BZEngine