#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

#include "Object3d.h"
#include "Input.h"

class Barrel
{
private: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


private:

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="input">入力</param>
	//static void Move(Input* input);

	/// <summary>
	/// 横軸移動
	/// </summary>
	/// <param name="leftPos">左端の値</param>
	/// <param name="rightPos">右端の値</param>
	//static void HorizontalMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos);

	/// <summary>
	/// 自機に移動量の加算
	/// </summary>
	/// <param name="move">移動量</param>
	//static void AddPosMove(const XMFLOAT3& move);

	/// <summary>
	/// 射出
	/// </summary>
	/// <param name="input">入力</param>
	//static void Injection(Input* input);

public:

	//Barrel();

	//~Barrel();


	/// <summary>
	/// 初期化
	/// </summary>
	static Barrel *Initialize(const XMFLOAT3& position);

	/// <summary>
	/// 更新
	/// </summary>
	//static void Update(Input* input);

	/// <summary>
	/// 解放
	/// </summary>
	//static void Finalize();

	//描画
	//static void Draw();


	const XMFLOAT3& GetPos() { return pos; }

	/// <summary>
	/// 位置情報のセット
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const XMFLOAT3& position) { pos = position; }

	//自機との衝突確認
	//static void CollisionPlayer();

private:
	XMFLOAT3 pos;
	static XMFLOAT3 move;

	static bool barrelInFlag;
	static bool moveFlag;
}; 