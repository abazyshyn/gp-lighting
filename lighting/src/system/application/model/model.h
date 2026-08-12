#pragma once

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "system/application/texture/texture.h"

namespace GP
{

    class CModel
    {
    public:
        CModel();

        bool Init(std::string modelFilename, std::string textureFilename, ID3D11Device *device, ID3D11DeviceContext *deviceContext);
        void Shutdown();
        void Render(ID3D11DeviceContext *deviceContext);

        int32_t GetIndexCount() const { return m_indexCount; }
        ID3D11ShaderResourceView *GetTexture() { return m_Texture.GetTexture(); }

    private:
        bool InitBuffers(ID3D11Device *device);
        void ShutdownBuffers();
        void RenderBuffers(ID3D11DeviceContext *deviceContext);

        bool LoadTexture(std::string textureFilename, ID3D11Device *device, ID3D11DeviceContext *deviceContext);
        void ReleaseTexture();

        bool LoadModel(std::string modelFilename);
        void ReleaseModel();

    private:
        struct Vertex_s
        {
            XMFLOAT3 position;
            XMFLOAT2 texture;
            XMFLOAT3 normal;
        };

        struct Model_s
        {
            float x, y, z;
            float tu, tv;
            float nx, ny, nz;
        };

        ID3D11Buffer *m_vertexBuffer;
        ID3D11Buffer *m_indexBuffer;
        int32_t m_vertexCount;
        int32_t m_indexCount;
        std::vector<Model_s> m_model;
        CTexture m_Texture;
    };

} // namespace GP
