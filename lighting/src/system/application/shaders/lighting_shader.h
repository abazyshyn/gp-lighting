#pragma once

namespace GP
{

    class CLightingShader
    {
    public:
        CLightingShader();

        bool Init(ID3D11Device *device, HWND hWnd);
        void Shutdown();
        bool Render(ID3D11DeviceContext *deviceContext, int32_t indexCount);
        bool SetShaderTexture(ID3D11DeviceContext *deviceContext, ID3D11ShaderResourceView *texture) { deviceContext->PSSetShaderResources(0, 1, &texture); }
        bool SetShaderLight(ID3D11DeviceContext *deviceContext, XMFLOAT3 cameraPosition, XMFLOAT3 lightDirection,
                            XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT4 specularColor, float specularPower);
        bool SetShaderMatrixBuffer(ID3D11DeviceContext *deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);

    private:
        bool InitShader(ID3D11Device *device, HWND hWnd, const std::filesystem::path &vsFilename, const std::filesystem::path &psFilename);

    private:
        ID3D11VertexShader *m_VertexShader;
        ID3D11PixelShader *m_PixelShader;
        ID3D11InputLayout *m_InputLayout;
        ID3D11Buffer *m_MatrixBuffer;
        ID3D11SamplerState *m_SampleState;
        ID3D11Buffer *m_LightBuffer;
        ID3D11Buffer *m_CameraBuffer;
    };

} // namespace GP
