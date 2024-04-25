#pragma once

#include "pch.h"
#include "Events/ApplicationEvent.h"
#include "Core/IWindow.h"
#include "LayerStack.h"
#include "Core/Log.h"
#include "Core/Asserts.h"

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

    inline IWindow& GetWindow() { return *m_Window; }

    static Application& Get() { return *s_Instance; }

private:
    bool OnWindowClose(WindowCloseEvent& e);

private:
    std::unique_ptr<IWindow> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
    static Application* s_Instance;

};
//should be implemented by the client
Application* CreateApplication();

} // namespace BZEngine