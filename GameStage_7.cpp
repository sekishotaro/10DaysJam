#include "GameStage_7.h"
#include "SceneManager.h"

GameStage_7::~GameStage_7()
{
	Finalize();
}

void GameStage_7::Initialize()
{
	Audio::GetInstance()->LoadWave("BGM.wav");
	Audio::GetInstance()->LoadWave("injection.wav");
	Audio::GetInstance()->PlayWave("BGM.wav", 0.05, true);

}

void GameStage_7::Finalize()
{
}

void GameStage_7::Update()
{
	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		Audio::GetInstance()->SoundStop("BGM.wav");
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void GameStage_7::Draw()
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
