#include "SceneChange.h"

#include<math.h>


SceneChange::SceneChange() :inendflag(false), outendflag(false)
{
	type = FADE_IN;
	Sprite::LoadTexture(100, L"Resources/black.png");
	sprite = Sprite::Create(100, { 1280,0 }, { 1,1,1,1 }, { 0,0 });

}

void SceneChange::Update()
{
	if (type == NO) { return; }
	nowTime += 0.03;
	timeRate = min(nowTime / endTime, 1);
	ease(type);

	if (outendflag)
	{
		SceneManager::GetInstance()->ChangeScene(sceneName);
	}

}

void SceneChange::Draw()
{
	if (type == NO) { return; }
	sprite->Draw();

}

bool SceneChange::SceneChangeStart(const std::string& sceneName)
{

	if (type != FADE_OUT)
	{
		outendflag = false;
		sprite->SetPosition({ -1280,0 });
		nowTime = 0;
	}

	type = FADE_OUT;
	isChange = true;
	this->sceneName = sceneName;

	return false;
}

void SceneChange::ease(TYPE type)
{
	if (type == FADE_OUT && outendflag)
	{
		return;
	}
	if (type == FADE_IN && inendflag)
	{
		return;
	}

	float start;
	float end = 0;
	if (type == FADE_IN)
	{
		start = -1280;
	}
	if (type == FADE_OUT)
	{
		start = 1280;
	}
	float pos;

	pos = (end - start) * ((timeRate * timeRate * timeRate) + 1) + start;
	XMFLOAT2 result;
	result.x = pos;
	result.y = 0;
	if (type == FADE_IN && timeRate >= endTime)
	{
		timeRate = 0;
		inendflag = true;
	}
	else if (type == FADE_OUT && timeRate >= endTime)
	{


		timeRate = 0;
		outendflag = true;
		count++;
		if (count >= 80)
		{
			count = 0;
		}
	}

	sprite->SetPosition(result);

}
