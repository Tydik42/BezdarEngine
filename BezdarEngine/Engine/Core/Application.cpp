#include "Application.h"


namespace BZEngine
{
Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
    WindowResizeEvent e(1280, 720);
    if (e.IsInCategory(EventCategoryApplication))
    {
        BZ_TRACE(e.ToString());
    }
    if (e.IsInCategory(EventCategoryInput))
    {
        BZ_TRACE(e.ToString());
    }
    while (true);
}
} // namespace BZEngine
