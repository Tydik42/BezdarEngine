#pragma once
#include "Application.h"
#include "Log.h"

extern BZEngine::Application* BZEngine::CreateApplication();

int main(int argc, char** argv)
{
    BZEngine::Log::Init();
    BZ_CORE_WARN("Log init");
    auto app = BZEngine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}