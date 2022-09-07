#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

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

public:

	static void  Initialize();

	static void Update();

	static void Draw();

private:

	static XMFLOAT3 pos;
};

