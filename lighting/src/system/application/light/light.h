#pragma once

namespace GP
{

    class CLight
    {
    public:
        void SetAmbientColor(XMFLOAT4 ambientColor) { m_ambientColor = ambientColor; };
        void SetDiffuseColor(XMFLOAT4 diffuseColor) { m_diffuseColor = diffuseColor; };
        void SetSpecularColor(XMFLOAT4 specularColor) { m_specularColor = specularColor; };
        void SetDirection(XMFLOAT3 direction) { m_direction = direction; };
        void SetSpecularPower(float power) { m_specularPower = power; };

        XMFLOAT4 GetAmbientColor() const { return m_ambientColor; };
        XMFLOAT4 GetDiffuseColor() const { return m_diffuseColor; };
        XMFLOAT4 GetSpecularColor() const { return m_specularColor; };
        XMFLOAT3 GetDirection() const { return m_direction; };
        float GetSpecularPower() const { return m_specularPower; };

    private:
        XMFLOAT4 m_ambientColor;
        XMFLOAT4 m_diffuseColor;
        XMFLOAT3 m_direction;
        XMFLOAT4 m_specularColor;
        float m_specularPower;
    };

} // namespace GP
