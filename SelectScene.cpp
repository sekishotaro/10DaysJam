#include "SelectScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"
SelectScene::~SelectScene()
{
	Finalize();
}

void SelectScene::Initialize()
{
}

void SelectScene::Finalize()
{
}

void SelectScene::Update()
{
	// ゲームシーンの毎フレーム処理

	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("STAGE_1");
	}
	DebugText::GetInstance()->Print(50, 20, 3, "select");
}

void SelectScene::Draw()
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

	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}
