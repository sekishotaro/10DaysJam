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
	// テクスチャ読み込み
	Sprite::LoadTexture(5, L"Resources/selectScene.png");
	// 背景スプライト生成
	spriteBG = Sprite::Create(5, { 0.0f,0.0f });
}

void SelectScene::Finalize()
{
}

void SelectScene::Update()
{
	// ゲームシーンの毎フレーム処理

	Input* input = Input::GetInstance();
	
	if (input->TriggerKey(DIK_1)&& sceneChange.inendflag)
	{
		//シーン切り替え
		//SceneManager::GetInstance()->ChangeScene("STAGE_1");
		sceneChange.SceneChangeStart("STAGE_1");
	}
	if (input->TriggerKey(DIK_2))
	{
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("STAGE_2");
	}
	if (input->TriggerKey(DIK_3))
	{
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("STAGE_3");
	}
	if (input->TriggerKey(DIK_4))
	{
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("STAGE_4");
	}
	if (input->TriggerKey(DIK_5))
	{
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("STAGE_5");
	}
	if (input->TriggerKey(DIK_6))
	{
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("STAGE_6");
	}
	if (input->TriggerKey(DIK_7))
	{
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("STAGE_7");
	}
	if (input->TriggerKey(DIK_8))
	{
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("STAGE_8");
	}
	DebugText::GetInstance()->Print(50, 20, 3, "select");
	sceneChange.Update();
}

void SelectScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画

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
	sceneChange.Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}
