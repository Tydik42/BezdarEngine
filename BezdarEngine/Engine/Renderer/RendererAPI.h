#pragma once
#include <cstdint>

namespace BZEngine {
    class RendererAPI {
    public:
        enum class API {
            None = 0, DirectX = 1
        };

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual void Clear() = 0;

        static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}