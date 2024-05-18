#include "sun.h"

void Sun::Init()
{
	m_deg = 0;
	m_scale = 1.1f;
	m_mat = Math::Matrix::Identity;

	m_model.Load("Asset/Data/LessonData/Planets/sun.gltf");
}

void Sun::Update()
{
	if (++m_deg > 360) m_deg -= 360;
	m_mat = Math::Matrix::CreateScale(m_scale) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_deg)) * Math::Matrix::CreateTranslation({ 0, 0, 0 });
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mat);
}
