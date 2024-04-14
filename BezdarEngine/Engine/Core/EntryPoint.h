#pragma once
#include "Application.h"

extern BZEngine::Application* BZEngine::CreateApplication();

int main(int argc, char** argv)
{
    auto app = BZEngine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}