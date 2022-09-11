#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

class MyMath
{
private: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	static XMFLOAT3 easeOut(const XMFLOAT3& start, const XMFLOAT3& end, const float& time);
};

