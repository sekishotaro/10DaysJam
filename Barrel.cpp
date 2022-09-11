#include "Barrel.h"
#include "Player.h"
#include "Collision.h"

Barrel::XMFLOAT3 Barrel::move = { 1.0f ,0.0f, 0.0f };

bool Barrel::barrelInFlag = false;
bool Barrel::moveFlag = true;

//void Barrel::Move(Input* input)
//{
//	XMFLOAT3 leftPos = { -50.0f, 0.0f, 0.0f };
//	XMFLOAT3 RightPos = { 50.0f, 0.0f, 0.0f };
//	HorizontalMove(leftPos, RightPos);
//}

//void Barrel::HorizontalMove(const XMFLOAT3& leftPos, const XMFLOAT3& rightPos, const XMFLOAT3& pos)
//{
//	//’M‚Ì’†‚É‚¢‚È‚¯‚ê‚Î“®‚©‚È‚¢
//	if (barrelInFlag == false)
//	{
//		return;
//	}
//
//	if (rightPos.x < pos.x && moveFlag == true)
//	{
//		move.x = -1.0f;
//		moveFlag = false;
//	}
//	if (pos.x < leftPos.x && moveFlag == false)
//	{
//		move.x = 1.0f;
//		moveFlag = true;
//	}
//	
//
//	AddPosMove(move);
//}
//
//void Barrel::AddPosMove(const XMFLOAT3& pos, const XMFLOAT3& move)
//{
//	pos.x += move.x;
//	pos.y += move.y;
//	pos.z += move.z;
//}
//
//void Barrel::Injection(const XMFLOAT3& pos, Input* input)
//{
//	//’M‚Ì’†‚É“ü‚Á‚Ä‚¢‚È‚¢‚Æ‚«‚Í•Ô‚·
//	if (barrelInFlag == false)
//	{
//		return;
//	}
//
//	if (input->PushKey(DIK_SPACE))
//	{
//		//‚Ç‚ê‚¾‚¯”ò‚Î‚·‚©
//		XMFLOAT3 InjectionMove = { pos.x, 30.0f, pos.z };
//		Player::AddInjectionMove(InjectionMove);
//		barrelInFlag = false;
//		Player::BarrelOut();
//	}
//}
//
//Barrel::Barrel()
//{
//}
//
//Barrel::~Barrel()
//{
//}
//
//void Barrel::CollisionPlayer()
//{
//	if (barrelInFlag == true)
//	{
//		return;
//	}
//	
//	SphereF sphere1, sphere2;
//	sphere1.center = pos;
//	sphere1.radius = 3;
//
//	sphere2.center = Player::GetPos();
//	sphere2.radius = 2;
//
//	if (Collision::CheckSphereSphere(sphere1, sphere2) == true)
//	{
//		barrelInFlag = true;
//		Player::GravityForcedEnd();
//		Player::BarrelIn();
//	}
//}

Barrel* Barrel::Initialize(const XMFLOAT3& position)
{
	Barrel* barrel = new Barrel();

	barrel->SetPosition(position);

	return barrel;
}

//void Barrel::Update(Input* input, const XMFLOAT3& pos)
//{
//	Move(input);
//	if (barrelInFlag == true)
//	{
//		Player::SetPosition(pos);
//	}
//
//	Injection(input);
//}
//
//void Barrel::Finalize()
//{
//}
//
//void Barrel::Draw()
//{
//}
