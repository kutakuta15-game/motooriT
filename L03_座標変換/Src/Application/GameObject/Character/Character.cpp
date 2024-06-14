#include "Character.h"
#include "../../main.h"
void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/loading_text.png");
}

void Character::Update()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// ① マウス座標を取得する
		POINT _mousePos;
		GetCursorPos(&_mousePos);
		ClientToScreen(Application::Instance().GetWindowHandle(), &_mousePos);

		// ② の発射方向を求める

		// 授業
		std::shared_ptr<KdCamera> _camera = m_wpCamera.lock();

		if (_camera)
		{
			Math::Vector3	_camPos = _camera->GetCameraMatrix().Translation();
			Math::Vector3	_rayDir = Math::Vector3::Zero;
			float			_rayRange = 1000.f;
			_camera->GenerateRayInfoFromClientPos(_mousePos, _camPos, _rayDir, _rayRange);

			// ③ 実際にレイを飛ばして衝突位置を求める

			// 授業
			const std::shared_ptr<KdGameObject> _terrain = m_wpTerrain.lock();
			if (_terrain)
			{
				Math::Vector3 _endRayPos = _camPos + (_rayDir * _rayRange);
				KdCollider::RayInfo _rayInfo(KdCollider::Type::TypeGround, _camPos, _endRayPos);

				// 実際の当たり判定の処理
				std::list<KdCollider::CollisionResult> _results;
				_terrain->Intersects(_rayInfo, &_results);

				// 結果が一つでも帰って来ていたら
				if (_results.size())
				{
					for (const KdCollider::CollisionResult& result : _results)
					{
						m_TargetPos = result.m_hitPos;
					}
				}
			}
		}


		// 自作
		/*if (!m_wpCamera.expired())
		{
			POINT _mousePos;
			GetCursorPos(&_mousePos);
			ClientToScreen(Application::Instance().GetWindowHandle(), &_mousePos);


			KdCollider::RayInfo ray;
			ray.m_type = KdCollider::Type::TypeGround;
			m_wpCamera.lock()->GenerateRayInfoFromClientPos(_mousePos, ray.m_pos, ray.m_dir, ray.m_range);


			std::list<KdCollider::CollisionResult> retRayList;
			for (const auto& obj : Application::Instance().GetObjList())
			{
				obj->Intersects(ray, &retRayList);
			}

			Math::Vector3 hitPos = {};
			float maxOverlap = 0;
			bool hit = false;
			for (const auto& ret : retRayList)
			{
				if (maxOverlap > ret.m_overlapDistance) continue;
				hitPos = ret.m_hitPos;
				maxOverlap = ret.m_overlapDistance;
				hit = true;
			}

			if (hit)
			{
				nowPos = hitPos;
			}
		}*/
	}
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();
	Math::Vector3 moveVec = m_TargetPos - nowPos;

	if (moveVec.Length() < moveSpd) moveSpd = moveVec.Length();
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	Math::Vector3 pos;
	if (!m_wpCamera.expired()) m_wpCamera.lock()->ConvertWorldToScreenDetail(m_mWorld.Translation() + Math::Vector3(0, 0.5f, 0), pos);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, pos.x, pos.y);
}
