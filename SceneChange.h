#pragma once
#include "Sprite.h"
#include "SceneManager.h"
#include <wrl.h>
#include <DirectXMath.h>
using namespace DirectX;
class SceneChange :public XMFLOAT2
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


public:
	enum TYPE {
		FADE_OUT = -1,
		NO = 0,
		FADE_IN = 1,
	};

	SceneChange();
	void Update();
	void Draw();

	bool SceneChangeStart(const std::string& sceneName);

	void ease(TYPE type);
	
	bool inendflag;
	bool outendflag;
	TYPE type;
private:
	bool isChange = false;
	std::string sceneName;
	float nowTime = 0;
	float endTime = 1;
	float timeRate = 0;
	int count=0;
	Sprite* sprite = nullptr;
};
