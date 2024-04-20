#include "BezdarEngine.h"

class ExampleLayer : public BZEngine::Layer
{
public:
    ExampleLayer() : BZEngine::Layer("Example") {}

    void OnUpdate() override
    {
        //BZ_INFO("ExampleLayer::Update");
    }

    void OnEvent(BZEngine::Event& event) override
    {
        BZ_TRACE("{0}", event.ToString());
    }

};


class Sandbox : public BZEngine::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {
    }

};

BZEngine::Application* BZEngine::CreateApplication()
{
    return new Sandbox();
}