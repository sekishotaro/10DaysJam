#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

#include "Object3d.h"
#include "Input.h"

enum MovePattern
{
	horizontal,		//横
	shield,			//縦
	obliwue,		//斜め
};



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
	void Move(Input* input);

	/// <summary>
	/// 横軸移動
	/// </summary>
	/// <param name="leftPos">左端の値</param>
	/// <param name="rightPos">右端の値</param>
	void StraightMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos);

	/// <summary>
	/// 自機に移動量の加算
	/// </summary>
	/// <param name="move">移動量</param>
	void AddPosMove(const XMFLOAT3& move);

	/// <summary>
	/// 射出
	/// </summary>
	/// <param name="input">入力</param>
	void Injection(Input* input);

public:

	/// <summary>
	/// 初期化
	/// </summary>
	static Barrel* Initialize(const XMFLOAT3& position, const XMFLOAT3& posA, const XMFLOAT3& posB);

	// <summary>
	// 更新
	// </summary>
	void Update(Input* input);


	const XMFLOAT3& GetPos() { return pos; }

	/// <summary>
	/// 位置情報のセット
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const XMFLOAT3& position) { pos = position; }

	//自機との衝突確認
	void CollisionPlayer();

private:
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 posA = { -50.0f, 0.0f, 0.0f };
	XMFLOAT3 posB = { 50.0f, 0.0f, 0.0f };
	XMFLOAT3 move = { 0,0,0 };

	XMFLOAT3 targetPos = { 0,0,0 };

	bool barrelIndividualInFlag = false;

	static bool barrelInFlag;
	static bool moveFlag;
}; 