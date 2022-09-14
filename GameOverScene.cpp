#include "GameOverScene.h"
#include "Input.h"
#include "SceneManager.h"

GameOverScene::~GameOverScene()
{
	Finalize();
}

void GameOverScene::Initialize()
{

	// テクスチャ読み込み
	Sprite::LoadTexture(7, L"Resources/gameover.png");
	// 背景スプライト生成
	Gameoverimg = Sprite::Create(7, { 0.0f,0.0f });

	// テクスチャ読み込み
	//Sprite::LoadTexture(100, L"Resources/black.png");
	//スプライト生成
	black = Sprite::Create(100, { 0.0f,0.0f });
	nowTime = 0;
	endTime = 1;
	timeRate = 0;
}

void GameOverScene::Finalize()
{
}

void GameOverScene::Update()
{
	nowTime += 0.03;
	timeRate = min(nowTime / endTime, 1);
	ease();
	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		nowTime = 0;
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void GameOverScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画

	Gameoverimg->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion 背景スプライト描画




#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	black->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}

void GameOverScene::ease()
{

	float start=800;
	float end = 0;
	
	float pos;

	pos = (end - start) * ((timeRate * timeRate * timeRate) + 1) + start;
	XMFLOAT2 result;
	result.x = 0;
	result.y = pos;

	black->SetPosition(result);
}
