#pragma once

#include "pch.h"
#include "Events/ApplicationEvent.h"
#include "Core/IWindow.h"


namespace BZEngine
{
class Application
{
public:
    Application();

    virtual ~Application();

    void Run();

private:
    std::unique_ptr<IWindow> m_Window;
    bool m_Running = true;
};
//should be implemented by the client
Application* CreateApplication();

} // namespace BZEngine