#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include <DirectXMath.h>
#include "Camera.h"
#include "Barrel.h"
#include "Mapchip.h"

class GameStage_2 : public BaseScene
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

	// �}�b�v�`�b�v����
	void MapCreate(int mapNumber);
	// �}�b�v�`�b�v�����蔻��
	bool MapCollide(XMFLOAT3& pos, float radiusX, float radiusY, int mapNumber, const XMFLOAT3 oldPos);

	//�}�b�v�`�b�v1�̑傫��
	const float LAND_SCALE = 5.0f;
	//�}�b�v�`�b�v�̔ԍ�
	enum MapNumber
	{
		None, Item
	};
	//mapchip�I�u�W�F�N�g
	std::vector<std::vector<int>> map; //�}�b�v�`�b�v
	std::unique_ptr<Object3d> objItem[map_max_y][map_max_x]; // �X�e�[�W�u���b�N
	// ���f��
	Model* item = nullptr;
	// �Ǘ��t���O
	bool hitFlag = false;
	// �}�b�v�ԍ�
	int height;
	int width;
	// �A�C�e�����Ǘ�
	int itemCount;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	Sprite* spriteBG = nullptr;
	Camera* camera = nullptr;

	// �o����
	std::unique_ptr<Object3d> barrelObject1;
	std::unique_ptr<Object3d> barrelObject2;
	Model* BarrelModel;

	// �v���C���[�ϐ�
	XMFLOAT3 p_pos;
	XMFLOAT3 old_p_pos;
	float p_radius_x;
	float p_radius_y;

	Barrel* barrel1;
	Barrel* barrel2;
};

