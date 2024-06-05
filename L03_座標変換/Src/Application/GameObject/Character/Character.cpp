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
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!m_camera.expired())
		{
			POINT mousePos;
			GetCursorPos(&mousePos);
			ClientToScreen(Application::Instance().GetWindowHandle(), &mousePos);

			// レイ情報
			KdCollider::RayInfo ray;
			ray.m_type = KdCollider::Type::TypeGround;
			m_camera.lock()->GenerateRayInfoFromClientPos(mousePos, ray.m_pos, ray.m_dir, ray.m_range);

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
		}
	}

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
	if(!m_camera.expired()) m_camera.lock()->ConvertWorldToScreenDetail(m_mWorld.Translation() + Math::Vector3(0, 0.5f, 0), pos);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, pos.x, pos.y);
}
