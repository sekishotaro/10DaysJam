#pragma once
#include "BaseScene.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include "Camera.h"
#include "SceneChange.h"
#include "Sprite.h"
#include "Object3d.h"

class SelectScene :public BaseScene
{
private: // エイリアス
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
	~SelectScene();
	// 初期化
	void Initialize() override;
	//終了
	void Finalize() override;
	// 毎フレーム処理
	void Update() override;

	// 描画
	void Draw() override;
private:
	Sprite* spriteBG = nullptr;
	SceneChange sceneChange;

	std::unique_ptr<Object3d> stage1obj;
	Model* stage1Model;

	std::unique_ptr<Object3d> stage2obj;
	Model* stage2Model;

	std::unique_ptr<Object3d> stage3obj;
	Model* stage3Model;

	std::unique_ptr<Object3d> stage4obj;
	Model* stage4Model;

	std::unique_ptr<Object3d> stage5obj;
	Model* stage5Model;

	std::unique_ptr<Object3d> stage6obj;
	Model* stage6Model;

	std::unique_ptr<Object3d> stage7obj;
	Model* stage7Model;

	std::unique_ptr<Object3d> stage8obj;
	Model* stage8Model;
	XMFLOAT3 scale;

	XMFLOAT3 stage1_pos;
	XMFLOAT3 stage2_pos;
	XMFLOAT3 stage3_pos;
	XMFLOAT3 stage4_pos;
	XMFLOAT3 stage5_pos;
	XMFLOAT3 stage6_pos;
	XMFLOAT3 stage7_pos;
	XMFLOAT3 stage8_pos;
	int count = 0;
	XMFLOAT3 savepos;
	float nowTime = 0;
	float endTime = 1;
	float timeRate = 0;
	bool Rmove = false;
	bool Lmove = false;
};

