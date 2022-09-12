#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

#include "Object3d.h"
#include "Input.h"

class Barrel
{
private: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


private:

	/// <summary>
	/// �ړ�
	/// </summary>
	/// <param name="input">����</param>
	static void Move(Input* input);

	/// <summary>
	/// �����ړ�
	/// </summary>
	/// <param name="leftPos">���[�̒l</param>
	/// <param name="rightPos">�E�[�̒l</param>
	static void HorizontalMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos);

	/// <summary>
	/// ���@�Ɉړ��ʂ̉��Z
	/// </summary>
	/// <param name="move">�ړ���</param>
	static void AddPosMove(const XMFLOAT3& move);

	/// <summary>
	/// �ˏo
	/// </summary>
	/// <param name="input">����</param>
	static void Injection(Input* input);

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

	//�`��
	static void Draw();


	const XMFLOAT3& GetPos() { return pos; }

	//���@�Ƃ̏Փˊm�F
	static void CollisionPlayer();

private:
	static std::unique_ptr<Object3d> objectX;
	static Model* model;
	static XMFLOAT3 pos;
	static XMFLOAT3 move;
	static XMFLOAT3 scale;

	static bool barrelInFlag;
	static bool moveFlag;
}; 