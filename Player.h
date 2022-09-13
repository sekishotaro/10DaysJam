#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

#include "Object3d.h"
#include "Input.h"

class Player
{
private: // エイリアス
	// Microsoft::WRL::を省略
	//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
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
	static void Move(Input* input);

	/// <summary>
	/// 移動量を自機に追加
	/// </summary>
	/// <param name="move">移動量</param>
	static void AddPosMove(const XMFLOAT3& move);

	/// <summary>
	/// 重力
	/// </summary>
	/// <param name="graflag">重力確認用フラグ</param>
	static void Gravity(const bool& graflag);

	/// <summary>
	/// 射出時移動場所の収集
	/// </summary>
	static void InjectionAddMove();

public:

	/// <summary>
	/// 初期化
	/// </summary>
	static void  Initialize(const XMFLOAT3& posision);

	/// <summary>
	/// 更新
	/// </summary>
	static void Update(Input* input);

	/// <summary>
	/// 解放
	/// </summary>
	static void Finalize();

	//描画
	static void Draw();

	/// <summary>
	/// 射出時の移動量の加算
	/// </summary>
	/// <param name="move">射出目標</param>
	static void AddInjectionMove(const XMFLOAT3& move);
	
	/// <summary>
	/// 樽の中に入っている
	/// </summary>
	static void BarrelIn();

	/// <summary>
	/// 樽に入っていない
	/// </summary>
	static void BarrelOut();

	/// <summary>
	/// 重力をかけない
	/// </summary>
	static void GravityForcedEnd();

	/// <summary>
	/// 位置情報を取得
	/// </summary>
	/// <returns>位置情報</returns>
	static const XMFLOAT3& GetPos() { return pos; }

	/// <summary>
	/// 位置情報のセット
	/// </summary>
	/// <param name="position">位置</param>
	static void SetPosition(const XMFLOAT3& position) { pos = position; }

	/// <summary>
	/// 大きさの取得
	/// </summary>
	/// <returns>大きさ</returns>
	static const XMFLOAT3& GetScale() { return scale; }

private:
	static std::unique_ptr<Object3d> objectX;	//オブジェクト
	static Model* model;						//モデル
	static XMFLOAT3 pos;						//位置
	static XMFLOAT3 move;						//移動量
	static XMFLOAT3 scale;						//大きさ

	static bool barrelInFlag;					//樽の中に入ってるかの確認フラグ
	static XMFLOAT3 barrelPos;					//樽の位置確認用
	static XMFLOAT3 injectionMove;				//射出時の移動場所

	static const float gravity;					//重力定数
	static const float graAdjustConstant;		//重力調整定数
	static float graValue;						//重力増加値
	static bool gravityFlag;					//重力がかかってるか確認用 : true : かかってない/ false : かかってる
	static float time;							//射出時の移動に使用
};	

