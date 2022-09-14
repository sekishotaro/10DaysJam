#include "SelectScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "MyMath.h"
#include "Mapchip.h"
SelectScene::~SelectScene()
{
	Finalize();
}

void SelectScene::Initialize()
{
	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	// カメラセット
	Object3d::SetCamera(camera);
	camera->SetEye({ 0.0f, 0.0f, -60.0f });
	// テクスチャ読み込み
	Sprite::LoadTexture(5, L"Resources/selectScene.png");
	// 背景スプライト生成
	spriteBG = Sprite::Create(5, { 0.0f,0.0f });

	// テクスチャ読み込み
	Sprite::LoadTexture(10, L"Resources/AD_UI.png");
	// スプライト生成
	AD_UI = Sprite::Create(10, { 460.0f,500.0f });

	// テクスチャ読み込み
	Sprite::LoadTexture(11, L"Resources/SPACE_UI.png");
	// スプライト生成
	SPACE_UI = Sprite::Create(11, { 830.0f,560.0f });



	scale = { 8,8,8 };
	stage1_pos = { 0,0,0 };

	{//stage1
		stage1Model = Model::LoadFromOBJ("stage1");
		stage1obj = Object3d::Create();

		//オブジェクトにモデルをひも付ける
		stage1obj->SetModel(stage1Model);
		stage1obj->SetScale(scale);
		stage1obj->SetPosition({ 0,0,0 });
	}

	{//stage2
		stage2Model = Model::LoadFromOBJ("stage2");
		stage2obj = Object3d::Create();

		//オブジェクトにモデルをひも付ける
		stage2obj->SetModel(stage2Model);
		stage2obj->SetScale(scale);
		stage1obj->SetPosition({ 0,0,0 });
	}

	{//stage3
		stage3Model = Model::LoadFromOBJ("stage3");
		stage3obj = Object3d::Create();

		//オブジェクトにモデルをひも付ける
		stage3obj->SetModel(stage3Model);
		stage3obj->SetScale(scale);
	}

	{//stage4
		stage4Model = Model::LoadFromOBJ("stage4");
		stage4obj = Object3d::Create();

		//オブジェクトにモデルをひも付ける
		stage4obj->SetModel(stage4Model);
		stage4obj->SetScale(scale);
	}

	{//stage5
		stage5Model = Model::LoadFromOBJ("stage5");
		stage5obj = Object3d::Create();

		//オブジェクトにモデルをひも付ける
		stage5obj->SetModel(stage5Model);
		stage5obj->SetScale(scale);
	}

	{//stage6
		stage6Model = Model::LoadFromOBJ("stage6");
		stage6obj = Object3d::Create();

		//オブジェクトにモデルをひも付ける
		stage6obj->SetModel(stage6Model);
		stage6obj->SetScale(scale);
	}

	{//stage7
		stage7Model = Model::LoadFromOBJ("stage7");
		stage7obj = Object3d::Create();

		//オブジェクトにモデルをひも付ける
		stage7obj->SetModel(stage7Model);
		stage7obj->SetScale(scale);
	}

	{//stage8
		stage8Model = Model::LoadFromOBJ("stage8");
		stage8obj = Object3d::Create();

		//オブジェクトにモデルをひも付ける
		stage8obj->SetModel(stage8Model);
		stage8obj->SetScale(scale);
	}
	stage1_pos = { 0,0,0 };
	stage2_pos = { stage1_pos.x - 40,stage1_pos.y,stage1_pos.z };
	stage3_pos = { stage2_pos.x - 40,stage2_pos.y,stage2_pos.z };
	stage4_pos = { stage3_pos.x - 40,stage3_pos.y,stage3_pos.z };
	stage5_pos = { stage4_pos.x - 40,stage4_pos.y,stage4_pos.z };
	stage6_pos = { stage5_pos.x - 40,stage5_pos.y,stage5_pos.z };
	stage7_pos = { stage6_pos.x - 40,stage6_pos.y,stage6_pos.z };
	stage8_pos = { stage7_pos.x - 40,stage7_pos.y,stage7_pos.z };

	stage1obj->SetPosition(stage1_pos);
	stage2obj->SetPosition(stage2_pos);
	stage3obj->SetPosition(stage3_pos);
	stage4obj->SetPosition(stage4_pos);

	stage5obj->SetPosition(stage5_pos);
	stage6obj->SetPosition(stage6_pos);
	stage7obj->SetPosition(stage7_pos);
	stage8obj->SetPosition(stage8_pos);
}

void SelectScene::Finalize()
{

}

void SelectScene::Update()
{

	camera->SetEye({ 0,0, +50.0f });


	Input* input = Input::GetInstance();
	if (input->TriggerKey(DIK_A) && count > 0 && !Lmove
		&& !Rmove)
	{
		count -= 1;
		Lmove = true;
		savepos = stage1obj->GetPosition();

	}
	else if (input->TriggerKey(DIK_D) && count < 7 && !Lmove
		&& !Rmove)
	{
		count += 1;
		Rmove = true;
		savepos = stage1obj->GetPosition();
	}
	{
		if (count == 0 && input->TriggerKey(DIK_SPACE))
		{
			//シーン切り替え 1
			//SceneManager::GetInstance()->ChangeScene("STAGE_1");
			sceneChange.SceneChangeStart("STAGE_1");
			Savepos();
		}
		else if (count == 1 && input->TriggerKey(DIK_SPACE))
		{
			//シーン切り替え 2
			//SceneManager::GetInstance()->ChangeScene("STAGE_2");
			sceneChange.SceneChangeStart("STAGE_2");
			Savepos();
		}
		else if (count == 2 && input->TriggerKey(DIK_SPACE))
		{
			//シーン切り替え 3
			//SceneManager::GetInstance()->ChangeScene("STAGE_3");
			sceneChange.SceneChangeStart("STAGE_3");
			Savepos();
		}
		else if (count == 3 && input->TriggerKey(DIK_SPACE))
		{
			//シーン切り替え 4
			//SceneManager::GetInstance()->ChangeScene("STAGE_4");
			sceneChange.SceneChangeStart("STAGE_4");
			Savepos();
		}
		else if (count == 4 && input->TriggerKey(DIK_SPACE))
		{
			//シーン切り替え 5
			//SceneManager::GetInstance()->ChangeScene("STAGE_5");
			sceneChange.SceneChangeStart("STAGE_5");
			Savepos();
		}
		else if (count == 5 && input->TriggerKey(DIK_SPACE))
		{
			//シーン切り替え 6
			//SceneManager::GetInstance()->ChangeScene("STAGE_6");
			sceneChange.SceneChangeStart("STAGE_6");
			Savepos();
		}
		else if (count == 6 && input->TriggerKey(DIK_SPACE))
		{
			//シーン切り替え 7
			//SceneManager::GetInstance()->ChangeScene("STAGE_7");
			sceneChange.SceneChangeStart("STAGE_7");
			Savepos();
		}
		else if (count == 7 && input->TriggerKey(DIK_SPACE))
		{
			//シーン切り替え 8
			//SceneManager::GetInstance()->ChangeScene("STAGE_8");
			sceneChange.SceneChangeStart("STAGE_8");
			Savepos();
		}
	}

	DebugText::GetInstance()->Print(50, 20, 3, "%f", stage1_pos.x);
	DebugText::GetInstance()->Print(50, 50, 3, "%f", stage1_pos.y);
	DebugText::GetInstance()->Print(50, 80, 3, "%f", stage1_pos.z);
	if (Rmove)
	{
		nowTime += 0.03;
		timeRate = min(nowTime / endTime, 1);

		float start = savepos.x;
		float end = savepos.x + 20;
		float pos;
		pos = (end - start) * ((timeRate * timeRate * timeRate) + 1) + start;
		stage1_pos.x = pos;
		if (nowTime >= endTime)
		{
			nowTime = 0;
			Rmove = false;
		}
	}

	if (Lmove)
	{
		nowTime += 0.03;
		timeRate = min(nowTime / endTime, 1);

		float start = savepos.x;
		float end = savepos.x - 20;
		float pos;
		pos = (end - start) * ((timeRate * timeRate * timeRate) + 1) + start;
		stage1_pos.x = pos;
		if (nowTime >= endTime)
		{
			nowTime = 0;
			Lmove = false;
		}
	}
	{
		camera->Update();
		sceneChange.Update();
		stage1obj->Update();
		stage2obj->Update();
		stage3obj->Update();
		stage4obj->Update();
		stage5obj->Update();
		stage6obj->Update();
		stage7obj->Update();
		stage8obj->Update();
	}
	{
		stage2_pos = { stage1_pos.x - 40,stage1_pos.y,stage1_pos.z };
		stage3_pos = { stage2_pos.x - 40,stage2_pos.y,stage2_pos.z };
		stage4_pos = { stage3_pos.x - 40,stage3_pos.y,stage3_pos.z };
		stage5_pos = { stage4_pos.x - 40,stage4_pos.y,stage4_pos.z };
		stage6_pos = { stage5_pos.x - 40,stage5_pos.y,stage5_pos.z };
		stage7_pos = { stage6_pos.x - 40,stage6_pos.y,stage6_pos.z };
		stage8_pos = { stage7_pos.x - 40,stage7_pos.y,stage7_pos.z };

		stage1obj->SetPosition(stage1_pos);
		stage2obj->SetPosition(stage2_pos);
		stage3obj->SetPosition(stage3_pos);
		stage4obj->SetPosition(stage4_pos);

		stage5obj->SetPosition(stage5_pos);
		stage6obj->SetPosition(stage6_pos);
		stage7obj->SetPosition(stage7_pos);
		stage8obj->SetPosition(stage8_pos);
	}
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

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);
	// 3Dオブクジェクトの描画

	stage1obj->Draw();
	stage2obj->Draw();

	stage3obj->Draw();
	stage4obj->Draw();

	stage5obj->Draw();
	stage6obj->Draw();

	stage7obj->Draw();
	stage8obj->Draw();
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	AD_UI->Draw();
	SPACE_UI->Draw();
	// デバッグテキストの描画
	//DebugText::GetInstance()->DrawAll(cmdList);
	sceneChange.Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion 前景スプライト描画
}

void SelectScene::Savepos()
{


	stage1obj->SetPosition({ 0,0,0 });
	nowTime = 0;
	endTime = 1;
	timeRate = 0;
	Rmove = false;
	Lmove = false;
}
