#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点 (ターゲット) の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.f, -10.f);
	// 一旦行列を確定させる
	m_mWorld = m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Vector3 _targetPos;
//	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetPos = _spTarget->GetPos();
//		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	UpdateLookAtRotate(_targetPos);
}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& _targetPos)
{
	//// YAW角
	//float _yaw = DirectX::XMConvertToDegrees(atan2(_targetVec.x, _targetVec.z));
	//// PITCH角
	//float _pitch = DirectX::XMConvertToDegrees(atan2(_targetVec.y, sqrt(pow(_targetVec.x, 2))));

	Math::Matrix _shadowVP = DirectX::XMMatrixLookAtLH(this->GetPos(), _targetPos, Math::Vector3::Up);

	m_mWorld = _shadowVP.Invert();
	
}
