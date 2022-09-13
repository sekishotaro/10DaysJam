#include "GameStage_1.h"
#include "SceneManager.h"
#include "DebugText.h"
#include "Input.h"
GameStage_1::~GameStage_1()
{
	Finalize();
}

void GameStage_1::Initialize()
{
	Sprite::LoadTexture(1, L"Resources/BG.png");
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
}

void GameStage_1::Finalize()
{
}

void GameStage_1::Update()
{
	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
	DebugText::GetInstance()->Print(50, 20, 3, "stage1");
}

void GameStage_1::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画

	//sprite->Draw();
	spriteBG->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion 背景スプライト描画




#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}
