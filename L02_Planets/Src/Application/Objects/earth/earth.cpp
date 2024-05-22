#include "earth.h"

void Earth::Init()
{
	m_deg = 0;
	m_scale = 0.5f;
	m_mat = Math::Matrix::Identity;

	m_model.Load("Asset/Data/LessonData/Planets/earth.gltf");
}

void Earth::Update()
{
	if (++m_deg > 360) m_deg -= 360;
	m_mat = Math::Matrix::CreateScale(m_scale) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians((m_deg * 4) % 360)) * Math::Matrix::CreateTranslation({ -3, 0, 0 }) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_deg));
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mat);
}
