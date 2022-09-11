#include "GamePlayScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"

#include "PLayer.h"
#include "Barrel.h"

void GamePlayScene::Initialize()
{
	Audio::GetInstance()->LoadWave("futta-dream.wav");
	Audio::GetInstance()->LoadWave("zaza.wav");

	//Audio::GetInstance()->PlayWave("zaza.wav", true);

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// カメラセット
	Object3d::SetCamera(camera);

	// テクスチャ読み込み

	Sprite::LoadTexture(1, L"Resources/background.png");
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// オブジェクト生成
	block = Model::LoadFromOBJ("block");

	//マップチップ用のCSV読み込み
	//(map, "Resource/scv/なんたら.csv")で追加可能
	Mapchip::CsvToVector(map, "Resources/csv/tutorial.csv");//mapNum=0
	
	//マップチップ用のオブジェクトの初期化
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x] = Object3d::Create();
			objBlock[y][x]->SetModel(block);
			objBlock[y][x]->SetScale({ 1.0f,1.0f,1.0f });
			objBlock[y][x]->SetPosition({ 1000.0f,1000.0f,0.0f });
		}
	}

	Player::Initialize();
	Barrel::Initialize();
}

void GamePlayScene::Finalize()
{
	//delete model;
	Player::Finalize();
	Barrel::Finalize();
}

void GamePlayScene::Update()
{
	// ゲームシーンの毎フレーム処理
	
	Input* input = Input::GetInstance();

	// マップチップ生成
	MapCreate(0);
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x]->Update();
		}
	}


	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		// 現在の座標を取得
		XMFLOAT3 position = camera->GetEye();

		DebugText::GetInstance()->Print(50, 30 * 1, 2, "%f", camera->GetEye().x);
		DebugText::GetInstance()->Print(50, 30 * 2, 2, "%f", camera->GetEye().y);
	}

	if (input->TriggerKey(DIK_SPACE))
	{
		p_pos = { map_max_x / 2 * LAND_SCALE,  -map_max_y / 2 * LAND_SCALE, 0 };
	}

	// 座標の変更を反映
	camera->SetEye({ p_pos.x, p_pos.y + 3.0f, p_pos.z - 100.0f });
	camera->SetTarget(p_pos);
	Barrel::CollisionPlayer();
	//アップデート
	camera->Update();
	Barrel::Update(input);
	Player::Update(input);
	
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
	//objectX->Draw();

	//マップチップの描画
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x]->Draw();
		}
	}

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	Player::Draw();
	Barrel::Draw();

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
}

void GamePlayScene::MapCreate(int mapNumber)
{
	for (int y = 0; y < map_max_y; y++) {//(yが12)
		for (int x = 0; x < map_max_x; x++) {//(xが52)

			if (Mapchip::GetChipNum(x, y, map[mapNumber]) == Coin)
			{
				//位置と大きさの変更(今は大きさは変更しないで)
				//objBlock[y][x]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
				objBlock[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 0 });
			}
			else
			{
				objBlock[y][x]->SetPosition({ 1000, 1000, 0 });
			}
		}
	}
}

int GamePlayScene::GetLeftMapChip(XMFLOAT3 position)
{
	int chip = Mapchip::GetChipNum(static_cast<int>((position.x + LAND_SCALE / 2) / LAND_SCALE - 1), -static_cast<int>((position.y - LAND_SCALE / 2) / LAND_SCALE), map[0]);
	return chip;
}

int GamePlayScene::GetRightMapChip(XMFLOAT3 position)
{
	int chip = Mapchip::GetChipNum(static_cast<int>((position.x + LAND_SCALE / 2) / LAND_SCALE + 1), -static_cast<int>((position.y - LAND_SCALE / 2) / LAND_SCALE), map[0]);
	return chip;
}

int GamePlayScene::GetUpMapChip(XMFLOAT3 position)
{
	int chip = Mapchip::GetChipNum(static_cast<int>((position.x + LAND_SCALE / 2) / LAND_SCALE), -static_cast<int>((position.y - LAND_SCALE / 2) / LAND_SCALE + 1), map[0]);
	return chip;
}
