#include "Barrel.h"
#include "Player.h"
#include "Collision.h"

std::unique_ptr<Object3d> Barrel::objectX;
Model* Barrel::model = nullptr;

Barrel::XMFLOAT3 Barrel::pos = { 0.0f, -65.0f, 0.0f };
Barrel::XMFLOAT3 Barrel::move = { 1.0f ,0.0f, 0.0f };
Barrel::XMFLOAT3 Barrel::scale = { 1.0f, 1.0f, 1.0f };

bool Barrel::barrelInFlag = false;
bool Barrel::moveFlag = true;

void Barrel::Move(Input* input)
{
	XMFLOAT3 leftPos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 RightPos = { 125.0f, 0.0f, 0.0f };
	HorizontalMove(leftPos, RightPos);
}

void Barrel::HorizontalMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos)
{
	//樽の中にいなければ動かない
	if (barrelInFlag == false)
	{
		return;
	}

	if (rightPos.x < pos.x && moveFlag == true)
	{
		move.x = -1.0f;
		moveFlag = false;
	}
	if (pos.x < leftPos.x && moveFlag == false)
	{
		move.x = 1.0f;
		moveFlag = true;
	}
	

	AddPosMove(move);
}

void Barrel::AddPosMove(const XMFLOAT3& move)
{
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;
}

void Barrel::Injection(Input* input)
{
	//樽の中に入っていないときは返す
	if (barrelInFlag == false)
	{
		return;
	}

	if (input->PushKey(DIK_SPACE))
	{
		//どれだけ飛ばすか
		XMFLOAT3 InjectionMove = { pos.x, 20.0f, pos.z };
		Player::AddInjectionMove(InjectionMove);
		barrelInFlag = false;
		Player::BarrelOut();
	}
}

void Barrel::CollisionPlayer()
{
	if (barrelInFlag == true)
	{
		return;
	}
	
	SphereF sphere1, sphere2;
	sphere1.center = pos;
	sphere1.radius = 3;

	sphere2.center = Player::GetPos();
	sphere2.radius = 2;

	if (Collision::CheckSphereSphere(sphere1, sphere2) == true)
	{
		barrelInFlag = true;
		Player::GravityForcedEnd();
		Player::BarrelIn();
	}
}

void Barrel::Initialize()
{
	//オブジェクト生成
	model = Model::LoadFromOBJ("block");

	objectX = Object3d::Create();

	//オブジェクトにモデルをひも付ける
	objectX->SetModel(model);
	objectX->SetScale(scale);
}

void Barrel::Update(Input* input)
{
	Move(input);
	if (barrelInFlag == true)
	{
		Player::SetPosition(pos);
	}


	objectX->SetPosition(pos);
	objectX->Update();

	Injection(input);
}

void Barrel::Finalize()
{
	delete model;
}

void Barrel::Draw()
{
	objectX->Draw();
}
