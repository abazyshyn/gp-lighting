#pragma once

namespace GP
{

    constexpr unsigned int NUM_LIGHTS = 4;

    class CLightingShader
    {
    public:
        CLightingShader();

        bool Init(ID3D11Device *device, HWND hWnd);
        void Shutdown();
        bool Render(ID3D11DeviceContext *deviceContext, int32_t indexCount);
        bool SetShaderTexture(ID3D11DeviceContext *deviceContext, ID3D11ShaderResourceView *texture) { deviceContext->PSSetShaderResources(0, 1, &texture); }
        bool SetShaderCamera(ID3D11DeviceContext *deviceContext, XMFLOAT3 cameraPosition);
        bool SetShaderMatrixBuffer(ID3D11DeviceContext *deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
        bool SetShaderLight(ID3D11DeviceContext *deviceContext, XMFLOAT3 lightDirection, XMFLOAT4 ambientColor,
                            XMFLOAT4 diffuseColor, XMFLOAT4 specularColor, float specularPower);

    private:
        bool InitShader(ID3D11Device *device, HWND hWnd, const std::filesystem::path &vsFilename, const std::filesystem::path &psFilename);
        void ShutdownShader();
        void OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hWnd, const std::filesystem::path &shaderFilename);
        void RenderShader(ID3D11DeviceContext *deviceContext, int32_t indexCount);

    private:
        struct MatrixBuffer_s
        {
            XMMATRIX worldMatrix;
            XMMATRIX viewMatrix;
            XMMATRIX projectionMatrix;
        };

        struct CameraBuffer_s
        {
            XMFLOAT3 cameraPosition;
            float _pad; // Padding
        };

        struct LightBuffer_s
        {
            XMFLOAT4 ambientColor;
            XMFLOAT4 diffuseColor;
            XMFLOAT3 lightDirection;
            float specularPower;
            XMFLOAT4 specularColor;
        };

        ID3D11VertexShader *m_vertexShader;
        ID3D11PixelShader *m_pixelShader;
        ID3D11InputLayout *m_inputLayout;
        ID3D11Buffer *m_matrixBuffer;
        ID3D11SamplerState *m_sampleState;
        ID3D11Buffer *m_lightBuffer;
        ID3D11Buffer *m_cameraBuffer;
        D3D11_MAPPED_SUBRESOURCE m_mappedSubresource;
    };

} // namespace GP
