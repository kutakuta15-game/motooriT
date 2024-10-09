#pragma once

class Water : public KdGameObject
{
public:
	Water() {}
	virtual ~Water()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

};