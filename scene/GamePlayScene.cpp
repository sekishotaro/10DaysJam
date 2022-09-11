#include "GamePlayScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"

#include "PLayer.h"

void GamePlayScene::Initialize()
{
	Audio::GetInstance()->LoadWave("futta-dream.wav");
	Audio::GetInstance()->LoadWave("zaza.wav");

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// カメラセット
	Object3d::SetCamera(camera);

	// テクスチャ読み込み

	Sprite::LoadTexture(1, L"Resources/background.png");
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	//オブジェクト生成
	BarrelModel = Model::LoadFromOBJ("block");

	barrelObject1 = Object3d::Create();
	barrelObject2 = Object3d::Create();

	//オブジェクトにモデルをひも付ける
	barrelObject1->SetModel(BarrelModel);
	barrelObject1->SetScale({ 0.5f, 0.5f, 0.5f });

	barrelObject2->SetModel(BarrelModel);
	barrelObject2->SetScale({ 0.5f, 0.5f, 0.5f });

	Player::Initialize();


	XMFLOAT3 posA = { -50.0f, -15.0f, 0.0f };
	XMFLOAT3 posB = {  50.0f, -15.0f, 0.0f };

	XMFLOAT3 posC = { -50.0f, -25.0f, 0.0f };
	XMFLOAT3 posD = {  50.0f, -25.0f, 0.0f };

	barrel1 = Barrel::Initialize(XMFLOAT3(0.0f, -15.0f, 0.0f), posA, posB);
	
	barrel2 = Barrel::Initialize(XMFLOAT3(0.0f, -25.0f, 0.0f), posC, posD);

	barrelObject1->SetPosition(barrel1->GetPos());
	barrelObject2->SetPosition(barrel2->GetPos());
}

void GamePlayScene::Finalize()
{
	delete BarrelModel;
	Player::Finalize();
}

void GamePlayScene::Update()
{
	// ゲームシーンの毎フレーム処理
	
	Input *input = Input::GetInstance();

	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		// 現在の座標を取得
		XMFLOAT3 position = camera->GetEye();

		// 移動後の座標を計算
		if (input->PushKey(DIK_W)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_S)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_D)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_A)) { position.x -= 1.0f; }

		// 座標の変更を反映
		camera->SetEye(position);
	}

	DebugText::GetInstance()->Print(50, 30 * 1, 2, "%f", barrel1->GetPos().y);
	DebugText::GetInstance()->Print(50, 30 * 2, 2, "%f", barrel2->GetPos().y);

	barrel1->CollisionPlayer();
	barrel2->CollisionPlayer();
	//アップデート
	camera->Update();
	barrel1->Update(input);
	barrel2->Update(input);
	Player::Update(input);

	barrelObject1->SetPosition(barrel1->GetPos());
	barrelObject1->Update();

	barrelObject2->SetPosition(barrel2->GetPos());
	barrelObject2->Update();
	
}

void GamePlayScene::Draw()
{
	// ゲームシーンの描画

// コマンドリストの取得
	ID3D12GraphicsCommandList *cmdList = DirectXCommon::GetInstance()->GetCmdList();

	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	DirectXCommon::GetInstance()->ClearDepthBuffer();

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	barrelObject1->Draw();
	barrelObject2->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	Player::Draw();

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
}
