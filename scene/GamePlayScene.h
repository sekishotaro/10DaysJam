#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include <DirectXMath.h>

#include <memory>

#include "Mapchip.h"
#include "Camera.h"



class GamePlayScene : public BaseScene
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
	bool MapCollide(XMFLOAT3& pos, float radiusX, float radiusY, int mapNumber, const XMFLOAT3 old_pos);
	// 位置取得
	int GetLeftMapChip(XMFLOAT3 position);
	int GetRightMapChip(XMFLOAT3 position);
	int GetUpMapChip(XMFLOAT3 position);

	//マップチップ1つの大きさ
	const float LAND_SCALE = 5.0f;
	//マップチップの番号
	enum MapNumber
	{
		None, Coin
	};
	//mapchipオブジェクト
	std::vector<std::vector<int>> map; //マップチップ
	std::unique_ptr<Object3d> objBlock[map_max_y][map_max_x]; //ステージブロック

	// モデル
	Model* block = nullptr;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite *spriteBG = nullptr;
	Camera *camera = nullptr;

	// プレイヤー変数
	XMFLOAT3 p_pos;
	XMFLOAT3 old_p_pos;
	float p_radius_x;
	float p_radius_y;

	// カメラ変数
	XMFLOAT3 c_pos;
};

