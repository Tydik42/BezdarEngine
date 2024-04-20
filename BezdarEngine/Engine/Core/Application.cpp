#include "Application.h"


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
    BZ_CORE_INFO("{0}", e.ToString());
}

void Application::Run()
{
    while (m_Running)
    {
        m_Window->OnUpdate();
    }
}
} // namespace BZEngine
