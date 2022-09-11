#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include <DirectXMath.h>

#include <memory>

#include "Mapchip.h"
#include "Camera.h"



class GamePlayScene : public BaseScene
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

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// ���
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �A�b�v�f�[�g
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	// �}�b�v�`�b�v�p
	void MapCreate(int mapNumber);
	int GetLeftMapChip(XMFLOAT3 position);
	int GetRightMapChip(XMFLOAT3 position);
	int GetUpMapChip(XMFLOAT3 position);

	//�}�b�v�`�b�v1�̑傫��
	const float LAND_SCALE = 5.0f;
	//�}�b�v�`�b�v�̔ԍ�
	enum MapNumber
	{
		None, Coin
	};
	//mapchip�I�u�W�F�N�g
	std::vector<std::vector<int>> map; //�}�b�v�`�b�v
	std::unique_ptr<Object3d> objBlock[map_max_y][map_max_x]; //�X�e�[�W�u���b�N

	// ���f��
	Model* block = nullptr;


	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	Sprite *spriteBG = nullptr;
	//std::unique_ptr<Object3d> objectX;
	//Model *model = nullptr;
	Camera *camera = nullptr;

	// �v���C���[�ϐ�
	XMFLOAT3 p_pos;

	// �J�����ϐ�
	XMFLOAT3 c_pos;
};

