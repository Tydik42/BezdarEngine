#pragma once

#include "Core/Layer.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_dx12.h"
#include "SDL.h"
#include "Core/Application.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace BZEngine
{
class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnEvent(Event& event) override;

private:
    float m_Time = 0.0f;
};
}