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

} // namespace GP
