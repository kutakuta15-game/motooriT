#include "ObjectManager.h"
#include "sun/sun.h"
#include "earth/earth.h"
#include "moon/moon.h"
void ObjectManager::Init()
{
	{
		std::shared_ptr<Sun> m_sun = std::make_shared<Sun>();
		m_sun->Init();
		m_objList.push_back(m_sun);
	}
	{
		std::shared_ptr<Earth> m_earth = std::make_shared<Earth>();
		m_earth->Init();
		m_objList.push_back(m_earth);
	}
	{
		std::shared_ptr<Moon> m_moon = std::make_shared<Moon>();
		m_moon->Init();
		m_objList.push_back(m_moon);
	}
}

void ObjectManager::Update()
{
	for (auto obj : m_objList) obj->Update();
}

void ObjectManager::DrawLit()
{
	for (auto obj : m_objList) obj->DrawLit();
}
