#pragma once

class CameraBase;
class Character : public KdGameObject
{
public:
	Character()							{}
	~Character()			override	{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;
	void GenerateDepthMapFromLight() override;
	void DrawLit()			override;

	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}

	void RegistHitObject(const std::shared_ptr<KdGameObject>& object)
	{
		m_wpHitObjectList.push_back(object);
	}

private:
	// キャラクターの回転行列を作成する
	void UpdateRotate(const Math::Vector3& srcMoveVec);
	// 衝突判定とそれに伴う座標の更新
	void UpdateCollision();

	std::shared_ptr<KdModelWork>				m_spModel		= nullptr;
	std::shared_ptr<KdAnimator>					m_spAnimator	= nullptr;

	std::weak_ptr<CameraBase>					m_wpCamera;
	std::vector<std::weak_ptr<KdGameObject>>	m_wpHitObjectList{};

	Math::Vector3								m_worldRot;

	float										m_Gravity		= 0;
	bool										m_isGround : 1	= false;

// ステートパターン管理系！
private:
	class ActionStateBase
	{
	public:
		virtual ~ActionStateBase() = default;

		virtual void Enter(Character& _own)		{}
		virtual void Update(Character& _own)	{}
		virtual void Exit(Character& _own)		{}
	};

	class ActionIdle : public ActionStateBase
	{
	public:
		ActionIdle() = default;

		void Enter(Character& _own)		override;
		void Update(Character& _own)	override;
		void Exit(Character& _own)		override;
	};

	class ActionJump : public ActionStateBase
	{
	public:
		ActionJump() = default;

		void Enter(Character& _own)		override;
		void Update(Character& _own)	override;
		void Exit(Character& _own)		override;
	};

	class ActionWalk : public ActionStateBase
	{
	public:
		ActionWalk() = default;

		void Enter(Character& _own)		override;
		void Update(Character& _own)	override;
		void Exit(Character& _own)		override;
	};

	void ChangeActionState(std::shared_ptr<ActionStateBase> _nextState);
	std::shared_ptr<ActionStateBase> m_nowAction = nullptr;
};