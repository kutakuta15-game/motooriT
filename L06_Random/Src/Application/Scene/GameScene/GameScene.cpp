#include "GameScene.h"
#include"../SceneManager.h"

#include "../../main.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
//	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);



	//===================================================================
	// 乱数実験場
	//===================================================================
	//int randRes[10] = {};

	//// 如何にrand()が偏るか
	//srand((unsigned)time(NULL));
	//for (int i = 0; i < 100000000; ++i)
	//{
	//	int tmp = rand() % 10000;
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}

	//OutputDebugStringA("----------------------------------\n");
	//for (int i = 0; i < 10; ++i)
	//{
	//	std::stringstream ss;
	//	ss << "取得した値が" << i * 1000 << "~" << (i + 1) * 1000 <<
	//		"の件数 : \t" << randRes[i] << " \n";
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("----------------------------------\n");


	// メルセンヌツイスタ！！！！！！！！！！！！！！！！！！
	//for (int i = 0; i < 100000000; ++i)
	//{
	//	int tmp = KdGetInt(0, 9999);
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}

	//OutputDebugStringA("----------------------------------\n");
	//for (int i = 0; i < 10; ++i)
	//{
	//	std::stringstream ss;
	//	ss << "取得した値が" << i * 1000 << "~" << (i + 1) * 1000 <<
	//		"の件数 : \t" << randRes[i] << " \n";
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("----------------------------------\n");


	// レッスンその1 : CカードとRカードをそれぞれ50%の確率で起動時に表示せよ
//	int rnd = KdGetInt(0, 999);
//	if(rnd < 500) OutputDebugStringA("Cカード\n");
//	else OutputDebugStringA("Rカード\n");

	// レッスンその2 : CカードとRカードをそれぞれ99.5%(Cカード)と0.5%(Rカード)の確率で起動時に表示せよ

	//int _Bunbo			= 1000;
	//int _ThusenNum		= 10000000;
	//int _TosenNum[2]	= { 0, 0 };
	//for (int i = 0; i < _ThusenNum; ++i)
	//{
	//	int _rnd = KdGetInt(0, _Bunbo - 1);
	//	if (_rnd <= 4) ++_TosenNum[1];
	//	else ++_TosenNum[0];
	//}

	//float prob = 0;
	//for (int i = 0; i < 2; i++)
	//{
	//	std::stringstream ss;
	//	prob = ((float)_TosenNum[i] / (float)_ThusenNum) * 100;
	//	round_n(prob, 3);
	//	switch (i)
	//	{
	//	case 0:
	//		ss << "Cカード当選回数 = " << _TosenNum[0] << " " <<
	//			"当選確率 = " << prob << "%" << "\n";
	//		break;
	//	case 1:
	//		ss << "Rカード当選確率 = " << _TosenNum[1] << " " <<
	//			"当選確率 = " << prob << "%" << "\n";
	//		break;
	//	}
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("------------------------------------------\n");


	// レッスンその3 : CカードとRカードとSRカードそれぞれ34% 33% 33%の確率っで起動時に表示せよ！
	int _Bunbo			= 100;
	int _ThusenNum		= 10000000;
	int _TosenNum[3]	= { 0, 0, 0 };
	for (int i = 0; i < _ThusenNum; ++i)
	{
		int _rnd = KdGetInt(0, _Bunbo - 1);
		if (_rnd <= 33) ++_TosenNum[0];
		else if (_rnd <= 66) ++_TosenNum[1];
		else ++_TosenNum[2];
	}

	float prob = 0;
	for (int i = 0; i < 3; i++)
	{
		std::stringstream ss;
		prob = ((float)_TosenNum[i] / (float)_ThusenNum) * 100;
		round_n(prob, 3);
		switch (i)
		{
		case 0:
			ss << "Cカード当選回数 = " << _TosenNum[0] << " " <<
				"当選確率 = " << prob << "%" << "\n";
			break;
		case 1:
			ss << "Rカード当選確率 = " << _TosenNum[1] << " " <<
				"当選確率 = " << prob << "%" << "\n";
			break;
		case 2:
			ss << "SRカード当選確率 = " << _TosenNum[1] << " " <<
				"当選確率 = " << prob << "%" << "\n";
			break;
		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("------------------------------------------\n");
}

void GameScene::Event()
{
}