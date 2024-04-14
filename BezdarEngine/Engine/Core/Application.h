#pragma once

namespace BZEngine
{
class Application
{
public:
    Application();

    virtual ~Application();

    void Run();
};
//should be implemented by the client
Application* CreateApplication();

} // namespace BZEngine