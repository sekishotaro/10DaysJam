#include "Barrel.h"
#include "Player.h"
#include "Collision.h"

<<<<<<< HEAD
=======
std::unique_ptr<Object3d> Barrel::objectX;
Model* Barrel::model = nullptr;

Barrel::XMFLOAT3 Barrel::pos = { 0.0f, -65.0f, 0.0f };
Barrel::XMFLOAT3 Barrel::move = { 1.0f ,0.0f, 0.0f };
Barrel::XMFLOAT3 Barrel::scale = { 1.0f, 1.0f, 1.0f };

>>>>>>> kuri
bool Barrel::barrelInFlag = false;
bool Barrel::moveFlag = true;

void Barrel::Move(Input* input)
{
<<<<<<< HEAD
	StraightMove(posA, posB);
=======
	XMFLOAT3 leftPos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 RightPos = { 125.0f, 0.0f, 0.0f };
	HorizontalMove(leftPos, RightPos);
>>>>>>> kuri
}

void Barrel::StraightMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos)
{
	//樽の中にいなければ動かない
	if (barrelInFlag == false)
	{
		return;
	}

	if (pos.x == rightPos.x)
	{
		targetPos = leftPos;
	}
	else if (pos.x == leftPos.x)
	{
		targetPos = rightPos;
	}

	XMFLOAT3 dis = { targetPos.x - pos.x,  targetPos.y - pos.y , targetPos.z - pos.z };

	float sb = sqrt(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);

	move.x = (dis.x / sb) / 2.0f;
	move.y = (dis.y / sb) / 2.0f;
	move.z = (dis.z / sb) / 2.0f;

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

	if (input->PushKey(DIK_SPACE) && barrelIndividualInFlag == true)
	{
		//どれだけ飛ばすか
		XMFLOAT3 InjectionMove = { pos.x, 20.0f, pos.z };
		Player::AddInjectionMove(InjectionMove);
		barrelInFlag = false;
		barrelIndividualInFlag = false;
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
		barrelIndividualInFlag = true;
		Player::GravityForcedEnd();
		Player::BarrelIn();
	}
}

Barrel* Barrel::Initialize(const XMFLOAT3& position, const XMFLOAT3& posA, const XMFLOAT3& posB)
{
<<<<<<< HEAD
	Barrel* barrel = new Barrel();
	barrel->posA = posA;
	barrel->posB = posB;
	barrel->pos = position;
	barrel->targetPos = posA;
	return barrel;
=======
	//オブジェクト生成
	model = Model::LoadFromOBJ("block");

	objectX = Object3d::Create();

	//オブジェクトにモデルをひも付ける
	objectX->SetModel(model);
	objectX->SetScale(scale);
>>>>>>> kuri
}

void Barrel::Update(Input* input)
{	
	Injection(input);

	Move(input);

	if (barrelInFlag == true && barrelIndividualInFlag == true)
	{
		Player::SetPosition(pos);
	}
}
