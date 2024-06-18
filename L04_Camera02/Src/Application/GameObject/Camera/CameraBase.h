#pragma once

class CameraBase : public KdGameObject
{
public:
	CameraBase()						{}
	virtual ~CameraBase()	override	{}

	void Init()				override;
	void Update()			override;
	void PreDraw()			override;

	void SetTarget(const std::shared_ptr<KdGameObject>& _target) { m_wpTarget = _target; }

protected:
	std::shared_ptr<KdCamera>	m_spCamera = nullptr;
	std::weak_ptr<KdGameObject> m_wpTarget;

	Math::Matrix				m_mLocalPos = Math::Matrix::Identity;
	Math::Matrix				m_mRotation = Math::Matrix::Identity;
};