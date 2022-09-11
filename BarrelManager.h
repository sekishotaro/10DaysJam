#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

#include "Input.h"

class BarrelManager
{
private: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	static void  Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	static void Update(Input* input);

	/// <summary>
	/// 解放
	/// </summary>
	static void Finalize();

	/// <summary>
	/// 描画
	/// </summary>
	static void Draw();

private:

	static bool barrelInFlag;
	static bool moveFlag;
};

