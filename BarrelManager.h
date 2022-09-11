#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

#include "Input.h"

class BarrelManager
{
private: // �G�C���A�X
// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	/// <summary>
	/// ������
	/// </summary>
	static void  Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	static void Update(Input* input);

	/// <summary>
	/// ���
	/// </summary>
	static void Finalize();

	/// <summary>
	/// �`��
	/// </summary>
	static void Draw();

private:

	static bool barrelInFlag;
	static bool moveFlag;
};

