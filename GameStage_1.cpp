#include "GameStage_1.h"
#include "SceneManager.h"
#include "Audio.h"
#include "DebugText.h"
#include "Fornt.h"
#include "DirectXCommon.h"
#include "PLayer.h"
#include "ResultScene.h"

void GameStage_1::Initialize()
{
	Audio::GetInstance()->LoadWave("BGM.wav");
	Audio::GetInstance()->LoadWave("injection.wav");

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// カメラセット
	Object3d::SetCamera(camera);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/BG.png");
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// テクスチャ読み込み
	Sprite::LoadTexture(6, L"Resources/item_ui.png");
	//スプライト生成
	itemui = Sprite::Create(6, { 0.0f,0.0f });

	// テクスチャ読み込み
	Sprite::LoadTexture(7, L"Resources/timer.png");
	//スプライト生成
	timerui = Sprite::Create(7, { 980.0f,5.0f });
	//オブジェクト生成
	BarrelModel = Model::LoadFromOBJ("Cannon");
	barrelObject1 = Object3d::Create();

	//オブジェクトにモデルをひも付ける
	barrelObject1->SetModel(BarrelModel);
	barrelObject1->SetScale({ 0.5f, 0.5f, 0.5f });

	// オブジェクト生成
	item = Model::LoadFromOBJ("item");

	//マップチップ用のCSV読み込み
	//(map, "Resource/scv/なんたら.csv")で追加可能
	Mapchip::CsvToVector(map, "Resources/csv/stage1.csv");//mapNum=0

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
	// マップチップ生成
	MapCreate(0);

	// プレイヤー初期座標
	p_pos = { map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE - 25.0f, 0 };
	// プレイヤー初期化
	Player::Initialize(p_pos);

	// バレルの中間位置
	float b_posX = map_max_x / 2 * LAND_SCALE;
	float b_posY = -map_max_y / 2 * LAND_SCALE;

	// バレル移動範囲
	XMFLOAT3 pos_range1 = { b_posX - 25.0f, -65.0f, 0.0f };
	XMFLOAT3 pos_range2 = { b_posX + 25.0f, -65.0f, 0.0f };

	// バレルの向き
	XMFLOAT3 rot = { 0.0f ,180.0f ,0.0f };

	// バレル初期化
	barrel1 = Barrel::Initialize(XMFLOAT3(b_posX, -65.0f, 0.0f), pos_range1, pos_range2, rot, 70.0f);

	barrelObject1->SetPosition(barrel1->GetPos());
	barrelObject1->SetScale(XMFLOAT3(4.0f, 4.0f, 4.0f));
	barrelObject1->SetRotation(rot);
	Audio::GetInstance()->PlayWave("BGM.wav", 0.05, true);
	time = 60;
}

void GameStage_1::Finalize()
{
	delete BarrelModel;
	Player::Finalize();
}

void GameStage_1::Update()
{
	// ゲームシーンの毎フレーム処理
	Input* input = Input::GetInstance();

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

	// 座標更新
	p_pos = Player::GetPos();
	old_p_pos = p_pos;
	// 半径取得
	p_radius_x = 0.5f * Player::GetScale().x;
	p_radius_y = 0.5f * Player::GetScale().y;

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
		itemCount--;
	}

	if (itemCount <= 0)
	{
		//シーン切り替え
		Audio::GetInstance()->SoundStop("BGM.wav");
		SceneManager::GetInstance()->ChangeScene("RESULT");

	}

	// 座標の変更を反映
	camera->SetEye({ map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE + 3.0f, -100.0f });
	camera->SetTarget({ map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE, 0 });

	barrel1->CollisionPlayer();

	//アップデート
	camera->Update();
	barrel1->Update(input);
	Player::Update(input);

	barrelObject1->SetPosition(barrel1->GetPos());
	barrelObject1->Update();
	//タイマー
	timer++;
	if (timer >= 60)
	{
		time -= 1;
		timer = 0;
	}
	//ゲームオーバー処理
	if (time <= 0 || p_pos.y <= -100)
	{
		bool gameover = true;
		Player::BarrelOut();
		p_pos = { map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE - 25.0f, 0 };
		Audio::GetInstance()->SoundStop("BGM.wav");
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");

	}
	Fornt::GetInstance()->Print(60, 35, 1.5, "%d", itemCount);
	Fornt::GetInstance()->Print(1068.0f, 50.0f, 2, "%d", time);
	sceneChange.Update();
}

void GameStage_1::Draw()
{
	// ゲームシーンの描画

// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();

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
	//マップチップの描画
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			if (Mapchip::GetChipNum(x, y, map[0]) == Item)
			{
				objItem[y][x]->Draw();
			}
		}
	}
	Player::Draw();

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	itemui->Draw();
	timerui->Draw();
	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(cmdList);
	Fornt::GetInstance()->DrawAll(cmdList);
	sceneChange.Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
}

void GameStage_1::MapCreate(int mapNumber)
{
	for (int y = 0; y < map_max_y; y++) {//(yが12)
		for (int x = 0; x < map_max_x; x++) {//(xが52)

			if (Mapchip::GetChipNum(x, y, map[mapNumber]) == Item)
			{
				//位置と大きさの変更(今は大きさは変更しないで)
				//objItem[y][x]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
				objItem[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 0 });
				itemCount++;
			}
			else
			{
				objItem[y][x]->SetPosition({ 1000, 1000, 0 });
			}
		}
	}
}

bool GameStage_1::MapCollide(XMFLOAT3& pos, float radiusX, float radiusY, int mapNumber, const XMFLOAT3 oldPos)
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
				mapRadiusX = 2.5f * objItem[h][w]->GetScale().x;
				mapRadiusY = 2.5f * objItem[h][w]->GetScale().y;

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
