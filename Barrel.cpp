#include "Barrel.h"
#include "Player.h"
#include "Collision.h"

bool Barrel::barrelInFlag = false;
bool Barrel::moveFlag = true;

void Barrel::Move(Input* input)
{
	HorizontalMove(posA, posB);
}

void Barrel::HorizontalMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos)
{
	//’M‚Ì’†‚É‚¢‚È‚¯‚ê‚Î“®‚©‚È‚¢
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
	//’M‚Ì’†‚É“ü‚Á‚Ä‚¢‚È‚¢‚Æ‚«‚Í•Ô‚·
	if (barrelInFlag == false)
	{
 		return;
	}

	if (input->PushKey(DIK_SPACE))
	{
		//‚Ç‚ê‚¾‚¯”ò‚Î‚·‚©
		XMFLOAT3 InjectionMove = { pos.x, 30.0f, pos.z };
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

Barrel* Barrel::Initialize(const XMFLOAT3& position, const XMFLOAT3& posA, const XMFLOAT3& posB)
{
	Barrel* barrel = new Barrel();
	barrel->posA = posA;
	barrel->posB = posB;
	barrel->pos = position;
	barrel->targetPos = posA;
	return barrel;
}

void Barrel::Update(Input* input)
{
	Move(input);
	
	if (barrelInFlag == true)
	{
		Player::SetPosition(pos);
	}

	Injection(input);
}
