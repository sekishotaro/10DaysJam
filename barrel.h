#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

#include "Object3d.h"
#include "Input.h"

#include <vector>

using namespace std;

enum MovePattern
{
	horizontal,		//��
	shield,			//�c
	obliwue,		//�΂�
};

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
	void Move(Input* input);

	/// <summary>
	/// �����ړ�
	/// </summary>
	/// <param name="leftPos">���[�̒l</param>
	/// <param name="rightPos">�E�[�̒l</param>
	void StraightMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos);

	/// <summary>
	/// ���@�Ɉړ��ʂ̉��Z
	/// </summary>
	/// <param name="move">�ړ���</param>
	void AddPosMove(const XMFLOAT3& move);

	/// <summary>
	/// �ˏo
	/// </summary>
	/// <param name="input">����</param>
	void Injection(Input* input);

public:

	/// <summary>
	/// ������
	/// </summary>
	static Barrel* Initialize(const XMFLOAT3& position, const XMFLOAT3& posA, const XMFLOAT3& posB, const XMFLOAT3& rot, const float& injectionDis);

	// <summary>
	// �X�V
	// </summary>
	void Update(Input* input);


	const XMFLOAT3& GetPos() { return pos; }

	const XMFLOAT3& GetRot() { return rot; }

	/// <summary>
	/// �ʒu���̃Z�b�g
	/// </summary>
	/// <param name="position">�ʒu</param>
	void SetPosition(const XMFLOAT3& position) { pos = position; }

	//���@�Ƃ̏Փˊm�F
	void CollisionPlayer();

	void rotationMove(vector<int> rota);

private:
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 posA = { -50.0f, 0.0f, 0.0f };
	XMFLOAT3 posB = { 50.0f, 0.0f, 0.0f };
	XMFLOAT3 move = { 0,0,0 };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 targetPos = { 0,0,0 };

	float Num = 0;
	float addNum = 1;

	float time = 0.0f;

	bool barrelIndividualInFlag = false;
	float injectionDis = 30.0f;

	static bool barrelInFlag;
	static bool moveFlag;
}; 