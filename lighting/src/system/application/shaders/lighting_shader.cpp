#include "pch.h"

#include "lighting_shader.h"

namespace GP
{

    CLightingShader::CLightingShader()
        : m_VertexShader(nullptr),
          m_PixelShader(nullptr),
          m_InputLayout(nullptr),
          m_MatrixBuffer(nullptr),
          m_SampleState(nullptr),
          m_LightBuffer(nullptr),
          m_CameraBuffer(nullptr)
    {
    }

    bool CLightingShader::Init(ID3D11Device *device, HWND hWnd)
    {
        std::filesystem::path vsFilename{std::filesystem::current_path() / "res" / "shaders" / "lighting_vs.hlsl"};
        std::filesystem::path psFilename{std::filesystem::current_path() / "res" / "shaders" / "lighting_ps.hlsl"};

        if (!InitShader(device, hWnd, vsFilename, psFilename))
        {
            return false;
        }

        return true;
    }

} // namespace GP
