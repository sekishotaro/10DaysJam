#include "ResultScene.h"
#include "SceneManager.h"

ResultScene::~ResultScene()
{
	Finalize();
}

void ResultScene::Initialize()
{
	// テクスチャ読み込み
	Sprite::LoadTexture(8, L"Resources/stageclear.png");
	// 背景スプライト生成
	GameClearImg = Sprite::Create(8, { 0.0f,0.0f });

	// テクスチャ読み込み
	//Sprite::LoadTexture(100, L"Resources/black.png");
	//スプライト生成
	black = Sprite::Create(100, { 0.0f,0.0f });
	nowTime = 0;
	endTime = 1;
	timeRate = 0;
}

void ResultScene::Finalize()
{
}

void ResultScene::Update()
{
	nowTime += 0.03;
	timeRate = min(nowTime / endTime, 1);
	ease();
	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		nowTime = 0;
		SceneManager::GetInstance()->ChangeScene("SELECT");
	}
}

void ResultScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画

	GameClearImg->Draw();

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

void ResultScene::ease()
{

	float start = -800;
	float end = 0;

	float pos;

	pos = (end - start) * ((timeRate * timeRate * timeRate) + 1) + start;
	XMFLOAT2 result;
	result.x = 0;
	result.y = pos;

	black->SetPosition(result);
}
