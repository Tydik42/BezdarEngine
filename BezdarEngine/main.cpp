#include "BezdarEngine.h"


class Sandbox : public BZEngine::Application
{
public:
    Sandbox()
    {
    }

    ~Sandbox()
    {
    }

};

BZEngine::Application* BZEngine::CreateApplication()
{
    return new Sandbox();
}