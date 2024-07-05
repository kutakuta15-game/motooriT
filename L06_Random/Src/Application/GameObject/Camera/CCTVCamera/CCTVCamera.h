#pragma once
#include "../CameraBase.h"
class CCTVCamera : public CameraBase
{
public:
	CCTVCamera() {}
	~CCTVCamera() {}

	void Init() override;

	void PostUpdate() override;
private:
	void UpdateLookAtRotate(const Math::Vector3& _targetPos);
};