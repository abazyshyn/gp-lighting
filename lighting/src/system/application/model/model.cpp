#include "pch.h"

#include "model.h"

namespace GP
{

    CModel::CModel()
        : m_vertexBuffer(nullptr),
          m_indexBuffer(nullptr),
          m_vertexCount(0),
          m_indexCount(0)
    {
    }

    bool CModel::Init(std::string modelFilename, std::string textureFilename, ID3D11Device *device, ID3D11DeviceContext *deviceContext)
    {
        if (!LoadModel(modelFilename))
        {
            return false;
        }

        if (!InitBuffers(device))
        {
            return false;
        }

        if (!LoadTexture(textureFilename, device, deviceContext))
        {
            return false;
        }

        return true;
    }

    void CModel::Shutdown()
    {
        ReleaseTexture();
        ReleaseModel();
        ShutdownBuffers();
    }

    void CModel::Render(ID3D11DeviceContext *deviceContext)
    {
        RenderBuffers(deviceContext);
    }

    bool CModel::InitBuffers(ID3D11Device *device)
    {
        std::vector<Vertex_s> vertices(m_vertexCount);
        std::vector<uint32_t> indices(m_indexCount);

        for (size_t i = 0; i < vertices.size(); ++i)
        {
            vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
            vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
            vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
            indices[i] = static_cast<uint32_t>(i);
        }

        D3D11_BUFFER_DESC vertexBufferDescription{};
        vertexBufferDescription.ByteWidth = static_cast<uint32_t>(vertices.size()) * static_cast<uint32_t>(sizeof(Vertex_s));
        vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
        vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        vertexBufferDescription.MiscFlags = 0;
        vertexBufferDescription.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA vertexData{};
        vertexData.pSysMem = vertices.data();
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        if (FAILED(device->CreateBuffer(&vertexBufferDescription, &vertexData, &m_vertexBuffer)))
        {
            return false;
        }

        D3D11_BUFFER_DESC indexBufferDescription{};
        indexBufferDescription.ByteWidth = static_cast<uint32_t>(indices.size()) * static_cast<uint32_t>(sizeof(uint32_t));
        indexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
        indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
        indexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        indexBufferDescription.MiscFlags = 0;
        indexBufferDescription.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA indexData{};
        indexData.pSysMem = indices.data();
        indexData.SysMemPitch = 0;
        indexData.SysMemSlicePitch = 0;

        if (FAILED(device->CreateBuffer(&indexBufferDescription, &indexData, &m_indexBuffer)))
        {
            return false;
        }

        return true;
    }

    void CModel::ShutdownBuffers()
    {
        if (m_vertexBuffer)
        {
            m_vertexBuffer->Release();
            m_vertexBuffer = nullptr;
        }

        if (m_indexBuffer)
        {
            m_indexBuffer->Release();
            m_indexBuffer = nullptr;
        }
    }

    void CModel::RenderBuffers(ID3D11DeviceContext *deviceContext)
    {
        const uint32_t stride = static_cast<uint32_t>(sizeof(Vertex_s));
        const uint32_t offset = 0;
        deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
        deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    bool CModel::LoadTexture(std::string textureFilename, ID3D11Device *device, ID3D11DeviceContext *deviceContext)
    {
        if (!m_Texture.Init(textureFilename, device, deviceContext))
        {
            return false;
        }

        return true;
    }

    void CModel::ReleaseTexture()
    {
        m_Texture.Shutdown();
    }

    bool CModel::LoadModel(std::string modelFilename)
    {
        std::ifstream fin;
        std::filesystem::path modelFilepath{std::filesystem::current_path() / "res" / "models" / modelFilename};

        fin.open(modelFilepath);
        if (fin.fail())
        {
            return false;
        }

        char input{};
        fin.get(input);
        while (input != ':')
        {
            fin.get(input);
        }

        fin >> m_vertexCount;
        m_indexCount = m_vertexCount;
        m_model.resize(m_vertexCount);

        fin.get(input);
        while (input != ':')
        {
            fin.get(input);
        }
        fin.get(input);
        fin.get(input);

        for (Model_s &m : m_model)
        {
            fin >> m.x >> m.y >> m.z;
            fin >> m.tu >> m.tv;
            fin >> m.nx >> m.ny >> m.nz;
        }

        fin.close();
        return true;
    }

    void CModel::ReleaseModel()
    {
        m_model.clear();
    }

} // namespace GP
