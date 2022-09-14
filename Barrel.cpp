#include "Barrel.h"
#include "Player.h"
#include "Collision.h"
#include "Math.h"
#include <DebugText.h>

bool Barrel::barrelInFlag = false;
bool Barrel::moveFlag = true;

void Barrel::Move(Input* input)
{
	StraightMove(posA, posB);
}

void Barrel::StraightMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos)
{
	//’M‚Ì’†‚É‚¢‚È‚¯‚ê‚Î“®‚©‚È‚¢
	if (barrelInFlag == false || leftPos.x == rightPos.x)
	{
		return;
	}

	if (pos.x >= rightPos.x && pos.y >= rightPos.y && pos.z >= rightPos.z)
	{
		targetPos = leftPos;
	}
	else if (pos.x <= leftPos.x && pos.y <= leftPos.y && pos.z <= leftPos.z)
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

	if (input->TriggerKey(DIK_SPACE) && barrelIndividualInFlag == true && collisionTimer <= 0)
	{
		collisionTimer = 20;
		//‚Ç‚ê‚¾‚¯”ò‚Î‚·‚©
		XMFLOAT3 vec1 = { 0.0f, injectionDis, 0.0f};


		float a =  cos(rot.z * (3.14f / 180.0f));
		float b = -sin(rot.z * (3.14f / 180.0f));
		float c =  sin(rot.z * (3.14f / 180.0f));
		float d =  cos(rot.z * (3.14f / 180.0f));

		float x = (a * vec1.x + b * vec1.y) * -1;
		float y = (c * vec1.x + d * vec1.y);


		XMFLOAT3 InjectionMove = { pos.x + x, pos.y + y, pos.z };
   		Player::AddInjectionMove(InjectionMove);
		barrelInFlag = false;
		barrelIndividualInFlag = false;
		time = 0.0f;
		Player::BarrelOut();
	}
}

void Barrel::CollisionPlayer()
{
	if (barrelInFlag == true || collisionTimer >= 0)
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

void Barrel::rotationMove(vector<int> rota)
{
	if (barrelInFlag == false) return;

	time += 0.1f;

	if (time <= 6.0f) return;

	for (int i = 0; i < rota.size(); i++)
	{
		if (Num == i)
		{
			rot.z = rota[i];
		}
	}

	if (Num == 0)
	{
		addNum = 1;
	}

	if (Num == rota.size() - 1)
	{
		addNum = -1;
	}

	Num += addNum;

	time = 0.0f;

}

Barrel* Barrel::Initialize(const XMFLOAT3& position, const XMFLOAT3& posA, const XMFLOAT3& posB, const XMFLOAT3& rot, const float& injectionDis)
{
	Barrel* barrel = new Barrel();
	barrel->posA = posA;
	barrel->posB = posB;
	barrel->pos = position;
	barrel->targetPos = posA;
	barrel->rot = rot;
	barrel->injectionDis = injectionDis;
	return barrel;
}

void Barrel::Update(Input* input)
{	
	Injection(input);

	Move(input);

	DebugText::GetInstance()->Print(50, 30 * 2, 2, "%d", collisionTimer);
	collisionTimer--;

	if (barrelInFlag == true && barrelIndividualInFlag == true)
	{
		Player::SetPosition(pos);
	}
}
