#include "SDLWindow.h"
#include "Core/Asserts.h"
#include "Events/ApplicationEvent.h"

namespace BZEngine {

static bool s_SDLInitialized = false;

IWindow* IWindow::Create(const WindowProps& props)
{
    return new SDLWindow(props);
}

SDLWindow::SDLWindow(const WindowProps& props)
{
    Init(props);
}

SDLWindow::~SDLWindow()
{
    Shutdown();
}

void SDLWindow::Init(const WindowProps& props)
{
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    BZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!s_SDLInitialized)
    {
        int success = SDL_Init(SDL_INIT_VIDEO);
        BZ_CORE_ASSERT(success == 0, "Failed to initialize SDL!");
        s_SDLInitialized = true;
    }

    m_Window = SDL_CreateWindow(props.Title.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                props.Width,
                                props.Height,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    BZ_CORE_ASSERT(m_Window, "Failed to create window!");

    SDL_GL_MakeCurrent(m_Window, SDL_GL_CreateContext(m_Window));
    SDL_SetWindowData(m_Window, "m_Data", &m_Data);
    SetVSync(true);
}

void SDLWindow::Shutdown()
{
    SDL_DestroyWindow(m_Window);
}

void SDLWindow::OnUpdate()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle your events here
    }
    SDL_GL_SwapWindow(m_Window);
}

void SDLWindow::SetVSync(bool enabled)
{
    m_Data.VSync = enabled;
    SDL_GL_SetSwapInterval(enabled ? 1 : 0);
}

bool SDLWindow::IsVSync() const
{
    return m_Data.VSync;
}
} // namespace BZEngine