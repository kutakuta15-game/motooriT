#include "CameraBase.h"
#include "../../main.h"
void CameraBase::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}

	// ↓マウスを画面中央へ固定させる
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
}

void CameraBase::PostUpdate()
{
	if (!m_spCamera) return;


	if (!m_wpTarget.expired())
	{
		Math::Vector3 _nowPos = m_mWorld.Translation();
		Math::Vector3 _targetPos = m_wpTarget.lock()->GetPos();
		Math::Vector3 _targetDir = _targetPos;
		float range = _targetDir.Length();
		_targetDir.Normalize();

		KdCollider::RayInfo ray(KdCollider::Type::TypeGround, _nowPos, _targetDir, range);
		std::list<KdCollider::CollisionResult> retRayResult;
		for (const auto& obj : Application::Instance().GetObjList())
		{
			obj->Intersects(ray, &retRayResult);
		}

		Math::Vector3 hitPos;
		float maxOverlap = 0;
		bool hit = false;
		for (const auto& ret : retRayResult)
		{
			if (ret.m_overlapDistance > maxOverlap)
			{
				maxOverlap = ret.m_overlapDistance;
				hitPos = ret.m_hitPos;
				hit = true;
			}
		}

		if (hit)
		{
			// TODO カメラの向きどうしよっか
			Math::Matrix pos = Math::Matrix::CreateTranslation(hitPos);
			m_mWorld =
		}
	}

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::PreDraw()
{
	if (!m_spCamera) return;

	m_spCamera->SetToShader();
}

void CameraBase::UpdateRotateByMouse()
{
	// ①マウスの現在の位置を取得する
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	// ②画面中央からの差分を算出する
	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	// ③カーソルを画面中央へ戻す
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// ④差分を利用して、回転角度を設定する
	m_DegAng.x += _mouseMove.y * 0.15f;
	m_DegAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -45.f, 45.f);
}
