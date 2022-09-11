#include "MyMath.h"

MyMath::XMFLOAT3 MyMath::easeOut(const XMFLOAT3& start, const XMFLOAT3& end, const float& time)
{
	XMFLOAT3 pos;

	pos.x = start.x * (1.0f - time * (2 - time)) + end.x * time * (2 - time);
	pos.y = start.y * (1.0f - time * (2 - time)) + end.y * time * (2 - time);
	pos.z = start.z * (1.0f - time * (2 - time)) + end.z * time * (2 - time);

	return pos;
}
