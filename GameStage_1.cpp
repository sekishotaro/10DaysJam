#include "GameStage_1.h"
#include "SceneManager.h"

GameStage_1::~GameStage_1()
{
	Finalize();
}

void GameStage_1::Initialize()
{
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
}

void GameStage_1::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画

	//sprite->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion 背景スプライト描画




#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}
