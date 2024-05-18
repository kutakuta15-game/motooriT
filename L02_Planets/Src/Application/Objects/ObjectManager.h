#pragma once

class ObjectManager
{
public:
	void Update();
	void DrawLit();
private:
	std::list<std::shared_ptr<KdGameObject>> m_objList;
private:
	ObjectManager() { Init(); }
	~ObjectManager() {}

	void Init();
public:
	static ObjectManager& Instance() {
		static ObjectManager instance;
		return instance;
	}
};