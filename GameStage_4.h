#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include <DirectXMath.h>
#include "Camera.h"
#include "Barrel.h"
#include "Mapchip.h"
#include "SceneChange.h"

class GameStage_4 : public BaseScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// アップデート
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	// マップチップ生成
	void MapCreate(int mapNumber);
	// マップチップ当たり判定
	bool MapCollide(XMFLOAT3& pos, float radiusX, float radiusY, int mapNumber, const XMFLOAT3 oldPos);

	//マップチップ1つの大きさ
	const float LAND_SCALE = 5.0f;
	//マップチップの番号
	enum MapNumber
	{
		None, Item
	};
	//mapchipオブジェクト
	std::vector<std::vector<int>> map; //マップチップ
	std::unique_ptr<Object3d> objItem[map_max_y][map_max_x]; // ステージブロック
	// モデル
	Model* item = nullptr;
	// 管理フラグ
	bool hitFlag = false;
	// マップ番号
	int height;
	int width;
	// アイテム個数管理
	int itemCount;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;
	Camera* camera = nullptr;

	// バレル
	std::vector<int> rotation;
	std::unique_ptr<Object3d> barrelObject1;
	std::unique_ptr<Object3d> barrelObject2;
	std::unique_ptr<Object3d> barrelObject3;
	std::unique_ptr<Object3d> barrelObject4;
	std::unique_ptr<Object3d> barrelObject5;
	Model* BarrelModel;

	// プレイヤー変数
	XMFLOAT3 p_pos;
	XMFLOAT3 old_p_pos;
	float p_radius_x;
	float p_radius_y;

	Barrel* barrel1;
	Barrel* barrel2;
	Barrel* barrel3;
	Barrel* barrel4;
	Barrel* barrel5;

	Sprite* itemui = nullptr;
	Sprite* timerui = nullptr;

	int timer = 0;
	int time = 60;
	SceneChange sceneChange;
};

