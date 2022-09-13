#include "Player.h"
#include "MyMath.h"

std::unique_ptr<Object3d> Player::objectX;
Model* Player::model = nullptr;

Player::XMFLOAT3 Player::pos = { 0.0f ,0.0f, 0.0f };
Player::XMFLOAT3 Player::move = { 0.0f ,0.0f, 0.0f };
Player::XMFLOAT3 Player::scale = { 2.0f ,2.0f, 2.0f };
Player::XMFLOAT3 Player::barrelPos = { 0.0f, 0.0f, 0.0f };
Player::XMFLOAT3 Player::injectionMove = { 0.0f, 0.0f, 0.0f };
bool Player::barrelInFlag = false;

const float Player::gravity = 9.8f;
const float Player::graAdjustConstant = 20.0f;
float Player::graValue = 0.0f;
bool Player::gravityFlag = false;
float Player::time = 0.0f;

void Player::Initialize(const XMFLOAT3& position)
{
	//�I�u�W�F�N�g����
	model = Model::LoadFromOBJ("sphere");

	objectX = Object3d::Create();

	//�I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	objectX->SetModel(model);
	objectX->SetPosition(position);
	pos = position;
	objectX->SetScale(scale);
}

void Player::Move(Input *input)
{
	move = { 0.0f,0.0f,0.0f };

	//���@�̈ړ�
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// ���݂̍��W���擾

		// �ړ���̍��W���v�Z
		//if (input->PushKey(DIK_UP)) { move.y += 1.0f; }
		//else if (input->PushKey(DIK_DOWN)) { move.y -= 1.0f; }
		if (input->PushKey(DIK_RIGHT)) { move.x += 0.2f; }
		else if (input->PushKey(DIK_LEFT)) { move.x -= 0.2f; }
	}

	//���@�̈ʒu�Ɉړ��ʂ����Z
	AddPosMove(move);
}

void Player::AddPosMove(const XMFLOAT3& move)
{
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;
}

void Player::Gravity(const bool& graflag)
{
	//�ړ��ʂ̃��Z�b�g
	XMFLOAT3 gramove = { 0.0f, 0.0f,0.0f };

	//�d�͊m�F�t���O�m�F
	if (graflag == true)
	{
		//�d�͗ʂ̃��Z�b�g
		graValue = 0.0f;
		return;
	}

	gramove.y -= gravity * graValue / graAdjustConstant;
	graValue += 0.1f;

	//���@�̈ʒu�Ɉړ��ʂ����Z
	AddPosMove(gramove);
}

void Player::InjectionAddMove()
{
	//�����M�̒��ɓ����Ă���܂��͏d�͂��������Ă���Ȃ炩����
	if (barrelInFlag == true || gravityFlag == false)
	{
		time = 0.0f;
		return;
	}


	if (time < 1.0f)
	{
		time += 0.05f;
	}
	else
	{
		gravityFlag = false;
		return;
	}
	
	XMFLOAT3 APos = MyMath::easeOut(barrelPos, injectionMove, time);
	XMFLOAT3 BPos;
	
	BPos.x = APos.x - pos.x;
	BPos.y = APos.y - pos.y;
	BPos.z = APos.z - pos.z;

	AddPosMove(BPos);
}

void Player::Update(Input* input)
{
	
	//�ˏo���Z
	InjectionAddMove();
	if (barrelInFlag == true)
	{
		//�I�u�W�F�N�g�̍X�V
		objectX->SetPosition(pos);
		objectX->Update();
		return;
	}

	//�d�͉��Z
	Gravity(gravityFlag);
	//���@�̈ړ�
	Move(input);

	//�I�u�W�F�N�g�̍X�V
	objectX->SetPosition(pos);
	objectX->Update();
}

void Player::Finalize()
{
	delete model;
}

void Player::Draw()
{
	objectX->Draw();
}

void Player::AddInjectionMove(const XMFLOAT3& move)
{
	injectionMove = move;
	barrelPos = pos;
}

void Player::BarrelIn()
{
	barrelInFlag = true;
}

void Player::BarrelOut()
{
	barrelInFlag = false;
}

void Player::GravityForcedEnd()
{
	gravityFlag = true;
}