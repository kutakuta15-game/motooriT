#include "moon.h"

void Moon::Init()
{
	m_deg = 0;
	m_scale = 0.5f;
	m_mat = Math::Matrix::Identity;

	m_model.Load("Asset/Data/LessonData/Planets/moon.gltf");
}

void Moon::Update()
{
	if (++m_deg > 360) m_deg -= 360;
	m_mat = Math::Matrix::CreateScale(m_scale) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians((m_deg * 8) % 360))
		* Math::Matrix::CreateTranslation({ -0.8f, 0, 0 }) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(360 - (m_deg * 2) % 360))
		* Math::Matrix::CreateTranslation({ -3, 0, 0 }) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(360 - m_deg));
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mat);
}
