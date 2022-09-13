#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

#include "Object3d.h"
#include "Input.h"

class Player
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
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
	/// �ړ��ʂ����@�ɒǉ�
	/// </summary>
	/// <param name="move">�ړ���</param>
	static void AddPosMove(const XMFLOAT3& move);

	/// <summary>
	/// �d��
	/// </summary>
	/// <param name="graflag">�d�͊m�F�p�t���O</param>
	static void Gravity(const bool& graflag);

	/// <summary>
	/// �ˏo���ړ��ꏊ�̎��W
	/// </summary>
	static void InjectionAddMove();

public:

	/// <summary>
	/// ������
	/// </summary>
	static void  Initialize(const XMFLOAT3& posision);

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

	/// <summary>
	/// �ˏo���̈ړ��ʂ̉��Z
	/// </summary>
	/// <param name="move">�ˏo�ڕW</param>
	static void AddInjectionMove(const XMFLOAT3& move);
	
	/// <summary>
	/// �M�̒��ɓ����Ă���
	/// </summary>
	static void BarrelIn();

	/// <summary>
	/// �M�ɓ����Ă��Ȃ�
	/// </summary>
	static void BarrelOut();

	/// <summary>
	/// �d�͂������Ȃ�
	/// </summary>
	static void GravityForcedEnd();

	/// <summary>
	/// �ʒu�����擾
	/// </summary>
	/// <returns>�ʒu���</returns>
	static const XMFLOAT3& GetPos() { return pos; }

	/// <summary>
	/// �ʒu���̃Z�b�g
	/// </summary>
	/// <param name="position">�ʒu</param>
	static void SetPosition(const XMFLOAT3& position) { pos = position; }

	/// <summary>
	/// �傫���̎擾
	/// </summary>
	/// <returns>�傫��</returns>
	static const XMFLOAT3& GetScale() { return scale; }

private:
	static std::unique_ptr<Object3d> objectX;	//�I�u�W�F�N�g
	static Model* model;						//���f��
	static XMFLOAT3 pos;						//�ʒu
	static XMFLOAT3 move;						//�ړ���
	static XMFLOAT3 scale;						//�傫��

	static bool barrelInFlag;					//�M�̒��ɓ����Ă邩�̊m�F�t���O
	static XMFLOAT3 barrelPos;					//�M�̈ʒu�m�F�p
	static XMFLOAT3 injectionMove;				//�ˏo���̈ړ��ꏊ

	static const float gravity;					//�d�͒萔
	static const float graAdjustConstant;		//�d�͒����萔
	static float graValue;						//�d�͑����l
	static bool gravityFlag;					//�d�͂��������Ă邩�m�F�p : true : �������ĂȂ�/ false : �������Ă�
	static float time;							//�ˏo���̈ړ��Ɏg�p
};	

