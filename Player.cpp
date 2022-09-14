#include "Player.h"
#include "MyMath.h"
#include <DebugText.h>

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
float Player::accel = 0.0f;

void Player::Initialize(const XMFLOAT3& position)
{
	//オブジェクト生成
	model = Model::LoadFromOBJ("sphere");

	objectX = Object3d::Create();
	pos = position;
	barrelPos = position;
	injectionMove = position;

	//オブジェクトにモデルをひも付ける
	objectX->SetModel(model);
	objectX->SetPosition(pos);
	objectX->SetScale(scale);
	objectX->Update();
}

void Player::Move(Input *input)
{
	move = { 0.0f,0.0f,0.0f };

	//自機の移動
	if (input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		accel += 0.01f;
		// 移動後の座標を計算
		if (input->PushKey(DIK_RIGHT)) { move.x += 0.2f + accel; }
		else if (input->PushKey(DIK_LEFT)) { move.x -= 0.2f + accel; }
	}
	// 加速度上限
	if (accel >= 0.5f)
	{
		accel = 0.5f;
	}

	//自機の位置に移動量を加算
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
	//移動量のリセット
	XMFLOAT3 gramove = { 0.0f, 0.0f,0.0f };

	//重力確認フラグ確認
	if (graflag == true)
	{
		//重力量のリセット
		graValue = 0.0f;
		return;
	}

	gramove.y -= gravity * graValue / graAdjustConstant;
	graValue += 0.1f;

	//自機の位置に移動量を加算
	AddPosMove(gramove);
}

void Player::InjectionAddMove()
{
	//GravityForcedEnd();
	//もし樽の中に入っているまたは重力がかかっているならかえす
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

	injectionMove.x += move.x + accel;
	XMFLOAT3 APos = MyMath::easeOut(barrelPos, injectionMove, time);
	XMFLOAT3 BPos;
	
	BPos.x = APos.x - pos.x;
	BPos.y = APos.y - pos.y;
	BPos.z = APos.z - pos.z;

	AddPosMove(BPos);
}

void Player::Update(Input* input)
{
	//射出加算
 	InjectionAddMove();
	if (barrelInFlag == true)
	{
		accel = 0.0f;
		//オブジェクトの更新
		objectX->SetPosition(pos);
		objectX->Update();
		return;
	}

	//重力加算
	Gravity(gravityFlag);
	//自機の移動
	if (barrelInFlag == false)
	{
		Move(input);
	}

	//オブジェクトの更新
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