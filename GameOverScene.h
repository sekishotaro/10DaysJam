#pragma once
#include "BaseScene.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include "Camera.h"
#include "Sprite.h"
class GameOverScene :public BaseScene
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public: // �����o�֐�
	// �f�X�g���N�^
	~GameOverScene();
	// ������
	void Initialize() override;
	//�I��
	void Finalize() override;
	// ���t���[������
	void Update() override;

	// �`��
	void Draw() override;

	void ease();
public:

private: // �����o�ϐ�
	//�X�v���C�g
	std::unique_ptr<Sprite> sprite;
	Sprite* Gameoverimg = nullptr;
	Sprite* black = nullptr;

	XMFLOAT2 blackpos = { 0,800 };
	XMFLOAT2 GameoverImgPos = { 0,0 };

	float nowTime = 0;
	float endTime = 1;
	float timeRate = 0;
};

