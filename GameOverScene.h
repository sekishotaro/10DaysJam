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
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public: // メンバ関数
	// デストラクタ
	~GameOverScene();
	// 初期化
	void Initialize() override;
	//終了
	void Finalize() override;
	// 毎フレーム処理
	void Update() override;

	// 描画
	void Draw() override;

	void ease();
public:

private: // メンバ変数
	//スプライト
	std::unique_ptr<Sprite> sprite;
	Sprite* Gameoverimg = nullptr;
	Sprite* black = nullptr;

	XMFLOAT2 blackpos = { 0,800 };
	XMFLOAT2 GameoverImgPos = { 0,0 };

	float nowTime = 0;
	float endTime = 1;
	float timeRate = 0;
};

