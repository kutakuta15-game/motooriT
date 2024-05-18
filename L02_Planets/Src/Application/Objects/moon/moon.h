#pragma once
class Moon : public KdGameObject
{
public:
	Moon() {}
	~Moon() {}

	void Init() override;
	void Update() override;
	void DrawLit() override;
private:
	int m_deg;
	float m_scale;
	Math::Matrix m_mat;

	KdModelData m_model;
};