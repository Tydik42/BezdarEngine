#include "Application.h"
#include "LayerStack.h"

namespace BZEngine
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
Application::Application()
{
    m_Window = std::unique_ptr<IWindow>(IWindow::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application()
{

}

void Application::OnEvent(BZEngine::Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BZ_BIND_EVENT_FN(Application::OnWindowClose));

    //BZ_CORE_INFO("{0}", e.ToString());

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.Handled)
            break;
    }
}

void Application::Run()
{
    while (m_Running)
    {
        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdate();
        }
        m_Window->OnUpdate();

    }
}

// TODO: add layers attach
void Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* layer)
{
    m_LayerStack.PushOverlay(layer);
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}

} // namespace BZEngine
