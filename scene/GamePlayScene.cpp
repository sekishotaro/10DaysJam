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
	item = Model::LoadFromOBJ("block");

	//マップチップ用のCSV読み込み
	//(map, "Resource/scv/なんたら.csv")で追加可能
	Mapchip::CsvToVector(map, "Resources/csv/tutorial.csv");//mapNum=0
	
	//マップチップ用のオブジェクトの初期化
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objItem[y][x] = Object3d::Create();
			objItem[y][x]->SetModel(item);
			objItem[y][x]->SetScale({ 1.0f,1.0f,1.0f });
			objItem[y][x]->SetPosition({ 1000.0f,1000.0f,0.0f });
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

	// 座標更新
	p_pos = Player::GetPos();
	old_p_pos = p_pos;
	// 半径取得
	p_radius_x = 0.5f * Player::GetScale().x;
	p_radius_y = 0.5f * Player::GetScale().y;

	// マップチップ生成
	MapCreate(0);
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objItem[y][x]->Update();
		}
	}

	// マップチップ当たり判定
	if (MapCollide(p_pos, p_radius_x, p_radius_y, 0, old_p_pos))
	{
		Mapchip::ChangeChipNum(width, height, map[0]);
		DebugText::GetInstance()->Print(50, 30 * 3, 2, "ObjectHit");
	}

	// 座標の変更を反映
	camera->SetEye({ map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE + 3.0f, -100.0f });
	DebugText::GetInstance()->Print(50, 30 * 1, 2, "%f", p_pos.x);
	DebugText::GetInstance()->Print(50, 30 * 2, 2, "%f", p_pos.y);
	camera->SetTarget({ map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE, 0 });
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
			objItem[y][x]->Draw();
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

			if (Mapchip::GetChipNum(x, y, map[mapNumber]) == Item)
			{
				//位置と大きさの変更(今は大きさは変更しないで)
				//objItem[y][x]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
				objItem[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 0 });
			}
			else
			{
				objItem[y][x]->SetPosition({ 1000, 1000, 0 });
			}
		}
	}
}

bool GamePlayScene::MapCollide(XMFLOAT3& pos, float radiusX, float radiusY, int mapNumber, const XMFLOAT3 oldPos)
{
	//マップチップ
	//X, Y
	float mapX = 0;
	float mapY = 0;
	//Radius
	float mapRadiusX = 0;
	float mapRadiusY = 0;

	//フラグ
	bool hitFlag = false;

	//判定
	int mapMaxX = static_cast<int>((pos.x + radiusX + LAND_SCALE / 2) / LAND_SCALE);
	int mapMinX = static_cast<int>((pos.x - radiusX + LAND_SCALE / 2) / LAND_SCALE);
	int mapMaxY = -static_cast<int>((pos.y - radiusY + LAND_SCALE / 2) / LAND_SCALE - 1);
	int mapMinY = -static_cast<int>((pos.y + radiusY + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = mapMinY; h <= mapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = mapMinX; w <= mapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}
			if (Mapchip::GetChipNum(w, h, map[mapNumber]) == Item)
			{
				mapX = objItem[h][w]->GetPosition().x;
				mapY = objItem[h][w]->GetPosition().y;
				mapRadiusX = 2.0f * objItem[h][w]->GetScale().x;
				mapRadiusY = 2.0f * objItem[h][w]->GetScale().y;

				if (pos.x <= mapX + mapRadiusX && mapX - mapRadiusX <= pos.x)
				{
					if (mapY + mapRadiusY + radiusY > pos.y && mapY < oldPos.y)
					{
						pos.y = mapY + mapRadiusY + radiusY;
						hitFlag = true;
						height = h;
						width = w;
					}
					else if (mapY - mapRadiusY - radiusY < pos.y && mapY > oldPos.y)
					{
						pos.y = mapY - mapRadiusY - radiusY;
						hitFlag = true;
						height = h;
						width = w;
					}
				}
				if (pos.y <= mapY + mapRadiusY && mapY - mapRadiusY <= pos.y)
				{
					if (mapX + mapRadiusX + radiusX > pos.x && mapX < oldPos.x)
					{
						pos.x = mapX + mapRadiusX + radiusX;
						hitFlag = true;
						height = h;
						width = w;
					}
					else if (mapX - mapRadiusX - radiusX < pos.x && mapX > oldPos.x)
					{
						pos.x = mapX - mapRadiusX - radiusX;
						hitFlag = true;
						height = h;
						width = w;
					}
				}
			}
		}
	}

	return hitFlag;
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
